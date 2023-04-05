/*
 * libuDraw - Simple lib. to draw in a SDL 1.2 window.
 * Copyright (C) 2023  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#ifndef LIBUDRAW_H
#define LIBUDRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/fs.h>
#include <time.h>

#define PATH_MAX 512
#define NAME_MAX 16

enum {
    KUP    = KEY_UP,
    KDOWN  = KEY_DOWN,
    KLEFT  = KEY_LEFT,
    KRIGHT = KEY_RIGHT,
    KX     = KEY_F1,
    KC     = KEY_F2,
    KV     = KEY_F3,
    KS     = KEY_F4
};
#define KEYAMOUNT 8

void uInit(int w, int h, const char *title, int scale, int fps);
void uClear(uint32_t color);
void uPixel(int x, int y, uint32_t color);
void uShow(void);
bool uAskexit(void);
bool uKeydown(int key);
char uGetchar(void);
void uWaitnextframe(void);
void uDeinit(void);

#endif
