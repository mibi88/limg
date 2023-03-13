#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <libudraw.h>
#include <rgbconv.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "gfx.h"
#include "text.h"
#include "keyboard.h"

void initfilechooser(char *dir_str);
int getdirsize(void);
int filechooser(int cur, int amount, int selection, Limg *milifont);
int pathchooser(int cur, int amount, int selection, Limg *milifont);

#endif
