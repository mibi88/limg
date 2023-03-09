#include "menu.h"

extern int _frame;

void draw_menu(int sx, int sy, int cur, bool active, const char menu[MENU_SIZE][9], Limg *milifont) {
    int i;
    unsigned char rgb[3];
    for(i=0;i<MENU_SIZE;i++){
        rgb[0] = (unsigned char)_frame*15;
        rgb[1] = rgb[0];
        rgb[2] = rgb[0];
        if(i == cur && active) rect(sx+(i*36), sx+(i*36)+35, sy, sy+9, makergb888(rgb));
        rect(sx+(i*36)+1, sx+(i*36)+34, sy+1, sy+8, 0xF8FCF8);
        stext(sx+(i*36)+2, sy+2, 3, 5, (char *)menu[i], milifont);
    }
}
