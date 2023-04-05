#ifndef GFX_H
#define GFX_H

#include <libudraw.h>
#include <rgbconv.h>

void vline(int x, int y1, int y2, uint32_t color);
void hline(int y, int x1, int x2, uint32_t color);
void rect(int x1, int x2, int y1, int y2, uint32_t color);
void rect16(int x1, int x2, int y1, int y2, uint16_t color);
void pixel16(int x, int y, uint16_t color);

#endif
