#ifndef _GUI_H
#define _GUI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
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
	SDL_Rect buttonRect = { 0, 0, 0, 0 };

	Button(SDL_Rect* buttonRect);
	Button() {}
	~Button() {}

	bool OnButtonPressed();
	bool OnCursorOverButton();
	void DrawButton(SDL_Renderer *renderer, const std::string buttonText, const SDL_Color *textColor, const float size, TTF_Font *font, const SDL_Color *buttonColor, const Uint32 buttonTextFlags);

private:
	GUI::Text text;
};

#endif // _GUI_H