#ifndef _COLLISION_H
#define _COLLISION_H

#include <SDL.h>
#include <list>

#include "Base.h"
#include "Shapes.h"

class Collision2D
{
public:
	Collision2D(Shape::Circle &circle);
	Collision2D(Shape::Triangle &triangle);
	Collision2D(Shape::Rectangle &rectangle);
	Collision2D(Shape::Polygon &polygon);
	Collision2D();
	~Collision2D();

private:
	std::list<Shape::Circle *> circlesList;
	std::list<Shape::Triangle *> trianglesList;
	std::list<Shape::Rectangle *> rectanglesList;
	std::list<Shape::Polygon *> polygonsList;

	SDL_Thread *checkDistances = nullptr;
	SDL_Thread *checkCollision = nullptr;
};

#endif // _COLLISION_H