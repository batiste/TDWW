all:
	g++ *.h *.cpp -std=c++11 -Wall -Werror -lSDL2 -lSDL2main -lGLEW -lGL -lGLU -o DWWE
