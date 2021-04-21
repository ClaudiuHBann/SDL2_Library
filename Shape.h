#ifndef _SHAPE_H
#define _SHAPE_H

#include <SDL.h>
#include <stdarg.h>

#include "Base.h"

class Shape2D
{
public:
	Shape2D(const SDL_Circle &circle, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });
	Shape2D(const SDL_Triangle &triangle, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });
	Shape2D(const SDL_Rect &rectangle, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });
	Shape2D(const SDL_Polygon &polygon, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });
	Shape2D() {}
	~Shape2D();

	void Draw(SDL_Renderer *renderer);

	void Set(const SDL_Circle &circle, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });
	void Set(const SDL_Triangle &triangle, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });
	void Set(const SDL_Rect &rectangle, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });
	void Set(const SDL_Polygon &polygon, const SDL_Point &rotation = { 0, 0 }, const SDL_FPoint &scale = { 1.0f, 1.0f });

	template <typename T>
	T Get(Shape2D shape) { return; };

protected:
	SDL_Circle *circle = nullptr;
	SDL_Triangle *triangle = nullptr;
	SDL_Rect *rectangle = nullptr;
	SDL_Polygon *polygon = nullptr;

	SDL_Point rotation = { 0, 0 };
	SDL_FPoint scale = { 1.0f, 1.0f };

private:
	template <typename T>
	bool CheckForNullity(const T &t, const std::string &what, const std::string &where, const SDL_Point &rotation, const SDL_FPoint &scale)
	{
		if (&t == nullptr)
		{
			SDL_PrintError(what + " parameter from " + where + " is null");
			return false;
		}

		if (&rotation == nullptr)
		{
			SDL_PrintError("SDL_Point* parameter from " + where + " is null");
			return false;
		}

		if (&scale == nullptr)
		{
			SDL_PrintError("SDL_FPoint* parameter from " + where + " is null");
			return false;
		}

		return true;
	}

	void ScaleShape2D();
};

#endif // _SHAPE_H
