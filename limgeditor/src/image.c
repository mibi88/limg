#include "image.h"

void simgpart(int sx, int sy, int ox, int oy, int w, int h, Limg *limg) {
    int x, y;
    uint32_t color;
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            color = rgb565torgb888(limg_getpixel(ox+x, oy+y, limg));
            uPixel(sx+x, sy+y, color);
        }
    }
}
