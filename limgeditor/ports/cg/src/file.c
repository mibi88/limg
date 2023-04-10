#include "../../../src/file.h"
#include <gint/gint.h>

extern int state;

Limg *_limg;

#define limg _limg

void _load_limg(char *file_name) {
    int out, size;
    FILE *fp;
    unsigned char *limg_data = NULL;
    fp = fopen(file_name, "rb");
    if(fp == NULL){
        printf("[Load limg] Can't open \"%s\"\n", file_name);
        state = -4;
    }else{
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        rewind(fp);
        limg_data = malloc(sizeof(unsigned char) * size);
        if(limg_data == NULL){
            puts("[Load limg] More memory needed !");
            state = -5;
        }else{
            if(!fread(limg_data, 1, sizeof(unsigned char) * size, fp)){
                fclose(fp);
                state = -6;
                return;
            }
            fclose(fp);
            out = limg_decode(limg_data, limg);
            free(limg_data);
            if(out < 0) state = -6;
        }
    }
}

#undef limg

void load_limg(char *file_name, Limg *limg) {
    _limg = limg;
    gint_world_switch(GINT_CALL(_load_limg, file_name));
}

int _save_limg(char *file_name) {
    return limg_tofile(file_name, _limg);
}

int save_limg(char *file_name, Limg *limg) {
    _limg = limg;
    return gint_world_switch(GINT_CALL(_save_limg, file_name));
}
