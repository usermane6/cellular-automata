all:
	g++ -I src/include -L src/lib -o main main.cpp tile.cpp -lmingw32 -lSDL2main -lSDL2