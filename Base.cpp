#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <sys/stat.h>

#include "Base.h"

SDL_bool isInitialized1 = SDL_FALSE;
Uint8 numberOfBases = 0;

Base::Base()
{
	numberOfBases++;

	if (!isInitialized1)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		{
			SDL_PrintError(" Could not initialize SDL. Error: " + std::string(SDL_GetError()));
		}

		srand(time(NULL));

		isInitialized1 = SDL_TRUE;
	}
}

Base::~Base()
{
	numberOfBases--;

	for (auto &i : renderersList)
	{
		if (i != nullptr)
		{
			SDL_DestroyRenderer(i);
		}
	}

	for (auto &i : windowsList)
	{
		if (i != nullptr)
		{
			SDL_DestroyWindow(i);
		}
	}

	if (numberOfBases == 0)
	{
		SDL_Quit();
	}

	renderersList.clear();
	windowsList.clear();
}

SDL_Window *Base::CreateWindow(const std::string& windowName, const Uint16 windowWidth, const Uint16 windowHeight, const Uint32 flags)
{
	if (&windowName == nullptr)
	{
		SDL_PrintError("std::string* parameter from Base::CreateWindow function call is null!");
		return nullptr;
	}

	SDL_Window *newWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);

	if (newWindow == nullptr)
	{
		SDL_PrintError(" Could not create window " + std::to_string(windowsList.size() + 1) + ". Error: " + SDL_GetError());
	}
	else
	{
		windowsList.push_back(newWindow);
	}

	return newWindow;
}

SDL_Renderer *Base::CreateRenderer(SDL_Window *window, const Uint32 flags)
{
	if (window == nullptr)
	{
		SDL_PrintError("SDL_Window* parameter from Base::CreateRenderer function call is null!");
		return nullptr;
	}

	SDL_Renderer *newRenderer = SDL_CreateRenderer(window, -1, flags);

	if (newRenderer == nullptr)
	{
		SDL_PrintError(" Could not create renderer " + std::to_string(renderersList.size() + 1) + ". Error: " + SDL_GetError());
	}
	else
	{
		renderersList.push_back(newRenderer);
	}

	return newRenderer;
}

void Base::RemoveWindow(SDL_Window *window)
{
	if (window == nullptr)
	{
		SDL_PrintError("SDL_Window* parameter from Base::RemoveWindow function call is null!");
		return;
	}

	for (auto &i : windowsList)
	{
		if (i == window)
		{
			windowsList.remove(i);
			break;
		}
	}

	SDL_DestroyWindow(window);
}

void Base::RemoveRenderer(SDL_Renderer *renderer)
{
	if (renderer == nullptr)
	{
		SDL_PrintError("SDL_Renderer* parameter from Base::RemoveRenderer function call is null!");
		return;
	}

	for (auto &i : renderersList)
	{
		if (i == renderer)
		{
			renderersList.remove(i);
			break;
		}
	}

	SDL_DestroyRenderer(renderer);
}

void SDL_RenderFillCircle(SDL_Renderer *renderer, const SDL_Circle &circle)
{
	if (renderer == nullptr)
	{
		SDL_PrintError("SDL_Renderer* parameter from SDL_RenderFillCircle function call is null!");
		return;
	}

	if (&circle == nullptr)
	{
		SDL_PrintError("SDL_Circle* parameter from SDL_RenderFillCircle function call is null!");
		return;
	}

	for (double dy = 1.0; dy <= circle.radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * circle.radius * dy) - (dy * dy)));

		SDL_RenderDrawLine(renderer, circle.point.x - (int)dx, circle.point.y + (int)dy - circle.radius, circle.point.x + (int)dx, circle.point.y + (int)dy - circle.radius);
		SDL_RenderDrawLine(renderer, circle.point.x - (int)dx, circle.point.y - (int)dy + circle.radius, circle.point.x + (int)dx, circle.point.y - (int)dy + circle.radius);
	}
}

inline void SDL_PrintError(const std::string& errorMessage)
{
	if (&errorMessage == nullptr)
	{
		SDL_PrintError("std::string* parameter from SDL_PrintError function call is null!");
		return;
	}

	std::cerr << std::endl << errorMessage << std::endl;
}

SDL_bool SDL_CheckFilePath(const std::string& filePath)
{
	if (&filePath == nullptr)
	{
		SDL_PrintError("std::string* parameter from SDL_CheckFilePath function call is null!");
		return SDL_FALSE;
	}

	struct stat info;
	return (!stat(filePath.c_str(), &info)) ? SDL_TRUE : SDL_FALSE;
}

SDL_Texture *SDL_GetRendererAsTexture(SDL_Window *window, SDL_Renderer *renderer, const SDL_Rect &windowRect)
{
	if (window == nullptr)
	{
		SDL_PrintError("SDL_Window* parameter from SDL_GetRendererAsTexture function call is null!");
		return nullptr;
	}

	if (renderer == nullptr)
	{
		SDL_PrintError("SDL_Renderer* parameter from SDL_GetRendererAsTexture function call is null!");
		return nullptr;
	}

	SDL_Surface *surface = nullptr;
	SDL_Texture *texture = nullptr;
	SDL_Rect tempRect = { 0, 0, 0, 0 };

	if (&windowRect == nullptr || SDL_RectEquals(&tempRect, &windowRect))
	{
		SDL_GetWindowSize(window, &tempRect.w, &tempRect.h);
		surface = SDL_CreateRGBSurfaceWithFormat(0, tempRect.w, tempRect.h, 32, SDL_PIXELFORMAT_RGBA32);
	}
	else
	{
		surface = SDL_CreateRGBSurfaceWithFormat(0, windowRect.w, windowRect.h, 32, SDL_PIXELFORMAT_RGBA32);
	}

	if (surface == nullptr)
	{
		SDL_PrintError("Could not create surface from window (SDL_GetRendererAsTexture)! Error: " + std::string(SDL_GetError()));
		return nullptr;
	}
	else
	{
		SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
		SDL_LockSurface(surface);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_UnlockSurface(surface);
		SDL_FreeSurface(surface);

		if (texture == nullptr)
		{
			SDL_PrintError("Could not create texture (SDL_GetRendererAsTexture)! Error: " + std::string(SDL_GetError()));
		}

		return (texture == nullptr) ? nullptr : texture;
	}
}