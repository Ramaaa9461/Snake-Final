#include "gameManager.h"

void main() //Punto de entrada 
{
	hideCursor(); //Apago el cursor	
	initializeConsoleColors(); //Inicializo el setup de colores

	Init(); 

	Update();
}

void Init()
{
	//Seteo las variables en 0
	score = 0;

	direction.x = 0;
	direction.y = 0;

	bodyLinks = minBodyLinks;

	srand(time(NULL));

	for (int i = 0; i < maxBodyLinks; i++) // Se crea la serpiente
	{
		if (i == 0) // Entra solo en la 1ra iteracion
		{
			int x = rand() % (getScreenWidth() - 3) + 2;
			int y = rand() % (getScreenHeight() / 2) + getScreenHeight() / 3 + 1;

			// Creo la cabeza en una posicion aleatoria
			snake[i] = CreateEntity(playerChart, x, y); 
		}
		else
		{
			// Creo el resto del cuerpo y le seteo el dibujo
			snake[i] = CreateEntity(tailChart, 0, 0); 
		}
	}

	//Creo un alimeto
	SpawnFood();
}

void Input()
{
	char input = '\0';

	if (_kbhit())
	{
		input = (char)_getch();

		switch (tolower(input)) //Paso a minuscula el input para evitar que no detecte matusculas
		{
		case 'w':
			direction.y = -1;
			direction.x = 0;
			break;
		case 'a':
			direction.y = 0;
			direction.x = -1;
			break;
		case 's':
			direction.y = 1;
			direction.x = 0;
			break;
		case 'd':
			direction.y = 0;
			direction.x = 1;
			break;
	
		}
	}
}

void DrawGameHud()
{
	//Dibujo el titulo del juego centrado
	drawTitle(); 

	//Dubijo un marco de juego
	drawFrame(minWidth, minHeight, maxWidth, maxHeight, 5); 

	//Dibujo en pantalla el puntaje
	goToCoordinates(getScreenWidth() / 2 - 15, getScreenHeight() - 2);
	cout << "Score: " << score << "		" << "High Score: " << highScore << endl;

	goToCoordinates(0, 0);
	setCurrentColor(5);
	cout << fire;

	//Aparece solo al principio del juego y desaparece cuando te empezas a mover
	if (direction.x == 0 && direction.y == 0) 
	{
		setCurrentColor(7);
		goToCoordinates(getScreenWidth() / 2 - 17, getScreenHeight() / 2 + 3);
		cout << "Your snake can grow up to ";
		setCurrentColor(5);
		cout << maxBodyLinks;
		setCurrentColor(7);
		cout << " links" << endl;
		setCurrentColor(1);
	}
	else
	{
		goToCoordinates(getScreenWidth() / 2 - 17, getScreenHeight() / 2 + 3);
		cout << "                                   ";
	}

}

void DrawEntities()
{

	// Dibujo el alimento en pantalla
	Draw(food.position.x, food.position.y, food.chart, 3);

	for (int i = bodyLinks - 1; i >= 0; i--) //Un for empezando desde la cola
	{
		if (i > 0) // Entra en todas las posiciones luego de la cabeza y las borra
		{
			if (i == bodyLinks - 1)
			{
				Draw(snake[i].position.x, snake[i].position.y, ' ', 0);
			}

			// Se Actualiza las posiciones del cuerpo
		
			snake[i].position = snake[i - 1].position;
			
		}
		else
		{
			// Cuando quede solo la cabeza la borro
			if (bodyLinks == 1)
			{
				Draw(snake[0].position.x, snake[0].position.y, ' ', 0);
			}

			// actualizo la posicion de la cabeza
			MoveEntity(snake[0], direction);

			//Limito su posicion con los marcos y la hago reaparecer del otro lado
			LimitsWithTheScreen(snake[0], minWidth + 1, maxWidth - 1, minHeight + 1, maxHeight - 1);
		}

		// Se dibuja al personaje con la posicion ya actualizada
		Draw(snake[i].position.x, snake[i].position.y, snake[i].chart, 5);
	}
}

void Update()
{
	do
	{
		switch (gameState)
		{
		case GameState::MENU:

			MainMenu(); //Dibuja el menu

			break;
		case GameState::GAMEPLAY:

			Input(); //Toma el input del juegador

			DrawGameHud(); //Dibuja el marco de juego, el titulo y el marcador

			DrawEntities(); //Dibuja a la serpiente y al alimento

			Collision(); //Chequea la colision en la serpiente contra si misma o contra el alimiento

			Sleep(frameTime); //Simula el delta time para limitar los frames por segundo

			break;
		case GameState::GAMEOVER:

			GameOver(); //Dibuja la pantalla de game over

			gameState = GameState::MENU;

			break;
		}

	} while (playing);
}

