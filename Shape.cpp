#include "Shape.h"

#include <iostream>
#include <algorithm>

Line::Line(const SDL_Point &pos1, const SDL_Point &pos2, const float thickness, const SDL_Color &color, const SDL_Point &rotation)
{
	if (!NULL63(&pos1, "SDL_Point*", "Line constructor") &&
		!NULL63(&pos2, "SDL_Point*", "Line constructor") &&
		!NULL63(&color, "SDL_Color*", "Line constructor") &&
		!NULL63(&rotation, "SDL_Point*", "Line constructor"))
	{
		pointsPos.push_back(pos1);
		pointsPos.push_back(pos2);
		this->thickness = thickness;
		this->color = color;
		this->rotation = rotation;
	}
}

void Line::Draw(SDL_Renderer *renderer)
{
	if (NULL63(renderer, "SDL_Renderer*", "Line::Draw function"))
	{
		return;
	}

	Uint8 r = 0, g = 0, b = 0, a = 0;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	SDL_Point tempPos1 = pointsPos[0], tempPos2 = pointsPos[1];
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (Uint16 i = 0; i < thickness; i++)
	{
		SDL_RenderDrawLine(renderer, tempPos1.x, tempPos1.y, tempPos2.x, tempPos2.y);
		tempPos1.x--;
		tempPos1.y--;
		tempPos2.x--;
		tempPos2.y--;
	}

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

Line::~Line()
{
	pointsPos.clear();
}

Circle::Circle(const SDL_Point &position, const float diameter, const SDL_Color &color, const SDL_Point &rotation)
{
	if (!NULL63(&position, "SDL_Point*", "Circle constructor") &&
		!NULL63(&color, "SDL_Color*", "Circle constructor") &&
		!NULL63(&rotation, "SDL_Point*", "Circle constructor"))
	{
		pointsPos.push_back(position);
		this->diameter = diameter;
		this->color = color;
		this->rotation = rotation;
	}
}

void Circle::Draw(SDL_Renderer *renderer)
{
	if (NULL63(renderer, "SDL_Renderer*", "Circle::Draw function"))
	{
		return;
	}

	Uint8 r = 0, g = 0, b = 0, a = 0;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillCircle(renderer, { pointsPos[0].x, pointsPos[0].y, (Uint16)(diameter / 2) });

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

Circle::~Circle()
{
	pointsPos.clear();
}

Triangle::Triangle(const SDL_Point &pos1, const SDL_Point &pos2, const SDL_Point &pos3, const SDL_Color &color, const SDL_Point &rotation)
{
	if (!NULL63(&pos1, "SDL_Point*", "Triangle constructor") &&
		!NULL63(&color, "SDL_Color*", "Triangle constructor") &&
		!NULL63(&rotation, "SDL_Point*", "Triangle constructor") &&
		!NULL63(&pos2, "SDL_Point*", "Triangle constructor") &&
		!NULL63(&pos3, "SDL_Point*", "Triangle constructor"))
	{
		pointsPos.push_back(pos1);
		pointsPos.push_back(pos2);
		pointsPos.push_back(pos3);
		this->color = color;
		this->rotation = rotation;
	}
}

void Triangle::Draw(SDL_Renderer *renderer)
{
	if (NULL63(renderer, "SDL_Renderer*", "Triangle::Draw function"))
	{
		return;
	}

	Uint8 r = 0, g = 0, b = 0, a = 0;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillTriangle(renderer, pointsPos[0], pointsPos[1], pointsPos[2]);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

Triangle::~Triangle()
{
	pointsPos.clear();
}

Rectangle::Rectangle(const SDL_Point &position, const SDL_FPoint scale, const SDL_Color &color, const SDL_Point &rotation)
{
	if (!NULL63(&position, "SDL_Point*", "Rectangle constructor") &&
		!NULL63(&color, "SDL_Color*", "Rectangle constructor") &&
		!NULL63(&rotation, "SDL_Point*", "Rectangle constructor"))
	{
		pointsPos.push_back(position);
		this->scale = scale;
		this->color = color;
		this->rotation = rotation;
	}
}

void Rectangle::Draw(SDL_Renderer *renderer)
{
	if (NULL63(renderer, "SDL_Renderer*", "Rectangle::Draw function"))
	{
		return;
	}

	Uint8 r = 0, g = 0, b = 0, a = 0;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { pointsPos[0].x - (scale.x / 2), pointsPos[0].y - (scale.y / 2), scale.x, scale.y };
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

Rectangle::~Rectangle()
{
	pointsPos.clear();
}

Polygon::Polygon(const SDL_Polygon &polygonPoss, const SDL_Color &color, const SDL_Point &rotation)
{
	if (!NULL63(&polygonPoss, "SDL_Polygon*", "Polygon constructor") &&
		!NULL63(&color, "SDL_Color*", "Polygon constructor") &&
		!NULL63(&rotation, "SDL_Point*", "Polygon constructor"))
	{
		pointsPos = polygonPoss.points;
		this->color = color;
		this->rotation = rotation;
	}
}

void Polygon::Draw(SDL_Renderer *renderer)
{
	if (NULL63(renderer, "SDL_Renderer*", "Polygon::Draw function"))
	{
		return;
	}

	Uint8 r = 0, g = 0, b = 0, a = 0;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Polygon tempPolygon;
	tempPolygon.points.assign(pointsPos.begin(), pointsPos.end());
	SDL_RenderFillPolygon(renderer, tempPolygon);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

Polygon::~Polygon()
{
	pointsPos.clear();
}