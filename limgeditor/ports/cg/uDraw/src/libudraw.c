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
int _time, _timer, _ticks;
int _key, _timeout, _lastkey;

uint32_t keymap_translate(int key, bool shift, bool alpha);

int getkey_ignoremod(void) {
    if(_timeout >= 5){
        if(_key == _lastkey){
            return _key;
        }else{
            _lastkey = _key;
            _timeout = 0;
            return _key;
        }
    }else _timeout++;
    return 0;
}

int _tick(void) {
    _time++;
    return TIMER_CONTINUE;
}

void uInit(int w, int h, const char *title, int scale, int fps) {
    _timeout = 0;
    _lastkey = 0;
    _time = 0;
    _timer = timer_configure(TIMER_TMU, 1000, GINT_CALL(_tick));
	if(_timer<0){
		exit(-1);
	}
	timer_start(_timer);
    _w = w;
    _h = h;
    _scale = scale;
    _fps = fps;
    _scale = 1;
    if(_fps<1){
    	_fps = 50;
    }
    _ticks = 1000/_fps;
    uClear(0x00000000);
}

void uClear(uint32_t color) {
    dclear(rgb888torgb565(color));
}

void uPixel(int x, int y, uint32_t color) {
    if(x>=0 && x<_w && y>=0 && y<_h){
        gint_vram[DWIDTH*y+x] = rgb888torgb565(color);
    }
}

void uShow(void) {
    dupdate();
}

bool uAskexit(void) {
    /* For getkey_ignoremod */
    key_event_t ev;
    _key = 0;
    bool kf = 0;
    while((ev = pollevent()).type != KEYEV_NONE){
        if(ev.key != KEY_SHIFT && !kf){
            _key = ev.key;
            kf = 1;
        }
    }
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
    while(_time < _ticks) sleep();
    _time = 0;
}

void uDeinit(void) {
    timer_stop(_timer);
}
