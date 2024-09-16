// console.clear();

(function (window, document, THREE){
  // "constants"... 
  var WIDTH = 700,
      HEIGHT = 500,
      VIEW_ANGLE = 45,
      ASPECT = WIDTH / HEIGHT,
      NEAR = 0.1,
      FAR = 10000,
      FIELD_WIDTH = 1200,
      FIELD_LENGTH = 3000,
      BALL_RADIUS = 20,
      PADDLE_WIDTH = 200,
      PADDLE_HEIGHT = 30,
      
      //get the scoreboard element.
      scoreP1 = document.getElementById('scoreP1'),
      scoreP2 = document.getElementById('scoreP2'),
      
      //declare members.
      container, renderer, camera, mainLight,
      scene, ball, paddle1, paddle2, field, running,
      max_height,
      language = localStorage.getItem('language') || 'English',
      start_text = {
        'English': 'Press "SPACE" to start!',
        'Español': 'Presiona "ESPACIO" para comenzar!',
        'Català': 'Prem "ESPAI" per començar!'
      },
      win_text = {
        'English': 'YOU WON!',
        'Español': '¡GANASTE!',
        'Català': 'HAS GUANYAT!'
      },
      lose_text = {
        'English': 'YOU LOST!',
        'Español': '¡PERDISTE!',
        'Català': 'HAS PERDUT!'
      },
      waiting_text = {
        'English': 'Waiting for the opponent...',
        'Español': 'Esperando al oponente...',
        'Català': 'Esperant a l\'oponent...'
      },
      // Sound var
      listener, sound, sound_gol,
      score = {
        player1: 0,
        player2: 0
      };


  const ip = window.location.href.split('/')[2]
  let url = `wss://${ip}/wss/ws/myapp/`
  var grupo = 'grupo-1';
  var status = 0; //0 (WAITING), 1 (PLAYING), 2 (ENDING)
  var enemyReady = false, iReady = false;
  var socket = null;
  var data_game;
  var skyTexture = null;
  var fieldTexture = null;

  function sendData(data)
  {
    if (socket && socket.readyState === WebSocket.OPEN)
    {
      socket.send(JSON.stringify({
        'comando': 'send_data',
        'grupo': grupo,
        'message': data
      }));
    }
  }

  function sendStart()
  {
    const data = {
      'comando': 'ready_player2'
    };
    sendData(data);
  }
  
  function updateBallPosition() {
    var ballPos = ball.position;
    
    //update the ball's position.
    if (ball.$velocity)
    {
      ballPos.x += ball.$velocity.x;
      ballPos.z += ball.$velocity.z;
    }
    
    // add an arc to the ball's flight. Comment this out for boring, flat pong.
    ballPos.y = -((ballPos.z - 1) * ((ballPos.z - 1) * max_height) / 5000) + 435 * max_height;
  }
  
  function startRender(){
    running = true;
    render();  
  }

  var leftKeyPressed = false;
  var rightKeyPressed = false;

  document.addEventListener('keydown', onKeyDown, false);
  document.addEventListener('keyup', onKeyUp, false);

  function onKeyDown(event) {
    if (event.key === 'ArrowUp' || event.key === 'ArrowDown')
      event.preventDefault();
    if (event.key === 'ArrowLeft') {
      if (status == 1)
        event.preventDefault();
      leftKeyPressed = true;
    } else if (event.key === 'ArrowRight') {
      if (status == 1)
        event.preventDefault();
      rightKeyPressed = true;
    }
    if (event.keyCode === 32)
      event.preventDefault();
    if (!iReady && event.keyCode === 32)
    {
      sendStart();
      iReady = true;
    }
  }
  
  function onKeyUp(event) {
    if (event.key === 'ArrowLeft') {
      leftKeyPressed = false;
    } else if (event.key === 'ArrowRight') {
      rightKeyPressed = false;
    }
    if (event.keyCode === 32)
      event.preventDefault();
  }
  
  function sendPosPlayer2()
  {
    const data = {
      'comando': 'move_player2',
      'player2': {
        'pos_x': paddle1.position.x
      }
    }
    sendData(data);
  }

  const fpsInterval = 1000 / 40; // Calcula el intervalo para 60 FPS
  let then = performance.now();

  function render(now) {
    if(running) {
      requestAnimationFrame(render);
      const init_text = document.getElementById('init_text');
      switch(status)
      {
        case 0:
          if (iReady && !enemyReady)
          {
            init_text.textContent = waiting_text[language];
            sendStart();
          }
          if (iReady && enemyReady)
          {
            init_text.textContent = '';
            status = 1;
          }
          if (score.player1 > 2 || score.player2 > 2)
            status = 2;
          break;
        case 1:
          const deltaTime = now - then;
          if (deltaTime > fpsInterval) {
            then = now - (deltaTime % fpsInterval);
            sendPosPlayer2();
            updateBallPosition();
            movePlayer();
          }
          if (score.player1 > 2 || score.player2 > 2)
            status = 2;
          break;
          case 2:
            if (score.player1 < score.player2)
              init_text.textContent = win_text[language];
            else
              init_text.textContent = lose_text[language];
            //Desactivamos navegacion
            const navigationLinks = document.querySelectorAll('.navbar-nav a');
            navigationLinks.forEach(link => {
              link.classList.remove('disabled');
            });
            if (score.player2 == 51)
            {
              var formData = new FormData();
              var winner1 = (score.player1 > score.player2)? data_game['player1'] : data_game['player2'];
              var loser1 = (score.player1 < score.player2)? data_game['player1'] : data_game['player2'];
              formData.append('mode', data_game['mode']);
              formData.append('score', score.player1 + '-' + score.player2);
              formData.append('winner1', winner1);
              formData.append('loser1', loser1);
              fetch(`/api/match_result/`, {method:'POST', credentials: 'include', mode: 'cors', body: formData})
              .then(response => {
                  if (!response.ok)
                      throw new Error('NO FUE POSIBLE MANDAR RESULTADOS...');
                  return (response.json());
              }).catch(e => console.error(e));
            }
            setTimeout(2000, () => {socket.close(); socket = null;});
            try {
              if (music)
                music.stop();
            }
            catch
            {
              console.log("No se pudo parar la música");
            }
            if (renderer) {
              disposeScene(scene);
              renderer.dispose();
              renderer = null;
            }
            window.postMessage((data_game['tour_id'] && (score.player1 < score.player2) && (data_game['mode'] != 'tour_final'))? 'endGameTour' : 'endGame', window.location.href + '/last_front/game/p2');
            status = 3;
          break;
      }
      if (renderer)
        renderer.render(scene, camera);
    }
  }
  
  async function init() {

    //Desactivamos navegacion
    const navigationLinks = document.querySelectorAll('.navbar-nav a');
    navigationLinks.forEach(link => {
        link.classList.add('disabled');
    });

    //Creo conexion
    const data = await localStorage.getItem('data-game');
    data_game = JSON.parse(data);
    grupo = data_game['gameID'];
    socket = new WebSocket(url); // Reemplaza 'tu-servidor' por tu URL o dirección IP


    // Evento cuando se abre la conexión
    socket.onopen = function(event) {
        // Mensaje para unirse a un grupo específico (por ejemplo, 'grupo-1')
        socket.send(JSON.stringify({
            'comando': 'unirse_grupo',
            'grupo': data_game['gameID'],
            'player': data_game['player2']
        }));
    };

    // Manejo de mensajes entrantes
    socket.onmessage = function(event) {
      // Procesar el mensaje recibido desde el servidor
      const data = JSON.parse(event.data).message;
      if (data.comando == 'move_player1')
        paddle2.position.set(-data.player1.pos_x, 0, paddle2.position.z);
      else if (data.comando == 'change_ball')
      {
        ball.$velocity = {
          x: -data.ball.vel_x,
          z: -data.ball.vel_z
        }
        ball.$stopped = data.ball.stop;
        ball.position.set(-data.ball.pos_x, data.ball.pos_y, -data.ball.pos_z);
        max_height = data.ball.max_height;
      }
      else if (data.comando == 'sound_paddle')
      {
        // Sound paddle
        sound.play();
      }
      else if (data.comando == 'change_score')
      {
        score = {
          player1: data.score.player1,
          player2: data.score.player2
        };
        scoreP1.innerText = score.player1;
        scoreP2.innerText = score.player2;
        ball.position.set(0,0,0);
        camera.position.x = paddle1.position.x = 0;
        paddle2.position.x = 0;
        ball.$velocity = null;
        // Sound gol
        if (sound_gol.isPlaying)
          sound_gol.stop();
        sound_gol.play();
      }
      else if (data.comando == 'ready_player1')
        enemyReady = true;
      else if (data.comando == 'disconnect' && status != 3)
        scoreP2.innerText = score.player2 = 51;
    };

    container = document.getElementById('game');
    
    // Ver si el container ya tiene un canvas hijo
    var canvas = container.querySelector('canvas');
    if (canvas) 
      return ;

    renderer = new THREE.WebGLRenderer();
    renderer.setSize(game.offsetWidth, game.offsetHeight);
    renderer.setClearColor(0x9999BB, 1);
    renderer.domElement.style.zIndex = 0;
    renderer.domElement.style.minHeight = '500px';
    renderer.domElement.id = 'canvas_game';
    container.appendChild(renderer.domElement);
    canvas = renderer.domElement;

    // Centrar canvas
    var elementTop = canvas.offsetTop;
    var elementHeight = canvas.offsetHeight;
    var windowHeight = window.innerHeight;
    var scrollTo = elementTop + elementHeight / 2 - windowHeight / 2 - 110;
    window.scrollTo({
        top: scrollTo,
        behavior: 'smooth'
    });
    
    camera = new THREE.PerspectiveCamera(VIEW_ANGLE, ASPECT, NEAR, FAR);
    camera.position.set(0, 100, FIELD_LENGTH / 2 + 500);
    
    scene = new THREE.Scene();
    scene.add(camera);
    
    // Cargar la textura del cielo
    var skyTextureLoader = new THREE.TextureLoader();
    skyTexture = skyTextureLoader.load('./srcs/fondo.jpg');
    skyTexture.wrapS = skyTexture.wrapT = THREE.RepeatWrapping;
    skyTexture.repeat.set(1, 1);

    // Crear el material con la textura del cielo
    var skyMaterial = new THREE.MeshBasicMaterial({
        map: skyTexture,
        side: THREE.BackSide
    });
    var skyGeometry = new THREE.BoxGeometry(10000, 8000, 10000);
    var skyBox = new THREE.Mesh(skyGeometry, skyMaterial);

    // Añadir el cielo a la escena
    scene.add(skyBox);


    var fieldGeometry = new THREE.BoxGeometry(FIELD_WIDTH, 5, FIELD_LENGTH);

    // Cargar la textura del suelo
    var fieldLoader = new THREE.TextureLoader();
    fieldTexture = fieldLoader.load('./srcs/suelo.jpg');
    
    fieldTexture.wrapS = fieldTexture.wrapT = THREE.RepeatWrapping;
    fieldTexture.repeat.set(1, 1);
    
    var fieldMaterial = new THREE.MeshBasicMaterial({
      map: fieldTexture,
      side: THREE.BackSide
    });

    field = new THREE.Mesh(fieldGeometry, fieldMaterial);
    field.position.set(0, -50, 0);
    
    scene.add(field);
    paddle1 = addPaddle1(data_game['spell_p2']);
    paddle1.position.z = FIELD_LENGTH / 2;
    paddle2 = addPaddle2(data_game['spell_p1']);
    paddle2.position.z = -FIELD_LENGTH / 2;
    
    var ballGeometry = new THREE.SphereGeometry(BALL_RADIUS, 16, 16),
        ballMaterial = new THREE.MeshLambertMaterial({ color: 0xCC0000 });
    ball = new THREE.Mesh(ballGeometry, ballMaterial);
    scene.add(ball);
    
    camera.lookAt(ball.position);
    
    mainLight = new THREE.HemisphereLight(0xFFFFFF, 0x003300);
    scene.add(mainLight);

    //Texto al empezar
    if (document.getElementById('init_text') == null)
    {
      let messageBox = document.createElement('p');
      messageBox.style.zIndex = 0;
      messageBox.id = 'init_text';
      messageBox.style.position = 'fixed';
      messageBox.textContent = start_text[language];
      messageBox.style.fontSize = '25px';
      messageBox.style.color = 'white';
      messageBox.style.top = '50%';
      messageBox.style.width = '100%';
      messageBox.style.textAlign = 'center';

      // APPEND TO BODY
      body = document.getElementsByTagName('body')[0];
      body.appendChild(messageBox);
    }
    else
    {
      let messageBox = document.getElementById('init_text');
      messageBox.textContent = start_text[language];
    }
    
    camera.lookAt(ball.position);
      
    scoreP1.innerText = score.player1;
    scoreP2.innerText = score.player2;

    // Sonidos
    listener = new THREE.AudioListener();
    camera.add(listener);
    sound = new THREE.Audio(listener);
    sound_gol = new THREE.Audio(listener);
    const scientist = ['charles-darwin.mp3', 'curie.mp3', 'hawking.mp3', 'newton.m4a', 'einstein.mp3', 'pitagoras.mp3'];
    music = new THREE.Audio(listener);
    const audioLoader = new THREE.AudioLoader();
    audioLoader.load('../audio/game/' + scientist[data_game['spell_p2']], function(buffer) {
      music.setBuffer(buffer);
      music.setVolume(0.4);
      music.setLoop(true);
      music.play();
    });
    audioLoader.load('../audio/game/paddle.mp3', function(buffer) {
      sound.setBuffer(buffer);
      sound.setVolume(0.5);
    });
    audioLoader.load('../audio/game/gol.m4a', function(buffer) {
      sound_gol.setBuffer(buffer);
      sound_gol.setVolume(0.5);
    });

    const select_idioma = document.getElementById('select_idioma');	
		select_idioma.style.display = 'none';

    max_height = 1;

    startRender();

    setTimeout(() => {
      if (status == 0)
      {
        if (iReady)
          score.player2 = 51;
        else
          score.player1 = 51;
        status = 2;
      }
    }, 15000);
    
    // renderer.domElement.style.cursor = 'none';
  }
  
  const color_scientist = [0x42FF00, 0xCE30F1, 0xFF7C00, 0xFF0000, 0x00FFE0, 0x002EFF];

  function addPaddle1(n) {
    var paddleGeometry = new THREE.BoxGeometry(PADDLE_WIDTH, PADDLE_HEIGHT, 10),
        paddleMaterial = new THREE.MeshLambertMaterial({ color: color_scientist[n] }),
        paddle = new THREE.Mesh(paddleGeometry, paddleMaterial);
    scene.add(paddle);
    return paddle;
  }

  function addPaddle2(n) {
    var paddleGeometry = new THREE.BoxGeometry(PADDLE_WIDTH, PADDLE_HEIGHT, 10),
        paddleMaterial = new THREE.MeshLambertMaterial({ color: color_scientist[n] }),
        paddle = new THREE.Mesh(paddleGeometry, paddleMaterial);
    scene.add(paddle);
    return paddle;
  }
  
  function movePlayer() {
    if (leftKeyPressed && paddle1.position.x - 30 - PADDLE_WIDTH > -WIDTH) {
      // Mover hacia la izquierda
      camera.position.x = paddle1.position.x -= 10;
    } else if (rightKeyPressed && paddle1.position.x + 30 + PADDLE_WIDTH < WIDTH) {
      // Mover hacia la derecha
      camera.position.x = paddle1.position.x += 10;
    }
  }

  window.addEventListener('resize', function () {
    container = document.getElementById('game');
    if (renderer)
      renderer.setSize(game.offsetWidth, game.offsetHeight);
  });

  // Controlamos reload y back history
  window.addEventListener('beforeunload', () => socket.close());
  window.addEventListener('popstate', () => {
    running = false;
    try {
      if (music)
        music.stop();
    }
    catch
    {
      console.log("No se pudo parar la música");
    }
    if (renderer) {
      disposeScene(scene);
      renderer.dispose();
      renderer = null;
    }
    if (socket)
      socket.close();
    socket = null;
    window.postMessage('endGameBack', window.location.href + '/last_front/game/p1');
  });

  function disposeScene(scene) {
    scene.traverse(function (object) {
        if (object instanceof THREE.Mesh) {
            if (object.geometry) {
                object.geometry.dispose();
            }
            if (object.material) {
                if (object.material instanceof THREE.MeshBasicMaterial || object.material instanceof THREE.MeshLambertMaterial) {
                    object.material.dispose();
                } else if (Array.isArray(object.material)) {
                    object.material.forEach(material => material.dispose());
                }
            }
        }
    });

    // Eliminar texturas cargadas manualmente
    if (skyTexture) {
        skyTexture.dispose();
    }
    if (fieldTexture) {
        fieldTexture.dispose();
    }

    // Eliminar la escena misma
    scene = null;
  }

  init();
  // init();
})(window, window.document, window.THREE);
