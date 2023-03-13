#include "textbox.h"

extern int _frame;

void textbox(int sx, int sy, int selected, char *text, int cur, int len, Limg *milifont) {
    unsigned char rgb[3];
    if(selected){
        rgb[0] = (unsigned char)_frame*15;
        rgb[1] = rgb[0];
        rgb[2] = rgb[0];
        rect(sx, sx+(len*4+3), sy, sy+7, makergb888(rgb));
    }
    rect(sx+1, sx+(len*4+3)-1, sy+1, sy+6, 0xF8FCF8);
    stext(sx+1, sy+1, 3, 5, text, milifont);
    if(selected) vline(sx+1+cur*4, sy+1, sy+6, 0x000000);
}
