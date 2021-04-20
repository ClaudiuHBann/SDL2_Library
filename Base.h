#ifndef _BASE_H
#define _BASE_H

#include <SDL.h>
#include <list>
#include <string>

class Base
{
public:
	Base();
	~Base();

	SDL_Window *CreateWindow(const std::string& windowName = "Window name is not initialized", const Uint16 windowWidth = 640, const Uint16 windowHeight = 480, const Uint32 flags = 0);
	SDL_Renderer *CreateRenderer(SDL_Window *window, const Uint32 flags = 0);
	void RemoveWindow(SDL_Window *window);
	void RemoveRenderer(SDL_Renderer *renderer);

private:
	std::list<SDL_Window *> windowsList;
	std::list<SDL_Renderer *> renderersList;
};

//Additional SDL functions
void SDL_RenderFillCircle(SDL_Renderer *renderer, const SDL_Point &position, const Uint16 radius);

template<typename T>
T SDL_GetRandomNumberInRange(T startRange, T endRange)
{
	return startRange + (T)rand() / ((T)RAND_MAX / (T)(endRange - startRange));
}

inline void SDL_PrintError(const std::string& errorMessage);

SDL_bool SDL_CheckFilePath(const std::string& filePath);

SDL_Texture *SDL_GetRendererAsTexture(SDL_Window *window, SDL_Renderer *renderer, const SDL_Rect &windowRect = { 0, 0, 0, 0 });

#endif // _BASE_H