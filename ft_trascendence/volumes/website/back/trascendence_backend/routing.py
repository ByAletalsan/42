# routing.py

from django.urls import path
from channels.routing import ProtocolTypeRouter, URLRouter
from data_app.consumers import MyConsumer

websocket_urlpatterns = [
    path('ws/myapp/', MyConsumer.as_asgi()),
]

application = ProtocolTypeRouter({
    'websocket': URLRouter(websocket_urlpatterns),
})
