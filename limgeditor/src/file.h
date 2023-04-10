#ifndef FILE_H
#define FILE_H

#include <liblimg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void load_limg(char *file_name, Limg *limg);
int save_limg(char *file_name, Limg *limg);

#endif
