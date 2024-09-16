from django.http import HttpResponse, JsonResponse
from django.core.validators import ValidationError
from ..models import Usuario, Amigo, MatchHistory
from django.core.cache import cache
from datetime import date, datetime, timedelta

queue = [] # Variable to store the users in queue
games = [] # Variable to store the games
tour_games = [] # Variable to store the tournament games

def to_queue(request):
    """
        This endpoint puts a user in queue
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user

        for users in queue:
            if users["username"] == request.user.username:
                return JsonResponse({"status" : "user already in queue"}, status=200)
        
        if request.user.is_authenticated == True:
            user_info = {
                "username" : user.username,
                "mode" : request.POST.get("mode"),
                "nickname" : request.POST.get("nickname", None),
                "spell" : user.scientist,
                "tour_id" : request.POST.get("tour_id", None),
            }
            queue.append(user_info)
            return (JsonResponse({"status" : "in_queue"}, status=200))
        else:
            return JsonResponse({"status" : "error"}, status=400)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    

def find_1v1(request):
    """
    function to queue for 1v1 match
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        username = request.user.username

        # Si esta creada la partida con el jugador, se mete
        for game in games:
            if game["mode"] == "1v1" and (game["player1"] == username or game["player2"] == username):
                return(JsonResponse({'status': 'Hay alguien contigo', 'game': game}, status=200))
            
        # Guardo el usuario para borrarlo de la lista en caso de encontrar partida
        this_user = ""
        for user in queue:
            if user["username"] == username:
                this_user = user
        
        # Si no está creada y encuentra a un jugador, la crea
        for user in queue:
                
            if user["mode"] == "1v1" and user["username"] != username:
                player1 = username
                player2 = user["username"]

                create_game = {
                    "player1" : player1,
                    "spell_p1" : request.user.scientist,
                    "player2" : player2,
                    "spell_p2" : user['spell'],
                    "mode" : "1v1",
                    "gameID" : player1 + "vs" + player2 + datetime.now().strftime("%H%M%S"),
                }
                games.append(create_game)
                queue.remove(user)
                queue.remove(this_user)
                return (JsonResponse({'status': 'Hay alguien contigo', 'game': create_game}, status=200))
        return(JsonResponse({'status': 'Solo de por vida'}, status=200))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)

def find_1v1_spells(request):
    """
    function to queue for 1v1 match with spells
    """

    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        username = request.user.username

        # Si esta creada la partida con el jugador, se mete
        for game in games:
            if game["mode"] == "1v1s" and (game["player1"] == username or game["player2"] == username):
                return(JsonResponse({'status': 'Hay alguien contigo', 'game': game}, status=200))
            
        # Guardo el usuario para borrarlo de la lista en caso de encontrar partida
        this_user = ""
        for user in queue:
            if user["username"] == username:
                this_user = user
        
        # Si no está creada y encuentra a un jugador, la crea
        for user in queue:
                
            if user["mode"] == "1v1s" and user["username"] != username:
                player1 = username
                spell_1 = this_user["spell"]
                player2 = user["username"]
                spell_2 = user["spell"]
                
                create_game = {
                    "player1" : player1,
                    "spell_p1" : spell_1,
                    "player2" : player2,
                    "spell_p2" : spell_2,
                    "mode" : "1v1s",
                    "gameID" : player1 + "vs" + player2 + datetime.now().strftime("%H%M%S"),
                }
                games.append(create_game)
                queue.remove(user)
                queue.remove(this_user)
                return (JsonResponse({'status': 'Hay alguien contigo', 'game': create_game}, status=200))
        return(JsonResponse({'status': 'Solo de por vida'}, status=200))

    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)


