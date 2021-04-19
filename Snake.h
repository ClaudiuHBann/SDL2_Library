#pragma once

#include <SDL.h>
#include <list>

#include "Text.h"
#include "Sound.h"
#include "UI.h"
#include "Texture.h"

#define WINDOW_NAME "Snake"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SQUARE_SIZE 25

enum Directions
{
	UP = 0,
	LEFT = 1,
	DOWN = 2,
	RIGHT = 3,
};

class Snake
{
public:
	Snake(SDL_Window* window, SDL_Renderer* renderer);
	~Snake();

	void Start();
	void Update();
	void Keys(SDL_Event* event);

private:
	void Map();
	void Draw();
	void SnakeMovement();
	void Apple();
	void Score();
	void GameOver();
	void StartMenu();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Map variables
	SDL_Texture* mapTexture = nullptr;
	SDL_Rect mapRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

	//Snake head variables
	int snakeHeadDirection = -1;
	SDL_Rect snakeHeadPosition = { 0, 0, SQUARE_SIZE, SQUARE_SIZE };

	//Snake tail variables
	int snakeTailLength = 0;
	int lastSnakeTailLength = 0;
	std::list<SDL_Rect> snakeTailPositions;

	//Time variables
	int lastTime = 0;
	int timeBetweenSnakeMoves = 100;

	//Apple variable
	SDL_Rect applePosition = { 0, 0, SQUARE_SIZE, SQUARE_SIZE };

	//Exe path
	std::string basePath = SDL_GetBasePath();

	//Text variables
	Text text;
	TTF_Font* arialFont = nullptr;
	std::string fontPath = basePath + "Resources\\arial.ttf";
	SDL_Color textColor = { 255, 255, 255, 0 };

	//Score variables
	char scoreAsText[10] = "";
	int highscore = 0;
	char highscoreAsText[14] = "";

	//Texture variables
	Texture texture;

	//Apple variables
	SDL_Texture* appleTexture = nullptr;
	std::string appleTexturePath = basePath + "Resources\\apple.png";

	//Music variables
	Sound music;
	std::string musicPath = basePath + "Resources\\background music.mp3";
	Mix_Music* backgroundMusic = nullptr;

	//Sound variables
	std::string deadSoundPath = basePath + "Resources\\die sound.wav";
	Mix_Chunk* deadSound = music.LoadChunk(deadSoundPath);

	std::string appleEatenSoundPath = basePath + "Resources\\apple eat sound.wav";
	Mix_Chunk* appleEatenSound = music.LoadChunk(appleEatenSoundPath);

	//User interface
	Button startButton;
	SDL_Rect buttonRect = { 325, 200, 150, 50 };
	SDL_Color buttonColor = { 0, 255, 0, 0 };
	std::string buttonText = "Start Game";
	SDL_Color buttonTextColor = { 0, 0, 0, 0 };
	SDL_Rect windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	std::string developer1 = "Developer: Hermann Claudiu-Andrei";
	std::string developer2 = "Facebook: Claudiu HBann";
	bool isStarted = false;
};