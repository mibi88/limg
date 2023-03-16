#include "editor.h"

const char menu[MENU_SIZE][9] = {
    "C. Scale",
    "Rep. Mv.",
    "Cg. Col.",
    "Gr. Col.",
    "Save    ",
    "Mn. Menu"
};

int ask_changestate = 0;

extern char _file[PATH_MAX+NAME_MAX], _path[PATH_MAX];

extern int state;
extern unsigned char *limg_data;
extern Limg limg, milifont;
int out, x = 0, y = 0, scale = 4, ix = 0, iy = 0, colorcur = 0, menucur = 0;
int w = 16, h = 16;
int dirsize, dircur = 0, dirview = 0;
int mainmenucur = 0;
bool moverepeat = 1;
uint16_t color = 0x0000;
unsigned char rgb[3];
char wtext[6], htext[6];
int wcur = 0, hcur = 0, ncur = 0;
char ftext[9];
int fcur = 0;
FILE *fp;

/*********************************** ACTIONS **********************************/

void act_editor(void) {
    /* Move the cursor */
    if(kbd_kdown(KUP) && y>0) y--;
    if(kbd_kdown(KDOWN) && y<limg.h-1) y++;
    if(kbd_kdown(KLEFT) && x>0) x--;
    if(kbd_kdown(KRIGHT) && x<limg.w-1) x++;
    /* Fix ix and iy */
    while(x > ix+VWIDTH/scale-1) ix++;
    while(x < ix) ix--;
    while(y > iy+VHEIGHT/scale-1) iy++;
    while(y < iy) iy--;
    if(x >= limg.w) x = limg.w - 1;
    if(y >= limg.h) y = limg.h - 1;
    /* Other actions */
    if(kbd_kdown(KC)){
        kbd_setrepeat(KLEFT, 0);
        kbd_setrepeat(KRIGHT, 0);
        kbd_setrepeat(KX, 0);
        state = SCREEN_MENU;
    }
    if(kbd_kdown(KX)) limg_setpixel(x, y, color, &limg);
    if(kbd_kdown(KV)){
        kbd_setrepeat(KUP, 0);
        kbd_setrepeat(KDOWN, 0);
        kbd_setrepeat(KLEFT, 1);
        kbd_setrepeat(KRIGHT, 1);
        kbd_setrepeat(KX, 0);
        state = SCREEN_COLORC;
    }
}

void act_colorc(void) {
    if(kbd_kdown(KX)){
        ask_changestate = 1;
    }else if(ask_changestate && !uKeydown(KX)){
        kbd_setrepeat(KUP, moverepeat);
        kbd_setrepeat(KDOWN, moverepeat);
        kbd_setrepeat(KLEFT, moverepeat);
        kbd_setrepeat(KRIGHT, moverepeat);
        kbd_setrepeat(KX, 1);
        ask_changestate = 0;
        state = SCREEN_EDITOR;
    }
    if(kbd_kdown(KUP)){
        colorcur--;
        if(colorcur < 0) colorcur = 2;
    }
    if(kbd_kdown(KDOWN)){
        colorcur++;
        if(colorcur > 2) colorcur = 0;
    }
    getrgb565(color, rgb);
    if(kbd_kdown(KLEFT) && rgb[colorcur] > 0) rgb[colorcur]--;
    if(kbd_kdown(KRIGHT) && (colorcur == 1 ? rgb[colorcur] < 63 : rgb[colorcur] < 31)) rgb[colorcur]++;
    color = makergb565(rgb);
}

void act_menu(void) {
    if(kbd_kdown(KLEFT) && menucur > 0) menucur--;
    if(kbd_kdown(KRIGHT) && menucur < MENU_SIZE-1) menucur++;
    if(kbd_kdown(KX)){
        if(menucur == 0){
            scale++;
            if(scale > 8) scale = 1;
        }else if(menucur == 1){
            ask_changestate = 2;
        }else if(menucur == 2){
            kbd_setrepeat(KUP, 0);
            kbd_setrepeat(KDOWN, 0);
            kbd_setrepeat(KLEFT, 1);
            kbd_setrepeat(KRIGHT, 1);
            kbd_setrepeat(KX, 0);
            ask_changestate = 0;
            state = SCREEN_COLORC;
        }else if(menucur == 3){
            color = limg_getpixel(x, y, &limg);
        }else if(menucur == 4){
            initfilechooser(".");
            state = SCREEN_SAVE1;
        }else if(menucur == 5){
            state = SCREEN_MAINMENU;
        }
    }else if(ask_changestate == 2 && !uKeydown(KX)){
        moverepeat = !moverepeat;
        kbd_setrepeat(KUP, moverepeat);
        kbd_setrepeat(KDOWN, moverepeat);
        kbd_setrepeat(KLEFT, moverepeat);
        kbd_setrepeat(KRIGHT, moverepeat);
        kbd_setrepeat(KX, 1);
        ask_changestate = 0;
        state = SCREEN_EDITOR;
    }
    if(kbd_kdown(KC)){
        ask_changestate = 1;
    }else if(ask_changestate == 1 && !uKeydown(KC)){
        kbd_setrepeat(KLEFT, moverepeat);
        kbd_setrepeat(KRIGHT, moverepeat);
        kbd_setrepeat(KX, 1);
        ask_changestate = 0;
        state = SCREEN_EDITOR;
    }
}

