from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.core.validators import ValidationError
from ..models import Usuario, Amigo, MatchHistory
from django.contrib.auth import authenticate, login, logout
from ..forms import CustomUserCreationForm, AvatarUpdateForm
from datetime import date, datetime, timedelta
from pyoauth2 import Client
import requests
from django.shortcuts import redirect
import os
from django.contrib.sessions.models import Session
from django.core.cache import cache
import re
import random
import urllib.request
from django.core.files.base import ContentFile

from data_app.endpoints.session_and_data import all_data




def register_error_control(username, password, password2, email):
    """
        Function for error checks when registering
    """
    if username == "" or email == "" or password == "":
        raise ValidationError("KEY VALUES EMPTY")
    if username.find("42_") != -1:
        raise ValidationError("USERNAME CAN'T CONTAIN \"42_\"")
    if email.count("@") == 1:
        split_email = email.split('@')
    else:
        raise ValidationError("EMAIL NOT VALID, EMAIL MUST CONTAIN ONLY 1 @")
    if split_email[1].find("42") != -1:
        raise ValidationError("EMAIL CAN'T CONTAIN \"42\" AFTER @")
    if split_email[1].find("ponger.ja") != -1:
        raise ValidationError("EMAIL CAN'T CONTAIN \"ponger.ja\" AFTER @")
    if password != password2:
        raise ValidationError("PASSWORDS DON'T MATCH")
    check_if_exists_user = Usuario.objects.filter(username=username).first()
    if check_if_exists_user != None:
        raise ValidationError("THIS USER ALREADY EXISTS. PLEASE TRY ANOTHER ONE")
    check_if_exists_email = Usuario.objects.filter(email=email).first()
    if check_if_exists_email != None:
        raise ValidationError("THIS EMAIL ALREADY EXISTS. PLEASE TRY ANOTHER ONE")
    if len(username) > 17:
        raise ValidationError("USERNAME LENGTH TOO LARGE. IT MUST CONTAIN MAX 17 CHARACTERS")
    if len(email) > 20:
        raise ValidationError("EMAIL LENGTH TOO LARGE. IT MUST CONTAIN MAX 20 CHARACTERS")


def register_user(request):
    """
        Endpoint for registering a user
    """
    try:
        if request.method == "POST":
            username = request.POST.get("username", "")
            password = request.POST.get("password", "")
            password2 = request.POST.get("password2", "")
            email = request.POST.get("email", "")
            try:
                register_error_control(username, password, password2, email)
                new_user = Usuario(username=username, email=email, password=password, avatar="/images/default.jpg", scientist=0)
                try:
                    new_user.full_clean()
                    user = Usuario.objects.create_user(username=username, email=email, password=password, avatar="/images/default.jpg", scientist=0)
                    user.save()
                    return manage_login(request)
                    #return(all_data(request))
                except ValidationError as e:
                    raise ValidationError("VALIDATION ERROR. USER DOESN'T MEET THE REQUIREMENTS. REMIND EMAIL MUST BE VALID AND PASSWORD MUST CONTAIN AT LEAST A SPECIAL CHARACTER, A NUMBER, AN UPPERCASE AND BE AT LEAST 8 CHARACTERS")
            except ValidationError as e:
                return(JsonResponse({"status" : str(e)}, status=401))
        else:
            return(JsonResponse({"status" : "method not valid"}, status=405))
    except Exception as e:
        return JsonResponse({"status" : "something went wrong"}, status=400)
    
 
