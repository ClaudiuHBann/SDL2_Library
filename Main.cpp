#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

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

	while (gameRunning)
	{
		

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
