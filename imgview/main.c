#include <liblimg.h>
#include <rgbconv.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

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
    SDL_Window *window;
    SDL_Surface *window_surface;
    SDL_Event event;
    unsigned char *pixels, rgb[3];
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
        puts("Failed to initialize the SDL2 !");
        return -1;
    }
    window = SDL_CreateWindow("Limg viewer", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, dlimg.w*scale, dlimg.h*scale, 0);
    if(!window){
        puts("Failed to create an SDL2 window !");
        return -1;
    }
    window_surface = SDL_GetWindowSurface(window);
    if(!window_surface){
        puts("Failed to get the surface from the SDL2 window !");
        return -1;
    }
    SDL_LockSurface(window_surface);
    pixels = (unsigned char *)window_surface->pixels;
    for(y=0;y<window_surface->h/scale;y++){
        for(x=0;x<window_surface->w/scale;x++){
            getrgb888(rgb565torgb888(limg_getpixel(x, y, &dlimg)), rgb);
            for(sy=0;sy<scale;sy++){
                for(sx=0;sx<scale;sx++){
                    pixels[4*((y*scale+sy)*window_surface->w+(x*scale+sx))] = rgb[2];
                    pixels[4*((y*scale+sy)*window_surface->w+(x*scale+sx))+1] = rgb[1];
                    pixels[4*((y*scale+sy)*window_surface->w+(x*scale+sx))+2] = rgb[0];
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
        SDL_UpdateWindowSurface(window);
    }
    limg_free(&dlimg);
    free(limg);
    return 0;
}
