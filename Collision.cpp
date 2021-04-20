#include "Collision.h"

SDL_bool isInitialized6 = SDL_FALSE;
SDL_bool closeThreads = SDL_FALSE;
Uint8 numberOfCollisionObjects = 0;

Collision2D::Collision2D()
{
	numberOfCollisionObjects++;

	if (!isInitialized6)
	{
		checkDistances = SDL_CreateThread(CheckDistanceBetweenObjects, "CD", (void *)NULL);
		SDL_DetachThread(checkDistances);

		checkCollision = SDL_CreateThread(CheckDistanceBetweenObjects, "CC", (void *)NULL);
		SDL_DetachThread(checkCollision);

		isInitialized6 = SDL_TRUE;
	}
}

Collision2D::~Collision2D()
{
	numberOfCollisionObjects--;

	if (numberOfCollisionObjects == 0)
	{
		closeThreads = SDL_TRUE;

		delete checkCollision;
		delete checkDistances;
	}
}

int CheckDistanceBetweenObjects(void *)
{
	while (closeThreads)
	{

	}

	return 0;
}

int CheckCollisionBetweenObjects(void *)
{
	while (closeThreads)
	{

	}

	return 0;
}