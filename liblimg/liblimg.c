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

#include "liblimg.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG (0)

#if DEBUG
#include <stdio.h>
#endif

/* Tools to manipulate data */

uint16_t _get_uint16_t(unsigned char n1, unsigned char n2) {
    return (n1<<8)+n2;
}

bool _colorinpalette(uint16_t color, uint16_t palette[256], int psize) {
    int i;
    for(i=0;i<psize;i++){
        if(palette[i] == color) return 1;
    }
    return 0;
}

void _put_uint16_t(uint16_t value, unsigned char *out, int start_pos) {
    out[start_pos] = value>>8;
    out[start_pos+1] = value;
}

int _getcolor(uint16_t color, uint16_t palette[256], int psize) {
    int i;
    for(i=0;i<psize;i++){
        if(palette[i] == color) return i;
    }
    return -1;
}

/****************************/

void limg_init(Limg *limg) {
    limg->carray = NULL;
    limg->w = 0;
    limg->h = 0;
}

int limg_encode(unsigned char **limg_data, Limg *limg) {
    uint16_t palette[256], color;
    int size = limg->w*limg->h, i, palette_pos = 0, pos, dsize;
    /* Get the amount of colors */
    for(i=0;i<size;i++){
        color = limg->carray[i];
        if(!_colorinpalette(color, palette, palette_pos)){
            /* If the color is not found, add it */
            palette[palette_pos] = color;
            palette_pos++;
            if(palette_pos > 255){
                /* If the palette is too big, exit the loop and set the palette
                size to 0. */
                palette_pos = 0;
                break;
            }
        }
    }
#if DEBUG
    printf("The image has %d colors.\n", palette_pos);
#endif
    /* malloc limg_data */
    *limg_data = NULL;
    dsize = (12+palette_pos*2+(palette_pos > 0 ? limg->w*limg->h : limg->w*limg->h*2))*sizeof(unsigned char);
    *limg_data = malloc(dsize);
    if(*limg_data == NULL){
        return MALLOCERROR_LIMGDATA;
    }
    /* Start writing ... */
    /* Write the magic "LIMG-V1" */
    strcpy((char*)*limg_data, "LIMG-V1");
    _put_uint16_t((uint16_t)limg->w, *limg_data, 7);
    _put_uint16_t((uint16_t)limg->h, *limg_data, 9);
    (*limg_data)[11] = (unsigned char)palette_pos;
    for(i=0;i<palette_pos;i++){ /* Put the palette into limg_data if we've one. */
        _put_uint16_t(palette[i], *limg_data, 12+i*2);
    }
    /* And now, trow the pixels into limg_data */
    if(palette_pos>0){ /* If we've a palette */
        for(i=0;i<limg->w*limg->h;i++){
            pos = _getcolor(limg->carray[i], palette, palette_pos);
            if(pos < 0) return COLOR_MISSING;
            (*limg_data)[12+palette_pos*2+i] = (unsigned char)pos;
        }
    }else{
        for(i=0;i<limg->w*limg->h;i++){
            _put_uint16_t(limg->carray[i], *limg_data, 12+i*2);
        }
    }
    return dsize;
}

int limg_decode(unsigned char *limg_data, Limg *limg) {
    unsigned char magic[8];
    int w, h, p, i, pos, color, out;
    /* Verify that the limg_data starts with magic "LIMG-V1" */
    strncpy((char *)magic, (char *)limg_data, 7);
    magic[7] = '\0';
    if(strcmp((char *)magic, "LIMG-V1") != 0){
        return MAGIC_NOTFOUND;
    }
    /* Get the width, the height and the palette size (0 if there is no
    palette) */
    w = (int)_get_uint16_t(limg_data[7], limg_data[8]);
    h = (int)_get_uint16_t(limg_data[9], limg_data[10]);
    p = (int)limg_data[11];
#if DEBUG
    printf("Image width = %d, height = %d, palette size %d\n", w, h, p);
#endif
    /* malloc carray */
    if(limg->carray != NULL){ /* Reset limg if required */
        out = limg_free(limg);
        if(out != 0){
            return out;
        }
    }
    limg->carray = NULL;
    limg->carray = malloc(sizeof(uint16_t)*(w*h));
    if(limg->carray == NULL){
        return MALLOCERROR_CARRAY;
    }
    /* load the image into carray */
    for(i=0;i<w*h;i++){
        if(p > 0){ /* If we have a palette */
            pos = (int)limg_data[12+(p*2)+i];
            if(pos >= p){
                return PALETTE_BADINDEX;
            }
            color = _get_uint16_t(limg_data[12+(pos*2)], limg_data[12+(pos*2)+1]);
        }else{ /* We have no palette so it's easier ! */
            color = _get_uint16_t(limg_data[12+(i*2)], limg_data[12+(i*2)+1]);
        }
        /* Put the color in carray */
        limg->carray[i] = color;
#if DEBUG
        printf("%04x, ", color);
#endif
    }
#if DEBUG
    puts("\n");
#endif
    /* Put the width and the height in size */
    limg->w = w;
    limg->h = h;
    return 0;
}

int limg_free(Limg *limg) {
    if(limg->carray == NULL){
        return LIMG_ALREADYFREE;
    }
    free(limg->carray);
    limg->carray = NULL;
    limg->w = 0;
    limg->h = 0;
    return 0;
}

void limg_setpixel(int x, int y, uint16_t color, Limg *limg) {
    /* Check that the position is valid */
    if(x>=0 && x<limg->w && y>=0 && y<limg->h){
        /* Put the color into carray */
        limg->carray[y*limg->w+x] = color;
    }
}

uint16_t limg_getpixel(int x, int y, Limg *limg) {
    /* Check that the position is valid */
    if(x>=0 && x<limg->w && y>=0 && y<limg->h){
        /* Get the color of carray */
        return limg->carray[y*limg->w+x];
    }
    /* Return 0 because it's black and we found nothing */
    return 0;
}
