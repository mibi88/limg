#include "text.h"

void stext(int sx, int sy, int cw, int ch, char *str, Limg *limg) {
    long unsigned int i;
    int px, py, pos;
    for(i=0;i<strlen(str);i++){
        pos = (unsigned char)str[i]-0x20;
        px = pos % 16;
        py = pos / 16;
        simgpart(sx+i*(cw+1), sy, px*(cw+2)+1, py*(ch+2)+1, cw, ch, limg);
    }
}
