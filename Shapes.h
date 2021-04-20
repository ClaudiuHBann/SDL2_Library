#ifndef _SHAPES_H
#define _SHAPES_H

#include <SDL.h>

#include "Base.h"

namespace Shape
{
	class Circle;
	class Rectangle;
	class Triangle;
	class Polygon;
}

class Shape::Circle
{
public:
	SDL_Point point = { 0, 0 };
	Uint16 radius = 0;
	SDL_Color color = { 0, 0, 0, 0 };

	Circle(SDL_Point &point, Uint16 radius, SDL_Color &color);
	Circle() {}
	~Circle() {}
};

class Shape::Triangle
{
public:
	SDL_Triangle triangle = { 0, 0, 0, 0, 0, 0 };
	SDL_Color color = { 0, 0, 0, 0 };

	Triangle(SDL_Triangle &triangle, SDL_Color &color);
	Triangle() {}
	~Triangle() {}
};

class Shape::Rectangle
{
public:
	SDL_Rect rect = { 0, 0, 0, 0 };
	SDL_Color color = { 0, 0, 0, 0 };

	Rectangle(SDL_Rect& rect, SDL_Color& color);
	Rectangle() {}
	~Rectangle() {}
};

class Shape::Polygon
{
public:
	SDL_Polygon polygon;
	SDL_Color color = { 0, 0, 0, 0 };
	
	Polygon(SDL_Polygon &polygon, SDL_Color &color);
	Polygon() {}
	~Polygon() {}
};

#endif // _SHAPES_H