#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "GUI.h"

SDL_Point mousePosition = { -1, -1 };
SDL_Point mousePosLeftClickDownStart = { -1, -1 };
SDL_Point mousePosLeftClickDownEnd = { -1, -1 };
bool isMouseLeftClickDown = false;

SDL_bool isInitialized5 = SDL_FALSE;
SDL_bool closeMVHThread = SDL_FALSE;

int MouseVariablesHandle(void*)
{
	Uint32 key;

	while (!closeMVHThread)
	{
		key = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

		switch (SDL_BUTTON(key))
		{
		case 1:
			if (!isMouseLeftClickDown)
			{
				SDL_GetMouseState(&mousePosLeftClickDownStart.x, &mousePosLeftClickDownStart.y);
				mousePosLeftClickDownEnd.y = -1;
				mousePosLeftClickDownEnd.x = -1;
				isMouseLeftClickDown = true;
			}

			break;

		default:
			if (isMouseLeftClickDown)
			{
				SDL_GetMouseState(&mousePosLeftClickDownEnd.x, &mousePosLeftClickDownEnd.y);
				isMouseLeftClickDown = false;
			}

			break;
		}

		SDL_Delay(1);
	}

	return 0;
}

GUI::Button::Button(SDL_Rect* buttonRect)
{
	if (!isInitialized5)
	{
		SDL_Thread *mvh;
		mvh = SDL_CreateThread(MouseVariablesHandle, "MHV", (void *)NULL);
		SDL_DetachThread(mvh);

		isInitialized5 = SDL_TRUE;
	}

	this->buttonRect = *buttonRect;
}

bool GUI::Button::OnButtonPressed()
{
	if (SDL_PointInRect(&mousePosLeftClickDownStart, &buttonRect) && SDL_PointInRect(&mousePosLeftClickDownEnd, &buttonRect))
	{
		mousePosLeftClickDownStart.x = -1;
		mousePosLeftClickDownStart.y = -1;

		return true;
	}

	return false;
}

bool GUI::Button::OnCursorOverButton()
{
	return (SDL_PointInRect(&mousePosition, &buttonRect)) ? true : false;
}

void GUI::Button::DrawButton(SDL_Renderer* renderer, const std::string buttonText, const SDL_Color* textColor, const float size, TTF_Font* font, const SDL_Color*buttonColor, const Uint32 buttonTextFlags)
{
	SDL_Rect tempTextRect = { 0, 0, 0, 0 };
	TTF_SizeText(font, buttonText.c_str(), &tempTextRect.w, &tempTextRect.h);

	SDL_Rect textRect;
	switch (buttonTextFlags)
	{
	case TOP_LEFT:
		textRect = { buttonRect.x, buttonRect.y, tempTextRect.w, tempTextRect.h };
		break;

	case TOP_MIDDLE:
		textRect = { (buttonRect.x + buttonRect.x + buttonRect.w) / 2 - (tempTextRect.w / 2), buttonRect.y, tempTextRect.w, tempTextRect.h };
		break;

	case TOP_RIGHT:
		textRect = { buttonRect.x + buttonRect.w - tempTextRect.w, buttonRect.y, tempTextRect.w, tempTextRect.h };
		break;

	case LEFT_MIDDLE:
		textRect = { buttonRect.x, (buttonRect.y + buttonRect.y + buttonRect.h) / 2 - (tempTextRect.h / 2), tempTextRect.w, tempTextRect.h };
		break;

	case MIDDLE:
		textRect = { (buttonRect.x + buttonRect.x + buttonRect.w) / 2 - (tempTextRect.w / 2), (buttonRect.y + buttonRect.y + buttonRect.h) / 2 - (tempTextRect.h / 2), tempTextRect.w, tempTextRect.h };
		break;

	case RIGHT_MIDDLE:
		textRect = { buttonRect.x + buttonRect.w - tempTextRect.w, (buttonRect.y + buttonRect.y + buttonRect.h) / 2 - (tempTextRect.h / 2), tempTextRect.w, tempTextRect.h };
		break;

	case BOTTOM_LEFT:
		textRect = { buttonRect.x, buttonRect.y + buttonRect.h - tempTextRect.h, tempTextRect.w, tempTextRect.h };
		break;

	case BOTTOM_MIDDLE:
		textRect = { (buttonRect.x + buttonRect.x + buttonRect.w) / 2 - (tempTextRect.w / 2), buttonRect.y + buttonRect.h - tempTextRect.h, tempTextRect.w, tempTextRect.h };
		break;

	case BOTTOM_RIGHT:
		textRect = { buttonRect.x + buttonRect.w - tempTextRect.w, buttonRect.y + buttonRect.h - tempTextRect.h, tempTextRect.w, tempTextRect.h };
		break;

	default:
		textRect = { (buttonRect.x + buttonRect.x + buttonRect.w) / 2 - (tempTextRect.w / 2), (buttonRect.y + buttonRect.y + buttonRect.h) / 2 - (tempTextRect.h / 2), tempTextRect.w, tempTextRect.h };
		break;
	}

	SDL_SetRenderDrawColor(renderer, buttonColor->r, buttonColor->g, buttonColor->b, buttonColor->a);
	SDL_RenderFillRect(renderer, &buttonRect);
	SDL_Point tempPoint = { textRect.x, textRect.y };
	text.RenderText(renderer, &tempPoint, buttonText, size, font, textColor);
}

