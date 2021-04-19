#pragma once

/*
	Worst 500+ lines of code

	Work time: ~8 hours

	Bugs? I would hope not, but you will find some for sure! :(
*/

#include <SDL.h>
#include <string>

#include "Text.h"
#include "Music.h"
#include "UI.h"
#include "Texture.h"

#define WINDOW_NAME "Artificial Intelligence Game"
#define SQUARE_SIZE 50
#define LINE_THICKNESS 3
#define WINDOW_WIDTH 12 * (SQUARE_SIZE + LINE_THICKNESS) - LINE_THICKNESS
#define WINDOW_HEIGHT 12 * (SQUARE_SIZE + LINE_THICKNESS) - LINE_THICKNESS
#define NUMBER_OF_WALLS 30
#define NUMBER_OF_GOLD_BAGS 3
#define NUMBER_OF_ENEMIES 3

enum Directions
{
	UP = 0,
	LEFT = 1,
	DOWN = 2,
	RIGHT = 3,
};

class AIGame
{
public:
	AIGame(SDL_Window* window, SDL_Renderer* renderer);
	~AIGame();

	void Start();
	void Update();
	void Keys(SDL_Event* event);

private:
	void Map();
	void Draw();
	void Score();
	void GameOver();
	void GoldBags();
	void Enemies();
	void Shoot();
	bool CheckForWalls(int playersXPos, int playersYPos);
	void StartMenu();
	void NoGoldBagsOrEnemiesLeft();

	//Main game variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Map variables
	SDL_Rect tempRect = { 0, 0, SQUARE_SIZE, SQUARE_SIZE };
	SDL_Texture* mapTexture = nullptr;
	SDL_Rect mapRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SDL_Point wallsPositions[NUMBER_OF_WALLS] =
	{
		{ 1, 1 }, { 4, 1 },
		{ 1, 2 }, { 4, 2 }, { 9, 2 },
		{ 1, 3 }, { 4, 3 }, { 6, 3 }, { 7, 3 }, { 9, 3 },
		{ 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 }, { 9, 4 },
		{ 1, 5 }, { 9, 5 },
		{ 1, 6 }, { 9, 6 },
		{ 1, 7 },
		{ 1, 8 }, { 7, 8 }, { 8, 8 }, { 9, 8 }, { 10, 8 },
		{ 1, 9 },
		{ 3, 10 }, { 4, 10 }, { 5, 10 }, { 6, 10 },
	};
	SDL_Point goldBagsPositions[NUMBER_OF_GOLD_BAGS] = { { 2, 2 }, { 10, 1 }, { 8, 10 } };
	SDL_Point enemiesPositions[NUMBER_OF_ENEMIES] = { { 7, 1 }, { 11, 5 }, { 5, 11 } };
	SDL_Point goldBagsAndEnemiesPositionsCopy[NUMBER_OF_ENEMIES + NUMBER_OF_GOLD_BAGS] = { { 2, 2 }, { 10, 1 }, { 8, 10 }, { 7, 1 }, { 11, 5 }, { 5, 11 } };

	//Player variables
	int playerDirection = RIGHT;
	SDL_Rect playerPosition = { 0, 11 * (SQUARE_SIZE + LINE_THICKNESS), SQUARE_SIZE, SQUARE_SIZE };

	//Time variables
	int lastTime;
	int timeBetweenSnakeMoves = 100;

	//Exe path
	std::string basePath = SDL_GetBasePath();

	//Text variables
	Text text;
	TTF_Font* arialFont = nullptr;
	std::string fontPath = basePath + "Resources\\arial.ttf";
	SDL_Color textColor = { 255, 255, 255, 255 };

	//Score variables
	int score = 0;
	char scoreAsText[10];
	int highscore = 0;
	char highscoreAsText[14];

	//Texture variables
	Texture texture;
	SDL_Texture* playerTexture[4];
	std::string playerTexturePath[4] =
	{
	basePath + "Resources\\playerUP.png",
	basePath + "Resources\\playerLEFT.png",
	basePath + "Resources\\playerDOWN.png",
	basePath + "Resources\\playerRIGHT.png"
	};
	SDL_Texture* enemyTexture[4];
	std::string enemyTexturePath[4] =
	{
	basePath + "Resources\\enemyUP.png",
	basePath + "Resources\\enemyLEFT.png",
	basePath + "Resources\\enemyRIGHT.png",
	basePath + "Resources\\enemyDOWN.png"
	};
	SDL_Texture* goldTexture;
	std::string goldTexturePath = basePath + "Resources\\gold.png";

	//Music variables
	Music music;
	std::string musicPath = basePath + "Resources\\background music.mp3";
	Mix_Music* backgroundMusic = nullptr;

	//User interface
	Button startButton;
	SDL_Rect buttonRect = { ((WINDOW_WIDTH) - 150) / 2, 150 - 25, 150, 50 };
	SDL_Color buttonColor = { 0, 255, 0, 0 };
	std::string buttonText = "Start Game";
	SDL_Color buttonTextColor = { 0, 0, 0, 0 };
	SDL_Rect windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	std::string tutorial = "Tutorial:";
	std::string tip1 = "To move use UP, LEFT, RIGHT or DOWN arrows";
	std::string tip2 = "To shoot press space bar";
	std::string tip3 = "To restart game press 'R'";
	std::string developer1 = "Developer: Hermann Claudiu-Andrei";
	bool isStarted = false;
};