def find_tour(request):
    """
    function to queue for a tournament
    """

    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        username = request.user.username

        for game in games:
            if game["mode"] == "tour_semifinal" and (game["player1"] == username or game["player2"] == username) and game['status'] == False:
                return(JsonResponse({'status': 'Hay alguien contigo', 'game': game}, status=200))

        this_user = ""
        for user in queue:
            if user["username"] == username:
                this_user = user
        user_list = []
        for user in queue:
            if user["mode"] == "tour_semifinal" and user["username"] != username:
                user_list.append(user)
            if len(user_list) == 3:
                time = datetime.now().strftime("%H%M%S")
                game1 = {
                    "mode" : "tour_semifinal",
                    "player1" : username,
                    "nickname1" : this_user["nickname"],
                    "spell_p1" : request.user.scientist,
                    "player2" : user_list[0]["username"],
                    "nickname2" : user_list[0]["nickname"],
                    "spell_p2" : user_list[0]['spell'],
                    "gameID" : username + "v" + user_list[0]["username"] + time,
                    "tour_id" : username + "v" + user_list[0]["username"] + "v" + user_list[1]["username"] + "v" + user_list[2]["username"] + time,
                    "status" : False
                }
                game2 = {
                    "mode" : "tour_semifinal",
                    "player1" : user_list[1]["username"],
                    "nickname1" : user_list[1]["nickname"],
                    "spell_p1" : user_list[1]['spell'],
                    "player2" : user_list[2]["username"],
                    "nickname2" : user_list[2]["nickname"],
                    "spell_p2" : user_list[2]['spell'],
                    "gameID" : user_list[1]["username"] + "v" + user_list[2]["username"] + time,
                    "tour_id" : username + "v" + user_list[0]["username"] + "v" + user_list[1]["username"] + "v" + user_list[2]["username"] + time,
                    "status" : False
                }
                games.append(game1)
                games.append(game2)
                tour_games.append(game1)
                tour_games.append(game2)
                for list_user in user_list:
                    queue.remove(list_user)
                queue.remove(this_user)
                return (JsonResponse({'status': 'Hay alguien contigo', 'game': game1}, status=200))
        return(JsonResponse({'status': 'Solo de por vida'}, status=200))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
def find_tour_final(request):
    """
    function to queue for tournament final match
    """

    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        username = request.user.username

        for game in games:
            if game["mode"] == "tour_final" and (game["player1"] == username or game["player2"] == username) and request.POST.get("tour_id") == game["tour_id"]:
                return(JsonResponse({'status': 'Hay alguien contigo', 'game': game}, status=200))

        this_user = ""
        for user in queue:
            if user["username"] == username:
                this_user = user
    
        for user in queue:
            if user["mode"] == "tour_final" and user["username"] != username and this_user["tour_id"] == user["tour_id"]:
                new_final = {
                    "mode" : "tour_final",
                    "player1" : username,
                    "nickname1" : this_user["nickname"],
                    "spell_p1" : request.user.scientist,
                    "player2" : user["username"],
                    "nickname2" : user["nickname"],
                    "spell_p2" : user['spell'],
                    "gameID" : username + "v" + user["username"] + datetime.now().strftime("%H%M%S"),
                    "tour_id" : user["tour_id"]
                }
                queue.remove(user)
                queue.remove(this_user)
                games.append(new_final)
                tour_games.append(new_final)
                return (JsonResponse({'status': 'Hay alguien contigo', 'game': new_final}, status=200))
        return(JsonResponse({'status': 'Solo de por vida'}, status=200))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)


