import { tournamentLocal, createGame } from './modules/tournamentLocal.js';

var userProgress = 0; // Progresion de usuario hasta loguearse (0 -> pantalla de moneda, 1 -> pantalla login, 2 -> dentro de la web logueado)
var mode = 'IA'; // Modo de juego escogido
var s4mode = 0; // Pantalla de juego :: 0 -> home, 1 -> 1v1, 2 -> tour_view
var scriptGame = null; // Script del juego
var estados = null; // Informacion de los cientificos
var searching = null; // setInterval y setTimeour cuando se busca partida o cuando se espera al torneo

// VARIABLES IDIOMAS //
var language_conf = localStorage.getItem('language') || 'English';
if (!localStorage.getItem('language')) localStorage.setItem('language', 'English');
const language_key = {
    'English': 'en',
    'Español': 'es',
    'Català': 'cat'
};
const key_language = {
    'en': 'English',
    'es': 'Español',
    'cat': 'Català'
};


// ** Controlador Idiomas ** //

// Cargamos idiomas de los .json
async function load_language(language, is_reload=false)
{
    const idiomas = document.getElementById("select_idioma");
    idiomas.textContent = language;
    await fetch(`./translate/${language_key[language]}.json`)
    .then(response => response.json())
    .then(data => {
        const elements = document.querySelectorAll('[translate-key]');
        elements.forEach(el => {
            const key = el.getAttribute('translate-key');
            el.innerHTML = data[key];
        });
    })
    .catch(error => console.error('Error al cargar las traducciones:', error));
    await fetch('./translate/scientist.json')
    .then(response => response.json())
    .then(data => {
        estados = data[language_conf];
        fetchDataAndHandleResponse().then(() => {
            localStorage.setItem('language', language);
            if (is_reload)
                location.reload();
            changeSection(localStorage.getItem('sectionNumber'), false);
        });
    })
    .catch(error => console.error('Error al cargar los estados:', error));
}

// Recoger data del usuario para coger su idioma
function fetchDataAndHandleResponse() {
    return fetch(`/api/test_auth/`, { method: 'GET', credentials: 'include', mode: 'cors' })
        .then(response => {
            if (!response.ok) {
                userProgress = -1;
                changeSection(0);
                throw new Error('Not Logged!');
            }
            return response.json();
        })
        .then(data => {
            if (data.status === "logged") {
                return fetch(`/api/all_data/`, { method: 'GET', credentials: 'include', mode: 'cors' })
                    .then(response1 => {
                        if (!response1.ok) {
                            changeSection(1, false);
                            throw new Error(`Request all data failed. Status: ${response1.statusText}`);
                        }
                        return response1.json();
                    })
                    .then(data2 => {
                        localStorage.setItem('perfil', JSON.stringify(data2));
                        userProgress = 2;
                        const sectionNumber = localStorage.getItem('sectionNumber');
                        actualizarInterfaz(JSON.parse(data2.data).user_info.scientist);
                        if (sectionNumber > 1) {
                            chargeData();
                            changeSection(sectionNumber, false);
                        } else {
                            chargeData();
                            changeSection(2, false);
                        }
                    })
                    .catch(error2 => console.error(error2));
            } else {
                changeSection(0);
            }
        })
        .catch(error => console.error(error));
}

// Boton de idiomas
const idiomas = document.getElementById("select_idioma");
idiomas.textContent = language_conf;
idiomas.addEventListener("click", () => {
    const opciones = document.querySelectorAll("#lista_idiomas > p");
    opciones.forEach((opcion) => {
        if (opcion.innerText == language_conf)
            opcion.style.color = "aquamarine";
        else
            opcion.style.color = "rgb(255, 156, 7)";
    });
    idiomas.style.display = "none";
    const lista_idiomas = document.getElementById("lista_idiomas");        
    lista_idiomas.style.display = "block";
    opciones.forEach((opcion) => {
        opcion.addEventListener("click", () => {
            idiomas.style.display = "block";
            lista_idiomas.style.display = "none";
            idiomas.textContent = opcion.innerText;
            language_conf = opcion.innerText;
            fetch(`/api/change_language/?language=${language_key[language_conf]}`);
            load_language(language_conf, true);
            opciones.forEach((opcion) => {
                opcion.style.color = "rgb(255, 156, 7)";
            });
            opcion.style.color = "aquamarine";
        });
    });
});

// Para cerrar el boton de idiomas al hacer click fuera
window.addEventListener("click", (e) => {
    if (e.target != idiomas && e.target != lista_idiomas && document.querySelectorAll("canvas").length == 0)
    {
        idiomas.style.display = "block";
        lista_idiomas.style.display = "none";
    }
});

// Al cargar el DOM se cargan los idiomas
load_language(language_conf);
fetch('/api/test_auth/')
.then(response => response.json())
.then(data => {
    if (data.status == 'logged')
    {
        fetch(`/api/get_language/`)
        .then(response => response.json())
        .then(data => {
            if (key_language[data.status] != language_conf)
            {
                localStorage.setItem('language', key_language[data.status]);
                load_language(key_language[data.status]);
            }
        })
        .catch(error => console.error(error));
    }
})
.catch(error => console.error(error));

// ** ONLINE SYSTEM (mantiene el estado conectado del usuario) ** //

fetch('/api/refresh/'); // Nos da igual si falla
setInterval(() => {
    fetch('/api/refresh/');
}, 2000 * 60); // Cada 2 min se dice al back que sigo conectado

// Evento para detectar si me voy de la página para ponerme offline y quitarme del matchmaking si estaba
window.addEventListener("beforeunload", function () {
    navigator.sendBeacon('/api/set_offline/'); // Navigator nos permite hacer un fetch aunque se cierre la página
    navigator.sendBeacon('/api/remove_from_queue/');
});


// ** DECLARACIONES ** //

// Obtener elementos relevantes
var btnLogOut = document.getElementById('btnLogOut'); // Boton logout
var audioElement = document.getElementById('audioElement'); // Boton sonido
btnLogOut.addEventListener('click', f_logout);
const btnDeleteAccount = document.getElementById('btnDeleteAccount'); // Boton borrar cuenta
btnDeleteAccount.addEventListener('click', f_deleteAccount);
const btnDownloadInfoUser = document.getElementById('btnDownloadInfoUser'); // Boton descargar datos usuario
btnDownloadInfoUser.addEventListener('click', f_downloadInfoUser);

// Elementos donde aparecen los cientificos en el DOM
var charAnim = document.getElementById('charAnim');
var charAnimHome = document.getElementById('charAnimHome');
var charSelected = document.getElementById('charSelected');
var homeCharInfo = document.getElementById('homeCharInfo');

// Acceder a elementos secundarios
var nameChar = homeCharInfo.querySelector('#nameChar');
var bornDateChar = homeCharInfo.querySelector('#bornDateChar');
var bornCityChar = homeCharInfo.querySelector('#bornCityChar');
var storyChar = homeCharInfo.querySelector('#storyChar');
const scientist_text_game = document.getElementById('scientist_text_game');

var botones = document.querySelectorAll('.btnWithImage'); // Botones de cientificos

var nick_tour = ''; // Nick escogido para el torneo seleccionado

//*** MATCHMAKING **/