def manage_login(request, user42=None):
    """
        Endpoint for login a user.
    """
    try:
        # JOSESANC EXIST
        if Usuario.objects.filter(username="JoseSanc").first() == None:
            user_sanc = Usuario.objects.create_user(username="JoseSanc", email="josesanc@gmail.com", password=str(os.environ.get('ADMIN_PASSWORD', '')), avatar="/images/default.jpg", scientist=0)
            user_sanc.save()
            user_anon = Usuario.objects.create_user(username="Anonimous", email="anonimous@gmail.com", password=str(os.environ.get('ADMIN_PASSWORD', '')), avatar="/images/default.jpg", scientist=0)
            user_anon.save()
        username = request.POST.get("username", "")
        password = request.POST.get("password", "")
        if user42 != None:
            username = user42
            password = str(os.environ.get('ADMIN_PASSWORD', ''))
        user = authenticate(request, username=username, password=password)
        if user is not None:
            userquery = Usuario.objects.filter(username=username).first()            
            # REMOVE ALL ACTIVE SESSIONS
            all_sessions = Session.objects.all()
            for session in all_sessions:
                    data = session.get_decoded()
                    if int(data.get('_auth_user_id')) == userquery.id:
                        session.delete()
            login(request, user)
            cache.set(str(userquery.id), (datetime.now() + timedelta(minutes=3)).strftime("%Y-%m-%d %H:%M:%S"))    
            return(all_data(request)) # DEVOLVER INFORMACION DEL USUARIO EN UN JSON
        else:
            return(JsonResponse({"status" : "Wrong user credentials"}, status=401)) # DEVOLVER CODIGO DE ERROR
    except:
        return JsonResponse({"status" : "Something went wrong"}, status=400)
    
def manage_logout(request):
    """
        This endpoint logs out a user
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        username = user.username
        is_authenticated = user.is_authenticated
        userquery = Usuario.objects.filter(username=username).first()
        logout(request)
        cache.delete(int(userquery.id))
        return(JsonResponse({"status" : "unlogged"}, status=200))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)

def add_friend(request):
    """
        This endpoint is used adding friends
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        friend_name = ""
        if user.is_authenticated:
            if request.method == "GET":
                if request.GET["username"]:
                    friend_name = request.GET["username"]
                else:
                    return JsonResponse({"status" : "include a username in the request"}, status=400)
            elif request.method == "POST":
                friend_name = request.POST["username"]
            else:
                return JsonResponse({"status" : "method not valid"}, status=405)
            
            user_query = Usuario.objects.filter(username=user).first()
            friend_query =  Usuario.objects.filter(username=friend_name).first()
            if (friend_query == user_query):
                return JsonResponse({"status" : "Eres tu"}, status=200)
            if friend_query:
                if Amigo.objects.filter(id1=user_query, id2=friend_query, matched=True).first() or Amigo.objects.filter(id1=friend_query, id2=user_query, matched=True).first():
                    return JsonResponse({"status" : "Estos usuarios ya son amigos"}, status=200)
                elif Amigo.objects.filter(id1=friend_query, id2=user_query, matched=False).first() or Amigo.objects.filter(id1=user_query, id2=friend_query, matched=False).first():
                    if Amigo.objects.filter(id1=friend_query, id2=user_query, matched=False).first():
                        req_match = Amigo.objects.filter(id1=friend_query, id2=user_query, matched=False).first()
                        if req_match:
                            req_match.matched = True
                            req_match.save()
                        return JsonResponse({"status" : "Petición aceptada, ahora sois amigos"}, status=200)
                    elif Amigo.objects.filter(id1=user_query, id2=friend_query, matched=False).first():
                        return JsonResponse({"status" : "La petición ya ha sido enviada, espera a que el otro usuario la devuelva"}, status=200)
                elif not Amigo.objects.filter(id1=friend_query, id2=user_query, matched=False).first() or not Amigo.objects.filter(id1=user_query, id2=friend_query, matched=False).first():
                    new_request = Amigo(date=date.today(), matched=False, id1 = user_query, id2=friend_query)
                    new_request.save()
                    return JsonResponse({"status" : "Petición realizada, el otro usuario tiene que hacerla también"}, status=200)
                    
                return JsonResponse({"status" : "SMTH WENT WRONG"}, status=400)

            else:
                return JsonResponse({"status" : "USER NOT FOUND"}, status=200)

        else:
            return JsonResponse({"status" : "LOG IN TO ADD FRIENDS"}, status=401)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
    
