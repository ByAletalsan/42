# consumers.py

import json
from channels.generic.websocket import WebsocketConsumer
from asgiref.sync import async_to_sync
from channels.generic.websocket import AsyncWebsocketConsumer

class MyConsumer(WebsocketConsumer):

	def connect(self):
		self.accept()
		self.group_name = None
		self.player_name = None
		
	def receive(self, text_data):
		data = json.loads(text_data)
		comando = data['comando']

		if comando == 'unirse_grupo':
			grupo = data['grupo']
			self.group_name = grupo
			self.player_name = data['player']
			async_to_sync(self.channel_layer.group_add)(
				grupo,
				self.channel_name
			)
		if comando == 'send_data':
			message = data['message']
			grupo = data['grupo']
			async_to_sync(self.channel_layer.group_send)(
				grupo,
				{
					'type': 'chat_message',
					'message': message
				}
			)

	def chat_message(self, event):
		message = event['message']
		self.send(text_data=json.dumps({
			'message': message
		}))
	
	def disconnect(self, close_code):
		if self.group_name is not None:
			data = {
				'comando': 'disconnect',
				'player': self.player_name
			}
			message = {
				'comando': 'send_data',
				'grupo': self.group_name,
				'message': data
			}
			self.receive(json.dumps(message))
			async_to_sync(self.channel_layer.group_discard)(self.group_name, self.channel_name)
