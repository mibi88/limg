#include "popups.h"

extern int _frame;

uint16_t color_chooser(int sx, int sy, int w, int h, uint16_t color, int cur) {
    unsigned char rgb[3], drgb[3];
    uint32_t dcolor;
    int i, n;
    vline(sx, sy+1, sy+h, 0xA85450);
    vline(sx+w, sy+1, sy+h, 0xA85450);
    hline(sy, sx+1, sx+w, 0xA85450);
    hline(sy+h, sx+1, sx+w, 0xA85450);
    rect(sx+1, sx+w, sy+1, sy+h, 0xF8FCF8);
    dcolor = rgb565torgb888(color);
    rect(sx+w/8+1, sx+w-(w/2+w/8), sy+h/4+1, sy+h-h/4, dcolor);
    getrgb888(dcolor, drgb);
    for(i=0;i<3;i++){
        if(i==cur){
            rgb[0] = (unsigned char)_frame*15;
            rgb[1] = rgb[0];
            rgb[2] = rgb[0];
            rect(sx+w-(w/2), sx+w-w/8+1, sy+h/4*(i+1), sy+h/4*(i+1)+h/8+1, makergb888(rgb));
        }
        for(n=0;n<3;n++) rgb[n] = 0;
        rgb[i] = drgb[i];
        rect(sx+w-(w/2)+1, sx+w-w/8, sy+h/4*(i+1)+1, sy+h/4*(i+1)+h/8, makergb888(rgb));
    }
    _frame++;
    if(_frame>17) _frame = 0;
    return color;
}
