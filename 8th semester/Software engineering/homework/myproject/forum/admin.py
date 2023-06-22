from django.contrib import admin
from .models import Topic, Forum, Post, UserProfile

admin.site.register(Topic)
admin.site.register(Post)
admin.site.register(UserProfile)
admin.site.register(Forum)

