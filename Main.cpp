#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <iostream>
#include <time.h>

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

	SDL_Polygon polygons[100];
	SDL_Point tempPoint;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tempPoint.x = SDL_GetRandomNumberInRange(0, 640);
			tempPoint.y = SDL_GetRandomNumberInRange(0, 480);

			polygons[i].points.push_back(tempPoint);
		}
	}

	Polygon polys[100];
	for (int i = 0; i < 100; i++)
	{
		polys[i].pointsPos = polygons[i].points;
		polys[i].color = { (Uint8)SDL_GetRandomNumberInRange(0, 255), (Uint8)SDL_GetRandomNumberInRange(0, 255), (Uint8)SDL_GetRandomNumberInRange(0, 255), (Uint8)SDL_GetRandomNumberInRange(0, 255) };
	}

	bool once = false;
	clock_t start;

	while (gameRunning)
	{
		if (!once)
		{
			start = clock();

			for (int i = 0; i < 100; i++)
			{
				polys[i].Draw(mainRenderer);
			}
			SDL_RenderPresent(mainRenderer);
		}

		polys[0].Draw(mainRenderer);
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

		if (!once)
		{
			std::cout << "Time to draw 100 polygons: " << clock() - start;
		}

		once = true;
	}

	return 0;
}
