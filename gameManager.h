#pragma once

#include "AdditionalFunctions.h"
#include "Entity.h"


#pragma region Enum

enum class GameState { MENU, GAMEPLAY, GAMEOVER };

#pragma endregion

#pragma region VARIABLES

//Seteo ╔ ╚ ╗ ╝ ═ ║ en variables para facilitar su uso
const int LEFT_UP = 201;
const int LEFT_DW = 200;
const int RIGHT_UP = 187;
const int RIGHT_DW = 188;
const int LINE_HOR = 205;
const int LINE_VER = 186;

//Se utiliza en el Sleep para simular un frame rate
const int frameTime = 40;

//Inializo el minimo y el maximo tamaño de la serpiente
const int maxBodyLinks = 100;
const int minBodyLinks = 1;

//Seteo el caracter que usara cada enitdad
const char playerChart = (char)2; // ☻
const char tailChart = (char)155; // ø     

const char foodChart = (char)157; // Ø

bool playing = true;

GameState gameState = GameState::MENU;

//creo el bodyLinks (tamaño actual del cuerpo) y lo inicializo en el minimo
int bodyLinks = minBodyLinks;

//Creo a la serpiente y al alimento
Entity snake[maxBodyLinks];
Entity food;

//Indicara en que direccion se esta moviendo
Vector2 direction;

//Creo el puntaje
int highScore = 0;
int score = 0;

//Establezco los limites del marco de juego 
int minWidth = 2;
int maxWidth = getScreenWidth() - 1;
int minHeight = getScreenHeight() / 3;
int maxHeight = getScreenHeight() - 4;



#pragma endregion

#pragma region Functions

void main(); //Punto de entrada

void Init(); //Inicializo los valores 

void Input(); //Toma el input del usuario

void DrawGameHud(); //Dibuja el Hud del juego

void DrawEntities(); //Dibuja la sepiente y el alimento

void Update(); //Actualiza frame a frame el juego

void MainMenu(); //Contiene el dibujado y la logica del menu

void SpawnFood(); //Spawnea un alimento en una posicion aleatoria

void Collision(); //Chequea las colisiones de la serpientre

void GameOver(); // Dibuja la pantalla de Game over y su logica

void AddScore(); //Agrega puntos y setea el HighScore

void AddBodyLinks(); //Agrega un eslabon a la serpiente

void drawFrame(int x1, int y1, int x2, int y2, int color); //Dibuja el marco de juego

void drawMenuOptions(int x, int y, int color); //Dibuja las opciones en ASCII

void drawTitle(int x, int y, int color);//Dibuja el Titulo en ASCII
void drawTitle();

void drawTutorial(int x, int y, int color1, int color2, int color3);//Dibuja el tutorial en ASCII

void drawFire(int x, int y, int color);

void drawGameOver(int x, int y, int color);//Dibuja el game over en ASCII

void Draw(int x, int y, char chart, int color = 9); //Dibuja un caracter en una posicion especifica
#pragma endregion

const char fire[] = R"(
	´´´´´´´´´´´´´´´´´´´´´´´´¶´´´´´´´´´¶´´´´´´´´´´´´´´´´´´´´´´´´´´
	´´´´´´´´´´´´´´´´´´´´´´´´´¶´´´´´´´´´¶´´´´´´´´´´´´´´´´´´´´´´´´´
	´´´´´´´´´´´´´´´´´´´´´¶´´´¶´´´´´´´´´¶´´´¶´´´´´´´´´´´´´´´´´´´´´
	´´´´´´´´´´´´´´´´´´´´´¶´´¶¶´´´´´´´´´¶¶´´¶´´´´´´´´´´´´´´´´´´´´´
	´´´´´´´´´´´´´´´´´´´´´¶¶´¶¶¶´´´´´´´¶¶¶´¶¶´´´´´´´´´´´´´´´´´´´´´
	´´´´´´´´´´´´´¶´´´´´´¶¶´´´¶¶¶´´´´´¶¶¶´´´¶¶´´´´´´¶´´´´´´´´´´´´´
	´´´´´´´´´´´´¶¶´´´´´´¶¶´´´¶¶¶´´´´´¶¶¶´´´¶¶´´´´´´¶¶´´´´´´´´´´´´
	´´´´´´´´´´´¶¶´´´´´´¶¶´´´´¶¶¶¶´´´¶¶¶¶´´´´¶¶´´´´´´¶¶´´´´´´´´´´´
	´´´´´´´´´´´¶¶´´´´´¶¶¶´´´´¶¶¶¶´´¶¶¶¶¶´´´´¶¶¶´´´´´¶¶¶´´´´´´´´´´
	´´´´´´´¶´´¶¶¶´´´´¶¶¶¶´´´´¶¶¶¶´´´¶¶¶¶´´´´¶¶¶¶´´´¶¶¶¶´´¶´´´´´´´
	´´´´´´´¶¶´¶¶¶¶¶´´¶¶¶¶´´´¶¶¶¶¶´´´¶¶¶¶¶´´´¶¶¶¶´´¶¶¶¶¶´¶¶´´´´´´´
	´´´´´´´¶¶´¶¶¶¶¶´´¶¶¶¶¶¶¶¶¶¶¶´´´´´¶¶¶¶¶¶¶¶¶¶¶´´¶¶¶¶¶´¶¶´´´´´´´
	´´´´´´´¶¶´¶¶¶¶¶´´¶¶¶¶¶¶¶¶¶¶¶´´´´´¶¶¶¶¶¶¶¶¶¶¶´´¶¶¶¶¶´¶¶´´´´´´´
	´´´´´´¶¶¶´´¶¶¶¶´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´¶¶¶¶´´¶¶¶´´´´´´
	´´´´´¶¶¶¶´´¶¶¶¶´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´¶¶¶¶´´¶¶¶¶´´´´´
	´´´´¶¶¶¶´´´¶¶¶¶¶´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´¶¶¶¶¶´´´¶¶¶¶´´´´
	´´´¶¶¶¶´´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´¶¶¶¶´´´´
	´´´¶¶¶¶¶´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´¶¶¶¶´´´´
	´´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´
	´´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´
	´´´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´
	´´´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´

)";