void act_open(void) {
    kbd_setrepeat(KUP, 0);
    kbd_setrepeat(KDOWN, 0);
    kbd_setrepeat(KX, 0);
    dirsize = getdirsize();
    if(dirsize > 0){
        if(kbd_kdown(KUP) && dircur > 0) dircur--;
        if(kbd_kdown(KDOWN) && dircur < dirsize-1) dircur++;
        if(dircur > dirsize-1){
            dircur = dirsize-1;
        }
        while(dircur > dirview+F_AMOUNT-1) dirview++;
        while(dircur < dirview) dirview--;
    }
    if(kbd_kdown(KC)){
        ask_changestate = 1;
    }else if(!kbd_kdown(KC) && ask_changestate){
        ask_changestate = 0;
        state = SCREEN_MAINMENU;
    }
}

void act_main_menu(void) {
    kbd_setrepeat(KUP, 0);
    kbd_setrepeat(KDOWN, 0);
    kbd_setrepeat(KX, 0);
    if(kbd_kdown(KUP) && mainmenucur) mainmenucur = 0;
    if(kbd_kdown(KDOWN) && !mainmenucur) mainmenucur = 1;
    if(kbd_kdown(KX)){
        ask_changestate = 1;
    }else if(!kbd_kdown(KX) && ask_changestate == 1){
        ask_changestate = 0;
        memset(wtext, '\0', 6);
        memset(htext, '\0', 6);
        wcur = 0;
        hcur = 0;
        ncur = 0;
        if(mainmenucur) initfilechooser(".");
        state = mainmenucur ? SCREEN_OPEN : SCREEN_NEW;
    }
    if(kbd_kdown(KV)){
        ask_changestate = 2;
    }else if(!kbd_kdown(KV) && ask_changestate == 2){
        kbd_setrepeat(KUP, moverepeat);
        kbd_setrepeat(KDOWN, moverepeat);
        kbd_setrepeat(KLEFT, moverepeat);
        kbd_setrepeat(KRIGHT, moverepeat);
        kbd_setrepeat(KX, 1);
        ask_changestate = 0;
        state = SCREEN_EDITOR;
    }
}

void act_new(void) {
    kbd_setrepeat(KUP, 0);
    kbd_setrepeat(KDOWN, 0);
    kbd_setrepeat(KLEFT, 0);
    kbd_setrepeat(KRIGHT, 0);
    kbd_setrepeat(KX, 0);
    if(kbd_kdown(KUP) && ncur) ncur = 0;
    if(kbd_kdown(KDOWN) && !ncur) ncur = 1;
    if(!ncur) intinput(wtext, &wcur, 5);
    if(ncur) intinput(htext, &hcur, 5);
    if(kbd_kdown(KX)){
        ask_changestate = 1;
    }else if(!kbd_kdown(KX) && ask_changestate){
        w = atoi(wtext);
        h = atoi(htext);
        if(w < 1) w = 1;
        if(h < 1) h = 1;
        limg_free(&limg);
        out = limg_create(w, h, 0x0000, &limg);
        kbd_setrepeat(KUP, moverepeat);
        kbd_setrepeat(KDOWN, moverepeat);
        kbd_setrepeat(KLEFT, moverepeat);
        kbd_setrepeat(KRIGHT, moverepeat);
        kbd_setrepeat(KX, 1);
        ask_changestate = 0;
        state = out < 0 ? -1 : SCREEN_EDITOR;
    }
}

