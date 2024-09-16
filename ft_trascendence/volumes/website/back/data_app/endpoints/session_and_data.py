from django.http import HttpResponse, JsonResponse
from django.core.validators import ValidationError
from ..models import Usuario, Amigo, MatchHistory
import json
from datetime import date, datetime, timedelta
from django.core.cache import cache
from reportlab.platypus import SimpleDocTemplate, Table, TableStyle, Paragraph, Spacer, Image
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.lib.pagesizes import letter
from io import BytesIO
from reportlab.platypus import TableStyle
from reportlab.lib import colors



def check_status_friend(username):
    """
        This function returns if a friend is online
    """
    try:
        user = username
        user_query = Usuario.objects.filter(username=user).first()
        if user_query != None:
            user_time = cache.get(str(user_query.id))
            if user_time != None:
                time_user = datetime.strptime(user_time, "%Y-%m-%d %H:%M:%S")
                if (time_user > datetime.now()):
                    return True
        return False
    except:
        raise Exception("Something went wrong when checking online status")


def all_data(request):
    """
        This endpoint returns all data related to a user for loading the page
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "User must be logged."}, status=401)
        all_data_list = []
        all_data_dict = {}
        # PILLAR LOS DATOS DE USUARIO DEL JUGADOR
        username = request.user.username

        user = Usuario.objects.all().filter(username=username)

        if not user.exists():
            return JsonResponse({"status" : "User doesn't exist."}, status=400)
        else:
            user_info = {
                    "username" : user[0].username,
                    "email" : user[0].email,
                    "scientist" : user[0].scientist,
                    "avatar" : str(user[0].avatar),
            }
        
        # PILLAR LAS EL HISTORIAL DE PARTIDAS DEL JUGADOR
        data = MatchHistory.objects.all()
        user = request.user
        match_list = []
    
        games_won = 0
        tour_played = 0
        tour_won = 0
        goals_fav = 0
        goals_con = 0
        
        for fila in data:
            winner1 = fila.winner_id1
            loser1 = fila.loser_id1
            
            winner1_username = None
            loser1_username = None

            if winner1 != None:
                winner1 = winner1.id
                winner1_username = Usuario.objects.filter(id=winner1).first().username
            if loser1 != None:
                loser1 = loser1.id
                loser1_username = Usuario.objects.filter(id=loser1).first().username
                        
            if winner1 == user.id or loser1 == user.id:
                game = {
                    "mode" : fila.mode,
                    "date" : str(fila.date),
                    "winner_1" : winner1_username,
                    "loser_1" : loser1_username,
                    "score" : fila.score,
                }
                splitted_result = fila.score.split('-')
                splitted_result[0] = '3' if (splitted_result[0] == '51') else splitted_result[0]
                splitted_result[1] = '3' if (splitted_result[1] == '51') else splitted_result[1]
                if loser1 == user.id:
                    if splitted_result[0] != '3':
                        goals_fav += int(splitted_result[0])
                        goals_con += int(splitted_result[1])
                    else:
                        goals_fav += int(splitted_result[1])
                        goals_con += int(splitted_result[0])
                else:
                    if splitted_result[0] != '3':
                        goals_con += int(splitted_result[0])
                        goals_fav += int(splitted_result[1])
                    else:
                        goals_con += int(splitted_result[1])
                        goals_fav += int(splitted_result[0])
                    games_won += 1
                if (fila.mode == "tour_semifinal" or fila.mode == "tour_semifinal_s") and (winner1 == user.id or loser1 == user.id):
                    tour_played += 1
                if (fila.mode == "tour_final" or fila.mode == "tour_final_s") and winner1 == user.id:
                    tour_won += 1
                match_list.append(game)

        # CALCULAR LAS STATS CON LAS VARIABLES DE ANTES
        
        # VARIABLES PARA LAS STATS
        games_played = len(match_list)
        games_lost = games_played - games_won
        if games_played != 0:
            winrate = games_won / games_played * 100
        else:
            winrate = 100
        player_stats = {"games_played" : games_played,
                        "games_won" : games_won,
                        "games_lost" : games_lost,
                        "winrate" : int(winrate),
                        "tour_won" : tour_won,
                        "tour_played" : tour_played,
                        "goals_fav" : goals_fav,
                        "goals_con" : goals_con
                    }
        # AMIGOS

        friend_list = []
        requests_sent = []
        requests_received = []
        user_query = Usuario.objects.filter(username=username).first()
        
        user_friends1 = Amigo.objects.filter(id1=user_query, matched=True)
        user_friends2 = Amigo.objects.filter(id2=user_query, matched=True)
        requests_sent_query = Amigo.objects.filter(id1=user_query, matched=False)
        requests_received_query = Amigo.objects.filter(id2=user_query, matched=False)
        for friend in user_friends1:
            friend_list.append(friend.id2)
        for friend in user_friends2:
            friend_list.append(friend.id1)
        for friend in requests_sent_query:
            requests_sent.append(friend.id2)
        for friend in requests_received_query:
            requests_received.append(friend.id1)
            

        dic_list = []
        for friend in friend_list:
            friend_online = check_status_friend(friend.username)
            friends_dic = {
                "username" : friend.username,
                "is_online" : friend_online,
                "status" : "friend"
            }
            dic_list.append(friends_dic)
        for friend in requests_sent:
            
            friends_dic = {
                "username" : friend.username,
                "is_online" : False,
                "status" : "request_sent"
            }
            dic_list.append(friends_dic)
        for friend in requests_received:
            
            friends_dic = {
                "username" : friend.username,
                "is_online" : False,
                "status" : "request_received"
            }
            dic_list.append(friends_dic)
        
            
        all_data_dict = {"user_info" : user_info,
                        "match_history" : match_list[-10:],
                        "user_stats" : player_stats,
                        "friends" : dic_list,
                        }
        test2 = json.dumps(all_data_dict)
        
        return JsonResponse({"data" : test2}, status=200)
    except Exception as e:
        return JsonResponse({"status" : "something went wrong"}, status=400)

def test_auth(request):
    """
        this endpoint checks if the curent user is logged or not
    """
    try:
        if (request.user.is_authenticated == True):
            return(JsonResponse({"status" : "logged"}, status=200))
        else:
            return(JsonResponse({"status" : "not logged"}, status=200))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
def add_delete_redis(username):
    """
        This endpoint adds to the logged users list the current user and also deletes from it users whose time has expired
    """
    user_list = cache.get('list')
    if user_list == None:
        cache.set('list', [username])
    else:
        if username not in user_list:
            user_list.append(username)
        
        for user in user_list:
            user_query = Usuario.objects.filter(username=user).first()
            if user_query == None:
                return
            user_time = cache.get(str(user_query.id))
            if user_time != None:
                time_user = datetime.strptime(user_time, "%Y-%m-%d %H:%M:%S")
                if (time_user < datetime.now()):
                    cache.delete(str(user_query.id))
                    user_list.remove(user)
            else:
                cache.delete(str(user_query.id))
                user_list.remove(user)
        cache.set('list', user_list)



def refresh(request):
    """
        This endpoint is used to refresh the chache time of a user
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=200)
        user_query = Usuario.objects.filter(username=request.user.username).first()
        if user_query != None:
            user_id = user_query.id
            cache.set(str(user_id), (datetime.now() + timedelta(minutes=3)).strftime("%Y-%m-%d %H:%M:%S"))
            add_delete_redis(request.user.username)
        return JsonResponse({"status" : "all good"})
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    

