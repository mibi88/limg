SRC = demo/main.c liblimg/liblimg.c

all:
	gcc $(SRC) -o main -Iliblimg -std=c89 -Wall -Wpedantic -Wextra -fsanitize=address
