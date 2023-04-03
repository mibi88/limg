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

#include "editor.h"
#include MILIFONT

int state = SCREEN_MAINMENU;
unsigned char *limg_data = NULL;
Limg limg, milifont;

int main(void) {
    limg_init(&milifont);
    if(limg_decode((unsigned char *)b_milifont, &milifont) < 0) state = -6;
    limg_init(&limg);
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
        switch(state){
            case SCREEN_EDITOR:
                act_editor();
                break;
            case SCREEN_COLORC:
                act_colorc();
                break;
            case SCREEN_MENU:
                act_menu();
                break;
            case SCREEN_OPEN:
                act_open();
                break;
            case SCREEN_MAINMENU:
                act_main_menu();
                break;
            case SCREEN_NEW:
                act_new();
                break;
            case SCREEN_SAVE1:
                act_save1();
                break;
            case SCREEN_SAVE2:
                act_save2();
                break;
            case SCREEN_VALIDSAVE:
                act_valid_save();
                break;
            default:
                act_default();
        }
        disp_editor();
        switch(state){
            case SCREEN_COLORC:
                disp_colorc();
                break;
            case SCREEN_OPEN:
                disp_open();
                break;
            case SCREEN_MAINMENU:
                disp_mainmenu();
                break;
            case SCREEN_NEW:
                disp_new();
                break;
            case SCREEN_SAVE1:
                disp_save1();
                break;
            case SCREEN_SAVE2:
                disp_save2();
                break;
            case SCREEN_VALIDSAVE:
                disp_valid_save();
                break;
            default:
                if(state < 0){
                    disp_error();
                }
        }
        uShow();
        uWaitnextframe();
    }
    limg_free(&limg);
    limg_free(&milifont);
    free(limg_data);
    return 0;
}
