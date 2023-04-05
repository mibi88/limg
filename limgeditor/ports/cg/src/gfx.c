#include "../../../src/gfx.h"
#include <gint/display.h>

void vline(int x, int y1, int y2, uint32_t color) {
    int tmp, i;
    if(y2<y1){
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    for(i=y1;i<y2;i++){
        uPixel(x, i, color);
    }
}

void hline(int y, int x1, int x2, uint32_t color) {
    int tmp, i;
    if(x2<x1){
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    for(i=x1;i<x2;i++){
        uPixel(i, y, color);
    }
}

void rect(int x1, int x2, int y1, int y2, uint32_t color) {
    drect(x1, y1, x2, y2, rgb888torgb565(color));
}

void rect16(int x1, int x2, int y1, int y2, uint16_t color) {
    drect(x1, y1, x2, y2, color);
}

void pixel16(int x, int y, uint16_t color) {
    gint_vram[DWIDTH*y+x] = color;
}
