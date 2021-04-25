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

	Shape2D* shape1 = new Line({ 100, 100 }, { 423, 327 }, 1.0f, { 255, 0, 0, 255 });
	Line* line = dynamic_cast<Line *>(shape1);
	
	Shape2D *shape2 = new Circle({ 300, 300 }, 150.0f, { 0, 255, 0, 255 });
	Circle *circle = dynamic_cast<Circle *>(shape2);

	while (gameRunning)
	{
		line->Draw(mainRenderer);
		circle->Draw(mainRenderer);
		SDL_RenderPresent(mainRenderer);

		//while (SDL_WaitEvent(&event) >= 0 && gameRunning)
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}
	}

	return 0;
}
