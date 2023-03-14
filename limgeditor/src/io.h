#ifndef IO_H
#define IO_H

#include <libudraw.h>
#include <rgbconv.h>
#include <liblimg.h>
#include <rgbconv.h>

#include "draw_limg.h"
#include "gfx.h"
#include "popups.h"
#include "keyboard.h"
#include "file.h"
#include "error.h"
#include "text.h"
#include "menu.h"
#include "filechooser.h"
#include "textbox.h"
#include "textinput.h"

#define VWIDTH  364
#define VHEIGHT 192

#define MILIFONT "./data/milifont.limg"

#define F_AMOUNT 30

typedef struct {
    unsigned char *limg_data;
    Limg limg, milifont;
    int out, x, y, scale, ix, iy, colorcur, menucur, w, h;
    int dirsize, dircur, dirview;
    int mainmenucur;
    bool moverepeat;
    uint16_t color;
    unsigned char rgb[3];
    char wtext[6], htext[6];
    int wcur, hcur, ncur;
    char ftext[9];
    int fcur;
    FILE *fp;
    int state, ask_changestate;
} Io;

void io_init(Io *io);
void editor_input(Io *io);

#endif
