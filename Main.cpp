#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <iostream>

#include "Base.h"
#include "Sound.h"
#include "Texture.h"
#include "Collision.h"
#include "Shape.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
	Base base;
	SDL_Window *mainWindow = base.CreateWindow("Test", 640, 480, SDL_WINDOW_OPENGL);
	SDL_Renderer *mainRenderer = base.CreateRenderer(mainWindow, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Event event;
	bool gameRunning = true;

	SDL_Circle c1 = { 100, 100, 10 };
	Shape2D circle1(c1);
	Collision2D circleCollision1(circle1);

	SDL_Circle c2 = { 200, 200, 30 };
	Shape2D circle2(c2);
	Collision2D circleCollision2(circle2);

	while (gameRunning)
	{
		circle1.Draw(mainRenderer);
		circle2.Draw(mainRenderer);
		SDL_RenderPresent(mainRenderer);

		//while (SDL_WaitEvent(&event) >= 0 && gameRunning)
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;

			case SDLK_w:
				c1.point.y -= 10;
				circle1.Set(c1);
				break;

			case SDLK_a:
				c1.point.x -= 10;
				circle1.Set(c1);
				break;

			case SDLK_s:
				c1.point.y += 10;
				circle1.Set(c1);
				break;

			case SDLK_d:
				c1.point.x += 10;
				circle1.Set(c1);
				break;
			}
		}
	}

	return 0;
}
