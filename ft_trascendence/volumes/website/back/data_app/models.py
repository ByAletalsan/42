from collections.abc import Collection
from django.db import models
from django import forms
from django.core.validators import EmailValidator, RegexValidator, MinValueValidator, MaxValueValidator
from django.contrib.auth.hashers import make_password
from django.contrib.auth.models import AbstractUser




# Create your models here.


class Usuario(AbstractUser):
    
    username = models.CharField(max_length=17, unique=True)
    email = models.EmailField(unique=True, max_length=50, validators=[EmailValidator("Email invalid. Enter a valid email address")],  null=True, blank=True)
    
    password = models.CharField(validators=[RegexValidator(
            regex=r'^(?=.*[A-Z])(?=.*\d)(?=.*[._!"`\'#$%&,:;<>=@{}~\$\(\)\*\+\/\\\?\[\]\^\|])[A-Za-z\d._!"`\'#$%&,:;<>=@{}~\$\(\)\*\+\/\\\?\[\]\^\|]{8,}$',
            message='Enter a valid password. It must be at least 8 characters long, include at least one uppercase letter, one number and one special character.',
        )])
        
    avatar = models.ImageField(null=True, blank=True, upload_to="images/")
    scientist = models.IntegerField(default=0 , validators=[
            MinValueValidator(limit_value=0),
            MaxValueValidator(limit_value=5),
        ])
    language = models.CharField(max_length=3, default='en')

class Amigo(models.Model):
    id1 = models.ForeignKey('Usuario', on_delete=models.CASCADE, related_name='id1')
    id2 = models.ForeignKey('Usuario', on_delete=models.CASCADE, related_name='id2')
    date = models.DateField()
    matched = models.BooleanField()
    
class MatchHistory(models.Model):
    
    score = models.CharField(max_length = 10)
    mode = models.CharField(max_length=25)
    date = models.DateField()
    winner_id1 = models.ForeignKey('Usuario', on_delete=models.SET_NULL, related_name='winner_id1', null=True)
    loser_id1 = models.ForeignKey('Usuario', on_delete=models.SET_NULL, related_name='loser_id1', null=True)
