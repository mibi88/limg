CC = gcc
AR = gcc-ar

OUT = liblimg.a
OUT_DIR = lib

SRC = src/liblimg.c src/rgbconv.c
OBJ = $(SRC:src/%=build/%.o)

BUILD = build

all: $(OBJ) | $(OUT_DIR)/
	$(AR) rsv $(OUT_DIR)/$(OUT) $(OBJ)
	cp --recursive include $(OUT_DIR)/

$(BUILD)/%.o: src/% | $(BUILD)/
	$(CC) -c $< -o $@ -Os -std=c89

.PRECIOUS: %/

%/:
	@ mkdir -p $@

clean: $(BUILD)/ | $(OUT_DIR)/
	rm $(OUT_DIR) --recursive
	rm $(BUILD) --recursive
