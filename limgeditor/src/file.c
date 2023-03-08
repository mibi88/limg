#include "file.h"

void load_limg(char *file_name, Limg *limg) {
    int out, size;
    FILE *fp;
    unsigned char *limg_data = NULL;
    fp = fopen(file_name, "rb");
    if(fp == NULL){
        printf("[Load limg] Can't open \"%s\"\n", file_name);
        exit(2);
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    limg_data = malloc(sizeof(unsigned char) * size);
    if(limg_data == NULL){
        puts("[Load limg] More memory needed !");
        exit(3);
    }
    fread(limg_data, 1, sizeof(unsigned char) * size, fp);
    fclose(fp);
    out = limg_decode(limg_data, limg);
    free(limg_data);
    if(out < 0) report_error(out);
}
