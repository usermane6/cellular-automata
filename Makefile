all:
	g++ -I src/include -L src/lib -o cells main.cpp grid.cpp -lmingw32 -lSDL2main -lSDL2