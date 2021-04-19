#include <SDL_mixer.h>
#include <iostream>

#include "Sound.h"

SDL_bool isInitialized3 = SDL_FALSE;
Uint8 numberOfSounds = 0;

Sound::Sound()
{
	numberOfSounds++;

	if (!isInitialized3)
	{
		if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MID | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS) == 0)
		{
			SDL_PrintError(" Could not initialize SDL_mixer. Error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) != 0)
		{
			SDL_PrintError(" Could not open audio. Error: " + std::string(Mix_GetError()));
		}

		isInitialized3 = SDL_TRUE;
	}
}

Sound::~Sound()
{
	numberOfSounds--;

	for (auto &i : musicMap)
	{
		Mix_FreeMusic(i.second);
	}

	for (auto &i : chunksMap)
	{
		Mix_FreeChunk(i.second);
	}

	if (numberOfSounds == 0)
	{
		Mix_Quit();
	}

	musicMap.clear();
	chunksMap.clear();
}

Mix_Music *Sound::LoadMusic(const std::string musicPath)
{
	if (!SDL_CheckFilePath(musicPath))
	{
		SDL_PrintError("std::string parameter from Sound::LoadMusic function call is invalid!");
		return nullptr;
	}

	if (musicMap.find(musicPath) != musicMap.end())
	{
		SDL_PrintError("The sound: " + musicPath + " is already loaded in memory!");
		return nullptr;
	}

	Mix_Music *newMusic = Mix_LoadMUS(musicPath.c_str());

	if (newMusic == nullptr)
	{
		SDL_PrintError(" Could not load music. Error: " + std::string(Mix_GetError()));
	}
	else
	{
		musicMap.insert(std::pair<std::string, Mix_Music *>(musicPath, newMusic));
	}

	return newMusic;
}

Mix_Chunk *Sound::LoadChunk(const std::string chunkPath)
{
	if (!SDL_CheckFilePath(chunkPath))
	{
		SDL_PrintError("std::string parameter from Sound::LoadChunk function call is invalid!");
		return nullptr;
	}

	if (chunksMap.find(chunkPath) != chunksMap.end())
	{
		SDL_PrintError("The sound: " + chunkPath + " is already loaded in memory!");
		return nullptr;
	}

	Mix_Chunk *newChunk = Mix_LoadWAV(chunkPath.c_str());

	if (newChunk == nullptr)
	{
		SDL_PrintError(" Could not load chunk. Error: " + std::string(Mix_GetError()));
	}
	else
	{
		chunksMap.insert(std::pair<std::string, Mix_Chunk *>(chunkPath, newChunk));
	}

	return newChunk;
}

void Sound::PlayMusic(Mix_Music *music, const SDL_bool inALoop)
{
	if (music == nullptr)
	{
		SDL_PrintError("Mix_Music* parameter from Sound::PlayMusic function call is null!");
		return;
	}

	(inALoop) ? Mix_PlayMusic(music, -1) : Mix_PlayMusic(music, 0);
}

void Sound::PauseMusic(const Mix_Music *music)
{
	if (music == nullptr)
	{
		SDL_PrintError("Mix_Music* parameter from Sound::PauseMusic function call is null!");
		return;
	}

	Mix_PauseMusic();
}

void Sound::RemoveMusic(Mix_Music *music)
{
	if (music == nullptr)
	{
		SDL_PrintError("Mix_Music* parameter from Sound::RemoveMusic function call is null!");
		return;
	}

	for (auto &i : musicMap)
	{
		if (i.second == music)
		{
			musicMap.erase(i.first);
			break;
		}
	}

	Mix_FreeMusic(music);
}

void Sound::PlayChunk(Mix_Chunk *chunk)
{
	if (chunk == nullptr)
	{
		SDL_PrintError("Mix_Chunk* parameter from Sound::PlayChunk function call is null!");
		return;
	}

	Mix_PlayChannel(-1, chunk, 0);
}

void Sound::RemoveChunk(Mix_Chunk *chunk)
{
	if (chunk == nullptr)
	{
		SDL_PrintError("Mix_Chunk* parameter from Sound::RemoveChunk function call is null!");
		return;
	}

	for (auto &i : chunksMap)
	{
		if (i.second == chunk)
		{
			musicMap.erase(i.first);
			break;
		}
	}

	Mix_FreeChunk(chunk);
}
