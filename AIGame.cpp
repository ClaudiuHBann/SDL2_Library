#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <iostream>

#include "AIGame.h"

AIGame::AIGame(SDL_Window* window, SDL_Renderer* renderer)
{
	//Initialize window and render variables
	this->window = window;
	this->renderer = renderer;
}

AIGame::~AIGame()
{
	SDL_DestroyTexture(mapTexture);
}

void AIGame::Start()
{
	//Load text font
	arialFont = text.LoadFont(fontPath, 25);

	//Init button variables for start menu
	startButton.buttonRect = buttonRect;
	startButton.buttonColor = buttonColor;
	startButton.font = arialFont;
	startButton.size = 1.0f;
	startButton.buttonText = "Start Game";
	startButton.textColor = buttonTextColor;
	startButton.buttonTextFlags = MIDDLE;
	UI_Init();

	//Initialize random seed
	srand(time(NULL));

	//Load player textures
	playerTexture[0] = texture.LoadTexture(renderer, playerTexturePath[0]);
	playerTexture[1] = texture.LoadTexture(renderer, playerTexturePath[1]);
	playerTexture[2] = texture.LoadTexture(renderer, playerTexturePath[2]);
	playerTexture[3] = texture.LoadTexture(renderer, playerTexturePath[3]);

	//Load enemy textures
	enemyTexture[0] = texture.LoadTexture(renderer, enemyTexturePath[0]);
	enemyTexture[1] = texture.LoadTexture(renderer, enemyTexturePath[1]);
	enemyTexture[2] = texture.LoadTexture(renderer, enemyTexturePath[2]);
	enemyTexture[3] = texture.LoadTexture(renderer, enemyTexturePath[3]);

	//Load gold texture
	goldTexture = texture.LoadTexture(renderer, goldTexturePath);

	//Create map texture
	Map();

	//Load music and play in a loop
	backgroundMusic = music.LoadMusic(musicPath);
	music.PlayMusic(backgroundMusic, true);

	//Rules
	std::cout << std::endl << " RULES !" << std::endl;
	std::cout << std::endl << " One move = -1 points." << std::endl;
	std::cout << std::endl << " One shoot = -25 points." << std::endl;
	std::cout << std::endl << " One monster killed = +50 points." << std::endl;
	std::cout << std::endl << " One treasure = +100 points." << std::endl;
	std::cout << std::endl << " One melee attack = -1000 points." << std::endl;
}

void AIGame::Update()
{
	if (!isStarted)
	{
		StartMenu();
	}
	else
	{
		Score();
		Draw();
		Enemies();
		GoldBags();
		NoGoldBagsOrEnemiesLeft();
	}
}

void AIGame::Map()
{
	SDL_Rect mapLines = { SQUARE_SIZE, 0, LINE_THICKNESS, WINDOW_HEIGHT };

	//Draw background
	SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
	SDL_RenderFillRect(renderer, &mapRect);

	//Draw the black lines as long as the screen width or height
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (int i = 0; i < (WINDOW_WIDTH) / (SQUARE_SIZE + LINE_THICKNESS); i++)
	{
		SDL_RenderFillRect(renderer, &mapLines);

		mapLines.x += SQUARE_SIZE + LINE_THICKNESS;
	}

	mapLines = { 0, SQUARE_SIZE, WINDOW_WIDTH, LINE_THICKNESS };

	for (int i = 0; i < (WINDOW_HEIGHT) / (SQUARE_SIZE + LINE_THICKNESS); i++)
	{
		SDL_RenderFillRect(renderer, &mapLines);

		mapLines.y += SQUARE_SIZE + LINE_THICKNESS;
	}

	//Draw walls
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for (int i = 0; i < NUMBER_OF_WALLS; i++)
	{
		tempRect = { wallsPositions[i].x * (SQUARE_SIZE + LINE_THICKNESS), wallsPositions[i].y * (SQUARE_SIZE + LINE_THICKNESS), SQUARE_SIZE, SQUARE_SIZE };
		SDL_RenderFillRect(renderer, &tempRect);
	}

	//Draw gold bags
	for (int i = 0; i < NUMBER_OF_GOLD_BAGS; i++)
	{
		tempRect = { goldBagsPositions[i].x * (SQUARE_SIZE + LINE_THICKNESS), goldBagsPositions[i].y * (SQUARE_SIZE + LINE_THICKNESS), SQUARE_SIZE, SQUARE_SIZE };
		texture.RenderTexture(renderer, tempRect.x, tempRect.y + 5, 0.2f, goldTexture);
	}

	//Draw enemies
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		tempRect = { enemiesPositions[i].x * (SQUARE_SIZE + LINE_THICKNESS), enemiesPositions[i].y * (SQUARE_SIZE + LINE_THICKNESS), SQUARE_SIZE, SQUARE_SIZE };
		texture.RenderTexture(renderer, tempRect.x, tempRect.y + 5, 0.2f, enemyTexture[rand() % 4]);
	}

	//Save the map into a texture
	SDL_Surface* mapSurface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);

	if (mapSurface == nullptr)
	{
		std::cout << std::endl << " Could not create screen surface for map and panel for snake game. Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		SDL_RenderReadPixels(renderer, nullptr, mapSurface->format->format, mapSurface->pixels, mapSurface->pitch);
		mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);

		if (mapTexture == nullptr)
		{
			std::cout << std::endl << " Could not create map and panel texture for snake game. Error: " << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(mapSurface);
	}
}

