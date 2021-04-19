#pragma once

#include <SDL_ttf.h>
#include <string>
#include <thread>
#include <map>

#include "Base.h"

namespace GUI
{
	class Button;
	class Text;
	enum ButtonTextPositions;
}

enum GUI::ButtonTextPositions
{
	TOP_LEFT = 0,
	TOP_MIDDLE = 1,
	TOP_RIGHT = 2,
	LEFT_MIDDLE = 3,
	MIDDLE = 4,
	RIGHT_MIDDLE = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_MIDDLE = 7,
	BOTTOM_RIGHT = 8,
};

class GUI::Text
{
public:
	Text();
	~Text();

	TTF_Font *LoadFont(const std::string fontPath, const Uint8 fontSize);
	void RenderText(SDL_Renderer *renderer, const SDL_Point *position, const std::string text, const float size, TTF_Font *font, const SDL_Color *color);
	void RemoveFont(TTF_Font *font);

private:
	std::map<std::string, TTF_Font *> fontsMap;
};

class GUI::Button
{
public:
	Button(SDL_Rect* buttonRect, SDL_Color* buttonColor, float size, std::string buttonText, SDL_Color* textColor, int buttonTextFlags);
	Button() {}
	~Button() {}

	SDL_Rect buttonRect = { 0, 0, 0, 0 };
	SDL_Color buttonColor = { 0, 0, 0, 0 };

	float size = 1.0f;
	std::string buttonText = "";
	SDL_Color textColor = { 0, 0, 0, 0 };
	int buttonTextFlags = 0;

	bool IsButtonPressed();
	bool IsCursorOverButton();
	void DrawButton(SDL_Renderer *renderer, TTF_Font *font);

private:
	GUI::Text text;
};
