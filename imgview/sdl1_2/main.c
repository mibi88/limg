/*
 * limgimgview - View limg images.
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
#include <rgbconv.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL/SDL.h>

void report_error(int error) {
    printf("Error when reading this image, error %d :\n", error);
    switch(error){
        case MAGIC_NOTFOUND:
            puts("Magic \"LIMG-V1\" not found !");
            break;
        case MALLOCERROR_CARRAY:
            puts("Need more ram to malloc carray !");
            break;
        case PALETTE_BADINDEX:
            puts("Bad index for the palette !");
            break;
        case LIMG_ALREADYFREE:
            puts("Limg image is already free !");
            break;
        case MALLOCERROR_LIMGDATA:
            puts("Need more ram to malloc limg_data !");
            break;
        case COLOR_MISSING:
            puts("Color missing !");
            break;
        default:
            puts("Unknown error !");
    }
}

int main(int argc, char **argv) {
    unsigned char *limg = NULL;
    Limg dlimg;
    int size, out, open = 1, x, y, scale = 1, sx, sy;
    FILE *fp;
    SDL_Surface *window_surface;
    SDL_Event event;
    uint32_t rgb;
    Uint32 *target_pixel;
    if(argc < 2){
        puts("More args required !");
        puts("imgview <limg image> <scale : optional>");
        return 1;
    }
    if(argc >= 3){
        scale = atoi(argv[2]);
        if(scale < 1){
            scale = 1;
        }
        if(scale > 8){
            scale = 8;
        }
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
		puts("More memory needed !");
        return 3;
	}
	fread(limg, 1, sizeof(unsigned char) * size, fp);
	fclose(fp);
    limg_init(&dlimg);
    out = limg_decode(limg, &dlimg);
    if(out < 0){
        report_error(out);
    }
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        puts("Failed to initialize the SDL !");
        return -1;
    }
    SDL_WM_SetCaption("Limg viewer", "Limg viewer");
    window_surface = SDL_SetVideoMode(dlimg.w*scale, dlimg.h*scale, 0, 0);
    if(!window_surface){
        puts("Failed to get the surface from the SDL window !");
        return -1;
    }
    SDL_LockSurface(window_surface);
    for(y=0;y<window_surface->h/scale;y++){
        for(x=0;x<window_surface->w/scale;x++){
            rgb = rgb565torgb888(limg_getpixel(x, y, &dlimg));
            for(sy=0;sy<scale;sy++){
                for(sx=0;sx<scale;sx++){
                    target_pixel = (Uint32 *)((Uint8 *)window_surface->pixels +
                    (y*scale+sy) * window_surface->pitch + (x*scale+sx) *
                    window_surface->format->BytesPerPixel);
                    *target_pixel = rgb;
                }
            }
        }
    }
    SDL_UnlockSurface(window_surface);
    while(open){
        while(SDL_PollEvent(&event) > 0){
            if(event.type == SDL_QUIT){
                open = 0;
            }
        }
        SDL_Flip(window_surface);
    }
    limg_free(&dlimg);
    free(limg);
    SDL_FreeSurface(window_surface);
    SDL_Quit();
    return 0;
}
