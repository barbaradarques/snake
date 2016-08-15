all:
	g++ -c src/*.cpp -I./includes -lm -std=c++11
	g++ *.o -o build/snakeGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++11
run:
	./build/snakeGame
val:
	g++ -c src/*.cpp -I./includes -lm -std=c++11 -g -O0
	g++ *.o -o build/snakeGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++11 -g -O0
	valgrind --leak-check=yes build/snakeGame
try:
	g++ tst/test.cpp -o tst/test -lm -std=c++11
	./tst/test