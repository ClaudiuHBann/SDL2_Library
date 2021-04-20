#include "Collision.h"

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

Collision2D::Collision2D(Shape::Circle &circle)
{
	circlesList.push_back(&circle);
}

Collision2D::Collision2D(Shape::Triangle &triangle)
{
	trianglesList.push_back(&triangle);
}

Collision2D::Collision2D(Shape::Rectangle &rectangle)
{
	rectanglesList.push_back(&rectangle);
}

Collision2D::Collision2D(Shape::Polygon &polygon)
{
	polygonsList.push_back(&polygon);
}

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

	for (auto &i : circlesList)
	{
		//aici
	}
}