def register_42(request):
    """
        This endpoint is user to register and log in users via 42 API
    """
    try:
        code = request.GET.get('code')
        url = 'https://api.intra.42.fr/oauth/token'
        uid = str(os.environ.get('UID', ''))
        secret = str(os.environ.get('SECRET', ''))
        
        payload = {
            "grant_type": "authorization_code",
            "client_id": uid,
            "client_secret": secret,
            "code" : code,
            "redirect_uri" : "https://" + str(os.environ.get('MI_IP', 'localhost') + ':' + str(os.environ.get('PORT', '443'))) + "/api/register_42/"
            }
        headers = {
            'Content-Type': 'application/x-www-form-urlencoded'
        }
        response = requests.request("POST", url, headers=headers, data=payload)

        responsejson = response.json()
        if "access_token" not in responsejson:
            return redirect("https://" + str(os.environ.get('MI_IP', 'localhost') + ':' + str(os.environ.get('PORT', '443'))))
        token = responsejson["access_token"]
        
        
        test_url = "https://api.intra.42.fr/v2/me"
        payload2 = {"access_token": token}
        response2 = requests.request("GET", test_url, headers=headers, data=payload2)
        # A partir de aqui, teniendo la info voy a registrar al usuario y/o logearlo
        
        user_info = response2.json()
        user_login = ''
        user_email = ''
        user_image = ''
        for data in user_info:
            if data == "login":
                user_login = user_info["login"]
            if data == "email":
                user_email = user_info["email"]
            if data == 'image':
                user_image = user_info["image"]["link"]

        
        ## Register user
        password42 =  str(os.environ.get('ADMIN_PASSWORD', ''))
        is_registered = Usuario.objects.filter(username="42_" + user_login).first()
        
        if is_registered:
            user = authenticate(request, username=is_registered.username, password=password42)
            if user is not None:
                manage_login(request, "42_" + user_login)
                return redirect("https://" + str(os.environ.get('MI_IP', 'localhost') + ':' + str(os.environ.get('PORT', '443'))))
            else:
                return JsonResponse({"status" : "user doesn't exist, something went wrong"}, status=400)
        else:
            try:
                # CREATE A USER WITH THE CREDENTIALS PASSED TO CHECK PASSWORD REQUIREMENTS
                # get image
                response_img = urllib.request.urlopen(user_image)
                img_data = response_img.read()
                image_file = ContentFile(img_data, name= user_login + '.jpg')
                # create_user
                user = Usuario.objects.create_user(username= "42_" + user_login, email=user_email, password=password42, avatar=image_file, scientist=0)
                user.is_active=True
                user.save()
                manage_login(request, "42_" + user_login)
                return redirect("https://" + str(os.environ.get('MI_IP', 'localhost') + ':' + str(os.environ.get('PORT', '443'))))
            except ValidationError as e:
                return JsonResponse({"status" : "smth went wrong when registering 42 user"}, status=400)
    except Exception as e:
        return JsonResponse({"status" : e}, status=400)
    
    
def upload_image(request):
    """
        This endpoint is used to upload images selected by users
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        if request.method == 'POST':
            form = AvatarUpdateForm(request.POST, request.FILES)
            if form.is_valid():
                existing_user = Usuario.objects.filter(username=request.user.username).first()
                if existing_user:
                    # Update the existing user with the new image
                    if existing_user.avatar != '/images/default.jpg':
                        os.remove('media/' + str(existing_user.avatar))
                    existing_user.avatar = form.cleaned_data['avatar']
                    existing_user.save()
                    return all_data(request)
            else:
                return JsonResponse({"status" : "form not valid"}, status=400)
        else:
            return JsonResponse({"status" : "method not valid"}, status=405)

        return JsonResponse({"status" : "image could not be uploaded"}, 400)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
    
def change_scientist(request):
    """
        This endpoint is used to change the selected scientist in the page
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        if request.method == "GET":
            userquery = Usuario.objects.filter(username=request.user.username, email=request.user.email).first()
            if userquery is not None:
                new_scientist = int(request.GET.get("scientist", -1))
                if new_scientist >= 0 and new_scientist <= 6:
                    userquery.scientist = new_scientist
                    userquery.save()
                    return JsonResponse({"status" : "Scientist changed succesfully"}, status=200)
                else:
                    return JsonResponse({"status" : "Select a number between 1 and 6"}, status=400)
            else:
                return JsonResponse({"user not found"}, status=400)
        else:
            return JsonResponse({"status" : "QUE ME HAGAS UN GET"}, status=405)
    except:
        return JsonResponse({"status" : "Something went wrong"}, status=400)
    

