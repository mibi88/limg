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

#include <libudraw.h>
#include <rgbconv.h>
#include <liblimg.h>
#include <rgbconv.h>

#include "draw_limg.h"
#include "gfx.h"

#define VWIDTH  364
#define VHEIGHT 192

#define KEYS    7

void report_error(int error) {
    printf("Error when reading this image, error %d :\n", error);
    switch(error){
        case MAGIC_NOTFOUND:
            puts("Magic \"LIMG-V1\" not found !");
            break;
        case MALLOCERROR_CARRAY:
            puts("Need more ram to malloc carray !");
            break;
        case PALETTE_BADINDEX:
            puts("Bad index for the palette !");
            break;
        case LIMG_ALREADYFREE:
            puts("Limg image is already free !");
            break;
        case MALLOCERROR_LIMGDATA:
            puts("Need more ram to malloc limg_data !");
            break;
        case COLOR_MISSING:
            puts("Color missing !");
            break;
        default:
            puts("Unknown error !");
    }
}

bool keys_already_down[KEYS];
int state = 0;
bool ask_changestate = 0;

int main(int argc, char **argv) {
    unsigned char *limg_data = NULL;
    Limg limg;
    int size, out, x = 0, y = 0, scale = 4, ix = 0, iy = 0, colorcur = 0;
    uint16_t color = 0x0000;
    unsigned char rgb[3];
    FILE *fp;
    if(argc < 2){
        puts("More args required !");
        puts("limgedit <limg image>");
        return 1;
    }
    fp = fopen(argv[1], "rb");
    if(fp == NULL){
        printf("Can't open \"%s\"\n", argv[1]);
        return 2;
    }
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	limg_data = malloc(sizeof(unsigned char) * size);
	if(limg_data == NULL){
		puts("More memory needed !");
        return 3;
	}
	fread(limg_data, 1, sizeof(unsigned char) * size, fp);
	fclose(fp);
    limg_init(&limg);
    out = limg_decode(limg_data, &limg);
    if(out < 0){
        report_error(out);
    }
    uInit(396, 224, "Limg image editor", 4, 20);
    while(!uAskexit()){
        uClear((uint32_t)0xC8FC90);
        if(state == 0){
            /* Move the cursor */
            if(uKeydown(KUP) && y>0) y--;
            if(uKeydown(KDOWN) && y<limg.h-1) y++;
            if(uKeydown(KLEFT) && x>0) x--;
            if(uKeydown(KRIGHT) && x<limg.w-1) x++;
            /* Fix ix and iy */
            while(x > ix+VWIDTH/scale-1) ix++;
            while(x < ix) ix--;
            while(y > iy+VHEIGHT/scale-1) iy++;
            while(y < iy) iy--;
            /* Other actions */
            if(uKeydown(KC)){
                if(!keys_already_down[5]){
                    scale++;
                    if(scale > 8) scale = 1;
                    keys_already_down[5] = 1;
                }
            }else if(keys_already_down[5]){
                keys_already_down[5] = 0;
            }
            if(uKeydown(KX)) limg_setpixel(x, y, color, &limg);
            if(uKeydown(KV)){
                if(!keys_already_down[6]){
                    state = 1;
                }
            }else if(keys_already_down[6]){
                keys_already_down[6] = 0;
            }
        }else if(state == 1){
            if(uKeydown(KX)){
                if(!keys_already_down[4]){
                    ask_changestate = 1;
                    keys_already_down[4] = 1;
                }
            }else if(keys_already_down[4]){
                if(ask_changestate) state = 0;
                keys_already_down[4] = 0;
            }
            if(uKeydown(KUP)){
                if(!keys_already_down[0]){
                    colorcur--;
                    if(colorcur < 0) colorcur = 2;
                    keys_already_down[0] = 1;
                }
            }else if(keys_already_down[0]){
                keys_already_down[0] = 0;
            }
            if(uKeydown(KDOWN)){
                if(!keys_already_down[1]){
                    colorcur++;
                    if(colorcur > 2) colorcur = 0;
                    keys_already_down[1] = 1;
                }
            }else if(keys_already_down[1]){
                keys_already_down[1] = 0;
            }
            getrgb565(color, rgb);
            if(uKeydown(KLEFT) && rgb[colorcur] > 0) rgb[colorcur]--;
            if(uKeydown(KRIGHT) && (colorcur == 1 ? rgb[colorcur] < 63 : rgb[colorcur] < 31)) rgb[colorcur]++;
            color = makergb565(rgb);
        }else{
            state = 0;
        }
        draw_limg(&limg, 32, 0, VWIDTH, VHEIGHT, ix, iy, scale, x, y);
        vline(31, 0, VHEIGHT, 0x588C28);
        hline(VHEIGHT, 32, 396, 0x588C28);
        if(state == 1){
            color = color_chooser(134, 80, 128, 64, color, colorcur);
        }
        uShow();
        uWaitnextframe();
    }
    limg_free(&limg);
    free(limg_data);
    return 0;
}
