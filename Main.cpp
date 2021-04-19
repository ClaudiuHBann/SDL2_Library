#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <iostream>

#include "Base.h"
#include "Sound.h"
#include "Texture.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
	Base base;
	SDL_Window *mainWindow = base.CreateWindow("Test", 640, 480, SDL_WINDOW_OPENGL);
	SDL_Renderer *mainRenderer = base.CreateRenderer(mainWindow, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Event event;
	bool gameRunning = true;

	GUI::Text t;
	TTF_Font *f = t.LoadFont("C:\\Users\\Claudiu HBann\\Desktop\\C++ Projects\\Working ON Projects\\SDL Project\\Release\\Resources\\arial.ttf", 10);
	SDL_Point p = { 0, 0 };
	SDL_Color c = { 0, 255, 0, 0 };
	SDL_Rect r = { 0, 0, 400, 400 };
	SDL_Color c2 = { 255, 0, 0, 0 };

	GUI::Button ui(mainRenderer, &r, &c2, 1.0f, "blabla", &c, 0);

	ui.DrawButton(mainRenderer, f);
	SDL_RenderPresent(mainRenderer);

	while (gameRunning)
	{
// 		while (SDL_PollEvent(&event))
		while (SDL_WaitEvent(&event) >= 0 && gameRunning)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (ui.IsButtonPressed())
				{
					std::cout << "Button apasat!\n";
				}
				break;

			default:
				break;
			}
		}
	}

	return 0;
}