// Eventos de partidas terminadas
window.addEventListener('message', (event) => {
    const mensajeRecibido = event.data;
    if (mensajeRecibido == 'endGameBack' && scriptGame != null) //Terminar partida normal
    {
        scriptGame.type = 'text/plain';
        scriptGame.remove();
        scriptGame = null;
    }
    if (mensajeRecibido == 'endGameTour1v1') // Controlador de flujo para el modo torneo 1v1 Local
    {
        const data_tour_1v1 = localStorage.getItem('data-tour-1v1');
        const data = JSON.parse(data_tour_1v1);
        if (data.win1 && data.win2)
            createGame(data.win1, data.win2, data.player1, data.player2, data.player3, data.player4, data.win1, data.win2);
        else if (data.win1)
            createGame(data.player3, data.player4, data.player1, data.player2, data.player3, data.player4, data.win1);
    }
    if (mensajeRecibido == 'endGame' && scriptGame != null) //Terminar partida normal y volver al menu
    {
        scriptGame.type = 'text/plain';
        scriptGame.remove();
        scriptGame = null;
        s4mode = 0;
        setTimeout(() => {
            changeSection(4);
            if (document.getElementById('init_text'))
                document.getElementById('init_text').remove();
        }, 5000); // Despues de 5 segundos volvemos al menu
    }
    // Controlador de flujo para el modo torneos online
    if ((mensajeRecibido == 'endGameTour' || mensajeRecibido == 'endGameTourS') && scriptGame != null)
    {
        scriptGame.type = 'text/plain';
        scriptGame.remove();
        scriptGame = null;
        setTimeout(() => {
            if (document.getElementById('init_text'))
            {
                const waiting_text = {
                    'English': 'Waiting for the opponent...',
                    'Español': 'Esperando al oponente...',
                    'Català': 'Esperant a l\'oponent...'
                };
                document.getElementById('init_text').innerText = waiting_text[language_conf];
            }
        }, 4000); // Despues de 4 segundos esperamos al proximo oponente para seguir el torneo
        const scientist = ['charles-darwin.gif', 'curie.gif', 'hawking.gif', 'newton.gif', 'einstein.gif', 'pitagoras.gif'];
        const data = localStorage.getItem('data-game');
        const data_game = JSON.parse(data);
        const tour_id = data_game['tour_id'];
        const formData = new FormData();
        formData.append('mode', mensajeRecibido == 'endGameTour' ? 'tour_final' : 'tour_final_s');
        formData.append('nickname', nick_tour);
        formData.append('tour_id', tour_id);
        // Nos metemos en cola para buscar la final
        fetch(`/api/to_queue/`, {method:'POST', credentials: 'include', mode: 'cors', body: formData})
        .then(response => {
            if (!response.ok)
                throw new Error('NO FUE POSIBLE METER EN COLA...');
            return (response.json());
        })
        .then(data => {
            var match = false;
            const in_queue = document.getElementById('in_queue');
            in_queue.style.display = 'block';
            btnCancelQueue.style.display = 'block';
            // Intervalo preguntando si ya tengo partida encontrada
            searching = setInterval(() => {
                fetch(`/api/is_match/`, {method:'POST', credentials: 'include', mode: 'cors', body: formData})
                .then(response => {
                    if (!response.ok)
                        throw new Error('...');
                    return (response.json());
                }).then(data => {
                    if (data.status == 'Hay alguien contigo')
                    {
                        in_queue.style.display = 'none';
                        btnCancelQueue.style.display = 'none';
                        clearInterval(searching);
                        const data_game = JSON.stringify(data.game);

                        // Guardar la data en localStorage
                        localStorage.setItem('data-game', data_game);
                        const data_game_json = JSON.parse(data_game);

                        // Agregamos datos de los jugadores
                        const nickP1 = document.getElementById('nickP1');
                        nickP1.innerText = data_game_json.nickname1;
                        const nickP2 = document.getElementById('nickP2');
                        nickP2.innerText = data_game_json.nickname2;
                        const scientistP1 = document.getElementById('charPlayer1');
                        scientistP1.src = 'gif/' + scientist[data_game_json.spell_p1];
                        const scientistP2 = document.getElementById('charPlayer2');
                        scientistP2.src = 'gif/flop/' + scientist[data_game_json.spell_p2];

                        // Consultamos que jugador somos para cargar el juego
                        const data_perfil = localStorage.getItem('perfil');
                        const nick = JSON.parse(JSON.parse(data_perfil).data)['user_info'].username;

                        // Crear un nuevo elemento de script juego
                        scriptGame = document.createElement('script');
                        if (mensajeRecibido == 'endGameTour')
                            scriptGame.src = data_game_json.player1 == nick ? 'game/p1/script.js' : 'game/p2/script.js';
                        else
                            scriptGame.src = data_game_json.player1 == nick ? 'game/p1s/script.js' : 'game/p2s/script.js';
                        
                        // Cambiamos a la sección del juego para empezar la final
                        match = true;
                        s4mode = 2;
                        changeSection(4);
                        if (document.getElementById('init_text'))
                            document.getElementById('init_text').remove();
                        setTimeout(() => {
                            document.body.appendChild(scriptGame);
                            s4mode = 1;
                            changeSection(4);
                        }, 10000);
                    }
                })
                .catch(error => console.error(error));
            }, 500);
            // TIMOUT por si no encontramos rival para la final
            setTimeout(() => {
                if (!match)
                {
                    clearInterval(searching);
                    const text_error = {
                        'English': 'No opponent found for the tournament final',
                        'Español': 'No se encontró oponente para la final del torneo',
                        'Català': 'No s\'ha trobat oponent per a la final del torneig'
                    }
                    Promise.resolve().then(() => {
                        alert(text_error[language_conf]);
                    });
                    s4mode = 0;
                    changeSection(4);
                    if (document.getElementById('init_text'))
                        document.getElementById('init_text').remove();
                    const data_perfil = localStorage.getItem('perfil');
                    const nick = JSON.parse(JSON.parse(data_perfil).data)['user_info'].username;
                    const formData = new FormData();
                    formData.append('mode', mensajeRecibido == 'endGameTour' ? 'tour_final' : 'tour_final_s');
                    formData.append('score', '51-0');
                    formData.append('winner1', nick);
                    formData.append('loser1', 'JoseSanc');
                    formData.append('tour_id', tour_id);
                    // Enviamos resultado final como que hemos ganado al no tener oponente
                    fetch(`/api/match_result/`, {method:'POST', credentials: 'include', mode: 'cors', body: formData})
                    .then(response => {
                        if (!response.ok)
                            throw new Error('NO FUE POSIBLE MANDAR RESULTADOS...');
                        window.location.reload();
                        return (response.json());
                    }).catch(e => console.error(e));
                }
            }, 240000); // 4 MIN de espera
        })
        .catch(error => console.error(error));
    }
});

//*********************************/

// ** POWER UPS y CIENTIFICOS ** //

// // Botones de cientificos
const btnCh0Game = document.getElementById('btnCh0Game');
const btnCh1Game = document.getElementById('btnCh1Game');
const btnCh2Game = document.getElementById('btnCh2Game');
const btnCh3Game = document.getElementById('btnCh3Game');
const btnCh4Game = document.getElementById('btnCh4Game');
const btnCh5Game = document.getElementById('btnCh5Game');

// Cambiar cientificos
function changeScientisGame(scientist)
{
    actualizarInterfaz(scientist);
    var formData = new FormData();
    formData.append('scientist', scientist);
    fetch(`/api/change_scientist/?scientist=${scientist}`, {method:'GET', credentials: 'include', mode: 'cors'}).then(response => {
        if (!response.ok)
            throw new Error('Server petted...');
        return (response.json());
    }).catch(error => console.error(error));
}

// Controladores boton cientificos
btnCh0Game.addEventListener('click', () => changeScientisGame(0));
btnCh1Game.addEventListener('click', () => changeScientisGame(1));
btnCh2Game.addEventListener('click', () => changeScientisGame(2));
btnCh3Game.addEventListener('click', () => changeScientisGame(3));
btnCh4Game.addEventListener('click', () => changeScientisGame(4));
btnCh5Game.addEventListener('click', () => changeScientisGame(5));

//*********************************/

// * MODE * //

// Obtener los elementos de los botones de modos de juego
const buttons = {
    btnIA: document.getElementById('btnIA'),
    btnIAs: document.getElementById('btnIAs'),
    btn1v1: document.getElementById('btn1v1'),
    btn1v1s: document.getElementById('btn1v1s'),
    btnT: document.getElementById('btnT'),
    btnTs: document.getElementById('btnTs'),
    btn1v1k: document.getElementById('btn1v1k'),
    btnT1v1k: document.getElementById('btnT1v1k')
};


// Input de nick tournament
var inputNick = document.getElementById('nick_tour');

// Manejador de eventos para cambiar el modo y el color de fondo
const handleButtonClick = (new_mode, activeButton) => {
    mode = new_mode;
    Object.values(buttons).forEach(button => button.style.backgroundColor = 'transparent');
    activeButton.style.backgroundColor = 'greenyellow';
    if (new_mode.startsWith('tour'))
        inputNick.style.display = 'block';
    else
        inputNick.style.display = 'none';
};

// Añadir eventos de click a cada boton
buttons.btnIA.addEventListener('click', () => handleButtonClick('IA', buttons.btnIA));
buttons.btnIA.style.backgroundColor = 'greenyellow';
buttons.btnIAs.addEventListener('click', () => handleButtonClick('IAs', buttons.btnIAs));
buttons.btn1v1.addEventListener('click', () => handleButtonClick('1v1', buttons.btn1v1));
buttons.btn1v1s.addEventListener('click', () => handleButtonClick('1v1s', buttons.btn1v1s));
buttons.btnT.addEventListener('click', () => handleButtonClick('tour_semifinal', buttons.btnT));
buttons.btnTs.addEventListener('click', () => handleButtonClick('tour_semifinal_s', buttons.btnTs));
buttons.btn1v1k.addEventListener('click', () => handleButtonClick('1v1k', buttons.btn1v1k));
buttons.btnT1v1k.addEventListener('click', () => handleButtonClick('T1v1k', buttons.btnT1v1k));