void MainMenu()
{
	system("cls");

	int input = 0;

	// Dibuja el titulo
	drawTitle();

	//Dibuja el puntaje
	goToCoordinates(getScreenWidth() / 2 - 15, 10);
	cout << "Score: " << score << "		" << "High Score: " << highScore << endl;

	// Dibuja las opciones del menu
	drawMenuOptions(10, 12, 5);

	std::cin >> input;

	switch (input)
	{
	case 1: // Te lleva al GamePlay
		gameState = GameState::GAMEPLAY;
		system("cls");
		break;

	case 2: // Te lleva al Tutorial
		system("cls");

		drawTutorial(5, 10, 5,5,5);

		system("pause");
		break;

	case 3: //Termina el gameLoop y termina el programa
		playing = false;
		break;
	}
}

void SpawnFood() //Se spawnea de forma random el alimento
{
	food = CreateEntity(foodChart, rand() % (getScreenWidth() - 4) + 3, rand() % (getScreenHeight() / 2 + 1) + getScreenHeight() / 3 + 2);
}

void Collision()
{
	//Chequea las colisiones contra el alimento
	if (food.position.x == snake[0].position.x && food.position.y == snake[0].position.y)
	{
		//agrega un eslabon mas a la serpiente
		AddBodyLinks();

		//Suma 10 puntos en cada llamada
		AddScore();

		//Spawnea otro alimento
		SpawnFood();
	}

	//Chequea la colision entre la propia serpiente
	for (int i = 1; i < bodyLinks; i++) //empieza en 1, no cuenta la cabeza
	{
		//Compara la primera posicion contra el resto de la serpiente
		if (snake[0].position.x == snake[i].position.x && snake[0].position.y == snake[i].position.y)
		{
			gameState = GameState::GAMEOVER;
		}
	}
}

void GameOver()
{
	system("cls");

	//Dibuja el texto ascii de "Game over"
	drawGameOver(10, 1, 7);

	//Muestra el puntaje con el terminaste la partida
	goToCoordinates(getScreenWidth() /2 - 10, 12);
	setCurrentColor(5);
	cout << "your final score is " << score << endl;

	//Muestra un agradecimiento por jugar Y lo concatena con el titulo del juego en ascii
	goToCoordinates(getScreenWidth() / 2 - 9, 18);
	setCurrentColor(2);
	cout << "Thanks for playing " << endl;

	drawTitle(getScreenWidth() / 2 - 28, 20, 2);

	setCurrentColor(1);

	//Dibuja mi nombre XD y luego llama al System Pause
	goToCoordinates(getScreenWidth() - 24, getScreenHeight() - 1);
	cout << "Create by Ramiro Guzman" << endl;

	goToCoordinates(0, getScreenHeight() - 1);
	system("pause");

	Init(); // Reinicio los parametros para luego reiniciar el partido
}

void AddScore()
{
	score += 10; //Suma en 10 el score

	if (score > highScore) //Si el score es mayor al highscore lo iguala al score
	{
		highScore = score;
	}
}

void AddBodyLinks()
{
	bodyLinks++;

	if (bodyLinks >= maxBodyLinks) //No permite el bodyLink exceda el maxBodyLink
	{
		bodyLinks = maxBodyLinks;
	}
}

