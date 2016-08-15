#include "game.hpp"
#include <unistd.h>



Game::Game(sf::RenderWindow &arg_window) : window(arg_window){
	loadResources();
	startNewGame(); // delegado a uma função pois vai ser reutilizado para novas partidas
}

Game::~Game(){
	// destruir o que precisar ser explicitamente destruído
}

void Game::updateAll(){
	// se não acabar colocando mais coisa aqui muda pro updateSNake direto
	updateSnake();
}

void Game::drawAll(){
	drawSnake();
	drawFood();
}

void Game::updateSnake(){
	/* 
		Lógica:
		O andar consiste em adicionar um segmento à cabeça e reduzir a cauda.
	*/

	PAIR moving_part = snake.front(); // salva a cabeça pra depois incrementá-la
	switch(dir){
		case STILL:
			return;
		case UP: // [0,-1]
			moving_part.second -= speed;
			break;
		case DOWN: // [0,1]
			moving_part.second += speed;
			break;
		case LEFT: // [-1,0]
			moving_part.first -= speed;
			break;
		case RIGHT: // [1,0]
			moving_part.first += speed;
			break;
	}

	// checa colisão com as paredes(futuramente substituído por colisão com mapa)
	// if(moving_part.first<0 || moving_part.second<0
	// 	|| moving_part.first>=cols || moving_part.second>=rows){
	// 	dir = STILL;
	// 	status = GAME_OVER;
	// 	return;
	// }

	if(moving_part.first < 0){
		moving_part.first = cols;
	} else if(moving_part.second < 0){
		moving_part.second = rows;
	} else if(moving_part.first >= cols){
		moving_part.first = 0;
	} else if(moving_part.second >= rows){
		moving_part.second = 0;
	}
	// pode depois juntar tudo em um só if, mas acho que não faz diferença, apesar de gerar mais código
	// checa colisão consigo mesmo
	if(didSelfCollide(moving_part)){
		dir = STILL;
		status = GAME_OVER;
		gameoverSound.play();
		return;
	}

	snake.push_front(moving_part); // adiciona nova cabeça

	if(moving_part==foodPos){ // se a cabeça sobrepôs a comida
		biteSound.play();
		genNewFood();
		window.setFramerateLimit(snake.size()/3+4);
	} else {
		snake.pop_back(); // apaga a ponta da cauda
	}
}

void Game::genNewSnake(){
	snake.clear();
	int middle_x = cols/2;
	int middle_y = rows/2;
	// std::cout << "cols = " << middle_x << " rows = " << middle_y << std::endl;
	snake.push_back(std::make_pair(middle_x, middle_y));
	snake.push_back(std::make_pair(middle_x, middle_y+1));
	snake.push_back(std::make_pair(middle_x, middle_y+2));
	// std::cout<<"first = ["<< snake[0].first*tile_size <<", "<< snake[0].second*tile_size <<"]"<<std::endl;
	first_square.setSize(sf::Vector2f(tile_size, tile_size));
	first_square.setFillColor(sf::Color(100, 250, 50));
	first_square.setOutlineThickness(-5);
	first_square.setOutlineColor(sf::Color::Black);
	square.setSize(sf::Vector2f(tile_size, tile_size));
	square.setFillColor(sf::Color(100, 100, 100));
	square.setOutlineThickness(-5);
	square.setOutlineColor(sf::Color::Black);
}

std::string getcwd_string(){ // resgata diretório atual e retorna como string
   char buff[128];
   getcwd(buff, 128);
   std::string full_path(buff);
   return full_path;
}