void act_save1(void) {
    kbd_setrepeat(KUP, 0);
    kbd_setrepeat(KDOWN, 0);
    kbd_setrepeat(KX, 0);
    dirsize = getdirsize();
    if(dirsize > 0){
        if(kbd_kdown(KUP) && dircur > 0) dircur--;
        if(kbd_kdown(KDOWN) && dircur < dirsize-1) dircur++;
        if(dircur > dirsize-1){
            dircur = dirsize-1;
        }
        while(dircur > dirview+F_AMOUNT-1) dirview++;
        while(dircur < dirview) dirview--;
    }
    if(kbd_kdown(KC)){
        ask_changestate = 2;
    }else if(!kbd_kdown(KC) && ask_changestate == 2){
        ask_changestate = 0;
        state = SCREEN_MAINMENU;
    }
}

void act_save2(void) {
    if(kbd_kdown(KX)){
        ask_changestate = 1;
    }else if(!kbd_kdown(KX) && ask_changestate){
        kbd_setrepeat(KUP, moverepeat);
        kbd_setrepeat(KDOWN, moverepeat);
        kbd_setrepeat(KLEFT, moverepeat);
        kbd_setrepeat(KRIGHT, moverepeat);
        kbd_setrepeat(KX, 1);
        strcat(_file, ftext);
        strcat(_file, ".limg");
        /* Save */
        out = limg_encode(&limg_data, &limg);
        if(out >= 0){
            fp = fopen(_file, "wb");
            if(fp != NULL){
                fwrite((char*)limg_data, 1, out, fp);
                fclose(fp);
            }else state = -3;
        }else state = -4;
        ask_changestate = 0;
        state = SCREEN_EDITOR;
    }
    if(!ask_changestate) fnameinput(ftext, &fcur, 8);
}

void act_default(void) {
    if(state < 0){
        kbd_setrepeat(KX, 0);
        if(kbd_kdown(KX)){
            ask_changestate = 1;
        }else if(!kbd_kdown(KX) && ask_changestate){
            kbd_setrepeat(KUP, moverepeat);
            kbd_setrepeat(KDOWN, moverepeat);
            kbd_setrepeat(KLEFT, moverepeat);
            kbd_setrepeat(KRIGHT, moverepeat);
            kbd_setrepeat(KX, 1);
            kbd_setrepeat(KC, 0);
            kbd_setrepeat(KV, 0);
            state = SCREEN_EDITOR;
            ask_changestate = 0;
        }
    }else{
        state = SCREEN_EDITOR;
    }
}

/*********************************** DISPLAY **********************************/

void disp_editor(void) {
    draw_limg(&limg, 32, 0, VWIDTH, VHEIGHT, ix, iy, scale, x, y);
    vline(31, 0, VHEIGHT, 0x588C28);
    hline(VHEIGHT, 32, 396, 0x588C28);
    draw_menu(32, 194, menucur, state == SCREEN_MENU, menu, &milifont);
}

void disp_colorc(void) {
    color = color_chooser(134, 80, 128, 64, color, colorcur, &milifont);
}

void disp_open(void) {
    if(filechooser(dirview, F_AMOUNT, dircur, &milifont)){
        ask_changestate = 1;
    }else if(!kbd_kdown(KX) && ask_changestate){
        ask_changestate = 0;
        kbd_setrepeat(KUP, moverepeat);
        kbd_setrepeat(KDOWN, moverepeat);
        kbd_setrepeat(KX, 1);
        limg_free(&limg);
        load_limg(_file, &limg);
        state = SCREEN_EDITOR;
    }
}

void disp_mainmenu(void) {
    main_menu(134, 80, 128, 64, mainmenucur, &milifont);
}

void disp_new(void) {
    new_file(134, 80, 128, 64, wtext, htext, wcur, hcur, ncur, &milifont);
}

void disp_save1(void) {
    if(pathchooser(dirview, F_AMOUNT, dircur, &milifont)){
        ask_changestate = 1;
    }else if(!kbd_kdown(KV) && ask_changestate == 1){
        ask_changestate = 0;
        if(strlen(_path)+15<=PATH_MAX+NAME_MAX){
            memset(_file, '\0', PATH_MAX+NAME_MAX);
            strcpy(_file, _path);
            strcat(_file, "/");
            state = SCREEN_SAVE2;
        }else{
            state = -2;
        }
    }
}

void disp_save2(void) {
    enter_filename(134, 80, 128, 64, ftext, fcur, &milifont);
}

void disp_error(void) {
    error(134, 80, 128, 64, &milifont);
}
