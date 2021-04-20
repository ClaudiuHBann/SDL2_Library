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
	enum class ButtonTextPositions;
}

enum class GUI::ButtonTextPositions
{
	TOP_LEFT = 0,
	TOP_MIDDLE,
	TOP_RIGHT,
	LEFT_MIDDLE,
	MIDDLE,
	RIGHT_MIDDLE,
	BOTTOM_LEFT,
	BOTTOM_MIDDLE,
	BOTTOM_RIGHT,
};

class GUI::Text
{
public:
	Text();
	~Text();

	TTF_Font *LoadFont(const std::string &fontPath, const Uint8 fontSize);
	void RenderText(SDL_Renderer *renderer, const SDL_Point &position, const std::string &text, const float size, TTF_Font *font, const SDL_Color &color);
	void RemoveFont(TTF_Font *font);

private:
	std::map<std::string, TTF_Font *> fontsMap;
};

class GUI::Button
{
public:
	SDL_Rect buttonRect = { 0, 0, 0, 0 };

	Button(SDL_Rect& buttonRect);
	Button() {}
	~Button();

	bool OnButtonPressed();
	bool OnCursorOverButton();
	void DrawButton(SDL_Renderer *renderer, const std::string& buttonText, const SDL_Color &textColor, const float size, TTF_Font *font, const SDL_Color &buttonColor, const Uint8 buttonTextFlags);

private:
	SDL_Thread *mvh = nullptr;
	GUI::Text text;
};

#endif // _GUI_H