def change_username(request):
    """
        This endpoint is used to change the username of an account
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        if request.method == "POST":
            try:
                new_username = request.POST.get("new_username")
                if new_username == "" or new_username == None:
                    raise Exception("THE NEW USERNAME CAN'T BE EMPTY")
                if user.username.find("42_") != -1:
                    raise Exception("THE 42 LOGED USERS CAN'T CHANGE USERNAME")
                if new_username.find("42_") != -1:
                    raise Exception("THE USERNAME CAN'T CONTAIN 42_")
                if new_username == user.username:
                    raise Exception("THE NEW USERNAME MUST BE DIFFERENT FROM THE CURRENT USERNAME")
                is_valid = Usuario.objects.filter(username=new_username).first()
                if is_valid != None:
                    raise Exception("THIS USERNAME ALREADY EXISTS")
                try:
                    userquery = Usuario.objects.filter(username=user.username).first()
                    userquery.username = new_username
                    userquery.save()
                except:
                    raise Exception("VALIDATION ERROR. THE USERNAME MUST BE MAX 17 CHARACTERS")
                return JsonResponse({"status" : "username changed correctly"}, status=200)
            except Exception as e:
                return JsonResponse({"status" : str(e)}, status=400)
        else:
            return JsonResponse({"status" : "method not valid"}, status=405)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    

def change_email(request):
    """
        This endpoint is used to change the email of an account
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        if request.method == "POST":
            try:
                if user.email.split('@')[1].find('42') != -1:
                    raise Exception("THE 42 LOGED USERS CAN'T CHANGE EMAIL")
                new_email = request.POST.get("new_email")
                if new_email == None or new_email == "":
                    raise Exception("THE NEW EMAIL CAN'T BE EMPTY")
                if new_email == user.email:
                    raise Exception("THE NEW EMAIL MUST BE DIFFERENT FROM THE CURRENT EMAIL")
                if new_email.count("@") == 1:
                    split_email = new_email.split('@')
                else:
                    raise Exception("THE EMAIL NOT VALID, EMAIL MUST CONTAIN ONLY 1 @")
                if split_email[1].find("42") != -1:
                    raise Exception("THE EMAIL CAN'T CONTAIN \"42\" AFTER @")
                if len(new_email) > 20:
                    raise ValidationError("THE EMAIL LENGTH TOO LARGE. IT MUST CONTAIN MAX 20 CHARACTERS")
                is_valid = Usuario.objects.filter(email=new_email).first()
                if is_valid != None:
                    raise Exception("THIS EMAIL IS ALREADY TAKEN")
                try :
                    userquery = Usuario.objects.filter(username=user.username).first()
                    userquery.email = new_email
                    userquery.save()
                    return JsonResponse({"status" : "email changed succesfully"}, status=200)
                except Exception as e:
                    raise Exception("VALIDATION ERROR. PLEASE INTRODUCE A VALID EMAIL")
            except Exception as e:
                return JsonResponse({"status" : str(e)}, status=400)
        else:
            return JsonResponse({"status" : "method not valid"}, status=405)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    

