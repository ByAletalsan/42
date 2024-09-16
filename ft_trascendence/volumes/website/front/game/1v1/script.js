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
		listener, sound, sound_gol,
		score = {
		  player1: 0,
		  player2: 0
		};
  
	  var status = 0; //0 (WAITING), 1 (PLAYING), 2 (ENDING)
	  var iReady = false;
	  var data_game;
	
	function startBallMovement() {
	  var direction = Math.random() > 0.5 ? -1 : 1;
	  ball.$velocity = {
		x: 0,
		z: direction * 50
	  };
	  ball.$stopped = false;
	  ball.position.set(0,0,0);
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
	//   ballPos.y = -((ballPos.z - 1) * (ballPos.z - 1) / 5000) + 435;
	}
	
	function isSideCollision() {
	  var ballX = ball.position.x,
		  halfFieldWidth = FIELD_WIDTH / 2;
		return (ballX - BALL_RADIUS < -halfFieldWidth && ball.$velocity.x < 0) || (ballX + BALL_RADIUS > halfFieldWidth && ball.$velocity.x > 0);
	}
	
	function hitBallBack(paddle) {
	  ball.$velocity.x = (ball.position.x - paddle.position.x) / 5; 
	  ball.$velocity.z *= -1;
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
  
	var upKeyPressed = false;
	var downKeyPressed = false;
	var wKeyPressed = false;
	var sKeyPressed = false;
  
	document.addEventListener('keydown', onKeyDown, false);
	document.addEventListener('keyup', onKeyUp, false);
  
	function onKeyDown(event) {
	  if (event.key === 'ArrowUp') {
		if (status == 1)
		  event.preventDefault();
		upKeyPressed = true;
	  } else if (event.key === 'ArrowDown') {
		if (status == 1)
		  event.preventDefault();
		downKeyPressed = true;
	  }
	  if (event.key === 'w' || event.key === 'W') {
		if (status == 1)
		  event.preventDefault();
		wKeyPressed = true;
	  } else if (event.key === 's' || event.key === 'S') {
		if (status == 1)
		  event.preventDefault();
		sKeyPressed = true;
	  }
	  if (event.keyCode === 32)
		event.preventDefault();
	  if (!iReady && event.keyCode === 32)
		iReady = true;
	}
	
	function onKeyUp(event) {
	  if (event.key === 'ArrowUp') {
		upKeyPressed = false;
	  } else if (event.key === 'ArrowDown') {
		downKeyPressed = false;
	  }
	  if (event.key === 'w' || event.key === 'W') {
		wKeyPressed = false;
	  } else if (event.key === 's' || event.key === 'S') {
		sKeyPressed = false;
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
			  movePlayer();
			}
			if (score.player1 > 2 || score.player2 > 2)
			  status = 2;
			break;
			case 2:
				if (data_game.tour)
					init_text.textContent = 'WIN ' + ((score.player1 > score.player2) ? data_game.tour[0].nick : data_game.tour[1].nick);
				else if (score.player1 > score.player2)
					init_text.textContent = win_text[language];
				else
					init_text.textContent = lose_text[language];
				//Desactivamos navegacion
				const navigationLinks = document.querySelectorAll('.navbar-nav a');
				navigationLinks.forEach(link => {
				link.classList.remove('disabled');
				});
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
				const data_tour_1v1 = localStorage.getItem('data-tour-1v1');
        		const data = JSON.parse(data_tour_1v1);
				if (data_game.tour && (!data.win1 || !data.win2))
				{
					if (data.win1 && !data.win2)
						data.win2 = score.player1 > score.player2 ? data_game.tour[0] : data_game.tour[1];
					if (!data.win1)
						data.win1 = score.player1 > score.player2 ? data_game.tour[0] : data_game.tour[1];
					localStorage.setItem('data-tour-1v1', JSON.stringify(data));
					window.postMessage('endGameTour1v1', window.location.href + '/front/game/p1');
				}
				else
					window.postMessage('endGame', window.location.href + '/front/game/p1');
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
	
		container = document.getElementById('game');

		// Ver si el container ya tiene un canvas hijo
		var canvas = container.querySelector('canvas');
		if (canvas) return ;
		
		renderer = new THREE.WebGLRenderer();
		renderer.setSize(game.offsetWidth, game.offsetHeight);
		renderer.setClearColor(0x000000, 1);
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
		
		var fieldGeometry = new THREE.BoxGeometry(FIELD_WIDTH, 5, FIELD_LENGTH),
			fieldMaterial = new THREE.MeshLambertMaterial({ color: 0x000000 });
		field = new THREE.Mesh(fieldGeometry, fieldMaterial);
		field.position.set(0, -50, 0);

		// BORDES
		var edgesGeometry = new THREE.EdgesGeometry(new THREE.BoxGeometry(FIELD_WIDTH, 5, FIELD_LENGTH));
		var edgesMaterial = new THREE.LineBasicMaterial({ color: 0xffffff });
		var edgesMesh = new THREE.LineSegments(edgesGeometry, edgesMaterial);
		scene.add(edgesMesh);
		edgesMesh.position.copy(field.position);

		// LINEA EN MEDIO
		var edgesGeometry = new THREE.EdgesGeometry(new THREE.BoxGeometry(FIELD_WIDTH, 5, 0));
		var edgesMaterial = new THREE.LineBasicMaterial({ color: 0xffffff });
		var edgesMesh = new THREE.LineSegments(edgesGeometry, edgesMaterial);
		scene.add(edgesMesh);
		edgesMesh.position.copy(field.position);
	  
		scene.add(field);
		paddle1 = addPaddle1();
		paddle1.position.z = FIELD_LENGTH / 2;
		paddle2 = addPaddle2();
		paddle2.position.z = -FIELD_LENGTH / 2;
		
		var ballGeometry = new THREE.SphereGeometry(BALL_RADIUS, 16, 16),
			ballMaterial = new THREE.MeshLambertMaterial({ color: 0xFFFFFF });
		ball = new THREE.Mesh(ballGeometry, ballMaterial);
		scene.add(ball);
		
		camera.lookAt(ball.position);
		camera.position.set(0, 3000, 0);
		camera.rotation.x = -Math.PI / 2;
		camera.rotation.z = Math.PI / 2;
		
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
		
		// Sonidos
		listener = new THREE.AudioListener();
		camera.add(listener);
		sound = new THREE.Audio(listener);
		sound_gol = new THREE.Audio(listener);
		music = new THREE.Audio(listener);
		const audioLoader = new THREE.AudioLoader();
		audioLoader.load('../audio/game/main.mp3', function(buffer) {
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

		updateScoreBoard();
		startRender();
		
		// renderer.domElement.style.cursor = 'none';
	}
	
	function addPaddle1() {
	  var paddleGeometry = new THREE.BoxGeometry(PADDLE_WIDTH, PADDLE_HEIGHT, 10),
		  paddleMaterial = new THREE.MeshLambertMaterial({ color: 0xFFFFFF }),
		  paddle = new THREE.Mesh(paddleGeometry, paddleMaterial);
	  scene.add(paddle);
	  return paddle;
	}
  
	function addPaddle2() {
	  var paddleGeometry = new THREE.BoxGeometry(PADDLE_WIDTH, PADDLE_HEIGHT, 10),
		  paddleMaterial = new THREE.MeshLambertMaterial({ color: 0xFFFFFF }),
		  paddle = new THREE.Mesh(paddleGeometry, paddleMaterial);
	  scene.add(paddle);
	  return paddle;
	}
	
	function movePlayer() {
	  if (wKeyPressed && paddle1.position.x - PADDLE_WIDTH > -WIDTH) {
		paddle1.position.x -= 10;
	  } else if (sKeyPressed && paddle1.position.x + PADDLE_WIDTH < WIDTH) {
		paddle1.position.x += 10;
	  }
	  if (upKeyPressed && paddle2.position.x - PADDLE_WIDTH > -WIDTH) {
		paddle2.position.x -= 10;
	  } else if (downKeyPressed && paddle2.position.x + PADDLE_WIDTH < WIDTH) {
		paddle2.position.x += 10;
	  }
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
		// Recorre todos los objetos de la escena
		scene.traverse(function (object) {
			if (object instanceof THREE.Mesh) {
				// Disponer de la geometría del mesh
				if (object.geometry) {
					object.geometry.dispose();
				}
				
				// Disponer de los materiales del mesh
				if (object.material) {
					if (Array.isArray(object.material)) {
						// Si el material es un array, recorre y dispone de cada material
						object.material.forEach(material => {
							if (material.map) {
								material.map.dispose();
							}
							material.dispose();
						});
					} else {
						// Si el material no es un array, dispone directamente
						if (object.material.map) {
							object.material.map.dispose();
						}
						object.material.dispose();
					}
				}
			}
		});
	
		// Elimina el campo y la pelota, si existen
		if (field) {
			field.geometry.dispose();
			field.material.dispose();
		}
		if (ball) {
			ball.geometry.dispose();
			ball.material.dispose();
		}
	
		// Elimina el canvas y el renderer
		if (renderer) {
			renderer.dispose();
		}
	
		// Elimina la escena misma
		scene = null;
	}
	
	  
  
	init();
  
  })(window, window.document, window.THREE);
  