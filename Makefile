all:
	g++ *.h *.cpp -std=c++11 -Wall -Werror -lSDL2 -lSDL2main -lSDL2_image -lGLEW -lGL -lGLU -o DWWE
