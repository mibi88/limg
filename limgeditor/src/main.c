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
#include "popups.h"
#include "keyboard.h"
#include "file.h"
#include "error.h"
#include "text.h"
#include "menu.h"

#define VWIDTH  364
#define VHEIGHT 192

#define MILIFONT "./data/milifont.limg"

int state = 0, ask_changestate = 0;
const char menu[MENU_SIZE][9] = {
    "C. Scale",
    "Rep. Mv.",
    "Cg. Col."
};

int main(int argc, char **argv) {
    unsigned char *limg_data = NULL;
    Limg limg, milifont;
    int out, x = 0, y = 0, scale = 4, ix = 0, iy = 0, colorcur = 0, menucur = 0, w = 16, h = 16;
    bool moverepeat = 1;
    uint16_t color = 0x0000;
    unsigned char rgb[3];
    FILE *fp;
    limg_init(&milifont);
    load_limg(MILIFONT, &milifont);
    limg_init(&limg);
    kbd_setrepeat(KUP, 1);
    kbd_setrepeat(KDOWN, 1);
    kbd_setrepeat(KLEFT, 1);
    kbd_setrepeat(KRIGHT, 1);
    kbd_setrepeat(KX, 1);
    kbd_setrepeat(KC, 0);
    kbd_setrepeat(KV, 0);
    if(argc >= 4 && argv[1][0] == 'o'){
        load_limg(argv[3], &limg);
    }else if(argc >= 5 && argv[1][0] == 'n'){
        w = atoi(argv[3]);
        h = atoi(argv[4]);
        if(w < 1) w = 1;
        if(h < 1) h = 1;
        out = limg_create(w, h, 0x0000, &limg);
    }else{
        puts("Need more args : $ limgedit o <out file> <in file>");
        puts("or               $ limgedit n <out file> <width> <height>");
        exit(1);
    }
    if(out < 0){
        report_error(out);
    }
    uInit(396, 224, "Limg image editor", 4, 20);
    while(!uAskexit()){
        uClear((uint32_t)0xC8FC90);
        if(state == 0){
            /* Move the cursor */
            if(kbd_kdown(KUP) && y>0) y--;
            if(kbd_kdown(KDOWN) && y<limg.h-1) y++;
            if(kbd_kdown(KLEFT) && x>0) x--;
            if(kbd_kdown(KRIGHT) && x<limg.w-1) x++;
            /* Fix ix and iy */
            while(x > ix+VWIDTH/scale-1) ix++;
            while(x < ix) ix--;
            while(y > iy+VHEIGHT/scale-1) iy++;
            while(y < iy) iy--;
            /* Other actions */
            if(kbd_kdown(KC)){
                kbd_setrepeat(KLEFT, 0);
                kbd_setrepeat(KRIGHT, 0);
                kbd_setrepeat(KX, 0);
                state = 2;
            }
            if(kbd_kdown(KX)) limg_setpixel(x, y, color, &limg);
            if(kbd_kdown(KV)){
                kbd_setrepeat(KUP, 0);
                kbd_setrepeat(KDOWN, 0);
                kbd_setrepeat(KLEFT, 1);
                kbd_setrepeat(KRIGHT, 1);
                kbd_setrepeat(KX, 0);
                state = 1;
            }
        }else if(state == 1){
            if(kbd_kdown(KX)){
                ask_changestate = 1;
            }else if(ask_changestate && !uKeydown(KX)){
                kbd_setrepeat(KUP, moverepeat);
                kbd_setrepeat(KDOWN, moverepeat);
                kbd_setrepeat(KLEFT, moverepeat);
                kbd_setrepeat(KRIGHT, moverepeat);
                kbd_setrepeat(KX, 1);
                ask_changestate = 0;
                state = 0;
            }
            if(kbd_kdown(KUP)){
                colorcur--;
                if(colorcur < 0) colorcur = 2;
            }
            if(kbd_kdown(KDOWN)){
                colorcur++;
                if(colorcur > 2) colorcur = 0;
            }
            getrgb565(color, rgb);
            if(kbd_kdown(KLEFT) && rgb[colorcur] > 0) rgb[colorcur]--;
            if(kbd_kdown(KRIGHT) && (colorcur == 1 ? rgb[colorcur] < 63 : rgb[colorcur] < 31)) rgb[colorcur]++;
            color = makergb565(rgb);
        }else if(state == 2){
            if(kbd_kdown(KLEFT) && menucur > 0) menucur--;
            if(kbd_kdown(KRIGHT) && menucur < MENU_SIZE-1) menucur++;
            if(kbd_kdown(KX)){
                if(menucur == 0){
                    scale++;
                    if(scale > 8) scale = 1;
                }else if(menucur == 1){
                    ask_changestate = 2;
                }else if(menucur == 2){
                    kbd_setrepeat(KUP, 0);
                    kbd_setrepeat(KDOWN, 0);
                    kbd_setrepeat(KLEFT, 1);
                    kbd_setrepeat(KRIGHT, 1);
                    kbd_setrepeat(KX, 0);
                    ask_changestate = 0;
                    state = 1;
                }
            }else if(ask_changestate == 2 && !uKeydown(KX)){
                moverepeat = !moverepeat;
                kbd_setrepeat(KUP, moverepeat);
                kbd_setrepeat(KDOWN, moverepeat);
                kbd_setrepeat(KLEFT, moverepeat);
                kbd_setrepeat(KRIGHT, moverepeat);
                kbd_setrepeat(KX, 1);
                ask_changestate = 0;
                state = 0;
            }
            if(kbd_kdown(KC)){
                ask_changestate = 1;
            }else if(ask_changestate == 1 && !uKeydown(KC)){
                kbd_setrepeat(KLEFT, moverepeat);
                kbd_setrepeat(KRIGHT, moverepeat);
                kbd_setrepeat(KX, 1);
                ask_changestate = 0;
                state = 0;
            }
        }else{
            state = 0;
        }
        draw_limg(&limg, 32, 0, VWIDTH, VHEIGHT, ix, iy, scale, x, y);
        vline(31, 0, VHEIGHT, 0x588C28);
        hline(VHEIGHT, 32, 396, 0x588C28);
        if(state == 1){
            color = color_chooser(134, 80, 128, 64, color, colorcur, &milifont);
        }
        draw_menu(32, 194, menucur, state == 2, menu, &milifont);
        uShow();
        uWaitnextframe();
    }
    /* Save */
    out = limg_encode(&limg_data, &limg);
    if(out < 0) report_error(out);
    fp = fopen(argv[2], "wb");
    if(fp == NULL){
        printf("Can't make \"%s\"\n", argv[2]);
        return 2;
    }
    fwrite((char*)limg_data, 1, out, fp);
    fclose(fp);
    limg_free(&limg);
    limg_free(&milifont);
    free(limg_data);
    return 0;
}