//*********************************/


// Boton para cancelar cola
const btnCancelQueue = document.getElementById('btnCancelQueue');
btnCancelQueue.addEventListener('click', () => {
    if (searching)
        clearInterval(searching);
    fetch('/api/remove_from_queue/')
    .then(response => {
        if (!response.ok)
            throw new Error('NO FUE POSIBLE SALIR DE LA COLA...');
        return (response.json());
    }).then(data => {
        const in_queue = document.getElementById('in_queue');
        in_queue.style.display = 'none';
        btnCancelQueue.style.display = 'none';
    }
    ).catch(error => console.error(error));
});

// Boton para ponerse en cola y jugar
const btnPlay = document.getElementById('btnPlay');
btnPlay.addEventListener('click', () => {
    const scientist = ['charles-darwin.gif', 'curie.gif', 'hawking.gif', 'newton.gif', 'einstein.gif', 'pitagoras.gif'];
    if (mode == 'T1v1k')
    {
        return Promise.resolve().then(() => {
            tournamentLocal();
        });
    }
    if (mode == 'IAs' || mode == 'IA' || mode == '1v1k') // Modos sin conexion
    {
        const data_perfil = localStorage.getItem('perfil');
        const nick = JSON.parse(JSON.parse(data_perfil).data)['user_info'].username;
        const scientistPlayer = localStorage.getItem('selectedScientist');
        const nickP1 = document.getElementById('nickP1');
        nickP1.innerText = nick;
        const nickP2 = document.getElementById('nickP2');
        nickP2.innerText = 'JoseSanc';
        const scientistP1 = document.getElementById('charPlayer1');
        scientistP1.src = 'gif/' + scientist[scientistPlayer];
        const scientistIA = Math.floor(Math.random() * 6);
        const scientistP2 = document.getElementById('charPlayer2');
        scientistP2.src = 'gif/flop/' + scientist[scientistIA];

        // DatachangeSection
        var data_game = JSON.stringify({'player1': nick, 'spell_p1': scientistPlayer, 'player2': 'JoseSanc', 'spell_p2': scientistIA});
        localStorage.setItem('data-game', data_game);

        // Crear un nuevo elemento de script
        scriptGame = document.createElement('script');
        scriptGame.src = 'game/IA/script.js';
        if (mode == 'IAs')
            scriptGame.src = 'game/IAs/script.js';
        if (mode == '1v1k')
            scriptGame.src = 'game/1v1/script.js';
        document.body.appendChild(scriptGame);

        // Cambiamos a la sección del juego
        s4mode = 1;
        changeSection(4);
        return ;
    }
    const formData = new FormData();
    formData.append('mode', mode);
    if (mode == "tour_semifinal" || mode == "tour_semifinal_s") // Modos de torneos online
    {
        nick_tour = document.getElementById('nick_tour').value.trim();
        if (nick_tour == '' || nick_tour.length > 7)
        {
            const text_error = {
                'English': 'NICKNAME TOURNAMENT INCORRECT!',
                'Español': 'NICKNAME TORNEO INCORRECTO!',
                'Català': 'NICKNAME TORNEIG INCORRECTE!'
            };
            // LAS ALERTAS están con una promesa para evitar el Warning -> [Violation] 'click' handler took 1940ms
            Promise.resolve().then(() => {
                alert(text_error[language_conf]);
            });
            return ;
        }
        formData.append('nickname', nick_tour);
    }
    // Buscar partida online
    fetch(`/api/to_queue/`, {method:'POST', credentials: 'include', mode: 'cors', body: formData})
    .then(response => {
        if (!response.ok)
            throw new Error('NO FUE POSIBLE METER EN COLA...');
        return (response.json());
    }).then(data => {
        if (data.status == 'user already in queue')
        {
            const text_error = {
                'English': 'You are already in queue',
                'Español': 'Ya estás en cola',
                'Català': 'Ja estàs en cua'
            };
            Promise.resolve().then(() => {
                alert(text_error[language_conf]);
            });
            return ;
        }
        const in_queue = document.getElementById('in_queue');
        in_queue.style.display = 'block';
        btnCancelQueue.style.display = 'block';
        // Intervalo preguntando si ya tenemos partida encontrada
        searching = setInterval(() => {
            fetch(`/api/is_match/`, {method:'POST', credentials: 'include', mode: 'cors', body: formData})
            .then(response => {
                if (!response.ok)
                    throw new Error('...');
                return (response.json());
            }).then(data => {
                if (data.status == 'Hay alguien contigo')
                {
                    in_queue.style.display = 'none';
                    btnCancelQueue.style.display = 'none';
                    clearInterval(searching);
                    var data_game = JSON.stringify(data.game);

                    // Guardar la data en localStorage
                    localStorage.setItem('data-game', data_game);
                    var data_game_json = JSON.parse(data_game);

                    // Agregamos datos de los jugadores
                    const nickP1 = document.getElementById('nickP1');
                    nickP1.innerText = mode == "tour_semifinal" ? data_game_json.nickname1 : data_game_json.player1;
                    const nickP2 = document.getElementById('nickP2');
                    nickP2.innerText = mode == "tour_semifinal" ? data_game_json.nickname2 : data_game_json.player2;
                    const scientistP1 = document.getElementById('charPlayer1');
                    scientistP1.src = 'gif/' + scientist[data_game_json.spell_p1];
                    const scientistP2 = document.getElementById('charPlayer2');
                    scientistP2.src = 'gif/flop/' + scientist[data_game_json.spell_p2];

                    // Consultamos que jugador somos para cargar el juego
                    const data_perfil = localStorage.getItem('perfil');
                    const nick = JSON.parse(JSON.parse(data_perfil).data)['user_info'].username;

                    // Crear un nuevo elemento de script
                    scriptGame = document.createElement('script');
                    if (data_game_json.player1 == nick)
                    {
                        scriptGame.src = 'game/p1/script.js';
                        if (mode == '1v1s' || mode == "tour_semifinal_s")
                            scriptGame.src = 'game/p1s/script.js';
                    }
                    else
                    {
                        scriptGame.src = 'game/p2/script.js';
                        if (mode == '1v1s' || mode == "tour_semifinal_s")
                            scriptGame.src = 'game/p2s/script.js';
                    }                        
                    
                    // Cambiamos a la sección del juego

                    if (mode == 'tour_semifinal' || mode == "tour_semifinal_s")
                    {
                        s4mode = 2;
                        changeSection(4);
                        setTimeout(() => fetch('/api/tour_flag/?tour_id=' + data_game_json.tour_id), 2000);
                        setTimeout(() => {
                            document.body.appendChild(scriptGame);
                            s4mode = 1;
                            changeSection(4);
                        }, 10000);
                    }
                    else
                    {
                        document.body.appendChild(scriptGame);
                        s4mode = 1;
                        changeSection(4);
                    }
                }
            }).catch(error => {
                console.log(error);
            });
        },500);
    }).catch(error => {
        console.log(error);
    });
});

//*********************************/


//*************** CHANGE PHOTO ************ */

const photoInput = document.getElementById('photoInput');
photoInput.onchange = function () {
    if ((this.value.includes('codigo') || this.value.includes('code')) && this.value.includes('lyoko'))
    {
        const backgroundMusic = document.getElementById('backgroundMusic');
        if (!backgroundMusic.paused)
            play_Stop();
        const easterEgg = document.getElementById('easterEgg');
        easterEgg.play();
    }
};
const btnChangePhoto = document.getElementById('btnChangePhoto');
btnChangePhoto.addEventListener('click', async () => {
    if (!photoInput.files.length)
    {
        const text_error = {
            'English': 'No file selected',
            'Español': 'Ningún archivo seleccionado',
            'Català': 'Cap arxiu seleccionat'
        };
        Promise.resolve().then(() => {
            alert(text_error[language_conf]);
        });
        return ;
    }
    const formData = new FormData();
    formData.append('avatar', photoInput.files[0]);
    await fetch(`/api/upload_image/`, {method:'post', credentials: 'include', mode: 'cors', body: formData})
    .then(response => {
        if (!response.ok)
            throw new Error('Upload Image failed');
        return (response.json());
    })
    .then((data) => {
        localStorage.setItem('perfil', JSON.stringify(data));
        chargeData();
    })
    .catch(error => console.error(error));
});

//**************************************** */

// ** CARGAR INTERFAZ ** //

