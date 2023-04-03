SRC = src/main.c \
	  src/draw_limg.c \
	  src/gfx.c \
	  src/popups.c \
	  src/keyboard.c \
	  src/file.c \
	  src/error.c \
	  src/text.c \
	  src/image.c \
	  src/menu.c \
	  src/filechooser.c \
	  src/textbox.c \
	  src/textinput.c \
	  src/editor.c \
	  ../liblimg/lib/lib/liblimg.a \
	  uDraw/lib/libuDraw.a

all:
	(cd uDraw && make)
	(cd ../liblimg/lib && make)
	python3 ./conv/binheader.py ./data/milifont.limg
	gcc $(SRC) -D_DEFAULT_SOURCE -o limgedit  -I../liblimg/lib/lib/include/liblimg/ \
	-IuDraw/include/libudraw -std=c89 -Wall -Wpedantic -Wextra -lSDL -O2 # -fsanitize=address
	(cd uDraw && make clean)
	(cd ../liblimg/lib && make clean)
