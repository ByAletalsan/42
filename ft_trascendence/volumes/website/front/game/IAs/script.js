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
      darwingIA = false,
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
      // Sound var
      listener, sound, sound_gol, sound_powerup,
      score = {
        player1: 0,
        player2: 0
      };

    var status = 0; //0 (WAITING), 1 (PLAYING), 2 (ENDING)
    var iReady = false;
    var data_game;
    
    var darwingP1 = false;
    var spell_ready = true;
    var spell_ready_ia = true;
    var cooldown_time = 10 * 1000;
    var spellID = 0, spellIDIA = 0;
    var stunIA = false, stunMe = false;
    var skyTexture = null;
    var fieldTexture = null;
  
  function startBallMovement() {
    var direction = Math.random() > 0.5 ? -1 : 1;
    ball.$velocity = {
      x: 0,
      z: direction * 40
    };
    ball.$stopped = false;
    ball.position.set(Math.random() > 0.5? -10 : 10,0,0);
  }
  
  function powerUpIA()
  {
    const scientist = ['charles-darwin.gif', 'curie.gif', 'hawking.gif', 'newton.gif', 'einstein.gif', 'pitagoras.gif'];
    const scientistP2 = document.getElementById('charPlayer2');
    scientistP2.src = 'gif/spells/flop/' + scientist[spellIDIA];
    setTimeout(() => scientistP2.src = 'gif/flop/' + scientist[spellIDIA], 1500);
    sound_powerup.pause();
    sound_powerup.currentTime = 0;
    sound_powerup.play();
    switch (spellIDIA)
    {
      case 0: // pw_size
        paddle2.scale.set(2,1,1);
        darwingIA = true;
        setTimeout(() => {
          paddle2.scale.set(1,1,1);
          darwingIA = false;
        }, 2500);
        break;
      case 1: // pw_invisible
        ball.visible = false;
        setTimeout(() => ball.visible = true, 750);
        break;
      case 2: // pw_dash
        ball.position.z += 100;
        ball.position.x = Math.random() * (WIDTH - 100) * ((Math.random() > 0.5)? 1 : -1);
        max_height = Math.random() * (1.5 - 0.5) + 0.5;
        break;
      case 3: // pw_stun
        stunMe = true;
        setTimeout(() => stunMe = false, 500);
        break;
      case 4: // pw_speed
        ball.$velocity.z *= 2;
        setTimeout(() => ball.$velocity.z *= 0.5, 500);
        break;
      case 5: // pw_wall
        ball.$velocity.x *= -1;
        break;
    }
  }

  var xFinal = 0;
  var counter = 0;

  function processCpuPaddle() {
    var ballPos = ball.position,
        cpuPos = paddle2.position;
    
    if (!stunIA)
    {
      // Calcular posicion final
      if (counter >= 60 && ball.$velocity.z < 0)
      {
        const tiempo = (Math.abs(cpuPos.z - ballPos.z) / (-ball.$velocity.z == 0 ? -1 : -ball.$velocity.z));
        xFinal = ballPos.x + ball.$velocity.x * tiempo;
        xFinal = xFinal > (FIELD_WIDTH / 2) ? (FIELD_WIDTH / 2) - (xFinal - (FIELD_WIDTH / 2)) : xFinal;
        xFinal = xFinal < (-FIELD_WIDTH / 2) ? ((-FIELD_WIDTH / 2) + (-FIELD_WIDTH / 2 - xFinal)) : xFinal;
        counter = 0;
      }
      if (cpuPos.x + 55 < xFinal)
        cpuPos.x += 10;
      else if (cpuPos.x - 55 > xFinal)
        cpuPos.x -= 10;
      
      // Limites
      if ((cpuPos.x - PADDLE_WIDTH / 2) < (-FIELD_WIDTH / 2))
        cpuPos.x = (-FIELD_WIDTH / 2) + PADDLE_WIDTH / 2;
      else if ((cpuPos.x + PADDLE_WIDTH / 2) > (FIELD_WIDTH / 2))
        cpuPos.x = (FIELD_WIDTH / 2) - PADDLE_WIDTH / 2;
    }
    if (spell_ready_ia)
    {
      //Power-Up
      if (ball.position.z < HEIGHT / 2) // desde mi campo
      {
        if ((spellIDIA != 0 && ball.$velocity.z > 0 && ball.position.z - paddle2.position.z > HEIGHT) || (spellIDIA == 0))
        {
          spell_ready_ia = false;
          document.getElementById('powerUpP2').className = 'texto-rojo';
          powerUpIA();
          setTimeout(() => 
          {
            spell_ready_ia = true;
            darwingIA = false;
            document.getElementById('powerUpP2').className = 'texto-verde';
          }, cooldown_time);
        }
      }
    }
    counter++;
  }
  
  function processBallMovement() {
    if(!ball.$velocity) {
      startBallMovement();
    }
    
    if(ball.$stopped) {
      return;
    }
    
    updateBallPosition();
    
    if(isSideCollision()) {
      ball.$velocity.x *= -1;
    }
    
    if(isPaddle1Collision()) {
      hitBallBack(paddle1);
    }
    
    if(isPaddle2Collision()) {
      hitBallBack(paddle2);
    }
    
    if(isPastPaddle1()) {
      scoreBy('player2');
    }
    
    if(isPastPaddle2()) {
      scoreBy('player1');
    }
  }
  
  function isPastPaddle1() {
    return ball.position.z > paddle1.position.z + 100;
  }
  
  function isPastPaddle2() {
    return ball.position.z < paddle2.position.z - 100;
  }
  
  function updateBallPosition() {
    var ballPos = ball.position;
    
    //update the ball's position.
    ballPos.x += ball.$velocity.x;
    ballPos.z += ball.$velocity.z;
    
    // add an arc to the ball's flight. Comment this out for boring, flat pong.
    ballPos.y = -((ballPos.z - 1) * ((ballPos.z - 1) * max_height) / 5000) + 435 * max_height;
  }
  
  function isSideCollision() {
    var ballX = ball.position.x,
        halfFieldWidth = FIELD_WIDTH / 2;
      return (ballX - BALL_RADIUS < -halfFieldWidth && ball.$velocity.x < 0) || (ballX + BALL_RADIUS > halfFieldWidth && ball.$velocity.x > 0);
  }
  
  function hitBallBack(paddle) {
    ball.$velocity.x = (ball.position.x - paddle.position.x) / 5; 
    ball.$velocity.z *= -1;
    max_height = Math.random() * (1.5 - 0.5) + 0.5;
    // Sound paddle
    sound.play();
  }
  
  function isPaddle2Collision() {
    return ball.position.z - BALL_RADIUS - 40 <= paddle2.position.z + (PADDLE_HEIGHT / 2) && ball.position.z + BALL_RADIUS >= paddle2.position.z - (PADDLE_HEIGHT / 2) &&
        isBallAlignedWithPaddle(paddle2) && ball.$velocity.z < 0;
  }
  
  function isPaddle1Collision() {
    return ball.position.z + BALL_RADIUS + 40 >= paddle1.position.z - (PADDLE_HEIGHT / 2) && ball.position.z - BALL_RADIUS <= paddle1.position.z + (PADDLE_HEIGHT / 2) &&
        isBallAlignedWithPaddle(paddle1) && ball.$velocity.z > 0;
  }
  
  function isBallAlignedWithPaddle(paddle) {
    var halfPaddleWidth = PADDLE_WIDTH / 2,
        paddleX = paddle.position.x,
        ballX = ball.position.x;
    // pw_size
    if (darwingP1 && paddle === paddle1)
      halfPaddleWidth = PADDLE_WIDTH;
    if (darwingIA && paddle === paddle2)
      halfPaddleWidth = PADDLE_WIDTH;
    return ballX + BALL_RADIUS > paddleX - halfPaddleWidth && 
        ballX - BALL_RADIUS < paddleX + halfPaddleWidth;
  }
  
  function scoreBy(playerName) {
      addPoint(playerName);
      updateScoreBoard();
      stopBall();
      setTimeout(reset, 2000);
  }
  
  function updateScoreBoard() {
      scoreP1.innerText = score.player1;
      scoreP2.innerText = score.player2;
  }
  
  function stopBall(){ 
    ball.$stopped = true;
  }
  
  function addPoint(playerName){
    score[playerName]++;
    // Sound gol
    if (sound_gol.isPlaying)
      sound_gol.stop();
    sound_gol.play();
  }
  
  function startRender(){
    running = true;
    render();  
  }
  
  function stopRender() {
    running = false;
  }

  function powerUp()
  {
    const scientist = ['charles-darwin.gif', 'curie.gif', 'hawking.gif', 'newton.gif', 'einstein.gif', 'pitagoras.gif'];
    const scientistP1 = document.getElementById('charPlayer1');
    scientistP1.src = 'gif/spells/' + scientist[spellID];
    setTimeout(() => scientistP1.src = 'gif/' + scientist[spellID], 1500);
    sound_powerup.pause();
    sound_powerup.currentTime = 0;
    sound_powerup.play();
    switch (spellID)
    {
      case 0: // pw_size
        paddle1.scale.set(2,1,1);
        darwingP1 = true;
        setTimeout(() => 
          {
            paddle1.scale.set(1,1,1);
            darwingP1 = false;
          }, 2500);
        break;
      case 1: // pw_invisible
        ball.visible = false;
        setTimeout(() => ball.visible = true, 750);
        break;
      case 2: // pw_dash
        ball.position.z -= 100;
        ball.position.x = Math.random() * WIDTH * ((Math.random() > 0.5)? 1 : -1);
        max_height = Math.random() * (1.5 - 0.5) + 0.5;
        break;
      case 3: // pw_stun
        stunIA = true;
        setTimeout(() => stunIA = false, 500);
        break;
      case 4: // pw_speed
        ball.$velocity.z *= 2;
        setTimeout(() => ball.$velocity.z *= 0.5, 500);
        break;
      case 5: // pw_wall
        ball.$velocity.x *= -1;
        break;
    }
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
    {
      event.preventDefault();
      if (!iReady) iReady = true;
      else if (spell_ready)
      {
        //Power-Up
        if (ball.position.z > HEIGHT / 2) // desde mi campo
        {
          spell_ready = false;
          document.getElementById('powerUpP1').className = 'texto-rojo';
          powerUp();
          setTimeout(() => 
          {
            spell_ready = true;
            document.getElementById('powerUpP1').className = 'texto-verde';
          }, cooldown_time);
        }
      }
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

  const fpsInterval = 1000 / 40; // Calcula el intervalo para 60 FPS
  let then = performance.now();

  function render(now) {
    if(running) {
      requestAnimationFrame(render);
      const init_text = document.getElementById('init_text');
      switch(status)
      {
        case 0:
          init_text.textContent = start_text[language];
          if (iReady)
          {
            init_text.textContent = '';
            status = 1;
          }
          break;
        case 1:
          const deltaTime = now - then;
          if (deltaTime > fpsInterval) {
            then = now - (deltaTime % fpsInterval);
            processBallMovement();
            processCpuPaddle();
            movePlayer();
          }
          if (score.player1 > 2 || score.player2 > 2)
            status = 2;
          break;
          case 2:
            if (score.player1 > score.player2)
              init_text.textContent = win_text[language];
            else
              init_text.textContent = lose_text[language];
            //Desactivamos navegacion
            const navigationLinks = document.querySelectorAll('.navbar-nav a');
            navigationLinks.forEach(link => {
              link.classList.remove('disabled');
            });
            var formData = new FormData();
            var winner1 = (score.player1 > score.player2)? data_game['player1'] : data_game['player2'];
            var loser1 = (score.player1 < score.player2)? data_game['player1'] : data_game['player2'];
            formData.append('mode', 'IAs');
            formData.append('score', score.player1 + '-' + score.player2);
            formData.append('winner1', winner1);
            formData.append('loser1', loser1);
            fetch(`/api/match_result/`, {method:'POST', credentials: 'include', mode: 'cors', body: formData})
            .then(response => {
                if (!response.ok)
                    throw new Error('NO FUE POSIBLE MANDAR RESULTADOS...');
                return (response.json());
            }).catch(e => console.error(e));
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
            window.postMessage('endGame', window.location.href + '/last_front/game/p1');
            status = 3;
          break;
      }
      if (renderer)
        renderer.render(scene, camera);
    }
  }
  
  function reset() {
    ball.position.set(0,0,0);
    camera.position.x = paddle1.position.x = 0;
    paddle2.position.x = 0;
    ball.$velocity = null;
    counter = 0;
    xFinal = 0;
  }
  
  function init() {

    //Desactivamos navegacion
    const navigationLinks = document.querySelectorAll('.navbar-nav a');
    navigationLinks.forEach(link => {
        link.classList.add('disabled');
    });

    const data = localStorage.getItem('data-game');
    data_game = JSON.parse(data);

    data_game['player1'] = data_game['player1'] == '' ? 'JoseSanc' : data_game['player1'];
		data_game['player2'] = data_game['player2'] == '' ? 'JoseSanc' : data_game['player2'];

    spellID = parseInt(data_game['spell_p1']);
    spellIDIA = parseInt(data_game['spell_p2']);

    container = document.getElementById('game');

    // Ver si el container ya tiene un canvas hijo
    var canvas = container.querySelector('canvas');
    if (canvas) return ;
    
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
    paddle1 = addPaddle1(data_game['spell_p1']);
    paddle1.position.z = FIELD_LENGTH / 2;
    paddle2 = addPaddle2(data_game['spell_p2']);
    paddle2.position.z = -FIELD_LENGTH / 2;
    
    var ballGeometry = new THREE.SphereGeometry(BALL_RADIUS, 16, 16),
        ballMaterial = new THREE.MeshLambertMaterial({ color: 0xCC0000 });
    ball = new THREE.Mesh(ballGeometry, ballMaterial);
    scene.add(ball);
    
    camera.lookAt(ball.position);
    
    mainLight = new THREE.HemisphereLight(0xFFFFFF, 0x003300);
    scene.add(mainLight);

    //Texto al empezar
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
    
    camera.lookAt(ball.position);


    // Sonidos
    listener = new THREE.AudioListener();
    camera.add(listener);
    sound = new THREE.Audio(listener);
    sound_gol = new THREE.Audio(listener);
    sound_powerup = new THREE.Audio(listener);
    const scientist = ['charles-darwin.mp3', 'curie.mp3', 'hawking.mp3', 'newton.m4a', 'einstein.mp3', 'pitagoras.mp3'];
    music = new THREE.Audio(listener);
    const audioLoader = new THREE.AudioLoader();
    audioLoader.load('../audio/game/' + scientist[data_game['spell_p1']], function(buffer) {
      music.setBuffer(buffer);
      music.setVolume(0.4);
      music.setLoop(true);
      music.play();
    });
    audioLoader.load('../audio/game/powerup.m4a', function(buffer) {
      sound_powerup.setBuffer(buffer);
      sound_powerup.setVolume(0.5);
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

    updateScoreBoard();
    startRender();
    
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
    if (leftKeyPressed && paddle1.position.x - 30 - PADDLE_WIDTH > -WIDTH && !stunMe)
      // Mover hacia la izquierda
      camera.position.x = paddle1.position.x -= 10;
    else if (rightKeyPressed && paddle1.position.x + 30 + PADDLE_WIDTH < WIDTH && !stunMe)
      // Mover hacia la derecha
      camera.position.x = paddle1.position.x += 10;
  }

  window.addEventListener('resize', function () {
    container = document.getElementById('game');
    if (renderer)
      renderer.setSize(game.offsetWidth, game.offsetHeight);
  });

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

})(window, window.document, window.THREE);
