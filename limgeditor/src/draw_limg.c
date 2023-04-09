/*
 * limgedit - Limg image editor.
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

#include "draw_limg.h"
#include <stdint.h>

int _frame = 0;

void draw_limg(Limg *limg, int sx, int sy, int w, int h, int ix, int iy, int scale, int cx, int cy){
    int mx = w/scale+1, my = h/scale+1, dx, dy, bx, by, x, y;
    unsigned char rgb[3];
    uint16_t color;
    uint32_t color32;
    rgb[0] = (unsigned char)_frame*15;
    rgb[1] = rgb[0];
    rgb[2] = rgb[0];
    for(y=0;y<my;y++){
        for(x=0;x<mx;x++){
            color = limg_getpixel(ix+x, iy+y, limg);
            if(ix+x == cx && iy+y == cy) color32 = makergb888(rgb);
            for(by=0;by<scale;by++){
                for(bx=0;bx<scale;bx++){
                    dx = (x*scale+bx);
                    dy = (y*scale+by);
                    if(dx>=0 && dx<w && dy>=0 && dy<h){
                        pixel16(sx+dx, sy+dy, color);
                        if(ix+x == cx && iy+y == cy) uPixel(sx+dx, sy+dy, color32);
                    }
                }
            }
            color = rgb888torgb565(makergb888(rgb));
            if(ix+x == limg->w+1 && iy+y < limg->h){
                dx = sx+(x-1)*scale;
                for(by=0;by<scale;by++){
                    dy = sy+by+y*scale;
                    if(dy>=0 && dy<w) pixel16(dx, dy, color);
                }
            }else if(iy+y == limg->h+1 && ix+x < limg->w){
                dy = sy+(y-1)*scale;
                for(bx=0;bx<scale;bx++){
                    dx = sx+bx+x*scale;
                    if(dx>=0 && dx<w) pixel16(dx, dy, color);
                }
            }
            if(ix+x == limg->w+1 && iy+y == limg->h+1){
                pixel16(sx+(x-1)*scale, sy+(y-1)*scale, color);
            }
        }
    }
    _frame++;
    if(_frame>17) _frame = 0;
}
