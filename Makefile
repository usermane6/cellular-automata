all:
	g++ main.cpp grid.cpp -I C:/dev_lib/include -L C:/dev_lib/lib/SDL2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o cells