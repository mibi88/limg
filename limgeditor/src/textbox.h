#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <libudraw.h>
#include <rgbconv.h>
#include "gfx.h"
#include "text.h"

void textbox(int sx, int sy, int selected, char *text, int cur, int len, Limg *milifont);

#endif
