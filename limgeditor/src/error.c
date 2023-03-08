#include "error.h"

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
        case LIMG_TOOBIG:
            puts("Too big image !");
            break;
        default:
            puts("Unknown error !");
    }
    exit(error);
}