void drawTitle(int x, int y, int color)//Dibuja el titulo en con los parametros que les llega
{
	setCurrentColor(color);

	goToCoordinates(x, y);
	cout << " ::::::::  ::::    :::     :::     :::    ::: :::::::::: " << endl;
	goToCoordinates(x, y+1);
	cout << ":+:    :+: :+:+:   :+:   :+: :+:   :+:   :+:  :+:        " << endl;
	goToCoordinates(x, y+2);
	cout << "+:+        :+:+:+  +:+  +:+   +:+  +:+  +:+   +:+        " << endl;
	goToCoordinates(x, y+3);
	cout << "+#++:++#++ +#+ +:+ +#+ +#++:++#++: +#++:++    +#++:++#   " << endl;
	goToCoordinates(x, y+4);
	cout << "       +#+ +#+  +#+#+# +#+     +#+ +#+  +#+   +#+        " << endl;
	goToCoordinates(x, y+5);
	cout << "#+#    #+# #+#   #+#+# #+#     #+# #+#   #+#  #+#        " << endl;
	goToCoordinates(x, y + 6);
	cout << " ########  ###    #### ###     ### ###    ### ########## " << endl;

	setCurrentColor(1);

	//Pagina usada para crear el texto en ascii:
	//https://www.messletters.com/es/big-text/ / alligator2 -> (Fuente)
}
void drawTitle() //Dibuja el titulo arriba y en el centro de la pantalla en color naranja 
{
	setCurrentColor(4);

	int x = getScreenWidth() / 2 - 28;
	int y = 1;

	goToCoordinates(x, y);
	cout << " ::::::::  ::::    :::     :::     :::    ::: :::::::::: " << endl;
	goToCoordinates(x, y + 1);
	cout << ":+:    :+: :+:+:   :+:   :+: :+:   :+:   :+:  :+:        " << endl;
	goToCoordinates(x, y + 2);
	cout << "+:+        :+:+:+  +:+  +:+   +:+  +:+  +:+   +:+        " << endl;
	goToCoordinates(x, y + 3);
	cout << "+#++:++#++ +#+ +:+ +#+ +#++:++#++: +#++:++    +#++:++#   " << endl;
	goToCoordinates(x, y + 4);
	cout << "       +#+ +#+  +#+#+# +#+     +#+ +#+  +#+   +#+        " << endl;
	goToCoordinates(x, y + 5);
	cout << "#+#    #+# #+#   #+#+# #+#     #+# #+#   #+#  #+#        " << endl;
	goToCoordinates(x, y + 6);
	cout << " ########  ###    #### ###     ### ###    ### ########## " << endl;


	setCurrentColor(1);

	//Pagina usada para crear el texto en ascii:
	//https://www.messletters.com/es/big-text/ / alligator2 -> (Fuente)
}

void drawFrame(int x1, int y1, int x2, int y2, int color)
{
	setCurrentColor(color);

	//Dibujos las esquinas         ╔ ╚ ╗ ╝
	goToCoordinates(x1, y1);
	cout << (char)LEFT_UP;
	goToCoordinates(x2, y1);
	cout << (char)RIGHT_UP;
	goToCoordinates(x2, y2);
	cout << (char)RIGHT_DW;
	goToCoordinates(x1, y2);
	cout << (char)LEFT_DW;

	//Completo el borde superior y el inferior   ═
	for (int i = x1 + 1; i < x2; i++)
	{
		goToCoordinates(i, y1);
		cout << (char)LINE_HOR;
		goToCoordinates(i, y2);
		cout << (char)LINE_HOR;
	}

	//Completo el borde Izquierdo y el derecho   ║
	for (int i = y1 + 1; i < y2; i++)
	{
		goToCoordinates(x2, i);
		cout << (char)LINE_VER;
		goToCoordinates(x1, i);
		cout << (char)LINE_VER;
	}

	setCurrentColor(1);
}

void drawMenuOptions(int x, int y, int color) //Dibujo las opciones del menu con los parametros que llegan
{
	setCurrentColor(color);

	goToCoordinates(x, y);
	cout << "  __        __     ____  __      __    _  _ " << endl;
	goToCoordinates(x, y + 1);
	cout << " /  )   ___ \\ \\   (  _ \\(  )    /__\\  ( \\/ )" << endl;
	goToCoordinates(x, y + 2);
	cout << "  )(   (___) > >   )___/ )(__  /(__)\\  \\  / " << endl;
	goToCoordinates(x, y + 3);
	cout << " (__)       /_/   (__)  (____)(__)(__) (__) " << endl;
	
	y += 5;

	goToCoordinates(x, y);
	cout << " ___         __     ____  __  __  ____  _____  ____  ____    __    __   " << endl;
	goToCoordinates(x, y + 1);
	cout << "(__ \\    ___ \\ \\   (_  _)(  )(  )(_  _)(  _  )(  _ \\(_  _)  /__\\  (  )  " << endl;
	goToCoordinates(x, y + 2);
	cout << " / _/   (___) > >    )(   )(__)(   )(   )(_)(  )   / _)(_  /(__)\\  )(__ " << endl;
	goToCoordinates(x, y + 3);
	cout << "(____)       /_/    (__) (______) (__) (_____)(_)\\_)(____)(__)(__)(____)" << endl;

	y += 5;

	goToCoordinates(x, y);
	cout << "(__ )   ___ \\ \\   ( ___)( \\/ )(_  _)(_  _)" << endl;
	goToCoordinates(x, y + 1);
	cout << " (_ \\  (___) > >   )__)  )  (  _)(_   )(  " << endl;
	goToCoordinates(x, y + 2);
	cout << "(___/       /_/   (____)(_/\\_)(____) (__) " << endl;

	setCurrentColor(1);
	goToCoordinates(25, getScreenHeight() - 1);
	cout << "Press 1 to go to the game, 2 to go to the tutorial and 3 to exit" << endl;
}

