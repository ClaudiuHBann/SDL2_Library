#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL_image.h>
#include <map>
#include <string>

#include "Base.h"

class Texture
{
public:
	Texture();
	~Texture();

	SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string texturePath);
	void RenderTexture(SDL_Renderer* renderer, const SDL_Point* position, const float size, SDL_Texture* texture);
	void RemoveTexture(SDL_Texture* texture);

private:
	std::map<std::string, SDL_Texture *> texturesMap;
};

#endif // _TEXTURE_H