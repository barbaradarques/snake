#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include "game.h"

class Renderer {
	public:
		Renderer(Game game);
		~Renderer();
		void drawAll();
	private:
		void drawSnake();
		void drawFood();
		void drawMap();
}

#endif