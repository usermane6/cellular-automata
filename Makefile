all:
	g++ main.cpp grid.cpp -I C:/dev_lib/include -L C:/dev_lib/lib/SDL2 -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o cells