def tour_semifinal_s(request):
    """
    Function to search for a tournament with spells
    """

    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        username = request.user.username

        for game in games:
            if game["mode"] == "tour_semifinal_s" and (game["player1"] == username or game["player2"] == username) and game['status'] == False:
                return(JsonResponse({'status': 'Hay alguien contigo', 'game': game}, status=200))

        this_user = ""
        for user in queue:
            if user["username"] == username:
                this_user = user
        user_list = []
        for user in queue:
            if user["mode"] == "tour_semifinal_s" and user["username"] != username:
                user_list.append(user)
            if len(user_list) == 3:
                time = datetime.now().strftime("%H%M%S")
                game1 = {
                    "mode" : "tour_semifinal_s",
                    "player1" : username,
                    "nickname1" : this_user["nickname"],
                    "spell_p1" : request.user.scientist,
                    "player2" : user_list[0]["username"],
                    "nickname2" : user_list[0]["nickname"],
                    "spell_p2" : user_list[0]['spell'],
                    "gameID" : username + "v" + user_list[0]["username"] + time,
                    "tour_id" : username + "v" + user_list[0]["username"] + "v" + user_list[1]["username"] + "v" + user_list[2]["username"] + time,
                    "status" : False
                }
                game2 = {
                    "mode" : "tour_semifinal_s",
                    "player1" : user_list[1]["username"],
                    "nickname1" : user_list[1]["nickname"],
                    "spell_p1" : user_list[1]['spell'],
                    "player2" : user_list[2]["username"],
                    "nickname2" : user_list[2]["nickname"],
                    "spell_p2" : user_list[2]['spell'],
                    "gameID" : user_list[1]["username"] + "v" + user_list[2]["username"] + time,
                    "tour_id" : username + "v" + user_list[0]["username"] + "v" + user_list[1]["username"] + "v" + user_list[2]["username"] + time,
                    "status" : False
                }
                games.append(game1)
                games.append(game2)
                tour_games.append(game1)
                tour_games.append(game2)
                for list_user in user_list:
                    queue.remove(list_user)
                queue.remove(this_user)
                return (JsonResponse({'status': 'Hay alguien contigo', 'game': game1}, status=200))
        return(JsonResponse({'status': 'Solo de por vida'}, status=200))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    

def tour_final_s(request):
    """
        Function to search for a tournament final match with spells
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        username = request.user.username

        for game in games:
            if game["mode"] == "tour_final_s" and (game["player1"] == username or game["player2"] == username) and request.POST.get("tour_id") == game["tour_id"]:
                return(JsonResponse({'status': 'Hay alguien contigo', 'game': game}, status=200))

        this_user = ""
        for user in queue:
            if user["username"] == username:
                this_user = user
    
        for user in queue:
            if user["mode"] == "tour_final_s" and user["username"] != username and this_user["tour_id"] == user["tour_id"]:
                new_final = {
                    "mode" : "tour_final_s",
                    "player1" : username,
                    "nickname1" : this_user["nickname"],
                    "spell_p1" : request.user.scientist,
                    "player2" : user["username"],
                    "nickname2" : user["nickname"],
                    "spell_p2" : user['spell'],
                    "gameID" : username + "v" + user["username"] + datetime.now().strftime("%H%M%S"),
                    "tour_id" : user["tour_id"]
                }
                queue.remove(user)
                queue.remove(this_user)
                games.append(new_final)
                tour_games.append(new_final)
                return (JsonResponse({'status': 'Hay alguien contigo', 'game': new_final}, status=200))
        return(JsonResponse({'status': 'Solo de por vida'}, status=200))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)    

# Parámetros: (mode: ej (tour_semifinal/1v1), nickname(opcional para torneos))
def is_match(request):
    """
        Endpoint to check if a game has been found while you are in queue
    """
    
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        username = user.username
        spell = user.scientist
        mode = request.POST.get("mode")
        nickname = request.POST.get("nickname", None)
        if mode == "1v1":
            return find_1v1(request)
        elif mode == "1v1s":
            return find_1v1_spells(request)
        elif mode == "tour_semifinal":
            return find_tour(request)
        elif mode == "tour_final":
            return find_tour_final(request)
        elif mode == "tour_semifinal_s":
            return tour_semifinal_s(request)
        elif mode == "tour_final_s":
            return tour_final_s(request)
        return(JsonResponse({}, status=500))
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
def match_result(request):
    """
        This stores a match result in the database
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        if request.method == "POST":
            score = request.POST.get("score")
            mode = request.POST.get("mode")
            winner1 = request.POST.get("winner1", None)
            loser1 = request.POST.get("loser1", None)
            winner1_id = loser1_id= None
            tour_id = request.POST.get("tour_id", None)

            # If tournament finish with an error
            if (mode == "tour_final" or mode == "tour_final-s") and score == "0-0":
                for game in tour_games[:]:
                    if game["tour_id"] == tour_id:
                        tour_games.remove(game)
                return JsonResponse({"status" : "Tournament finished"}, status=200)

            if winner1 != None:
                winner1_id = Usuario.objects.filter(username=winner1).first()
            if loser1 != None:
                loser1_id = Usuario.objects.filter(username=loser1).first()

            # ! Hay que tocar esto para arreglar lo de si llegan 2 match_result de los 2 jugadores no guarden los 2

            new_match = MatchHistory(score=score, mode=mode, date=date.today(), winner_id1=winner1_id, loser_id1=loser1_id)
            new_match.save()
            for game in games[:]:
                if game['player1'] == winner1 or game['player2'] == winner1:
                    if game["mode"] == "tour_final" or game["mode"] == "tour_final_s":
                        for g in tour_games[:]:
                            if g["tour_id"] == game["tour_id"]:
                                tour_games.remove(g)
                    games.remove(game)

        else:
            return JsonResponse({"status" : "wrong request method"}, status=405)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
    return JsonResponse({"status" : "ahí tienes tu partido"}, status=200)


