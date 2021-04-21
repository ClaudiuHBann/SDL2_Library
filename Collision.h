#ifndef _COLLISION_H
#define _COLLISION_H

#include <SDL.h>

#include "Base.h"
#include "Shape.h"

class Collision2D : Shape2D
{
public:
	Collision2D(Shape2D &shape);
	Collision2D();
	~Collision2D();

	void AddCollision2D(Shape2D &shape);

	static int CheckCollisionBetweenObjects(void *);
};

#endif // _COLLISION_H