#include "rgbconv.h"

uint16_t rgb888torgb565(uint32_t rgb888) {
    int r, g, b;
    uint16_t c;
    r = rgb888>>16;
	g = (rgb888>>8) - (r<<8);
	b = rgb888 - (rgb888>>8<<8);
    c = b/8;
    c += (g/4)<<5;
    c += (r/8)<<11;
    return (uint16_t)c;
}

uint32_t rgb565torgb888(uint16_t rgb565) {
    int r, g, b;
    uint32_t c;
    r = rgb565>>11;
	g = (rgb565>>5) - (r<<6);
	b = rgb565 - (rgb565>>5<<5);
    c = b*8;
    c += (g*4)<<8;
    c += (r*8)<<16;
    return c;
}

void getrgb888(uint32_t rgb888, unsigned char rgb_out[3]) {
    int r, g, b;
    r = rgb888>>16;
	g = (rgb888>>8) - (r<<8);
	b = rgb888 - (rgb888>>8<<8);
    rgb_out[0] = r;
    rgb_out[1] = g;
    rgb_out[2] = b;
}

void getrgb565(uint16_t rgb565, unsigned char rgb_out[3]) {
    int r, g, b;
    r = rgb565>>11;
	g = (rgb565>>5) - (r<<6);
	b = rgb565 - (rgb565>>5<<5);
    rgb_out[0] = r;
    rgb_out[1] = g;
    rgb_out[2] = b;
}

uint32_t makergb888(unsigned char rgb888[3]) {
    int r, g, b;
    uint32_t c;
    r = rgb888[0];
    g = rgb888[1];
    b = rgb888[2];
    c = b;
    c += g<<8;
    c += r<<16;
    return c;
}

uint16_t makergb565(unsigned char rgb565[3]) {
    int r, g, b;
    uint16_t c;
    r = rgb565[0];
    g = rgb565[1];
    b = rgb565[2];
    c = b;
    c += g<<5;
    c += r<<11;
    return c;
}