// Función para actualizar la interfaz según el estado actual (cientifico escogido y sus datos)
function actualizarInterfaz(number) {

    number = parseInt(number);
    const estadoActual = estados[`btnCh${number}`];
    
    // Cargamos los datos del cientifico seleccionado
    charAnim.src = estadoActual.charAnim;
    charAnimHome.src = estadoActual.charAnimHome;
    charSelected.textContent = estadoActual.selectChar;
    nameChar.textContent = estadoActual.nameChar;
    bornDateChar.textContent = estadoActual.bornDateChar;
    bornCityChar.textContent = estadoActual.bornCityChar;
    storyChar.textContent = estadoActual.storyChar;
    scientist_text_game.innerHTML = `<span style="color:rgb(255, 156, 7);">${estadoActual.nameChar}: </span><span style="color:red;">${estadoActual.spellName}</span><br>${estadoActual.spellDesc}`;
    localStorage.setItem('selectedScientist', number);

    // Circulo al rededor del cientifico para indicar cual está seleccionado
    const circle = document.getElementById('circle');
    const circle2 = document.getElementById('circle2');
    if (circle) circle.remove();
    if (circle2) circle2.remove();
    const new_circle = document.createElement('div');
    const new_circle2 = document.createElement('div');
    new_circle.id = 'circle';
    new_circle2.id = 'circle2';
    new_circle.style.position = new_circle2.style.position = 'absolute';
    new_circle.style.width = new_circle2.style.width = '120px';
    new_circle.style.height = new_circle2.style.height = '120px';
    new_circle.style.borderRadius = new_circle2.style.borderRadius = '50%';
    new_circle.style.border = new_circle2.style.border = '5px solid greenyellow';
    new_circle.style.left = new_circle2.style.left = '50%';
    new_circle.style.top = new_circle2.style.top = '50%';
    new_circle.style.transform = new_circle2.style.transform = 'translate(-50%, -50%)';
    switch (number)
    {
        case 0:
            btnCh0Game.appendChild(new_circle);
            btnCh0.appendChild(new_circle2);
            break;
        case 1:
            btnCh1Game.appendChild(new_circle);
            btnCh1.appendChild(new_circle2);
            break;
        case 2:
            btnCh2Game.appendChild(new_circle);
            btnCh2.appendChild(new_circle2);
            break;
        case 3:
            btnCh3Game.appendChild(new_circle);
            btnCh3.appendChild(new_circle2);
            break;
        case 4:
            btnCh4Game.appendChild(new_circle);
            btnCh4.appendChild(new_circle2);
            break;
        case 5:
            btnCh5Game.appendChild(new_circle);
            btnCh5.appendChild(new_circle2);
            break;
    }
}

// Cargamos los datos para la página de STATS
function chargeData() {
    const data = JSON.parse(localStorage.getItem('perfil'));
    const user_info = JSON.parse(data['data']);
    const charact = localStorage.getItem('selectedScientist');
    if (user_info)
    {
        const Nname = document.getElementsByClassName('NickName');
        Array.from(Nname).forEach(nick => nick.innerText = user_info['user_info'].username);
        const Email = document.getElementsByClassName('Email');
        Array.from(Email).forEach(mail => mail.innerText = user_info['user_info'].email);
        if (charact)
            actualizarInterfaz(charact);
        else
            actualizarInterfaz(user_info['user_info'].scientist);

            // LISTA DE AMIGOS

            const ulElement = document.getElementById('friendListFull');
            ulElement.innerHTML = "";
            ulElement.style.display = 'flex';
            ulElement.style.flexDirection = 'column';
            ulElement.style.alignItems = 'center';

            // Ordenamos la lista de amigos para poner arriba los que están online
            user_info.friends.sort(function(a, b) {
                return (b.is_online ? 1 : 0) - (a.is_online ? 1 : 0);
            });                

            user_info.friends.forEach(function(item) {
                const liElement = document.createElement('li');
                liElement.innerHTML += `<p style="margin:0; margin-right:35px;">${item.username}</p>`;
                liElement.style.display = 'flex';
                liElement.style.width = '50%';
                liElement.style.alignItems = 'center';
                liElement.style.justifyContent = 'space-between';
                liElement.style.marginBottom = '10px';
                if (item.status == 'request_sent')
                {
                    liElement.classList.add('almost-friends');
                    liElement.innerHTML += '<div>...</div>'
                }
                else if (item.status == 'request_received')
                {
                    liElement.style.color = 'cyan';
                    liElement.innerHTML += '<div>?</div>'
                    liElement.addEventListener('click', () => ft_gestorFriend(item.username, '/api/add_friend/'));
                }
                else
                {
                    liElement.classList.remove('almost-friends');
                    liElement.addEventListener('click', function() {
                        chargeFriendData(item); // Funcion que carga los datos del amigo clickeado
                    });
                    // Punto verde para indicar que está online
                    if (item.is_online)
                        liElement.innerHTML += '<div class="puntoVerde"></div>'
                    else
                        liElement.innerHTML += '<div class="puntoTransparente"></div>'
                }
                if (item.status != 'request_sent')
                {
                    liElement.style.cursor = 'pointer';
                    liElement.addEventListener('mouseenter', function() {
                        this.style.backgroundColor = 'lightcoral'; // Cambia el color de fondo al pasar el mouse
                        });
                    liElement.addEventListener('mouseleave', function() {
                        this.style.backgroundColor = '#00000000'; // Restaura el color original al quitar el mouse
                    });
                }
            ulElement.appendChild(liElement);
        });

        // ACTUALIZA TABLA STATS DE USER
        var user = document.getElementById('infoUser');
        var tableElement = document.getElementById('tableStats');
        var rowElement = tableElement.querySelector('tbody tr');
        user.textContent = user_info.user_info.username;

        rowElement.cells[0].textContent = user_info['user_stats'].games_played || '0';
        rowElement.cells[1].textContent = user_info['user_stats'].games_won || '0';
        rowElement.cells[2].textContent = user_info['user_stats'].games_lost || '0';
        rowElement.cells[3].textContent = (user_info['user_stats'].winrate || '0') + ' %';
        rowElement.cells[4].textContent = user_info['user_stats'].tour_played || '0';
        rowElement.cells[5].textContent = user_info['user_stats'].tour_won || '0';

        const tableGames = document.getElementById('tableGames');

        // LIMPIAR TABLA
        while (tableGames.rows.length > 1)
            tableGames.deleteRow(1);

        const match_history = user_info['match_history'].reverse();
        match_history.forEach(match => {
            const row = tableGames.insertRow();
            const cell1 = row.insertCell();
            const cell2 = row.insertCell();
            const cell3 = row.insertCell();
            const cell4 = row.insertCell();
            const cell5 = row.insertCell();
            cell1.textContent = match.winner_1;
            cell2.textContent = match.loser_1;
            cell3.textContent = match.mode;
            cell4.textContent = match.score;
            cell5.textContent = match.date;
        });

        //Avatar
        const avatars = document.getElementsByClassName('avatar');
        Array.from(avatars).forEach((avatar) => avatar.src = user_info['user_info']['avatar']);
    }
}


// Actualizar datos del usuario y también la página de STATS
function refreshData()
{
    // Recogemos los datos del usuario
    var param = {method: 'GET', mode: 'cors', credentials: 'include' };
    fetch(`/api/all_data/`, param).then(response => {
        if (!response.ok)
        {
            changeSection(1);
            throw new Error('Refresh Data failed.');
        }
        return (response.json());
    }).then(data => {
        // Cargamos los nuevos datos y actualizamos STATS
        localStorage.setItem('perfil', JSON.stringify(data));
        chargeData();
    }).catch(error => console.log(error));
}

// BOTON Refrescamos datos del STATS con el boton
function refreshLista(is_new = false)
{
    if (!is_new) window.scrollTo({top: 0, behavior: 'smooth'});
    var ctx = document.getElementById('grafico');
    if (ctx.getElementsByTagName('canvas').length > 0)
    {
        ctx.style.height = '0px';
        ctx.removeChild(ctx.getElementsByTagName('canvas')[0]);
    }
    refreshData();
}
document.getElementById('btnRefreshLista').addEventListener('click', () => refreshLista());