def check(request):
    """
        This endpoint checks if a user is online or offline
    """
    try:
        user = request.GET.get("username", None)
        user_query = Usuario.objects.filter(username=user).first()
        if user_query != None:
            user_time = cache.get(str(user_query.id))
            if user_time != None:
                time_user = datetime.strptime(user_time, "%Y-%m-%d %H:%M:%S")
                if (time_user > datetime.now()):
                    return JsonResponse({"status": "ONLINE"}, status=200)
        return JsonResponse({"status": "OFFLINE"}, status=200)
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
 

def stats_friend(request):
    """
        This endpoint returns the stats of a friend
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        data = MatchHistory.objects.all()
        usern = request.GET.get('friend_name')
        user = Usuario.objects.filter(username=usern).first()
        user_image = str(user.avatar)
        match_list = []

        games_won = 0
        tour_played = 0
        tour_won = 0
        goals_fav = 0
        goals_con = 0

        
        for fila in data:
            winner1 = fila.winner_id1
            loser1 = fila.loser_id1
 
            winner1_username = None
            loser1_username = None

            if winner1 != None:
                winner1 = winner1.id
                winner1_username = Usuario.objects.filter(id=winner1).first().username
            if loser1 != None:
                loser1 = loser1.id
                loser1_username = Usuario.objects.filter(id=loser1).first().username
                        
            if winner1 == user.id or loser1 == user.id:
                game = {
                    "mode" : fila.mode,
                    "date" : str(fila.date),
                    "winner_1" : winner1_username,
                    "loser_1" : loser1_username,
                    "score" : fila.score,
                }
                splitted_result = fila.score.split('-')
                splitted_result[0] = '3' if (splitted_result[0] == '51') else splitted_result[0]
                splitted_result[1] = '3' if (splitted_result[1] == '51') else splitted_result[1]
                if loser1 == user.id:
                    if splitted_result[0] != '3':
                        goals_fav += int(splitted_result[0])
                        goals_con += int(splitted_result[1])
                    else:
                        goals_fav += int(splitted_result[1])
                        goals_con += int(splitted_result[0])
                else:
                    if splitted_result[0] != '3':
                        goals_con += int(splitted_result[0])
                        goals_fav += int(splitted_result[1])
                    else:
                        goals_con += int(splitted_result[1])
                        goals_fav += int(splitted_result[0])
                    games_won += 1
                if (fila.mode == "tour_semifinal" or fila.mode == "tour_semifinal_s") and (winner1 == user.id or loser1 == user.id):
                    tour_played += 1
                if (fila.mode == "tour_final" or fila.mode == "tour_final_s") and winner1 == user.id:
                    tour_won += 1
                match_list.append(game)

        # CALCULAR LAS STATS CON LAS VARIABLES DE ANTES
        
        # VARIABLES PARA LAS STATS
        games_played = len(match_list)
        games_lost = games_played - games_won
        if games_played != 0:
            winrate = games_won / games_played * 100
        else:
            winrate = 100
        player_stats = {"games_played" : games_played,
                        "games_won" : games_won,
                        "games_lost" : games_lost,
                        "winrate" : int(winrate),
                        "tour_won" : tour_won,
                        "tour_played" : tour_played,
                        "goals_fav" : goals_fav,
                        "goals_con" : goals_con,
                        "match_history" : match_list[-10:],
                        "image" : user_image,
                    }
        ret_data = json.dumps(player_stats)
        return JsonResponse(player_stats)
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)



    
def set_offline(request):
    """
        This endpoint makes the cache time of the user expire
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        if user != None:
            cache.set(str(user.id), (datetime.now() - timedelta(minutes=1)).strftime("%Y-%m-%d %H:%M:%S"))
            return JsonResponse({"status" : "USER SET OFFLINE"})
        else:
            return JsonResponse({"status": "COULDN'T FIND USER"})
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
    
