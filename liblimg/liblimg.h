/*
 * liblimg - Manipulate limg images in C.
 * Copyright (C) 2023  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#ifndef LIBLIMG_H
#define LIBLIMG_H

#include <stdint.h>

/* Error codes */

enum {
    MAGIC_NOTFOUND       = -1,
    MALLOCERROR_CARRAY   = -2,
    PALETTE_BADINDEX     = -3,
    LIMG_ALREADYFREE     = -4,
    MALLOCERROR_LIMGDATA = -5,
    COLOR_MISSING        = -6
};

typedef struct {
    uint16_t *carray;
    int w, h;
} Limg;

/***************/

/* void limg_init(Limg *limg);

Prepare the Limg struct to be used. Only use this function one time, before
calling any other functions of this lib.
*/

void limg_init(Limg *limg);

/* int limg_encode(unsigned char **limg_data, Limg *limg);

Converts the data in the Limg struct to a LIMG-V1 image inside of limg_data.
This function allocates limg_data to the right size.
This function returns a negative error code or the size of limg_data.
Here is an example, where we suppose that we already wrote everything into a
Limg struct named limg :

unsigned char *limg_data;
int out;

out = limg_encode(&limg_data, &limg);

if(out < 0) return out;
fp = fopen(argv[2], "wb");
if(fp == NULL){
    printf("Can't make \"%s\"\n", argv[2]);
    return 2;
}
fwrite((char*)limg_data, 1, out, fp);
fclose(fp);
free(limg_data);
*/

int limg_encode(unsigned char **limg_data, Limg *limg);

/* int limg_decode(unsigned char *limg_data, Limg *limg);

This function reads limg_data and puts anything into limg, a Limg struct.
This function returns a negative error code or 0.
*/

int limg_decode(unsigned char *limg_data, Limg *limg);

/* int limg_free(Limg *limg);

This function frees limg, so that you can reuse it for another image or use it
when you finished using a Limg struct to free the array of colors before
exiting.
*/

int limg_free(Limg *limg);

/* void limg_setpixel(int x, int y, uint16_t color, Limg *limg);

Set the color of the pixel at position x, y to color, of Limg limg.
*/

void limg_setpixel(int x, int y, uint16_t color, Limg *limg);

/* uint16_t limg_getpixel(int x, int y, Limg *limg);

Returns the color of the pixel at (x, y) of limg, or 0 (black) if the position
is not in the image.
*/

uint16_t limg_getpixel(int x, int y, Limg *limg);

#endif
