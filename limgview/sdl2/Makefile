SRC = main.c ../../liblimg/lib/lib/liblimg.a

all:
	(cd ../../liblimg/lib && make)
	gcc $(SRC) -o limgview -I../../liblimg/lib/lib/include/liblimg/ -std=c89 -Wall -Wpedantic -Wextra -lSDL2
	(cd ../../liblimg/lib && make clean)
