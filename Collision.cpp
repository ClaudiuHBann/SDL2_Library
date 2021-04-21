#include "Collision.h"

SDL_Thread *checkDistances = nullptr;
SDL_Thread *checkCollision = nullptr;
SDL_bool isInitialized6 = SDL_FALSE;
SDL_bool closeThreads = SDL_FALSE;
Uint8 numberOfCollisionObjects = 0;

std::list<Collision2D *> shapesList;
std::list<Collision2D *> shapesListForCollisionCheck;

int CheckDistanceBetweenObjects(void *)
{
	while (closeThreads)
	{
		for (auto &i : shapesList)
		{
			for (auto &j : shapesList)
			{

			}
		}
	}

	return 0;
}

int Collision2D::CheckCollisionBetweenObjects(void *)
{
	while (closeThreads)
	{
		for (auto &i : shapesListForCollisionCheck)
		{
			for (auto &j : shapesListForCollisionCheck)
			{
				
			}
		}
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

		checkCollision = SDL_CreateThread(Collision2D::CheckCollisionBetweenObjects, "CC", (void *)NULL);
		SDL_DetachThread(checkCollision);

		isInitialized6 = SDL_TRUE;
	}
}

Collision2D::Collision2D(Shape2D &shape)
{
	if (&shape == nullptr)
	{
		SDL_PrintError("Circle* parameter from Collision2D constructor is null");
		return;
	}
	
	CheckForInit();
	shapesList.push_back(&shape);
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

		shapesList.clear();
		shapesListForCollisionCheck.clear();
	}
}

void Collision2D::AddCollision2D(Shape2D &shape)
{
	if (&shape == nullptr)
	{
		SDL_PrintError("Circle* parameter from Collision2D constructor is null");
		return;
	}

	CheckForInit();
	shapesList.push_back(&shape);
}
