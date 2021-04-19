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
	TTF_Font *f = t.LoadFont("C:\\Users\\Claudiu HBann\\Desktop\\C++ Projects\\Working ON Projects\\SDL Project\\Resources\\arial.ttf", 10);
	SDL_Point p = { 0, 0 };
	SDL_Color c = { 0, 255, 0, 0 };
	SDL_Rect r = { 0, 0, 100, 100 };
	SDL_Color c2 = { 255, 0, 0, 0 };

	GUI::Button ui(&r);

	ui.DrawButton(mainRenderer, "Pulea Spataru", &c2, 1.0f, f, &c, GUI::ButtonTextPositions::MIDDLE);
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

			default:
				break;
			}

			if (ui.OnButtonPressed())
			{
				std::cout << "Button apasat!\n";
			}
		}
	}

	return 0;
}