def data_pdf(request):
    """
        This endpoint returns a pdf file with a users information
    """
    try:
        if not request.user.is_authenticated:
            return JsonResponse({"status": "user must be logged"}, status=401)
        user = request.user
        buffer = BytesIO()
        pdf = SimpleDocTemplate(buffer, pagesize=letter)
        styles = getSampleStyleSheet()
        
        matches = [["WINNER", "LOSER", "GAME MODE", "SCORE", "DATE"]]
        match_history = MatchHistory.objects.all()
        for game in match_history:
            if str(game.winner_id1) == str(user.username) or str(game.loser_id1) == str(user.username):
                new_game = [str(game.winner_id1), str(game.loser_id1), str(game.mode), str(game.score), str(game.date)]
                matches.append(new_game)
        
        friends = Amigo.objects.all()
        
        friend_list = [["USERNAME", "DATE", "MATCH STATUS"]]
        friend_title = Paragraph('Friends', styles['Title'])

        for friend in friends:
            if str(friend.id1) == str(user.username):
                new_friend = [str(friend.id2), str(friend.date), str(friend.matched)]
                friend_list.append(new_friend)
            elif str(friend.id2) == str(user.username):
                new_friend = [str(friend.id1), str(friend.date), str(friend.matched)]
                friend_list.append(new_friend)

        table = Table(matches)
        friend_list_table = Table(friend_list)
        title = Paragraph('Match History', styles['Title'])

        teal = colors.Color(red=(0.0/255), green=(128.0/255), blue=(128.0/255))
        
        style = TableStyle([
            ('BACKGROUND', (0,0), (-1,0), teal),
            ('TEXTCOLOR', (0,0), (-1,0), colors.whitesmoke),
            ('ALIGN', (0,0), (-1,-1), 'CENTER'),
            ('FONTNAME', (0,0), (-1,0), 'Helvetica-Bold'),
            ('FONTSIZE', (0,0), (-1,0), 14),
            ('BOTTOMPADDING', (0,0), (-1,0), 12),
            ('BACKGROUND', (0,1), (-1,-1), colors.beige),
            ('GRID', (0,0), (-1,-1), 1, colors.black)
        ])
        table.setStyle(style)
        friend_list_table.setStyle(style)
        spaces = Spacer(1, 20)
        
        personal_info = Table([["USERNAME", "EMAIL"], [user.username, user.email]])
        personal_info.setStyle(style)

        image_path = "media/" + str(user.avatar)
        image = Image(image_path, width=150, height=150)

        flowables = [image, spaces, personal_info, spaces, friend_title, friend_list_table ,spaces, title, table]
        pdf.build(flowables)
        pdf_data = buffer.getvalue()
        buffer.close()
        response = HttpResponse(pdf_data, content_type='application/pdf')
        response['Content-Disposition'] = 'attachment; filename="match_history.pdf"'
        return response
    except:
        return JsonResponse({"status": "something went wrong"}, status=400)