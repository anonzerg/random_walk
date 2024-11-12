CC := clang
CFLAGS := -g -Oz -Wall -Wextra -Werror -Wpedantic
LIBS := -lSDL2 -lgsl -lgslcblas -lm
PROGRAM_NAME = random_walk

./bin/$(PROGRAM_NAME): ./src/main.c ./bin
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

./bin:
	mkdir ./bin

clean:
	rm ./bin/$(PROGRAM_NAME)

