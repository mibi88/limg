#ifndef POPUPS_H
#define POPUPS_H

#include <libudraw.h>
#include <rgbconv.h>
#include "gfx.h"
#include "text.h"
#include "textbox.h"

uint16_t color_chooser(int sx, int sy, int w, int h, uint16_t color, int cur, Limg *milifont);
void main_menu(int sx, int sy, int w, int h, int cur, Limg *milifont);
void valid_save(int sx, int sy, int w, int h, int cur, Limg *milifont);
void new_file(int sx, int sy, int w, int h, char *wtext, char *htext, int wcur, int hcur, int cur, Limg *milifont);
void error(int sx, int sy, int w, int h, Limg *milifont);
void enter_filename(int sx, int sy, int w, int h, char *filename, int cur, Limg *milifont);

#endif