// FUNCION para cargar los datos del amigo clickeado
function chargeFriendData(item)
{
    window.scrollTo({top: 0, behavior: 'smooth'});
    const Uname = document.getElementById('infoUser');
    Uname.textContent = item.username;
    // DATA USER
    const data = JSON.parse(localStorage.getItem('perfil'));
    const user_info = JSON.parse(data['data']);
    const info_user = JSON.parse(data.data).user_info;
    fetch(`/api/stats_friend/?friend_name=${item.username}`)
    .then(response => {
        if (response.ok)
            return (response.json());
        const text_error = {
            'English': 'Friend Data failed',
            'Español': 'Datos del amigo fallaron',
            'Català': 'Dades de l\'amic fallades'
        };
        Promise.resolve().then(() => {
            alert(text_error[language_conf]);
        });
    }).then(data => {
        const tableElement = document.getElementById('tableStats');
        const rowElement = tableElement.querySelector('tbody tr');
    
        // Cargamos los datos del amigo

        document.getElementById('imagen_friend').src = data.image;
    
        rowElement.cells[0].textContent = data.games_played || '0';
        rowElement.cells[1].textContent = data.games_won || '0';
        rowElement.cells[2].textContent = data.games_lost || '0';
        rowElement.cells[3].textContent = (data.winrate || '0') + ' %';
        rowElement.cells[4].textContent = data.tour_played || '0';
        rowElement.cells[5].textContent = data.tour_won || '0';

        const me_gf_porc = user_info['user_stats'].games_played != 0 ? (user_info['user_stats'].goals_fav / (user_info['user_stats'].games_played * 3)) * 100 : 100;
        const me_ge_porc = user_info['user_stats'].games_played != 0 ? (user_info['user_stats'].goals_con / (user_info['user_stats'].games_played * 3)) * 100 : 100;
        const me_tg_porc = user_info['user_stats'].tour_played != 0 ? (user_info['user_stats'].tour_won / user_info['user_stats'].tour_played) * 100 : 100;

        const friend_gf_porc = data.games_played != 0 ? (data.goals_fav / (data.games_played * 3)) * 100 : 100;
        const friend_ge_porc = data.games_played != 0 ? (data.goals_con / (data.games_played * 3)) * 100 : 100;
        const friend_tg_porc = data.tour_played != 0 ? (data.tour_won / data.tour_played) * 100 : 100;


        const ctx = document.getElementById('grafico');
        ctx.style.height = '600px'; 

        if (ctx.getElementsByTagName('canvas').length > 0)
            ctx.removeChild(ctx.getElementsByTagName('canvas')[0]);

        // Creamos canvas para poner la grafica
        const canvas = document.createElement('canvas');
        canvas.id = 'grafico_ctx';
        canvas.width = 400;
        canvas.height = 200;
        ctx.appendChild(canvas);
        
        const labels_trans = {
            'English': ['Goals For %', 'Goals Against %', 'WinRate %', 'Tournaments Won %'],
            'Español': ['Goles a favor %', 'Goles en contra %', 'Porcentaje de Victorias %', 'Torneos Ganados %'],
            'Català': ['Gols a favor %', 'Gols en contra %', 'Percentatge de Victòries %', 'Tornejos Guanyats %']
        };

        // Grafico del modulo de CHART.JS
        new Chart(canvas, {
            type: 'bar',
            data: {
                labels: labels_trans[language_conf],
                datasets: [{
                    label: info_user.username,
                    data: [me_gf_porc, me_ge_porc, user_info['user_stats'].winrate, me_tg_porc], // Los valores para el Perfil 1
                    backgroundColor: 'rgba(255, 99, 132, 0.2)',
                    borderColor: 'rgba(255, 99, 132, 1)',
                    borderWidth: 1
                }, {
                    label: item.username,
                    data: [friend_gf_porc, friend_ge_porc, data.winrate, friend_tg_porc], // Los valores para el Perfil 2
                    backgroundColor: 'rgba(54, 162, 235, 0.2)',
                    borderColor: 'rgba(54, 162, 235, 1)',
                    borderWidth: 1
                }]
            },
            options: {
                scales: {
                    y: {
                        beginAtZero: true,
                        ticks: {
                            color: 'white',
                            font: {
                                size: 14,
                                family: "'Press Start 2P', sans-serif"
                            }
                        }
                    },
                    x: {
                        ticks: {
                            color: 'white',
                            font: {
                                size: 14,
                                family: "'Press Start 2P', sans-serif"
                            }
                        }
                    }
                },
                plugins: {
                    legend: {
                        labels: {
                            color: 'white',
                            font: {
                                size: 14,
                                family: "'Press Start 2P', sans-serif"
                            }
                        }
                    }
                }
            }
        });

        const tableGames = document.getElementById('tableGames');

        // LIMPIAR TABLA
        while (tableGames.rows.length > 1)
            tableGames.deleteRow(1);

        const match_history = data.match_history.reverse();
        match_history.forEach(match => {
            const row = tableGames.insertRow();
            const cell1 = row.insertCell();
            const cell2 = row.insertCell();
            const cell3 = row.insertCell();
            const cell4 = row.insertCell();
            const cell5 = row.insertCell();
            cell1.textContent = match.winner_1;
            cell2.textContent = match.loser_1;
            cell3.textContent = match.mode;
            cell4.textContent = match.score;
            cell5.textContent = match.date;
        });

    });
}

// Agregar evento de clic a cada botón de los cientificos en la página USER
botones.forEach(function (boton) {
    boton.addEventListener('click', function () {
        // Obtener el ID del botón clicado
        const btnId = boton.id;
        let i = 0;

        // Verificar si el ID del botón existe en la lista de estados
        if (estados.hasOwnProperty(btnId)) {
            // Actualizar la interfaz
            for (let clave in estados)
            {
                if (clave === btnId)
                {
                    actualizarInterfaz(i);
                    const formData = new FormData();
                    formData.append('scientist', i);
                    fetch(`/api/change_scientist/?scientist=${i}`, {method:'GET', credentials: 'include', mode: 'cors'}).then(response => {
                        if (!response.ok)
                            throw new Error('Server petted...');
                        return (response.json());
                    })
                    .catch(error => console.error(error));
                    break ;
                }
                i++;
            }
        }
    });
});

//****************************************//


// **  PROGRESO USER Y FORMULARIOS ** //

// Boton de la moneda
document.getElementById('coin').addEventListener('click', () => {
    userProgress++;
    changeSection(userProgress);  
});

// CONTROLADOR DE FORMULARIOS PARA QUITARLE SU EVENTO POR DEFECTO DE RECARGAR
const forms = document.querySelectorAll('form');
forms.forEach(form => {
    form.addEventListener('submit', (e) => {e.preventDefault();});
});

// Formulario de LOGIN como INVITADO
const login_guest = document.getElementById('login_guest');
login_guest.addEventListener('click', () => {
    fetch('/api/register_guest/')
    .then(response => {
        if (!response.ok)
        {
            return response.json().then(errorData => {
                const status = errorData.status;
                if (language_conf == 'English')
                {
                    Promise.resolve().then(() => {
                        alert(status);
                    });
                    throw new Error(`${status}`);
                }
                // API que nos permite traducir los mensajes de error del back
                fetch('https://www.apertium.org/apy/translate', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: new URLSearchParams({
                        'langpair': 'en|' + language_key[language_conf],
                        'q': status
                    })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.responseStatus === 200) {
                        Promise.resolve().then(() => {
                            alert(`${data.responseData.translatedText}`);
                        });
                    } else {
                        console.error('Error in translation:', data.responseDetails);
                    }
                })
                .catch(error => console.error('Error:', error));
                throw new Error(`${status}`);
            });
        }
        return (response.json());
    }
    ).then(data => {
        userProgress = 2;
        changeSection(2);
        // Si consigue loguearse se activa la musica
        const backgroundMusic = document.getElementById('backgroundMusic');
        if (backgroundMusic.paused)
            play_Stop();
        localStorage.setItem('perfil', JSON.stringify(data));
        chargeData();
        fetch(`/api/change_language/?language=${language_key[language_conf]}`);
    }).catch(error => {
        console.log(error);
    });
});

// Formulario de LOGUEO (NORMAL y 42)
const formLog = document.getElementById('formLog');
formLog.addEventListener('submit', (e) => {
    const formData = new FormData();
    const uname = document.getElementById('formLogNick').value.trim();
    const pass = document.getElementById('formLogPass').value.trim();
    formData.append('username', uname);
    formData.append('password', pass);
    const param = {method: 'POST', credentials: 'include', mode: 'cors', body: formData};
    e.preventDefault();
    const buttonAction = e.submitter.getAttribute('data-action');

    if (buttonAction === 'normal')
    {
        userProgress = 2;
        fetch('/api/manage_login/', param)
        .then(response => {
            if (!response.ok)
            {
                return response.json().then(errorData => {
                    const status = errorData.status;
                    if (language_conf == 'English')
                    {
                        Promise.resolve().then(() => {
                            alert(status);
                        });
                        throw new Error(`${status}`);
                    }
                    fetch('https://www.apertium.org/apy/translate', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/x-www-form-urlencoded'
                        },
                        body: new URLSearchParams({
                            'langpair': 'en|' + language_key[language_conf],
                            'q': status
                        })
                    })
                    .then(response => response.json())
                    .then(data => {
                        if (data.responseStatus === 200) {
                            Promise.resolve().then(() => {
                                alert(`${data.responseData.translatedText}`);
                            });
                        } else {
                            console.error('Error in translation:', data.responseDetails);
                        }
                    })
                    .catch(error => console.error('Error:', error));
                    throw new Error(`${status}`);
                });
            }
            return (response.json());
        })
        .then(data => {
            document.getElementById('formLogNick').value = '';
            document.getElementById('formLogPass').value = '';
            userProgress = 2;
            changeSection(2);
            const backgroundMusic = document.getElementById('backgroundMusic');
            if (backgroundMusic.paused)
                play_Stop();
            localStorage.removeItem('perfil');
            localStorage.setItem('perfil', JSON.stringify(data));
            chargeData();
            fetch(`/api/get_language/`)
            .then(response => response.json())
            .then(data => {
                localStorage.setItem('language', key_language[data.status]);
                load_language(key_language[data.status], true);
            })
            .catch(error => console.error(error));
        })
        .catch(error => console.error(error));
    }
    else if (buttonAction === '42')
    {
        fetch('/api/get_api_id/')
        .then(response => response.json())
        .then(data => window.location.href = data.url)
        .catch(error => console.error(error));
    }
});

