#ifndef _SHAPE_H
#define _SHAPE_H

#include <SDL.h>

#include "Base.h"

class Shape2D
{
public:
	std::vector<SDL_Point> pointsPos;
	SDL_Point rotation = { 0, 0 };
	SDL_Color color = { 0, 0, 0 ,0 };

	Shape2D() {}
	virtual ~Shape2D() {}

	virtual void Draw(SDL_Renderer *renderer) = 0;
};

class Line : public Shape2D
{
public:
	float thickness = 1.0f;

	Line(const SDL_Point &pos1, const SDL_Point &pos2, const float thickness, const SDL_Color &color = { 0, 0, 0, 0 }, const SDL_Point &rotation = { 0, 0 });
	Line() {}
	~Line();

	void Draw(SDL_Renderer *renderer) override;
};

class Circle : public Shape2D
{
public:
	float diameter = 1.0f;

	Circle(const SDL_Point &position, const float diameter, const SDL_Color &color = { 0, 0, 0, 0 }, const SDL_Point &rotation = { 0, 0 });
	Circle() {}
	~Circle();

	void Draw(SDL_Renderer *renderer) override;
};

class Triangle : public Shape2D
{
public:
	SDL_FPoint scale = { 1.0f, 1.0f };

	Triangle(const SDL_Point &position, const SDL_FPoint scale, const SDL_Color &color = { 0, 0, 0, 0 }, const SDL_Point &rotation = { 0, 0 });
	Triangle() {}
	~Triangle();

	void Draw(SDL_Renderer *renderer) override;
};

class Rectangle : public Shape2D
{
public:
	SDL_FPoint scale = { 1.0f, 1.0f };

	Rectangle();
	~Rectangle();

	void Draw(SDL_Renderer *renderer) override;
};

class Polygon : public Shape2D
{
public:
	SDL_FPoint scale = { 1.0f, 1.0f };

	Polygon();
	~Polygon();

	void Draw(SDL_Renderer *renderer) override;
};

#endif // _SHAPE_H
