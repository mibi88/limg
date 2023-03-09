#ifndef MENU_H
#define MENU_H

#include <libudraw.h>
#include <rgbconv.h>
#include "gfx.h"
#include "text.h"

#define MENU_SIZE 3

void draw_menu(int sx, int sy, int cur, bool active, const char menu[MENU_SIZE][9], Limg *milifont);

#endif
