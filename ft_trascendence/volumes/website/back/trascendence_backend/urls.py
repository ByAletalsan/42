"""
URL configuration for trascendence_backend project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based viewsº
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include
from data_app import views

from data_app.endpoints import matchmaking, session_and_data, user_management


urlpatterns = [
    path('data_app/', include('data_app.urls')),
    path('register_user/', user_management.register_user), # User manag
    path('manage_login/', user_management.manage_login), # User manag
    path('manage_logout/', user_management.manage_logout),# User manag
    path('test_auth/', session_and_data.test_auth), # session
    path('add_friend/', user_management.add_friend), # user manag
    path('register_42/', user_management.register_42), # user manag
    path('upload_image/', user_management.upload_image), # user manag
    path('to_queue/', matchmaking.to_queue), # MM
    path('is_match/', matchmaking.is_match), # MM
    path('change_scientist/', user_management.change_scientist), # user manag
    path('all_data/', session_and_data.all_data), # session
    path('change_username/', user_management.change_username), # user manag
    path('change_email/', user_management.change_email), # user manag
    path('change_password/', user_management.change_password), # user manag
    path('match_result/', matchmaking.match_result), # MM
    path('refresh/', session_and_data.refresh), # session
    path('check/', session_and_data.check), # session
    path('stats_friend/', session_and_data.stats_friend), # session
    path('delete_friend/', user_management.delete_friend), # user manag
    path('set_offline/', session_and_data.set_offline), # session
    path('info_tour/', matchmaking.info_tour),  # MM
    path('remove_from_queue/', matchmaking.remove_from_queue), 
    path('delete_account/', user_management.delete_account), # user manag
    path('data_pdf/', session_and_data.data_pdf), # session
    path('register_guest/', user_management.register_guest), # user manag
    path('is_in_queue/', matchmaking.is_in_queue), # MM
    path('tour_flag/', matchmaking.tour_flag), # MM
    path('change_language/', user_management.change_language),
    path('get_language/', user_management.get_language),
    path('get_api_id/', user_management.get_api_id),
]
