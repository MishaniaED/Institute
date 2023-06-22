from django.urls import path
from rest_framework.urlpatterns import format_suffix_patterns
from . import views
from .views import (
    PostView, ForumListView, ForumView, TopicListView, TopicView, PostListView, UserProfileListView, UserProfileView,
)

urlpatterns = [
    path('forums', views.forum_list, name='home'),
    path('forum_topics/<int:forum_id>', views.topic_list),
    path('topic_posts/<int:topic_id>', views.post_list),
    path('topic/<int:topic_id>', views.topic_detail),
    path('user/<int:user_id>/', views.get_user_info),
    path('search_form/', views.search_form, name='search_form'),
    path('search/', views.search, name='search'),
    path('', views.all_objects),
    path('create/', views.create_post, name='create_post'),
    path('forums/', ForumListView.as_view()),
    path('forums/<int:id>/', ForumView.as_view()),
    path('topics/', TopicListView.as_view()),
    path('topics/<int:id>/', TopicView.as_view()),
    path('posts/', PostListView.as_view()),
    path('posts/<int:id>/', PostView.as_view()),
    path('userprofiles/', UserProfileListView.as_view()),
    path('userprofiles/<int:id>/', UserProfileView.as_view()),
]

urlpatterns = format_suffix_patterns(urlpatterns)
