#ifndef _SOUND_H
#define _SOUND_H

#include <SDL_mixer.h>
#include <map>
#include <string>

#include "Base.h"

class Sound
{
public:
	Sound();
	~Sound();

	Mix_Music *LoadMusic(const std::string musicPath);
	Mix_Chunk *LoadChunk(const std::string chunkPath);

	void PlayMusic(Mix_Music *music, const SDL_bool inALoop = SDL_FALSE);
	void PauseMusic(const Mix_Music *music);
	void RemoveMusic(Mix_Music *music);

	void PlayChunk(Mix_Chunk *chunk);
	void RemoveChunk(Mix_Chunk *chunk);

private:
	std::map<std::string, Mix_Music *> musicMap;
	std::map<std::string, Mix_Chunk *> chunksMap;
};

#endif // _SOUND_H