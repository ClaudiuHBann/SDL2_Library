#ifndef _BASE_H
#define _BASE_H

#include <SDL.h>
#include <list>
#include <vector>
#include <string>

#include <iostream>

#define NULL63(var, type, where) IsNull63(var, type, where)

typedef struct SDL_Circle
{
	SDL_Point point;
	Uint16 radius;
}SDL_Circle;

typedef struct SDL_Triangle
{
	SDL_Point point1;
	SDL_Point point2;
	SDL_Point point3;
}SDL_Triangle;

typedef struct SDL_Rectangle
{
	SDL_Point point;
	Uint16 width;
	Uint16 height;
}SDL_Rectangle;

typedef struct SDL_Polygon
{
	std::vector<SDL_Point> points;
}SDL_Polygon;

class Base
{
public:
	Base();
	~Base();

	SDL_Window *CreateWindow(const std::string &windowName = "Window name is not initialized", const Uint16 windowWidth = 640, const Uint16 windowHeight = 480, const Uint32 flags = 0);
	SDL_Renderer *CreateRenderer(SDL_Window *window, const Uint32 flags = 0);
	void RemoveWindow(SDL_Window *window);
	void RemoveRenderer(SDL_Renderer *renderer);

private:
	std::list<SDL_Window *> windowsList;
	std::list<SDL_Renderer *> renderersList;
};



/*
	Additional SDL functions
*/

void SDL_RenderFillCircle(SDL_Renderer *renderer, const SDL_Circle &circle);

void SDL_RenderFillTriangle(SDL_Renderer *renderer, const SDL_Point &pos1, const SDL_Point &pos2, const SDL_Point &pos3);

void SDL_RenderFillPolygon(SDL_Renderer *renderer, const SDL_Polygon &polygon);

bool SDL_PointInPolygon(const SDL_Point &point, const SDL_Polygon &polygon);

template<typename T>
T SDL_GetRandomNumberInRange(T startRange, T endRange)
{
	return startRange + (T)rand() / ((T)RAND_MAX / (T)(endRange - startRange));
}

inline void SDL_PrintError(const std::string &errorMessage);

template<typename T>
bool IsNull63(const T *t, const std::string &type, const std::string &where)
{
	if (t == nullptr)
	{
		SDL_PrintError(type + " parameter from " + where + " call is null!");
		return 1;
	}
	else
	{
		return 0;
	}
}

inline int CrossProduct(const SDL_Point &p1, const SDL_Point &p2);

SDL_bool SDL_CheckFilePath(const std::string &filePath);

SDL_Texture *SDL_GetRendererAsTexture(SDL_Window *window, SDL_Renderer *renderer, const SDL_Rect &windowRect = { 0, 0, 0, 0 });

#endif // _BASE_H