#include "popups.h"

extern int _frame;

uint16_t color_chooser(int sx, int sy, int w, int h, uint16_t color, int cur, Limg *milifont) {
    unsigned char rgb[3], drgb[3], trgb[3];
    char tcolor[8], crgb[4];
    uint32_t dcolor;
    int i, n;
    vline(sx, sy+1, sy+h, 0xA85450);
    vline(sx+w, sy+1, sy+h, 0xA85450);
    hline(sy, sx+1, sx+w, 0xA85450);
    hline(sy+h, sx+1, sx+w, 0xA85450);
    rect(sx+1, sx+w, sy+1, sy+h, 0xF8FCF8);
    dcolor = rgb565torgb888(color);
    rgb[0] = (unsigned char)_frame*15;
    rgb[1] = rgb[0];
    rgb[2] = rgb[0];
    rect(sx+w/8, sx+w-(w/2+w/8)+1, sy+h/4, sy+h-h/4+1, makergb888(rgb));
    rect(sx+w/8+1, sx+w-(w/2+w/8), sy+h/4+1, sy+h-h/4, dcolor);
    getrgb888(dcolor, drgb);
    getrgb565(color, trgb);
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
        sprintf(crgb, "%02d", trgb[i]);
        stext(sx+w-w/8+3, sy+h/4*(i+1)+2, 3, 5, crgb, milifont);
    }
    sprintf(tcolor, "#%04x", color);
    stext(sx+w-26, sy+h-6, 3, 5, tcolor, milifont);
    sprintf(tcolor, "#%06x", dcolor);
    stext(sx+w-34, sy+6, 3, 5, tcolor, milifont);
    return color;
}

void main_menu(int sx, int sy, int w, int h, int cur, Limg *milifont) {
    unsigned char rgb[3];
    vline(sx, sy+1, sy+h, 0xA85450);
    vline(sx+w, sy+1, sy+h, 0xA85450);
    hline(sy, sx+1, sx+w, 0xA85450);
    hline(sy+h, sx+1, sx+w, 0xA85450);
    rect(sx+1, sx+w, sy+1, sy+h, 0xF8FCF8);
    /* Inside the popup */
    /* New */
    if(!cur){
        rgb[0] = (unsigned char)_frame*15;
        rgb[1] = rgb[0];
        rgb[2] = rgb[0];
        rect(sx+3, sx+w-2, sy+3, sy+h/2-2, makergb888(rgb));
    }
    rect(sx+4, sx+w-3, sy+4, sy+h/2-3, 0xF8FCF8);
    stext(sx+w/2-(4*3/2), sy+h/4-3, 3, 5, "New", milifont);
    /* Open */
    if(cur){
        rgb[0] = (unsigned char)_frame*15;
        rgb[1] = rgb[0];
        rgb[2] = rgb[0];
        rect(sx+3, sx+w-2, sy+h/2+1, sy+h-2, makergb888(rgb));
    }
    rect(sx+4, sx+w-3, sy+h/2+2, sy+h-3, 0xF8FCF8);
    stext(sx+w/2-(4*4/2), sy+h/2+h/4-3, 3, 5, "Open", milifont);
}

void new_file(int sx, int sy, int w, int h, char *wtext, char *htext, int wcur, int hcur, int cur, Limg *milifont) {
    vline(sx, sy+1, sy+h, 0xA85450);
    vline(sx+w, sy+1, sy+h, 0xA85450);
    hline(sy, sx+1, sx+w, 0xA85450);
    hline(sy+h, sx+1, sx+w, 0xA85450);
    rect(sx+1, sx+w, sy+1, sy+h, 0xF8FCF8);
    /* Inside the popup */
    stext(sx+3, sy+3, 3, 5, "Width  :", milifont);
    textbox(sx+3+(9*4), sy+1, !cur, wtext, wcur, 5, milifont);
    stext(sx+3, sy+11, 3, 5, "Height :", milifont);
    textbox(sx+3+(9*4), sy+8, cur, htext, hcur, 5, milifont);
}

void error(int sx, int sy, int w, int h, Limg *milifont) {
    vline(sx, sy+1, sy+h, 0xA85450);
    vline(sx+w, sy+1, sy+h, 0xA85450);
    hline(sy, sx+1, sx+w, 0xA85450);
    hline(sy+h, sx+1, sx+w, 0xA85450);
    rect(sx+1, sx+w, sy+1, sy+h, 0xF8FCF8);
    /* Inside the popup */
    stext(sx+w/2-(7*4/2), sy+h/2-3, 3, 5, "Error !", milifont);
}

void enter_filename(int sx, int sy, int w, int h, char *filename, int cur, Limg *milifont) {
    vline(sx, sy+1, sy+h, 0xA85450);
    vline(sx+w, sy+1, sy+h, 0xA85450);
    hline(sy, sx+1, sx+w, 0xA85450);
    hline(sy+h, sx+1, sx+w, 0xA85450);
    rect(sx+1, sx+w, sy+1, sy+h, 0xF8FCF8);
    /* Inside the popup */
    stext(sx+3, sy+h/2-3, 3, 5, "File name :", milifont);
    textbox(sx+3+(12*4), sy+h/2-4, 1, filename, cur, 8, milifont);
    stext(sx+3+(21*4), sy+h/2-3, 3, 5, ".limg", milifont);
}
