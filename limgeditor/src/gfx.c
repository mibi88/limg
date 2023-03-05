#include "gfx.h"

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
    int x, y, tmp;
    if(x2<x1){
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if(y2<y1){
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    for(y=y1;y<y2;y++){
        for(x=x1;x<x2;x++){
            uPixel(x, y, color);
        }
    }
}
