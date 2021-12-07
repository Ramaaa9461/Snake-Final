#pragma once


#pragma region Structs

struct Vector2
{
	int x;
	int y;
};

struct Entity
{
	char chart;
	Vector2 position;
};

#pragma endregion

#pragma region Functions

//Creo la entidad en base a los parametros que llegan
Entity CreateEntity(char chart, int posX, int posY);

//Llegan por parametros los limites de la pantalla y setea la posicion en 
// el otro extremo en caso de colision
void LimitsWithTheScreen(Entity& entity, int minWidth, int maxWidth, int minHeight, int maxHeight);

//Mueve la entidad en base a la direccion que le llega
void MoveEntity(Entity& entity, Vector2 direction);

#pragma endregion