// Formulario de REGISTRO
const formReg = document.getElementById('formReg');
formReg.addEventListener('submit', async (e) => {
    const formData = new FormData();
    const uname = document.getElementById('fname').value.trim();
    const email = document.getElementById('femail').value.trim();
    const pass = document.getElementById('fpass').value.trim();
    const pass2 = document.getElementById('fpass2').value.trim();
    const ckTerms = document.getElementById('ckTerms');
    document.getElementById('femail').checked = false;
    // Los terminos y condiciones deben aceptarse
    if (!ckTerms.checked)
    {
        const trans_text = {
            'English': 'You must accept the terms and conditions',
            'Español': 'Debes aceptar los términos y condiciones',
            'Italiano': 'Devi accettare i termini e le condizioni'
        }
        Promise.resolve().then(() => {
            alert(trans_text[language_conf]);
        });
        return ;
    }
    formData.append('username', uname);
    formData.append('email', email);
    formData.append('password', pass);
    formData.append('password2', pass2);
    const param = {method: 'POST', credentials: 'include', mode: 'cors', body: formData};
    e.preventDefault();
    await fetch(`/api/register_user/`, param)
    .then(async (response) => {
        if (!response.ok)
        {
            return response.json().then(async  (errorData) => {
                const status = errorData.status;
                if (language_conf == 'English')
                {
                    Promise.resolve().then(() => {
                        alert(status);
                    });
                    throw new Error(`${status}`);
                }
                await fetch('https://www.apertium.org/apy/translate', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: new URLSearchParams({
                        'langpair': 'en|' + language_key[language_conf],
                        'q': status
                    })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.responseStatus === 200) {
                        Promise.resolve().then(() => {
                            alert(`${data.responseData.translatedText}`);
                        });
                    } else {
                        console.error('Error in translation:', data.responseDetails);
                    }
                })
                .catch(error => console.error('Error:', error));
                throw new Error(`${status}`);
            });
        }
        return (response.json());
    })
    .then(data => {
        // Limpiamos campos
        document.getElementById('fname').value = '';
        document.getElementById('femail').value = '';
        document.getElementById('fpass').value = '';
        document.getElementById('fpass2').value = '';
        userProgress = 2;
        changeSection(2);
        const backgroundMusic = document.getElementById('backgroundMusic');
        if (backgroundMusic.paused)
            play_Stop();
        localStorage.setItem('perfil', JSON.stringify(data));
        chargeData();
        fetch(`/api/change_language/?language=${language_key[language_conf]}`);
    }).catch(error => {
        console.log(error);
    });
});


// Formulario de AÑADIR AMIGO

var lastClickedButtonId = ''; // Para rastrear el ID del último botón clickeado para los amigos

document.getElementById('addFriend').addEventListener('click', function() {
    lastClickedButtonId = this.id; // Actualiza con el ID del botón clickeado
});

document.getElementById('removeFriend').addEventListener('click', function() {
    lastClickedButtonId = this.id; // Actualiza con el ID del botón clickeado
});

function ft_gestorFriend(friendName, endPoint)
{
    const formData = new FormData();
    document.getElementById('friendName').value = '';
    formData.append('username', friendName);
    const param = {method: 'POST', credentials: 'include', mode: 'cors', body: formData};
    fetch(endPoint, param).then(response => {
        if (response.ok)
            return (response.json());
        Promise.resolve().then(() => {
            alert('ERROR');
        });
    })
    .then(data => {
        if (data.status == 'USER NOT FOUND')
        {
            const text_error = {
                'English': 'User not found',
                'Español': 'Usuario no encontrado',
                'Català': 'Usuari no trobat'
            };
            Promise.resolve().then(() => {
                alert(text_error[language_conf]);
            });
            throw new Error(`Can't add Friend: ${data.status}`);
        }
        else if (data.status == 'Eres tu')
        {
            const text_error = {
                'English': 'You cannot add yourself as a friend',
                'Español': 'No te puedes añadir a ti mismo como amigo',
                'Català': 'No et pots afegir a tu mateix com a amic'
            };                
            Promise.resolve().then(() => {
                alert(text_error[language_conf]);
            });
            throw new Error(`Can't add Friend: ${data.status}`);
        }
        else
            refreshLista();
    })
    .catch(error => console.error(error));
}

const friendForm = document.getElementById('friendForm');
friendForm.addEventListener('submit', (e) => {
    const friendName = document.getElementById('friendName').value.trim();
    e.preventDefault();

    let endPoint = '/api/add_friend/';
    if (lastClickedButtonId === 'removeFriend')
        endPoint = '/api/delete_friend/?friend_name=' + friendName;

    ft_gestorFriend(friendName, endPoint);
});

// ************************* //

// ** FORMULARIOS DE USERS PARA CAMBIAR DATOS DEL USUARIO ** //

// Formulario para cambiar el NICK
const nickForm = document.getElementById('nickForm');
nickForm.addEventListener('submit', (e) => {
    const formData = new FormData();
    const new_username = document.getElementById('newNickName').value.trim();
    document.getElementById('newNickName').value = '';
    formData.append('new_username', new_username);
    const param = {method: 'POST', credentials: 'include', mode: 'cors', body: formData};
    e.preventDefault();
    fetch(`/api/change_username/`, param).then(response => {
        if (!response.ok)
        {
            return response.json().then(errorData => {
                const status = errorData.status;
                if (language_conf == 'English')
                {
                    Promise.resolve().then(() => {
                        alert(status);
                    });
                    throw new Error(`${status}`);
                }
                fetch('https://www.apertium.org/apy/translate', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: new URLSearchParams({
                        'langpair': 'en|' + language_key[language_conf],
                        'q': status
                    })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.responseStatus === 200) {
                        Promise.resolve().then(() => {
                            alert(`${data.responseData.translatedText}`);
                        });
                    } else {
                        console.error('Error in translation:', data.responseDetails);
                    }
                })
                .catch(error => console.error('Error:', error));
                throw new Error(`${status}`);
            });
        }
        return (response.json());
    })
    .then(() => refreshData())
    .catch(error => console.log(error));
});

// Formulario cambiar CORREO
const emailForm = document.getElementById('emailForm');
emailForm.addEventListener('submit', (e) => {
    const formData = new FormData();
    const new_email = document.getElementById('newEmail').value.trim();
    document.getElementById('newEmail').value = '';
    formData.append('new_email', new_email);
    const param = {method: 'POST', credentials: 'include', mode: 'cors', body: formData};
    e.preventDefault();
    fetch(`/api/change_email/`, param).then(response => {
        if (!response.ok)
        {
            return response.json().then(errorData => {
                const status = errorData.status;
                if (language_conf == 'English')
                {
                    Promise.resolve().then(() => {
                        alert(status);
                    });
                    throw new Error(`${status}`);
                }
                fetch('https://www.apertium.org/apy/translate', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: new URLSearchParams({
                        'langpair': 'en|' + language_key[language_conf],
                        'q': status
                    })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.responseStatus === 200) {
                        Promise.resolve().then(() => {
                            alert(`${data.responseData.translatedText}`);
                        });
                    } else {
                        console.error('Error in translation:', data.responseDetails);
                    }
                })
                .catch(error => console.error('Error:', error));
                throw new Error(`${status}`);
            });
        }
        return (response.json());
    })
    .then(() => refreshData())
    .catch(error => console.error(error));
});

