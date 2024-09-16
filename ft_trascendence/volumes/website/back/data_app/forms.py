from django import forms
from django.contrib.auth.forms import UserCreationForm, UserChangeForm
from django.contrib.auth.models import User
from .models import Usuario

    
class CustomUserCreationForm(UserCreationForm):
    class Meta:
        model = Usuario
        fields = ('username', 'password1', 'password2' ,'email')

class AvatarUpdateForm(forms.ModelForm):
    avatar = forms.ImageField(label="avatar")
    class Meta:
        model = Usuario
        fields = ('avatar',)