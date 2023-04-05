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

#include "../include/libudraw/libudraw.h"
#include <rgbconv.h>

#define Uint8 uint8_t
#define Uint32 uint32_t

int _scale, _w, _h, _fps;
clock_t _last_t;
Uint8 *_kbuffer;
char _char = '\0';

uint32_t keymap_translate(int key, bool shift, bool alpha);

int getkey_ignoremod(void) {
    key_event_t ev;
    bool kf = 0;
    int key = 0;
    while((ev = pollevent()).type != KEYEV_NONE){
        if(ev.key != KEY_SHIFT && !kf){
            key = ev.key;
            kf = 1;
        }
    }
    return key;
}

void uInit(int w, int h, const char *title, int scale, int fps) {
    _w = w;
    _h = h;
    _scale = scale;
    _fps = fps;
    _scale = 1;
    if(_fps<1){
    	_fps = 50;
    }
    uClear(0x00000000);
    _last_t = clock()*1000;
}

void uClear(uint32_t color) {
    dclear(rgb888torgb565(color));
}

void uPixel(int x, int y, uint32_t color) {
    if(x>=0 && x<_w && y>=0 && y<_h){
        dpixel(x, y, rgb888torgb565(color));
    }
}

void uShow(void) {
    dupdate();
}

bool uAskexit(void) {
    clearevents();
    return keydown(KEY_MENU) | keydown(KEY_EXIT);
}

bool uKeydown(int key) {
    return keydown(key);
}

char uGetchar(void) {
    if(keydown(KEY_DEL)) return 0x08;
    return (char)keymap_translate(getkey_ignoremod(), keydown(KEY_SHIFT), keydown(KEY_ALPHA));
}

void uWaitnextframe(void) {
    Uint32 ticks;
    if(clock()*1000 <= _last_t){
        _last_t = clock()*1000;
        return;
    }
    ticks = 1000/(Uint32)_fps;
    while(clock()*1000 - _last_t < ticks);
    _last_t = clock()*1000;
}

void uDeinit(void) {
    return;
}