def change_password(request):
    """
        This endpoint is used to change the password of an account
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        if request.method == "POST":
            try:
                new_password = request.POST.get("new_password")
                user = request.user
                
                if user.username.find("42_") != -1:
                    raise Exception("THE 42 USERS CAN'T CHANGE THEIR PASSWORD")
                if new_password == "" or new_password == None:
                    raise Exception("THE NEW PASSWORD CAN'T BE EMPTY")
                regex=r'^(?=.*[A-Z])(?=.*\d)(?=.*[._!"`\'#$%&,:;<>=@{}~\$\(\)\*\+\/\\\?\[\]\^\|])[A-Za-z\d._!"`\'#$%&,:;<>=@{}~\$\(\)\*\+\/\\\?\[\]\^\|]{8,}$'
                if not re.match(regex, new_password):
                    raise Exception("VALIDATION ERROR. THE PASSWORDS MUST CONTAIN AT LEAST 1 UPPERCASE, 1 DIGIT, 1 SPECIAL CHARACTER AND MIN 8 CHARACTERS")
                userquery = Usuario.objects.filter(username=user.username).first()
                userquery.set_password(new_password)
                userquery.save()
                return JsonResponse({"status" : "password changed succesfully"}, status=200)
            except Exception as e:
                return JsonResponse({"status" : str(e)}, status=400)
        else:
            return JsonResponse({"status" : "method not valid"}, status=405)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
    
def delete_friend(request):
    """
        This endpoint is used for deleting a friend
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.GET.get("friend_name")
        user_query = Usuario.objects.filter(username=user).first()
        me = Usuario.objects.filter(username=request.user.username).first()
        
        if user_query == None:
            return JsonResponse({"status" : "USER NOT FOUND"}, status=200) 
        
        check1 = Amigo.objects.filter(id1_id=int(me.id), id2_id=int(user_query.id)).first()
        check2 = Amigo.objects.filter(id1_id=int(user_query.id), id2_id=int(me.id)).first()
        
        if check1 != None:
            check1.delete()
            return JsonResponse({"status" : "FRIEND DELETED"})
        elif check2 != None:
            check2.delete()
            return JsonResponse({"status" : "FRIEND DELETED"})

        return JsonResponse({"status" : "USER NOT FOUND"})
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    

def delete_account(request):
    """
        This endpoint is used to delete an account
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)


        anon = Usuario.objects.filter(username='Anonimous').first()

        userquery = Usuario.objects.filter(username=request.user.username).first()

        if userquery.avatar != '/images/default.jpg':
            os.remove('media/' + str(userquery.avatar))


        userquery.delete()

        for match in MatchHistory.objects.all():
            if match.winner_id1 is None:
                match.winner_id1 = anon
            if match.loser_id1 is None:
                match.loser_id1 = anon
            match.save()

        return JsonResponse({"status" : "OK"})
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    

def register_guest(request):
    """
        Endpoint used to create a guest user
    """
    try:
        user_check = "not none"
        while user_check != None:
            username = "guest" + str(random.randint(1, 100000000))
            user_check = Usuario.objects.filter(username=username).first()

        password_42 = str(os.environ.get('ADMIN_PASSWORD', ''))
        email = username + "@ponger.ja"
        user = Usuario.objects.create_user(username=username, email=email, password=password_42, avatar="/images/default.jpg", scientist=0)
        user.save()
        return manage_login(request, username)
    except:
        return JsonResponse({"status" : "something went wrong when creating the guest user"}, status=400)

def change_language(request):
    """
        Endpoint used to change the default language of a user
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        try:
            username = request.user.username
            language = request.GET.get("language")
            language_list = ['en', 'es', 'cat']
            
            if language not in language_list:
                return JsonResponse({"status" : "language not supported"}, status=400)
            userquery = Usuario.objects.filter(username=username).first()
            userquery.language = language
            userquery.save()
            return JsonResponse({"status" : "language changed succesfully"}, status=200)
        except:
            return JsonResponse({"status" : "invalid values"}, status=400)
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)

def get_language(request):
    """
        this endpoint returns the default language of a user
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)

        username = request.user.username
        userquery = Usuario.objects.filter(username=username).first()
        language = userquery.language
        return JsonResponse({"status" : str(language)}, status=200)
   
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)

def get_api_id(resquest):
    """
        This endpoint returns the redirect url for 42 login
    """
    url = f"https://api.intra.42.fr/oauth/authorize?client_id={str(os.environ.get('UID', '1234'))}&redirect_uri=https://{str(os.environ.get('MI_IP', '127.0.0.1'))}:{str(os.environ.get('PORT', '443'))}%2Fapi%2Fregister_42%2F&response_type=code"
    return JsonResponse({"url" : str(url)}, status=200)