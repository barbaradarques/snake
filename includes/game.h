#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <deque>
#include <ctime>
#include "utils.h"

typedef std::pair<float, float> PAIR;

#define STILL 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define TRUE 1
#define FALSE 0
#define START 11
#define INGAME 22
#define GAME_OVER 33
#define PAUSE 44

class Game {
	public:
		Game(sf::RenderWindow &window);
		~Game();
		std::deque<PAIR> getSnake();
		void setDir(int new_dir);
		int getScore();
		int getLives();
		int getStatus();
		PAIR getFoodPos();
		sf::Sprite getFoodSprite(); // fazer um jeito de a outra thread guardar o FoodSprite
		void getMap();
		void updateAll();
		void drawAll();
		void restart();
		int status;
		sf::Font mainFont;
	private:
		void updateSnake();
		void genNewFood();
		void genNewSnake();
		void genMap();
		void drawSnake();
		void drawFood();
		void drawMap();
		int didSelfCollide(PAIR moving_part);
		void startNewGame();
		void loadResources();
		sf::RenderWindow& window;
		std::vector<sf::Sprite> foodSprites;
		std::deque<PAIR> snake;
		int dir; // direção de movimentação da cobra
		int prevDir; // direção anterior (ou seja, direção oposta não pode ser tomada)
		int speed;
		PAIR foodPos;
		int spriteRow;
		int spriteCol;
		int score;
		int lives;
		int tile_size;
		int cols;
		int rows;
		sf::RectangleShape first_square;
		sf::RectangleShape square;
		sf::Texture spritesheet;
		sf::Sprite food;
		sf::SoundBuffer biteBuffer;
		sf::Sound biteSound;
		sf::SoundBuffer gameoverBuffer;
		sf::Sound gameoverSound;

};

#endif