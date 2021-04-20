#include "Shapes.h"

Shape::Circle::Circle(SDL_Point &point, Uint16 radius, SDL_Color &color)
{
	if (&point == nullptr)
	{
		SDL_PrintError("SDL_Point* parameter from Shape::Circle constructor call is null!");
		return;
	}

	if (&color == nullptr)
	{
		SDL_PrintError("SDL_Color* parameter from Shape::Circle constructor call is null!");
		return;
	}

	this->point = point;
	this->radius = radius;
	this->color = color;
}

Shape::Rectangle::Rectangle(SDL_Rect &rect, SDL_Color &color)
{
	if (&rect == nullptr)
	{
		SDL_PrintError("SDL_Rect* parameter from Shape::Rectangle constructor call is null!");
		return;
	}

	if (&color == nullptr)
	{
		SDL_PrintError("SDL_Color* parameter from Shape::Rectangle constructor call is null!");
		return;
	}

	this->rect = rect;
	this->color = color;
}

Shape::Triangle::Triangle(SDL_Triangle &triangle, SDL_Color &color)
{
	if (&triangle == nullptr)
	{
		SDL_PrintError("SDL_Triangle* parameter from Shape::Triangle constructor call is null!");
		return;
	}

	if (&color == nullptr)
	{
		SDL_PrintError("SDL_Color* parameter from Shape::Triangle constructor call is null!");
		return;
	}

	this->triangle = triangle;
	this->color = color;
}

Shape::Polygon::Polygon(SDL_Polygon &polygon, SDL_Color &color)
{
	if (&polygon == nullptr)
	{
		SDL_PrintError("SDL_Polygon* parameter from Shape::Polygon constructor call is null!");
		return;
	}

	if (&color == nullptr)
	{
		SDL_PrintError("SDL_Color* parameter from Shape::Polygon constructor call is null!");
		return;
	}

	this->polygon = polygon;
	this->color = color;
}
