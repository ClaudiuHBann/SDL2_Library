#ifndef _COLLISION_H
#define _COLLISION_H

#include <SDL.h>

#include "Base.h"

class Collision2D
{
public:
	Collision2D();
	~Collision2D();

private:
	SDL_Thread *checkDistances = nullptr;
	SDL_Thread *checkCollision = nullptr;
};

#endif // _COLLISION_H