#ifndef GFX_H
#define GFX_H

#include <libudraw.h>

void vline(int x, int y1, int y2, uint32_t color);
void hline(int y, int x1, int x2, uint32_t color);
void rect(int x1, int x2, int y1, int y2, uint32_t color);

#endif
