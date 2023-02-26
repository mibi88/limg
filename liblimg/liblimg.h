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

void limg_init(Limg *limg);
int limg_encode(unsigned char **limg_data, Limg *limg);
int limg_decode(unsigned char *limg_data, Limg *limg);
int limg_free(Limg *limg);

#endif