void drawTutorial(int x, int y, int color1, int color2, int color3)//Dibujo el tutorial
{
	drawTitle();

	setCurrentColor(color1);
	goToCoordinates(0, y);
	cout << "Tutorial: " << endl;
	goToCoordinates(x, y + 1);
	cout << " Your character is a snake, as he feeds his tail will grow." << endl;
	goToCoordinates(x, y + 2);
	cout << " When you get to the sides your Snake appears at the other end of " << endl;
	goToCoordinates(x, y + 3);
	cout << " the screen, the only way to lose is to eat your own tail !!" << endl;
	
	y += 5;
	setCurrentColor(color2);
	
	goToCoordinates(0, y);
	cout << "Controls:" << endl;
	goToCoordinates(x, y + 1);
	cout << " Your sepiente will start in a random space on the screen, " << endl;
	goToCoordinates(x, y + 2);
	cout << " and will remain static until you indicate a direction in" << endl;
	goToCoordinates(x, y + 3);
	cout << " which to move! Once it started to move it was impossible " << endl;
	goToCoordinates(x, y + 4);
	cout << " to stop it !!     " << endl;

	y += 6;
	setCurrentColor(color3);

	goToCoordinates(0, y);
	cout << "Movement keys:" << endl;
	goToCoordinates(x, y + 1);
	cout << "W " << (char)26 << " you move up. " << endl;
	goToCoordinates(x, y + 2);
	cout << "A " << (char)26 << " you move to the left." << endl;
	goToCoordinates(x, y + 3);
	cout << "S " << (char)26 << " you move down." << endl;
	goToCoordinates(x, y + 4);
	cout << "D " << (char)26 << " you move to the right." << endl;

	setCurrentColor(1);
	goToCoordinates(0, getScreenHeight() - 1);
}

void drawFire(int x, int y, int color)
{
	setCurrentColor(color);

	goToCoordinates(x, y);
	cout << " ::::::::      :::     ::::    ::::  ::::::::::         ::::::::  :::     ::: :::::::::: :::::::::  " << endl;
	goToCoordinates(x, y + 1);
	cout << ":+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:               :+:    :+: :+:     :+: :+:        :+:    :+: " << endl;
	goToCoordinates(x, y + 2);
	cout << "+:+         +:+   +:+  +:+ +:+:+ +:+ +:+               +:+    +:+ +:+     +:+ +:+        +:+    +:+ " << endl;
	goToCoordinates(x, y + 3);
	cout << ":#:        +#++:++#++: +#+  +:+  +#+ +#++:++#          +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:  " << endl;
	goToCoordinates(x, y + 4);
	cout << "+#+   +#+# +#+     +#+ +#+       +#+ +#+               +#+    +#+  +#+   +#+  +#+        +#+    +#+ " << endl;
	goToCoordinates(x, y + 5);
	cout << "#+#    #+# #+#     #+# #+#       #+# #+#               #+#    #+#   #+#+#+#   #+#        #+#    #+# " << endl;
	goToCoordinates(x, y + 6);
	cout << " ########  ###     ### ###       ### ##########         ########      ###     ########## ###    ### " << endl;

	setCurrentColor(1);

}

void drawGameOver(int x, int y, int color) //Dibujo el texto Ascii de gameOver
{
	setCurrentColor(color);

	goToCoordinates(x, y);
	cout << " ::::::::      :::     ::::    ::::  ::::::::::         ::::::::  :::     ::: :::::::::: :::::::::  " << endl;
	goToCoordinates(x, y + 1);
	cout << ":+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:               :+:    :+: :+:     :+: :+:        :+:    :+: " << endl;
	goToCoordinates(x, y + 2);
	cout << "+:+         +:+   +:+  +:+ +:+:+ +:+ +:+               +:+    +:+ +:+     +:+ +:+        +:+    +:+ " << endl;
	goToCoordinates(x, y + 3);
	cout << ":#:        +#++:++#++: +#+  +:+  +#+ +#++:++#          +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:  " << endl;
	goToCoordinates(x, y + 4);
	cout << "+#+   +#+# +#+     +#+ +#+       +#+ +#+               +#+    +#+  +#+   +#+  +#+        +#+    +#+ " << endl;
	goToCoordinates(x, y + 5);
	cout << "#+#    #+# #+#     #+# #+#       #+# #+#               #+#    #+#   #+#+#+#   #+#        #+#    #+# " << endl;
	goToCoordinates(x, y + 6);
	cout << " ########  ###     ### ###       ### ##########         ########      ###     ########## ###    ### " << endl;

	setCurrentColor(1);

	//https://www.messletters.com/es/big-text/ / alligator2
}

void Draw(int x, int y, char chart, int color)
{
	setCurrentColor(color);
	goToCoordinates(x, y);
	cout << chart;
	setCurrentColor(1); // Vuelve a blanco
}