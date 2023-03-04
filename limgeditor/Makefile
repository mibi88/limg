SRC = src/main.c ../liblimg/lib/lib/liblimg.a uDraw/lib/libuDraw.a

all:
	(cd uDraw && make)
	(cd ../liblimg/lib && make)
	gcc $(SRC) -o limgedit  -I../liblimg/lib/lib/include/liblimg/ \
	-IuDraw/include/libudraw -std=c89 -Wall -Wpedantic -Wextra -lSDL
	(cd uDraw && make clean)
	(cd ../liblimg/lib && make clean)
