#ifndef EDITOR_H
#define EDITOR_H

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

#define MILIFONT "../data/milifont.h"

#define F_AMOUNT 30

enum {
    SCREEN_EDITOR = 0,
    SCREEN_COLORC,
    SCREEN_MENU,
    SCREEN_OPEN,
    SCREEN_MAINMENU,
    SCREEN_NEW,
    SCREEN_SAVE1,
    SCREEN_SAVE2
};

void act_editor(void);
void act_colorc(void);
void act_menu(void);
void act_open(void);
void act_main_menu(void);
void act_new(void);
void act_save1(void);
void act_save2(void);
void act_default(void);

void disp_editor(void);
void disp_colorc(void);
void disp_open(void);
void disp_mainmenu(void);
void disp_new(void);
void disp_save1(void);
void disp_save2(void);
void disp_error(void);

#endif