SDL_bool isInitialized4 = SDL_FALSE;
Uint8 numberOfTextObjects = 0;

GUI::Text::Text()
{
	numberOfTextObjects++;

	if (!isInitialized4)
	{
		if (TTF_Init() == -1)
		{
			SDL_PrintError(" Could not initialize SDL_ttf. Error: " + std::string(TTF_GetError()));
		}

		isInitialized4 = SDL_TRUE;
	}
}

GUI::Text::~Text()
{
	numberOfTextObjects--;

	for (auto &i : fontsMap)
	{
		if (i.second != nullptr)
		{
			TTF_CloseFont(i.second);
		}
	}

	if (numberOfTextObjects == 0)
	{
		TTF_Quit();
	}

	fontsMap.clear();
}

TTF_Font *GUI::Text::LoadFont(const std::string fontPath, const Uint8 fontSize)
{
	if (!SDL_CheckFilePath(fontPath))
	{
		SDL_PrintError("std::string parameter from Text::LoadFont function call is invalid!");
		return nullptr;
	}

	if (fontsMap.find(fontPath) != fontsMap.end())
	{
		SDL_PrintError("The font: " + fontPath + " is already loaded in memory!");
		return nullptr;
	}
	else
	{
		TTF_Font *newFont = TTF_OpenFont(fontPath.c_str(), fontSize);

		if (newFont == nullptr)
		{
			SDL_PrintError(" Could not load font. Error: " + std::string(TTF_GetError()));
		}
		else
		{
			fontsMap.insert(std::pair<std::string, TTF_Font *>(fontPath, newFont));
		}

		return newFont;
	}
}

void GUI::Text::RenderText(SDL_Renderer *renderer, const SDL_Point *position, const std::string text, const float size, TTF_Font *font, const SDL_Color *color)
{
	if (renderer == nullptr)
	{
		SDL_PrintError("SDL_Renderer* parameter from Text::RenderText function call is null!");
		return;
	}

	if (font == nullptr)
	{
		SDL_PrintError("TTF_Font* parameter from Text::RenderText function call is null!");
		return;
	}

	SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), *color);

	if (surface == nullptr)
	{
		SDL_PrintError(" Could not create text surface. Error: " + std::string(TTF_GetError()));
	}
	else
	{
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == nullptr)
		{
			SDL_PrintError(" Could not create texture. Error: " + std::string(TTF_GetError()));
			SDL_FreeSurface(surface);
		}
		else
		{
			SDL_Rect textRect = { position->x, position->y, (int)(surface->w * size), (int)(surface->h * size) };
			SDL_RenderCopy(renderer, texture, nullptr, &textRect);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
	}
}

void GUI::Text::RemoveFont(TTF_Font *font)
{
	if (font == nullptr)
	{
		SDL_PrintError("TTF_Font* parameter from Text::RemoveFont function call is null!");
		return;
	}

	for (auto &i : fontsMap)
	{
		if (font == i.second)
		{
			fontsMap.erase(i.first);
			break;
		}
	}

	TTF_CloseFont(font);
}