void AIGame::Draw()
{
	//Draw the texture with the map
	SDL_RenderCopy(renderer, mapTexture, nullptr, &mapRect);

	//Draw player
	texture.RenderTexture(renderer, playerPosition.x, playerPosition.y + 5, 0.2f, playerTexture[playerDirection]);

	//Draw score
	text.RenderText(renderer, 0, 0, scoreAsText, 1.0f, arialFont, &textColor);

	//Draw highscore
	text.RenderText(renderer, WINDOW_WIDTH - 175, 0, highscoreAsText, 1.0f, arialFont, &textColor);

	//Update the screen
	SDL_RenderPresent(renderer);
}

//This function is in fact the player movement...
void AIGame::Keys(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_UP:
			if (playerPosition.y - (SQUARE_SIZE + LINE_THICKNESS) >= 0 && playerDirection == UP && !CheckForWalls(playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS), playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) - 1))
			{
				playerPosition.y -= SQUARE_SIZE + LINE_THICKNESS;
				score--;
			}
			else if (playerDirection != UP)
			{
				playerDirection = UP;
				score--;
			}

			break;

		case SDLK_LEFT:
			if (playerPosition.x - (SQUARE_SIZE + LINE_THICKNESS) >= 0 && playerDirection == LEFT && !CheckForWalls(playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) - 1, playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS)))
			{
				playerPosition.x -= SQUARE_SIZE + LINE_THICKNESS;
				score--;
			}
			else if(playerDirection != LEFT)
			{
				playerDirection = LEFT;
				score--;
			}

			break;

		case SDLK_DOWN:
			if (playerPosition.y + (SQUARE_SIZE + LINE_THICKNESS) <= WINDOW_HEIGHT && playerDirection == DOWN && !CheckForWalls(playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS), playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) + 1))
			{
				playerPosition.y += SQUARE_SIZE + LINE_THICKNESS;
				score--;
			}
			else if (playerDirection != DOWN)
			{
				playerDirection = DOWN;
				score--;
			}

			break;

		case SDLK_RIGHT:
			if (playerPosition.x + (SQUARE_SIZE + LINE_THICKNESS) < WINDOW_WIDTH && playerDirection == RIGHT && !CheckForWalls(playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) + 1, playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS)))
			{
				playerPosition.x += SQUARE_SIZE + LINE_THICKNESS;
				score--;
			}
			else if (playerDirection != RIGHT)
			{
				playerDirection = RIGHT;
				score--;
			}

			break;

		case SDLK_SPACE:
			Shoot();
			break;

		case SDLK_r:
			GameOver();
			break;

		default:
			break;
		}
	}
}

void AIGame::Score()
{
	//Update score
	sprintf(scoreAsText, "Score: %d", score);

	//Update highscore
	sprintf(highscoreAsText, "Highscore: %d", highscore);
}

