/*
 * liblimg demo - A demo of liblimg.
 * Copyright (C) 2023  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#include <liblimg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    unsigned char *limg = NULL, *elimg = NULL;
    Limg dlimg;
    int size, out, i;
    FILE *fp;
    if(argc < 3){
        puts("More args required !\n");
        return 1;
    }
	fp = fopen(argv[1], "rb");
    if(fp == NULL){
        printf("Can't open \"%s\"\n", argv[1]);
        return 2;
    }
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	limg = malloc(sizeof(unsigned char) * size);
	if(limg == NULL){
		puts("More memory needed\n");
        return 3;
	}
	fread(limg, 1, sizeof(unsigned char) * size, fp);
	fclose(fp);
    limg_init(&dlimg);
    out = limg_decode(limg, &dlimg);
    /* printf("liblimg decodelimg returned %d\n", out); */
    /*for(i=0;i<dlimg.w*dlimg.h;i++){
        printf("%d, ", (int)dlimg.carray[i]);
    }
    puts("\n");*/
    out = limg_encode(&elimg, &dlimg);
    if(out < 0) return out;
    fp = fopen(argv[2], "wb");
    if(fp == NULL){
        printf("Can't make \"%s\"\n", argv[2]);
        return 2;
    }
    fwrite((char*)elimg, 1, out, fp);
    fclose(fp);
    limg_free(&dlimg);
    free(limg);
    free(elimg);
    return 0;
}
