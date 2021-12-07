#include "Entity.h"

Entity CreateEntity(char chart, int posX, int posY)
{
	//Crea un entity y le agrega los parametros que llegan
	Entity entity;
	entity.chart = chart;
	entity.position.x = posX;
	entity.position.y = posY;

	return entity; //y lo retorna
}

void LimitsWithTheScreen(Entity& entity, int minWidth, int maxWidth, int minHeight, int maxHeight)
{
	// Limite superior

	if (entity.position.y < minHeight)
	{
		entity.position.y = maxHeight;
	}

	// Limite izquierdo

	if (entity.position.x < minWidth)
	{
		entity.position.x = maxWidth;
	}

	// Limite Inferior

	if (entity.position.y > maxHeight)
	{
		entity.position.y = minHeight;
	}

	// Limite derecho

	if (entity.position.x > maxWidth)
	{
		entity.position.x = minWidth;
	}
}

void MoveEntity(Entity& entity, Vector2 direction)
{
	//Suma la direccion a la posicion
	entity.position.x += direction.x;
	entity.position.y += direction.y;
}