void AIGame::GameOver()
{
	//Change highscore
	if (score > highscore)
	{
		highscore = score;
	}

	//Reset score
	score = 0;

	//Reset gold bags and enemies positions
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		enemiesPositions[i].x = goldBagsAndEnemiesPositionsCopy[i + NUMBER_OF_GOLD_BAGS].x;
		enemiesPositions[i].y = goldBagsAndEnemiesPositionsCopy[i + NUMBER_OF_GOLD_BAGS].y;
	}

	for (int i = 0; i < NUMBER_OF_GOLD_BAGS; i++)
	{
		goldBagsPositions[i].x = goldBagsAndEnemiesPositionsCopy[i].x;
		goldBagsPositions[i].y = goldBagsAndEnemiesPositionsCopy[i].y;
	}

	//Reset map
	Map();

	//Reset player position
	playerPosition.x = 0;
	playerPosition.y = 11 * (SQUARE_SIZE + LINE_THICKNESS);
}

void AIGame::GoldBags()
{
	for (int i = 0; i < NUMBER_OF_GOLD_BAGS; i++)
	{
		if (playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) == goldBagsPositions[i].x && playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) == goldBagsPositions[i].y)
		{
			goldBagsPositions[i].x = -1;
			goldBagsPositions[i].y = -1;

			score += 100;

			SDL_DestroyTexture(mapTexture);
			Map();

			break;
		}
	}
}

void AIGame::Enemies()
{
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		if (playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) == enemiesPositions[i].x && playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) == enemiesPositions[i].y)
		{
			enemiesPositions[i].x = -1;
			enemiesPositions[i].y = -1;

			score -= 1000;

			SDL_DestroyTexture(mapTexture);
			Map();

			break;
		}
	}
}

void AIGame::Shoot()
{
	bool enemyIsAround = false;

	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		if ((playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) + 1 == enemiesPositions[i].x && playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) == enemiesPositions[i].y && playerDirection == RIGHT) ||
			(playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) - 1 == enemiesPositions[i].x && playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) == enemiesPositions[i].y && playerDirection == LEFT) ||
			(playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) == enemiesPositions[i].x && playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) + 1 == enemiesPositions[i].y && playerDirection == DOWN) ||
			(playerPosition.x / (SQUARE_SIZE + LINE_THICKNESS) == enemiesPositions[i].x && playerPosition.y / (SQUARE_SIZE + LINE_THICKNESS) - 1 == enemiesPositions[i].y && playerDirection == UP))
		{
			enemyIsAround = true;

			enemiesPositions[i].x = -1;
			enemiesPositions[i].y = -1;

			SDL_DestroyTexture(mapTexture);
			Map();

			break;
		}
	}

	if (enemyIsAround)
	{
		score += 24;
	}
	else
	{
		score -= 26;
	}
}

bool AIGame::CheckForWalls(int playersXPos, int playersYPos)
{
	for (int i = 0; i < NUMBER_OF_WALLS; i++)
	{
		if (playersXPos == wallsPositions[i].x && playersYPos == wallsPositions[i].y)
		{
			return true;
		}
	}

	return false;
}

void AIGame::StartMenu()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &windowRect);
	startButton.DrawButton(renderer);
	text.RenderText(renderer, 275, 250, tutorial, 1.0f, arialFont, &buttonColor);
	text.RenderText(renderer, 50, 300, tip1, 1.0f, arialFont, &buttonColor);
	text.RenderText(renderer, 175, 350, tip2, 1.0f, arialFont, &buttonColor);
	text.RenderText(renderer, 175, 400, tip3, 1.0f, arialFont, &buttonColor);
	text.RenderText(renderer, 110, 550, developer1, 1.0f, arialFont, &buttonColor);
	SDL_RenderPresent(renderer);

	if (startButton.IsButtonPressed() && !isStarted)
	{
		isStarted = true;
	}
}

void AIGame::NoGoldBagsOrEnemiesLeft()
{
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		if (!(enemiesPositions[i].x == -1 && enemiesPositions[i].y == -1))
		{
			return;
		}
	}

	for (int i = 0; i < NUMBER_OF_GOLD_BAGS; i++)
	{
		if (!(goldBagsPositions[i].x == -1 && goldBagsPositions[i].y == -1))
		{
			return;
		}
	}

	GameOver();
}
