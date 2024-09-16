from django.urls import path
from django.conf import settings
from django.conf.urls.static import static


urlpatterns = [
    #path('test_endpoint/', test_endpoint, name='test_endpoint'),
    #path('submit_register_data/', submit_register_data, name='register_data'),
]
urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)