def info_tour(request):
    """
        This endpoint sends a current tournament information
    """

    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        tour_id = str(request.GET.get("tour_id"))
        tour_semifinals = []
        tour_final = None
        print(tour_games)
        for tour_game in tour_games:
            if (tour_game["mode"] == "tour_semifinal" or tour_game["mode"] == "tour_semifinal_s") and tour_game["tour_id"] == tour_id:
                tour_semifinals.append(tour_game)
            if (tour_game["mode"] == "tour_final" or tour_game["mode"] == "tour_final_s") and tour_game["tour_id"] == tour_id:
                tour_final = tour_game

        if len(tour_semifinals) != 2:
            print(len(tour_semifinals))
            print(tour_id)
            return JsonResponse({"status" : "smth went wrong"}, status=400)
        semifinal1 = tour_semifinals[0]
        semifinal2 = tour_semifinals[1]
        final = tour_final
        ret_json = {"semifinal1" : semifinal1, "semifinal2" : semifinal2, "final" : final}
        
        return JsonResponse(ret_json)
    except Exception as e:
        print(e)
        return JsonResponse({"status" : "smth went wrong", "error": e}, status=400)
    

def remove_from_queue(request):
    """
        This enpoint is used to remove a user from queue
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        for queue_user in queue:
            if queue_user["username"] == user.username:
                queue.remove(queue_user)
                return JsonResponse({"status" : "user removed from queue"})
        return JsonResponse({"status" : "USER IS NOT LOOKING FOR A GAME"})
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)
    
    
def is_in_queue(request):
    """
        This endpoint checks if a user is in queue
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        user = request.user
        for queue_user in queue:
            if queue_user["username"] == user.username:
                return JsonResponse({"status" : "user is in queue"})
        return JsonResponse({"status" : "user is not in queue"})
    except:
        return JsonResponse({"status" : "smth went wrong"}, status=400)


def tour_flag(request):
    """
        This endpoint is user to check if a user has joined a tournament
    """
    try:
        if request.user.is_authenticated == False:
            return JsonResponse({"status" : "user must be logged"}, status=401)
        tour_id = request.GET.get("tour_id")

        for game in games:
            if tour_id == game['tour_id']:
                game['status'] = True
        return JsonResponse({"status" : "good"}, status=200)
    except Exception as e:
        return JsonResponse({"status" : "smth went wrong", "error": e}, status=400)