// Formulario cambiar CONTRASEÑA
const passForm = document.getElementById('passForm');
passForm.addEventListener('submit', (e) => {
    const formData = new FormData();
    const new_password = document.getElementById('newPass').value.trim();
    formData.append('new_password', new_password);
    document.getElementById('newPass').value = '';
    const param = {method: 'POST', credentials: 'include', mode: 'cors', body: formData};
    e.preventDefault();
    fetch(`/api/change_password/`, param).then(response => {
        if (!response.ok)
        {
            return response.json().then(errorData => {
                const status = errorData.status;
                if (language_conf == 'English')
                {
                    Promise.resolve().then(() => {
                        alert(status);
                    });
                    throw new Error(`${status}`);
                }
                fetch('https://www.apertium.org/apy/translate', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: new URLSearchParams({
                        'langpair': 'en|' + language_key[language_conf],
                        'q': status
                    })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.responseStatus === 200) {
                        Promise.resolve().then(() => {
                            alert(`${data.responseData.translatedText}`);
                        });
                    } else {
                        console.error('Error in translation:', data.responseDetails);
                    }
                })
                .catch(error => console.error('Error:', error));
                throw new Error(`${status}`);
            });
        }
        return (response.json());
    }).then(() => {
        // Salimos para que tenga que volver a loguearse
        userProgress = -1;
        changeSection(1);
    }).catch(error => console.log(error));
});

// Boton para descargar el PDF con los datos del USUARIO
function f_downloadInfoUser()
{
    fetch('/api/data_pdf/')
    .then(response => {
        if (!response.ok) {
            const text_error = {
                'English': 'Download Info failed',
                'Español': 'Descarga de información fallida',
                'Català': 'Descàrrega d\'informació fallida'
            };
            Promise.resolve().then(() => {
                alert(text_error[language_conf]);
            });
            throw new Error(`Download Info failed`);
        }
        return response.blob();
    })
    .then(blob => {
        const pdfUrl = URL.createObjectURL(blob);
        window.open(pdfUrl, '_blank');
    })
    .catch(error => {
        console.log(error);
    });
}

// Boton para borrar USUARIO
function f_deleteAccount()
{
    // Promesa porque esperamos a que termine un PROMPT con la confirmacion del usuario
    Promise.resolve().then(() => {
        const message = prompt('Are you sure you want to delete your account? Type "yes" to confirm');
        if (message !== 'yes')
            return ;
        fetch('/api/delete_account/')
        .then(response => {
            if (!response.ok)
            {
                return response.json().then(errorData => {
                    const status = errorData.status;
                    if (language_conf == 'English')
                    {
                        Promise.resolve().then(() => {
                            alert(status);
                        });
                        throw new Error(`${status}`);
                    }
                    fetch('https://www.apertium.org/apy/translate', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/x-www-form-urlencoded'
                        },
                        body: new URLSearchParams({
                            'langpair': 'en|' + language_key[language_conf],
                            'q': status
                        })
                    })
                    .then(response => response.json())
                    .then(data => {
                        if (data.responseStatus === 200) {
                            Promise.resolve().then(() => {
                                alert(`${data.responseData.translatedText}`);
                            });
                        } else {
                            console.error('Error in translation:', data.responseDetails);
                        }
                    })
                    .catch(error => console.error('Error:', error));
                    throw new Error(`${status}`);
                });
            }
            return (response.json());
        })
        .then(() => {
            // Volvemos a la página de logueo
            userProgress = -1;
            changeSection(0);
        })
        .catch(error => console.error(error));
    });
}

// Boton LOGOUT para cerrar sesion del USUARIO
function f_logout() {
    userProgress = -1;
    const parameter = {method: 'GET', mode: 'cors', credentials: 'include' };
    fetch(`/api/manage_logout/`, parameter).then(response => {
        if (!response.ok)
        {
            return response.json().then(errorData => {
                const status = errorData.status;
                if (language_conf == 'English')
                {
                    Promise.resolve().then(() => {
                        alert(status);
                    });
                    throw new Error(`${status}`);
                }
                fetch('https://www.apertium.org/apy/translate', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: new URLSearchParams({
                        'langpair': 'en|' + language_key[language_conf],
                        'q': status
                    })
                })
                .then(response => response.json())
                .then(data => {
                    if (data.responseStatus === 200) {
                        Promise.resolve().then(() => {
                            alert(`${data.responseData.translatedText}`);
                        });
                    } else {
                        console.error('Error in translation:', data.responseDetails);
                    }
                })
                .catch(error => console.error('Error:', error));
                throw new Error(`${status}`);
            });
        }
        
        // Paramos la musica y borramos datos guardados del usuario
        const backgroundMusic = document.getElementById('backgroundMusic');
        if (!backgroundMusic.paused)
            play_Stop();
        changeSection(0);
        localStorage.clear();
        localStorage.setItem('sectionNumber', 0);
        localStorage.setItem('language', language_conf);
        return (response.json());

    }).then(() => localStorage.removeItem('perfil'))
    .catch(error => console.error(error));

    localStorage.removeItem('sectionNumber');
    localStorage.removeItem('selectedScientist');
}

// **************************** //

// ** LOGICA MENU ** //
document.querySelectorAll('#menu .nav-link').forEach(item => {
    item.addEventListener('click', function() {
        const sectionNo = this.getAttribute('data-no');
        if (sectionNo)
            changeSection(sectionNo);
        else
            play_Stop();
    });
});

// ** FUNCION PARA CONTROLAR LA MUSICA ** //
function play_Stop() {
    const easterEgg = document.getElementById('easterEgg');
    if (!easterEgg.paused)
        easterEgg.pause();
    const backgroundMusic = document.getElementById('backgroundMusic');
    const playStop = document.getElementById('btnPlayStop');
    const text_mute = {
        'English': 'MUTE',
        'Español': 'MUTEAR',
        'Català': 'MUTE'
    };
    const text_unmute = {
        'English': 'UNMUTE',
        'Español': 'DESMUTEAR',
        'Català': 'UNMUTE'
    };

    if (backgroundMusic.paused) {
        backgroundMusic.play();
        backgroundMusic.volume = 0.2;
        playStop.textContent = text_mute[language_conf];
    }
    else
    {
        playStop.textContent = text_unmute[language_conf];
        backgroundMusic.pause();
    }
}

// ** TERMS & COND ** //
const term_cond = document.getElementById('term_cond');
term_cond.addEventListener('click', () => changeSection(6));


// ** Funcion que controla INTERFAZ de torneo local ** //
export function changeSectionGameLocal(p1, p2, p3, p4, fp1=null, fp2=null)
{
    const navigationLinks = document.querySelectorAll('.navbar-nav p');
    navigationLinks.forEach(link => {
        link.classList.add('disabled');
    });

    const canvasGame = document.getElementById('game');
    const selHome = document.getElementById('homegame');
    const sel1 = document.getElementById('1v1');
    const tournament = document.getElementById('tournament');

    const renderer = canvasGame.firstElementChild;
    if (renderer instanceof HTMLCanvasElement) {
        const context = renderer.getContext('webgl') || renderer.getContext('experimental-webgl');
        if (context) {
            const extension = context.getExtension('WEBGL_lose_context');
            if (extension) {
                extension.loseContext();
            }
        }
        canvasGame.removeChild(renderer);
    }
    const data = localStorage.getItem('data-game');
    const data_game = JSON.parse(data);
    sel1.style.display = 'none';
    selHome.style.display = 'none';
    tournament.style.display = 'block';

    // CUADRO DE TORNEO
    document.getElementById('player1S1').textContent = p1.nick;
    document.getElementById('player2S1').textContent = p2.nick;
    document.getElementById('player1S2').textContent = p3.nick;
    document.getElementById('player2S2').textContent = p4.nick;
    document.getElementById('player1F').textContent = fp1 ? fp1.nick : '...';
    document.getElementById('player2F').textContent = fp2 ? fp2.nick : '...';

    // MATCH ACTUAL
    const scientist = ['charles-darwin.gif', 'curie.gif', 'hawking.gif', 'newton.gif', 'einstein.gif', 'pitagoras.gif'];
    document.getElementById('nickMatchP1').textContent = data_game.player1;
    document.getElementById('nickMatchP2').textContent = data_game.player2;
    document.getElementById('imgMatchP1').src = '/gif/' + scientist[data_game.spell_p1];
    document.getElementById('imgMatchP2').src = '/gif/flop/' + scientist[data_game.spell_p2];

    scriptGame = document.createElement('script');
    scriptGame.src = 'game/1v1/script.js';
    if (document.getElementById('init_text'))
        document.getElementById('init_text').remove();
    searching = setTimeout(() => {
        document.body.appendChild(scriptGame);
        s4mode = 1;
        changeSection(4);
    }, 10000);
}

