#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <iostream>
#include <time.h>

#include "Snake.h"
#include "Base.h"

Snake::Snake(SDL_Window *window, SDL_Renderer *renderer)
{
	//Initialize window and render variables
	this->window = window;
	this->renderer = renderer;
}

Snake::~Snake()
{
	//Clear snake tail list
	snakeTailPositions.clear();
}

void Snake::Start()
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

	//Create map texture
	Map();

	//Initialize snake head position with a random position on the map
	snakeHeadPosition.x = rand() % (WINDOW_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
	snakeHeadPosition.y = rand() % (WINDOW_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;

	//Initialize last time snake moved
	lastTime = SDL_GetTicks();

	//Spawn apple in a random position
	applePosition.x = rand() % (WINDOW_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
	applePosition.y = rand() % (WINDOW_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;

	//If the apple position is on the snake head position change the apple position
	while (snakeHeadPosition.x == applePosition.x && snakeHeadPosition.y == applePosition.y)
	{
		applePosition.x = rand() % (WINDOW_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
		applePosition.y = rand() % (WINDOW_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;
	}

	//Load apple texture
	appleTexture = texture.LoadTexture(renderer, appleTexturePath);

	//Load music and play in a loop
	backgroundMusic = music.LoadMusic(musicPath);
	music.PlayMusic(backgroundMusic, SDL_TRUE);
}

void Snake::Update()
{
	if (!isStarted)
	{
		StartMenu();
	}
	else
	{
		SnakeMovement();
		Apple();
		Draw();
	}
}

void Snake::Map()
{
	//Draw the map and panel
	SDL_Rect squareRect = { 0, 0, SQUARE_SIZE, SQUARE_SIZE };
	SDL_Rect mapRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

	//First change the background color so we need to draw just half the squares
	SDL_SetRenderDrawColor(renderer, 170, 215, 81, 0);
	SDL_RenderFillRect(renderer, &mapRect);

	//Draw the squares
	SDL_SetRenderDrawColor(renderer, 162, 209, 73, 0);

	for (int i = -1; i <= WINDOW_HEIGHT / SQUARE_SIZE; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / SQUARE_SIZE / 2; j++)
		{
			if (i % 2 == 0)
			{
				squareRect.x = j * SQUARE_SIZE * 2;
			}
			else
			{
				squareRect.x = (j + 1) * SQUARE_SIZE * 2 - SQUARE_SIZE;
			}

			SDL_RenderFillRect(renderer, &squareRect);
		}

		squareRect.y = i * SQUARE_SIZE;
	}

	//Save the map into a texture
	mapTexture = SDL_GetRendererAsTexture(window, renderer, nullptr);
}

void Snake::Draw()
{
	//Draw the texture with the map
	SDL_RenderCopy(renderer, mapTexture, nullptr, &mapRect);

	//Draw apple
	SDL_Point tempPoint1 = { applePosition.x, applePosition.y };
	texture.RenderTexture(renderer, &tempPoint1, 0.1125f, appleTexture);

	//Draw snake head
	SDL_SetRenderDrawColor(renderer, 72, 118, 237, 0);
	SDL_RenderFillRect(renderer, &snakeHeadPosition);

	//Draw snake tail
	SDL_SetRenderDrawColor(renderer, 72, 118, 237, 0);
	for (auto &i : snakeTailPositions)
	{
		SDL_RenderFillRect(renderer, &i);
	}

	//Draw score
	SDL_Point tempPoint2 = { 0, 0 };
	text.RenderText(renderer, &tempPoint2, scoreAsText, 1.0f, arialFont, &textColor);

	//Draw highscore
	SDL_Point tempPoint3 = { WINDOW_WIDTH - 175, 0 };
	text.RenderText(renderer, &tempPoint3, highscoreAsText, 1.0f, arialFont, &textColor);

	//Update the screen
	SDL_RenderPresent(renderer);
}

void Snake::Keys(SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_UP:
			if (snakeHeadDirection != DOWN || snakeTailLength == 0)
			{
				snakeHeadDirection = UP;
			}

			break;

		case SDLK_LEFT:
			if (snakeHeadDirection != RIGHT || snakeTailLength == 0)
			{
				snakeHeadDirection = LEFT;
			}

			break;

		case SDLK_DOWN:
			if (snakeHeadDirection != UP || snakeTailLength == 0)
			{
				snakeHeadDirection = DOWN;
			}

			break;

		case SDLK_RIGHT:
			if (snakeHeadDirection != LEFT || snakeTailLength == 0)
			{
				snakeHeadDirection = RIGHT;
			}

			break;

		default:
			break;
		}
	}
}

void Snake::SnakeMovement()
{
	if (lastTime < SDL_GetTicks())
	{
		lastTime += timeBetweenSnakeMoves;

		//Add snake tail and update snake tail positions
		if (snakeTailLength > lastSnakeTailLength)
		{
			snakeTailPositions.push_back({ snakeHeadPosition.x, snakeHeadPosition.y, SQUARE_SIZE, SQUARE_SIZE });
			lastSnakeTailLength++;
		}
		else if (snakeTailLength > 0)
		{
			snakeTailPositions.pop_front();
			snakeTailPositions.push_back({ snakeHeadPosition.x, snakeHeadPosition.y, SQUARE_SIZE, SQUARE_SIZE });
		}

		//Move the next snake head
		switch (snakeHeadDirection)
		{
		case UP:
			snakeHeadPosition.y -= SQUARE_SIZE;
			break;

		case LEFT:
			snakeHeadPosition.x -= SQUARE_SIZE;
			break;

		case DOWN:
			snakeHeadPosition.y += SQUARE_SIZE;
			break;

		case RIGHT:
			snakeHeadPosition.x += SQUARE_SIZE;
			break;

		default:
			break;
		}

		//Check if the snake head is outside the map and if it is move it to the opposite extremity
		if (snakeHeadPosition.x < 0)
		{
			snakeHeadPosition.x = WINDOW_WIDTH - SQUARE_SIZE;
		}
		else if (snakeHeadPosition.x >= WINDOW_WIDTH)
		{
			snakeHeadPosition.x = 0;
		}
		else if (snakeHeadPosition.y < 0)
		{
			snakeHeadPosition.y = WINDOW_HEIGHT - SQUARE_SIZE;
		}
		else if (snakeHeadPosition.y >= WINDOW_HEIGHT)
		{
			snakeHeadPosition.y = 0;
		}

		//Check if snake head bites himself
		for (auto &i : snakeTailPositions)
		{
			if (i.x == snakeHeadPosition.x && i.y == snakeHeadPosition.y)
			{
				music.PlayChunk(deadSound);
				GameOver();
				break;
			}
		}

		//Update score when snake moves, no need to update score more than once every 100 ms
		Score();
	}
}

void Snake::Apple()
{
	//Check if snake head is on the apple
	if (snakeHeadPosition.x == applePosition.x && snakeHeadPosition.y == applePosition.y)
	{
		music.PlayChunk(appleEatenSound);

		snakeTailLength++;

		//Spawn another apple but not on snake
		bool appleIsFree = true;
		while (appleIsFree)
		{
			appleIsFree = false;

			applePosition.x = rand() % (WINDOW_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
			applePosition.y = rand() % (WINDOW_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;

			for (auto &i : snakeTailPositions)
			{
				if ((i.x == applePosition.x && i.y == applePosition.y) || (snakeHeadPosition.x == i.x && snakeHeadPosition.y == i.y))
				{
					appleIsFree = true;
				}
			}
		}
	}
}

void Snake::Score()
{
	//Update score
	sprintf(scoreAsText, "Score: %d", snakeTailLength);

	//Change highscore
	if (snakeTailLength > highscore)
	{
		highscore = snakeTailLength;
	}

	//Update highscore
	sprintf(highscoreAsText, "Highscore: %d", highscore);
}

void Snake::GameOver()
{
	//Reset variables

	//Delete tail
	snakeTailPositions.clear();

	//Reset tail length variables
	snakeTailLength = 0;
	lastSnakeTailLength = 0;

	//Reset the snake head direction to neutral
	snakeHeadDirection = -1;

	//Spawn snake head in a random position
	snakeHeadPosition.x = rand() % (WINDOW_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
	snakeHeadPosition.y = rand() % (WINDOW_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;

	//Reset last time
	lastTime = SDL_GetTicks();

	//Spawn new apple in a random position
	applePosition.x = rand() % (WINDOW_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
	applePosition.y = rand() % (WINDOW_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;

	//If the apple position is on the snake head position change the apple position
	while (snakeHeadPosition.x == applePosition.x && snakeHeadPosition.y == applePosition.y)
	{
		applePosition.x = rand() % (WINDOW_WIDTH / SQUARE_SIZE) * SQUARE_SIZE;
		applePosition.y = rand() % (WINDOW_HEIGHT / SQUARE_SIZE) * SQUARE_SIZE;
	}
}

void Snake::StartMenu()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &windowRect);
	startButton.DrawButton(renderer);
	SDL_Point tempPoint1 = { 200, 300 };
	text.RenderText(renderer, &tempPoint1, developer1, 1.0f, arialFont, &buttonColor);
	SDL_Point tempPoint2 = { 250, 400 };
	text.RenderText(renderer, &tempPoint2, developer2, 1.0f, arialFont, &buttonColor);
	SDL_RenderPresent(renderer);

	if (startButton.IsButtonPressed() && !isStarted)
	{
		isStarted = true;
	}
}
