from django.contrib.auth.models import User
from django import forms
from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.http import require_http_methods
from forum.models import Topic, Post, Forum, UserProfile
from django.core import serializers
from django.db.models import Q
from rest_framework.generics import ListAPIView, RetrieveAPIView, UpdateAPIView, DestroyAPIView, \
    RetrieveUpdateDestroyAPIView
from .serializers import ForumSerializer, TopicSerializer, PostSerializer, UserProfileSerializer


# Получение списка всех форумов:
@require_http_methods(["GET", "POST"])
def forum_list(request):
    forums = Forum.objects.all()
    data = {"forums": list(forums.values())}
    return JsonResponse(data, safe=False)


# Получение списка всех тем для конкретного форума:
@require_http_methods(["GET", "POST"])
def topic_list(request, forum_id):
    topics = Topic.objects.filter(forum_id=forum_id)
    data = {"topics": list(topics.values())}
    return JsonResponse(data)


# Получение списка всех сообщений для конкретной темы
@require_http_methods(["GET", "POST"])
def post_list(request, topic_id):
    # return JsonResponse({'status': 'success', 'API': 'Hello'})
    posts = Post.objects.filter(topic_id=topic_id)
    data = {"posts": list(posts.values())}
    return JsonResponse(data)


# Получение детальной информации о конкретном топике:
def topic_detail(request, topic_id):
    # return JsonResponse({'status': 'success', 'API': 'Hello'})
    try:
        topic = Topic.objects.get(id=topic_id)
    except Topic.DoesNotExist:
        return JsonResponse({'error': 'Topic not found'}, status=404)

    data = {
        'title': topic.title,
        'forum': topic.forum.title,
        'author': topic.author.username,
        'created_at': topic.created_at,
        'posts': list(topic.post_set.values())
    }
    return JsonResponse(data)


# получение информации о пользователе
@require_http_methods(["GET"])
def get_user_info(request, user_id):
    try:
        user = UserProfile.objects.get(id=user_id)
        user_data = serializers.serialize('json', [user, ])
        return JsonResponse({'status': 'success', 'user_data': user_data})
    except User.DoesNotExist:
        return JsonResponse({'status': 'error', 'message': 'User not found'})


# поиск

def search_form(request):
    return render(request, 'search_form.html')


@require_http_methods(["GET"])
def search(request):
    query = request.GET.get('q')
    if not query:
        return JsonResponse({'error': 'Query parameter "q" is missing'})

    posts = Post.objects.filter(Q(content__icontains=query) | Q(author__username__icontains=query))
    profiles = UserProfile.objects.filter(Q(user__username__icontains=query) | Q(bio__icontains=query))
    forums = Forum.objects.filter(Q(title__icontains=query) | Q(description__icontains=query))
    topics = Topic.objects.filter(Q(title__icontains=query))

    data = {
        'posts': list(posts.values()),
        'profiles': list(profiles.values()),
        'forums': list(forums.values()),
        'topics': list(topics.values()),
    }
    print(data)
    return JsonResponse(data, safe=False)


@require_http_methods(["GET"])
def all_objects(request):
    forums = list(Forum.objects.values())
    topics = list(Topic.objects.values())
    posts = list(Post.objects.values())
    profiles = list(UserProfile.objects.values())

    data = {
        'forums': forums,
        'topics': topics,
        'posts': posts,
        'profiles': profiles,
    }
    print(data)
    return JsonResponse(data)


class PostForm(forms.ModelForm):
    class Meta:
        model = Post
        fields = ['content', 'topic']
        widgets = {
            'content': forms.Textarea(attrs={'rows': 4, 'cols': 50}),
            'topic': forms.Select(attrs={'id': 'topic'}),
        }


@require_http_methods(["GET", "POST"])
def create_post(request):
    if request.method == "GET":
        form = PostForm()
        topics = Topic.objects.all()
        return render(request, 'create_form.html', {'form': form, 'topics': topics})
    elif request.method == 'POST':
        form = PostForm(request.POST)
        if form.is_valid():
            post = form.save(commit=False)
            post.author = request.user
            post.save()
            data = {
                'status': 'success',
                'message': 'Post created successfully.',
                'post': {
                    'id': post.id,
                    'content': post.content,
                    'author_id': post.author_id,
                    'topic_id': post.topic_id,
                    'created_at': post.created_at,
                }
            }
            print(data)
            return JsonResponse(data)
        else:
            return JsonResponse({'status': 'error', 'message': 'Invalid form data.'})
    else:
        return JsonResponse({'status': 'error', 'message': 'Invalid request method.'})


class ForumListView(ListAPIView):
    queryset = Forum.objects.all()
    serializer_class = ForumSerializer


class ForumView(RetrieveUpdateDestroyAPIView):
    queryset = Forum.objects.all()
    serializer_class = ForumSerializer
    lookup_field = "id"


class TopicListView(ListAPIView):
    queryset = Topic.objects.all()
    serializer_class = TopicSerializer


class TopicView(RetrieveUpdateDestroyAPIView):
    queryset = Topic.objects.all()
    serializer_class = TopicSerializer
    lookup_field = "id"


class PostListView(ListAPIView):
    queryset = Post.objects.all()
    serializer_class = PostSerializer


class PostView(RetrieveUpdateDestroyAPIView):
    queryset = Post.objects.all()
    serializer_class = PostSerializer
    lookup_field = "id"


class UserProfileListView(ListAPIView):
    queryset = UserProfile.objects.all()
    serializer_class = UserProfileSerializer


class UserProfileView(DestroyAPIView):
    queryset = UserProfile.objects.all()
    serializer_class = UserProfileSerializer
    lookup_field = "id"