function ft_infoTour()
{
    const selHome = document.getElementById('homegame');
    const sel1 = document.getElementById('1v1');
    const tournament = document.getElementById('tournament');
    const data = localStorage.getItem('data-game');
    const data_game = JSON.parse(data);
    const tour_id = data_game['tour_id'];
    const select_idioma = document.getElementById('select_idioma');
    select_idioma.style.display = 'none';
    fetch(`/api/info_tour/?tour_id=${tour_id}`)
    .then( response => {
        if (response.ok)
            return (response.json());
        throw new Error('Error al cargar esquema del torneo');
    })
    .then(
        data => {
            sel1.style.display = 'none';
            selHome.style.display = 'none';
            tournament.style.display = 'block';
            const data_user = JSON.parse(localStorage.getItem('perfil'));
            const user_info = JSON.parse(data_user['data']);
            const my_nick = user_info.user_info.username;

            // CUADRO DE TORNEO
            document.getElementById('player1S1').textContent = data.semifinal1.nickname1;
            document.getElementById('player2S1').textContent = data.semifinal1.nickname2;
            document.getElementById('player1S2').textContent = data.semifinal2.nickname1;
            document.getElementById('player2S2').textContent = data.semifinal2.nickname2;
            document.getElementById('player1F').textContent = '...';
            document.getElementById('player2F').textContent = '...';
            if (data.final)
            {
                if (data.semifinal1.nickname1 == data.final.nickname1 || data.semifinal1.nickname2 == data.final.nickname1)
                {
                    document.getElementById('player1F').textContent = data.final.nickname1;
                    document.getElementById('player2F').textContent = data.final.nickname2;
                }
                else
                {
                    document.getElementById('player2F').textContent = data.final.nickname1;
                    document.getElementById('player1F').textContent = data.final.nickname2;
                }
            }

            // MATCH ACTUAL
            const nickMatchP1 = document.getElementById('nickMatchP1');
            const nickMatchP2 = document.getElementById('nickMatchP2');
            const imgMatchP1 = document.getElementById('imgMatchP1');
            const imgMatchP2 = document.getElementById('imgMatchP2');
            const scientist = ['charles-darwin.gif', 'curie.gif', 'hawking.gif', 'newton.gif', 'einstein.gif', 'pitagoras.gif'];
            if (data.final)
            {
                nickMatchP1.textContent = data.final.nickname1;
                nickMatchP2.textContent = data.final.nickname2;
                imgMatchP1.src = '/gif/' + scientist[data.final.spell_p1];
                imgMatchP2.src = '/gif/flop/' + scientist[data.final.spell_p2];
            }
            else if (my_nick == data.semifinal1.player1 || my_nick == data.semifinal1.player2)
            {
                nickMatchP1.textContent = data.semifinal1.nickname1;
                nickMatchP2.textContent = data.semifinal1.nickname2;
                imgMatchP1.src = '/gif/' + scientist[data.semifinal1.spell_p1];
                imgMatchP2.src = '/gif/flop/' + scientist[data.semifinal1.spell_p2];
            }
            else if (my_nick == data.semifinal2.player1 || my_nick == data.semifinal2.player2)
            {
                nickMatchP1.textContent = data.semifinal2.nickname1;
                nickMatchP2.textContent = data.semifinal2.nickname2;
                imgMatchP1.src = '/gif/' + scientist[data.semifinal2.spell_p1];
                imgMatchP2.src = '/gif/flop/' + scientist[data.semifinal2.spell_p2];
            }
        }
    )
    .catch((e) => console.error(e));
}


// ** FUNCION PRINCIPAL QUE SE ENCARGA DE CAMBIAR LAS PANTALLAS ** //
export function changeSection(sectionNumber, shouldPushState = true) {

    // Añadimos la página actual al historial
    if (shouldPushState)
        history.pushState({page: sectionNumber, user_prog: userProgress, mode: s4mode}, "", "/");

    // Oculta todas las secciones
    const allSections = document.querySelectorAll('.cd-hero-slider li');
    allSections.forEach(section => {
        if (section.classList.contains('pages'))
            section.style.display = 'none';
    });

    // Cancelamos cualquier Interval o Timeout
    if (searching)
        clearInterval(searching);

    // Muestra la sección correspondiente al número seleccionado
    const selectedSection = document.getElementById(`section${sectionNumber}`);
    if (selectedSection) {
        const canvasGame = document.getElementById('game');
        if (s4mode == 0 || sectionNumber != 4)
        {
            const renderer = canvasGame.firstElementChild;
            if (renderer instanceof HTMLCanvasElement) {
                const context = renderer.getContext('webgl') || renderer.getContext('experimental-webgl');
                if (context) {
                    const extension = context.getExtension('WEBGL_lose_context');
                    if (extension) {
                        extension.loseContext();
                    }
                }
                canvasGame.removeChild(renderer);
            }
        }
        const select_idioma = document.getElementById('select_idioma');
        select_idioma.style.display = 'block';
        if (sectionNumber == 4)
        {
            const selHome = document.getElementById('homegame');
            const sel1 = document.getElementById('1v1');
            const tournament = document.getElementById('tournament');
            const init_text = document.getElementById('init_text');
            if (init_text)
                document.getElementById('init_text').remove();
            switch (s4mode)
            {
                case 0:
                    sel1.style.display = 'none';
                    selHome.style.display = 'block';
                    tournament.style.display = 'none';
                    btnCancelQueue.style.display = 'none';
                    fetch('/api/is_in_queue/')
                    .then(response => {
                        if (response.ok)
                            return (response.json());
                        Promise.resolve().then(() => {
                            alert('ERROR');
                        });
                    })
                    .then(data => {
                        const in_queue = document.getElementById('in_queue');
                        in_queue.style.display = (data.status == 'user is in queue')? 'block' : 'none';
                        btnCancelQueue.style.display = (data.status == 'user is in queue')? 'block' : 'none';
                    });
                    break ;
                case 1:
                    sel1.style.display = 'block';
                    selHome.style.display = 'none';
                    tournament.style.display = 'none';
                    break ;
                case 2:
                    const renderer = canvasGame.firstElementChild;
                    if (renderer instanceof HTMLCanvasElement) {
                        const context = renderer.getContext('webgl') || renderer.getContext('experimental-webgl');
                        if (context) {
                            const extension = context.getExtension('WEBGL_lose_context');
                            if (extension) {
                                extension.loseContext();
                            }
                        }
                        canvasGame.removeChild(renderer);
                    }
                    if (shouldPushState == false)
                        break ;
                    ft_infoTour();
                    break ;
            }
        }
        if (sectionNumber == 5 && shouldPushState == true)
        {
            const param = {method: 'GET', mode: 'cors', credentials: 'include' };
            fetch(`/api/all_data/`, param).then(response => {
                if (response.ok)
                    return (response.json());
                Promise.resolve().then(() => {
                    alert('ERROR');
                });
            }).then(data => {
                localStorage.removeItem('perfil');
                localStorage.setItem('perfil', JSON.stringify(data));
                refreshLista(true);
            });
        }

        selectedSection.style.display = 'block';

        const navigationLinks = document.querySelectorAll('.navbar-nav .nav-link');
        navigationLinks.forEach(link => {
        const linkSectionNumber = parseInt(link.getAttribute('data-no'));
        if (linkSectionNumber == sectionNumber) {
            link.parentElement.classList.add('active');
        } else {
            link.parentElement.classList.remove('active');
        }
        });


        if (userProgress > 1 && s4mode == 0)
        {
            const navigationLinks = document.querySelectorAll('.navbar-nav p');
            navigationLinks.forEach(link => {
                link.classList.remove('disabled');
            });
        }
        
        if (userProgress == -1 || s4mode > 0)
        {
            const navigationLinks = document.querySelectorAll('.navbar-nav p');
            navigationLinks.forEach(link => {
                link.classList.add('disabled');
            });
            if (userProgress == -1)
            userProgress = 0;
            const backgroundMusic = document.getElementById('backgroundMusic');
            if (!backgroundMusic.paused)
                play_Stop();
        }
        localStorage.setItem('sectionNumber', sectionNumber);
    }
}

// ** CONTROLADOR EVENTO DE BACK AND FORWARD ** //
window.addEventListener('popstate', function(event) {
    const state = event.state;
    if (state) {
        if (state.page >= 2 && userProgress < 2)
        {
            userProgress = -1;
            changeSection(0, false);
            return ;
        }
        if (state.page < 2 && userProgress >= 2) {
            changeSection(2, false);
            return ;
        }
        userProgress = state.user_prog;
        s4mode = state.mode;
        if (s4mode > 0)
            s4mode = 0;
        changeSection(state.page, false);
    }
});