void Game::genNewFood(){
	// fazer um random entre as extremidades do mapa
	// testar se a cobra cobre a posição
	// fazer um random do sprite a ser usado
	srand(time(NULL));
	int collides = 	TRUE; // se colide com alguma posição da cobra
	std::deque<PAIR>::size_type size = snake.size();
	while(collides){
		foodPos.first = rand() % cols;
		foodPos.second = rand() % rows;
		collides = FALSE;
		for(int i=0; i<size; ++i){
			if(foodPos == snake[i]){
				collides = TRUE;
				break;
			}
		}
	}
	
	spriteRow = rand() % 10;
	spriteCol = rand() % 10;
	food.setTexture(spritesheet);
	food.setTextureRect(sf::IntRect(spriteCol*48+8, spriteRow*48+8, 32, 32));
	food.setPosition(foodPos.first*32, foodPos.second*32);
}

void Game::genMap(){
	// por enquanto: definir o tamanho e a quantidade de tiles no mapa
	// baseando nas dimensoes da janela
	sf::Vector2u w_size = window.getSize();
	tile_size = 32;
	cols = w_size.x / tile_size;
	rows = w_size.y / tile_size;
	// std::cout << "cols = " << cols << " rows = " << rows << std::endl;
}

void Game::setDir(int new_dir){
	// testa se a cobra não está dando ré (inválido)
	switch(new_dir){
		case STILL:
			dir = STILL;
			break;
		case UP: // [-1,0]
			if(dir!=DOWN){
				dir = UP;
			}
			break;
		case DOWN: // [1,0]
			if(dir!=UP){
				dir = DOWN;
			}
			break;
		case LEFT: // [0,-1]
			if(dir!=RIGHT){
				dir = LEFT;
			}
			break;
		case RIGHT: // [0,1]
			if(dir!=LEFT){
				dir = RIGHT;
			}
			break;
	}
}

void Game::drawSnake(){
	std::deque<PAIR>::size_type size = snake.size();
	first_square.setPosition(snake[0].first*tile_size, snake[0].second*tile_size);
	// std::cout<<"tile_size = "<<tile_size<<" first = ["<<snake[0].first*tile_size<<", "<<snake[0].second*tile_size<<"]"<<std::endl;
	window.draw(first_square);
	for(int i=1; i<size; ++i){
		square.setPosition(snake[i].first*tile_size, snake[i].second*tile_size);
		window.draw(square);
	}
}

void Game::drawFood(){
	window.draw(food);
}

int Game::didSelfCollide(PAIR moving_part){
	std::deque<PAIR>::size_type size = snake.size();
	for(int i=2; i<size; ++i){
		if(moving_part==snake[i]){
			return 1;
		}
	}
	return 0;
}

void Game::startNewGame(){ // seta parâmetros iniciais
	score = 0;
	lives = 3;
	status = INGAME;
	speed = 1; // um tile -> depois pode deletar e colocar só ++ e --
	dir = STILL;
	genMap(); // gera mapa de colisões
	genNewSnake(); // gera snake com 3 segmentos
	genNewFood(); // gera vetor de sprites de foods
}

void Game::restart(){
	status = INGAME;
	startNewGame();
	window.setFramerateLimit(4);
}

void Game::loadResources(){ // carrega recursos que estão armazenados em disco
	// carrega fonte
	if (!mainFont.loadFromFile("res/fonts/8bit.ttf")){
	    std::cout << "Não foi possível carregar a fonte." << std::endl;
	}
	// carrega spritesheet
	if(!spritesheet.loadFromFile("res/images/foods.png", sf::IntRect(12, 12, 480, 480))){
		// x0 = 9 y0=12 size = 32+16 = 48
	    std::cout<<"Não foi possível carregar o spritesheet." << std::endl;
	}
	// carrega o som de mordida
	if(!biteBuffer.loadFromFile("res/audio/bite.wav")){
		std::cout << "Não foi possível carregar o som." << std::endl;
	} else {
		biteSound.setBuffer(biteBuffer);
	}
	// carrega o som de fim de jogo
	if(!gameoverBuffer.loadFromFile("res/audio/gameover.wav")){
		std::cout << "Não foi possível carregar o som." << std::endl;
	} else {
		gameoverSound.setBuffer(gameoverBuffer);
	}
}