./bin/main: ./src/main.c ./bin
	gcc -Wall -o ./bin/main ./src/main.c -lSDL2

./bin:
	mkdir ./bin

