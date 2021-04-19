#include <SDL_image.h>
#include <iostream>

#include "Texture.h"

SDL_bool isInitialized2 = SDL_FALSE;
Uint8 numberOfTextures = 0;

Texture::Texture()
{
	numberOfTextures++;

	if (!isInitialized2)
	{
		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0)
		{
			SDL_PrintError(" Could not initialize SDL_image. Error: " + std::string(IMG_GetError()));
		}

		isInitialized2 = SDL_TRUE;
	}
}

Texture::~Texture()
{
	numberOfTextures--;

	for (auto &i : texturesMap)
	{
		if (i.second != nullptr)
		{
			SDL_DestroyTexture(i.second);
		}
	}

	if (numberOfTextures == 0)
	{
		IMG_Quit();
	}

	texturesMap.clear();
}

void Texture::RenderTexture(SDL_Renderer *renderer, const SDL_Point *position, const float size, SDL_Texture *texture)
{
	if (renderer == nullptr)
	{
		SDL_PrintError("SDL_Renderer* parameter from Texture::RenderTexture function call is null!");
		return;
	}

	if (texture == nullptr)
	{
		SDL_PrintError("SDL_Texture* parameter from Texture::RenderTexture function call is null!");
		return;
	}

	if (position == nullptr)
	{
		SDL_PrintError("SDL_Point* parameter from Texture::RenderTexture function call is null!");
		return;
	}

	if (size == 0)
	{
		SDL_PrintError("float parameter from Texture::RenderTexture function call is null!");
		return;
	}

	SDL_Rect textureRect = { position->x, position->y, 0, 0 };
	SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);
	textureRect.w *= size;
	textureRect.h *= size;

	SDL_RenderCopy(renderer, texture, nullptr, &textureRect);
}

SDL_Texture *Texture::LoadTexture(SDL_Renderer *renderer, const std::string texturePath)
{
	if (renderer == nullptr)
	{
		SDL_PrintError("SDL_Renderer* parameter from Texture::LoadTexture function call is null!");
		return nullptr;
	}

	if (texturesMap.find(texturePath) != texturesMap.end())
	{
		SDL_PrintError("The texture: " + texturePath + " is already loaded in memory!");
		return nullptr;
	}

	if (!SDL_CheckFilePath(texturePath))
	{
		SDL_PrintError("std::string parameter from Texture::LoadTexture function call is invalid!");
		return nullptr;
	}

	SDL_Texture *newTexture = nullptr;
	SDL_Surface *surface = IMG_Load(texturePath.c_str());

	if (surface == nullptr)
	{
		SDL_PrintError(" Could not load texture. Error: " + std::string(IMG_GetError()));
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, surface);

		if (newTexture == nullptr)
		{
			SDL_PrintError(" Could not create texture. Error: " + std::string(IMG_GetError()));
		}

		SDL_FreeSurface(surface);
	}

	return newTexture;
}

void Texture::RemoveTexture(SDL_Texture *texture)
{
	if (texture == nullptr)
	{
		SDL_PrintError("SDL_Texture* parameter from Texture::RemoveTexture function call is null!");
		return;
	}

	for (auto &i : texturesMap)
	{
		if (i.second == texture)
		{
			texturesMap.erase(i.first);
			break;
		}
	}

	SDL_DestroyTexture(texture);
}
