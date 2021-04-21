#include "Shape.h"

#define NULL63(var, type, what, where) if (CheckForNullity(circle, what, where, rotation, scale))\
{\
    this->var = new type;\
    *(this->var) = var;\
	ScaleShape2D();\
}

#define DELETE(var) if (var != nullptr)\
{\
	delete var;\
}

Shape2D::Shape2D(const SDL_Circle &circle, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	NULL63(circle, SDL_Circle, "SDL_Circle*", "Shape2D constructor")
}

Shape2D::Shape2D(const SDL_Triangle &triangle, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	NULL63(triangle, SDL_Triangle, "SDL_Triangle*", "Shape2D constructor")
}

Shape2D::Shape2D(const SDL_Rect &rectangle, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	NULL63(rectangle, SDL_Rect, "SDL_Rect*", "Shape2D constructor")
}

Shape2D::Shape2D(const SDL_Polygon &polygon, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	NULL63(polygon, SDL_Polygon, "SDL_Polygon*", "Shape2D constructor")
}

Shape2D::~Shape2D()
{
	DELETE(circle)
		DELETE(triangle)
		DELETE(rectangle)
		DELETE(polygon)
}

void Shape2D::Draw(SDL_Renderer *renderer)
{

}

void Shape2D::Set(const SDL_Circle &circle, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	*this->circle = circle;
}

void Shape2D::Set(const SDL_Triangle &triangle, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	*this->triangle = triangle;
}

void Shape2D::Set(const SDL_Rect &rectangle, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	*this->rectangle = rectangle;
}

void Shape2D::Set(const SDL_Polygon &polygon, const SDL_Point &rotation, const SDL_FPoint &scale)
{
	*this->polygon = polygon;
}

void Shape2D::ScaleShape2D()
{
	if (circle != nullptr)
	{
		return;
	}

	if (triangle != nullptr)
	{
		return;
	}

	if (rectangle != nullptr)
	{
		return;
	}

	if (polygon != nullptr)
	{
		return;
	}
}