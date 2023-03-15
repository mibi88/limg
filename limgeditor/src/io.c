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
