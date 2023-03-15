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

#include "io.h"

const char menu[MENU_SIZE][9] = {
    "C. Scale",
    "Rep. Mv.",
    "Cg. Col.",
    "Gr. Col.",
    "Save    ",
    "Mn. Menu"
};

Io io;
extern char _file[PATH_MAX+NAME_MAX], _path[PATH_MAX];

int main(void) {
    io_init(&io);
    limg_init(&io.milifont);
    load_limg(MILIFONT, &io.milifont);
    limg_init(&io.limg);
    kbd_setrepeat(KUP, 1);
    kbd_setrepeat(KDOWN, 1);
    kbd_setrepeat(KLEFT, 1);
    kbd_setrepeat(KRIGHT, 1);
    kbd_setrepeat(KX, 1);
    kbd_setrepeat(KC, 0);
    kbd_setrepeat(KV, 0);
    uInit(396, 224, "Limg image editor", 4, 20);
    while(!uAskexit()){
        uClear((uint32_t)0xC8FC90);
        switch(io.state){
            case 0:
                editor_input(&io);
                break;
            case 1:
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
                break;
            case 2:
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
                    }else if(menucur == 3){
                        color = limg_getpixel(x, y, &limg);
                    }else if(menucur == 4){
                        initfilechooser(".");
                        state = 6;
                    }else if(menucur == 5){
                        state = 4;
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
                break;
            case 3:
                kbd_setrepeat(KUP, 0);
                kbd_setrepeat(KDOWN, 0);
                kbd_setrepeat(KX, 0);
                dirsize = getdirsize();
                if(dirsize > 0){
                    if(kbd_kdown(KUP) && dircur > 0) dircur--;
                    if(kbd_kdown(KDOWN) && dircur < dirsize-1) dircur++;
                    if(dircur > dirsize-1){
                        dircur = dirsize-1;
                    }
                    while(dircur > dirview+F_AMOUNT-1) dirview++;
                    while(dircur < dirview) dirview--;
                }
                if(kbd_kdown(KC)){
                    ask_changestate = 1;
                }else if(!kbd_kdown(KC) && ask_changestate){
                    ask_changestate = 0;
                    state = 4;
                }
                break;
            case 4:
                kbd_setrepeat(KUP, 0);
                kbd_setrepeat(KDOWN, 0);
                kbd_setrepeat(KX, 0);
                if(kbd_kdown(KUP) && mainmenucur) mainmenucur = 0;
                if(kbd_kdown(KDOWN) && !mainmenucur) mainmenucur = 1;
                if(kbd_kdown(KX)){
                    ask_changestate = 1;
                }else if(!kbd_kdown(KX) && ask_changestate == 1){
                    ask_changestate = 0;
                    memset(wtext, '\0', 6);
                    memset(htext, '\0', 6);
                    wcur = 0;
                    hcur = 0;
                    ncur = 0;
                    if(mainmenucur) initfilechooser(".");
                    state = mainmenucur ? 3 : 5;
                }
                if(kbd_kdown(KV)){
                    ask_changestate = 2;
                }else if(!kbd_kdown(KV) && ask_changestate == 2){
                    kbd_setrepeat(KUP, moverepeat);
                    kbd_setrepeat(KDOWN, moverepeat);
                    kbd_setrepeat(KLEFT, moverepeat);
                    kbd_setrepeat(KRIGHT, moverepeat);
                    kbd_setrepeat(KX, 1);
                    ask_changestate = 0;
                    state = 0;
                }
                break;
            case 5:
                kbd_setrepeat(KUP, 0);
                kbd_setrepeat(KDOWN, 0);
                kbd_setrepeat(KLEFT, 0);
                kbd_setrepeat(KRIGHT, 0);
                kbd_setrepeat(KX, 0);
                if(kbd_kdown(KUP) && ncur) ncur = 0;
                if(kbd_kdown(KDOWN) && !ncur) ncur = 1;
                if(!ncur) intinput(wtext, &wcur, 5);
                if(ncur) intinput(htext, &hcur, 5);
                if(kbd_kdown(KX)){
                    ask_changestate = 1;
                }else if(!kbd_kdown(KX) && ask_changestate){
                    w = atoi(wtext);
                    h = atoi(htext);
                    if(w < 1) w = 1;
                    if(h < 1) h = 1;
                    limg_free(&limg);
                    out = limg_create(w, h, 0x0000, &limg);
                    kbd_setrepeat(KUP, moverepeat);
                    kbd_setrepeat(KDOWN, moverepeat);
                    kbd_setrepeat(KLEFT, moverepeat);
                    kbd_setrepeat(KRIGHT, moverepeat);
                    kbd_setrepeat(KX, 1);
                    ask_changestate = 0;
                    state = out < 0 ? -1 : 0;
                }
                break;
            case 6:
                kbd_setrepeat(KUP, 0);
                kbd_setrepeat(KDOWN, 0);
                kbd_setrepeat(KX, 0);
                dirsize = getdirsize();
                if(dirsize > 0){
                    if(kbd_kdown(KUP) && dircur > 0) dircur--;
                    if(kbd_kdown(KDOWN) && dircur < dirsize-1) dircur++;
                    if(dircur > dirsize-1){
                        dircur = dirsize-1;
                    }
                    while(dircur > dirview+F_AMOUNT-1) dirview++;
                    while(dircur < dirview) dirview--;
                }
                if(kbd_kdown(KC)){
                    ask_changestate = 2;
                }else if(!kbd_kdown(KC) && ask_changestate == 2){
                    ask_changestate = 0;
                    state = 4;
                }
                break;
            case 7:
                if(kbd_kdown(KX)){
                    ask_changestate = 1;
                }else if(!kbd_kdown(KX) && ask_changestate){
                    kbd_setrepeat(KUP, moverepeat);
                    kbd_setrepeat(KDOWN, moverepeat);
                    kbd_setrepeat(KLEFT, moverepeat);
                    kbd_setrepeat(KRIGHT, moverepeat);
                    kbd_setrepeat(KX, 1);
                    strcat(_file, ftext);
                    strcat(_file, ".limg");
                    /* Save */
                    out = limg_encode(&limg_data, &limg);
                    if(out >= 0){
                        fp = fopen(_file, "wb");
                        if(fp != NULL){
                            fwrite((char*)limg_data, 1, out, fp);
                            fclose(fp);
                        }else state = -3;
                    }else state = -4;
                    ask_changestate = 0;
                    state = 0;
                }
                if(!ask_changestate) fnameinput(ftext, &fcur, 8);
                break;
            default:
                if(state < 0){
                    kbd_setrepeat(KX, 0);
                    if(kbd_kdown(KX)){
                        ask_changestate = 1;
                    }else if(!kbd_kdown(KX) && ask_changestate){
                        kbd_setrepeat(KUP, moverepeat);
                        kbd_setrepeat(KDOWN, moverepeat);
                        kbd_setrepeat(KLEFT, moverepeat);
                        kbd_setrepeat(KRIGHT, moverepeat);
                        kbd_setrepeat(KX, 1);
                        kbd_setrepeat(KC, 0);
                        kbd_setrepeat(KV, 0);
                        state = 0;
                        ask_changestate = 0;
                    }
                }else{
                    state = 0;
                }
        }
        draw_limg(&limg, 32, 0, VWIDTH, VHEIGHT, ix, iy, scale, x, y);
        vline(31, 0, VHEIGHT, 0x588C28);
        hline(VHEIGHT, 32, 396, 0x588C28);
        draw_menu(32, 194, menucur, state == 2, menu, &milifont);
        if(state == 1){
            color = color_chooser(134, 80, 128, 64, color, colorcur, &milifont);
        }else if(state == 3){
            if(filechooser(dirview, F_AMOUNT, dircur, &milifont)){
                ask_changestate = 1;
            }else if(!kbd_kdown(KX) && ask_changestate){
                ask_changestate = 0;
                kbd_setrepeat(KUP, moverepeat);
                kbd_setrepeat(KDOWN, moverepeat);
                kbd_setrepeat(KX, 1);
                limg_free(&limg);
                load_limg(_file, &limg);
                state = 0;
            }
        }else if(state == 4){
            main_menu(134, 80, 128, 64, mainmenucur, &milifont);
        }else if(state == 5){
            new_file(134, 80, 128, 64, wtext, htext, wcur, hcur, ncur, &milifont);
        }else if(state == 6){
            if(pathchooser(dirview, F_AMOUNT, dircur, &milifont)){
                ask_changestate = 1;
            }else if(!kbd_kdown(KV) && ask_changestate == 1){
                ask_changestate = 0;
                if(strlen(_path)+15<=PATH_MAX+NAME_MAX){
                    memset(_file, '\0', PATH_MAX+NAME_MAX);
                    strcpy(_file, _path);
                    strcat(_file, "/");
                    state = 7;
                }else{
                    state = -2;
                }
            }
        }else if(state == 7){
            enter_filename(134, 80, 128, 64, ftext, fcur, &milifont);
        }else if(state < 0){
            error(134, 80, 128, 64, &milifont);
        }
        uShow();
        uWaitnextframe();
    }
    limg_free(&limg);
    limg_free(&milifont);
    free(limg_data);
    return 0;
}
