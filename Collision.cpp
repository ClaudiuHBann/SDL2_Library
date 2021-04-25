#include "Collision.h"

SDL_Thread *checkDistances = nullptr;
SDL_Thread *checkCollision = nullptr;
SDL_bool isInitialized6 = SDL_FALSE;
SDL_bool closeThreads = SDL_FALSE;
Uint8 numberOfCollisionObjects = 0;

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

void CheckForInit()
{
	numberOfCollisionObjects++;

	if (!isInitialized6)
	{
		checkDistances = SDL_CreateThread(CheckDistanceBetweenObjects, "CD", (void *)NULL);
		SDL_DetachThread(checkDistances);

		checkCollision = SDL_CreateThread(CheckCollisionBetweenObjects, "CC", (void *)NULL);
		SDL_DetachThread(checkCollision);

		isInitialized6 = SDL_TRUE;
	}
}

Collision2D::Collision2D()
{
	CheckForInit();
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