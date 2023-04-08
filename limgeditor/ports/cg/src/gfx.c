#include "../../../src/gfx.h"
#include <gint/display.h>

void pixel16(int x, int y, uint16_t color) {
    gint_vram[DWIDTH*y+x] = color;
}

void vline(int x, int y1, int y2, uint32_t color) {
    int tmp, i;
    uint16_t color16;
    color16 = rgb888torgb565(color);
    if(y2<y1){
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    for(i=y1;i<y2;i++){
        pixel16(x, i, color16);
    }
}

void hline(int y, int x1, int x2, uint32_t color) {
    int tmp, i;
    uint16_t color16;
    color16 = rgb888torgb565(color);
    if(x2<x1){
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    for(i=x1;i<x2;i++){
        pixel16(i, y, color16);
    }
}

void rect(int x1, int x2, int y1, int y2, uint32_t color) {
    drect(x1, y1, x2 - 1, y2 - 1, rgb888torgb565(color));
}

void rect16(int x1, int x2, int y1, int y2, uint16_t color) {
    drect(x1, y1, x2 - 1, y2 - 1, color);
}
