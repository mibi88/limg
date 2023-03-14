#include "io.h"
void io_init(Io *io) {
     io->limg_data = NULL;
     io->x = 0;
     io->y = 0;
     io->scale = 4;
     io->ix = 0;
     io->iy = 0;
     io->colorcur = 0;
     io->menucur = 0;
     io->w = 16;
     io->h = 16;
     io->dircur = 0;
     io->dirview = 0;
     io->mainmenucur = 0;
     io->moverepeat = 1;
     io->color = 0x0000;
     io->wcur = 0;
     io->hcur = 0;
     io->ncur = 0;
     io->fcur = 0;
     io->state = 4;
     io->ask_changestate = 0;
}

void editor_input(Io *io) {
    /* Move the cursor */
    if(kbd_kdown(KUP) && io->y > 0) io->y--;
    if(kbd_kdown(KDOWN) && io->y < io->limg.h-1) io->y++;
    if(kbd_kdown(KLEFT) && io->x > 0) io->x--;
    if(kbd_kdown(KRIGHT) && io->x < io->limg.w-1) io->x++;
    /* Fix ix and iy */
    while(io->x > io->ix+VWIDTH/io->scale-1) io->ix++;
    while(io->x < io->ix) io->ix--;
    while(io->y > io->iy+VHEIGHT/io->scale-1) io->iy++;
    while(io->y < io->iy) io->iy--;
    if(io->x >= io->limg.w) io->x = io->limg.w - 1;
    if(io->y >= io->limg.h) io->y = io->limg.h - 1;
    /* Other actions */
    if(kbd_kdown(KC)){
        kbd_setrepeat(KLEFT, 0);
        kbd_setrepeat(KRIGHT, 0);
        kbd_setrepeat(KX, 0);
        io->state = 2;
    }
    if(kbd_kdown(KX)) limg_setpixel(io->x, io->y, io->color, &io->limg);
    if(kbd_kdown(KV)){
        kbd_setrepeat(KUP, 0);
        kbd_setrepeat(KDOWN, 0);
        kbd_setrepeat(KLEFT, 1);
        kbd_setrepeat(KRIGHT, 1);
        kbd_setrepeat(KX, 0);
        io->state = 1;
    }
}
