#include "filechooser.h"

extern int _frame;

char _path[PATH_MAX];
char _file[PATH_MAX+NAME_MAX];

int getdirsize(void) {
    DIR *dir;
    struct dirent *ent;
    int i=0;
    dir = opendir(_path);
    if(dir != NULL){
        ent = readdir(dir);
        while(ent != NULL){
            if(ent->d_type == DT_DIR && !(ent->d_name[1] != '.' && ent->d_name[0] == '.')){
                i++;
            }
            if(ent->d_type == DT_REG){
                i++;
            }
            ent = readdir(dir);
        }
        closedir(dir);
        return i;
    }
    return 0;
}

void initfilechooser(char *dir_str) {
    strcpy(_path, dir_str);
}

int filechooser(int cur, int amount, int selection, Limg *milifont) {
    DIR *dir;
    struct dirent *ent;
    int i = 0, di, r = 0;
    char dsp[97];
    unsigned char rgb[3];
    dir = opendir(_path);
    uClear((uint32_t)0xC8FC90);
    selection = selection-cur;
    if(dir != NULL){
        ent = readdir(dir);
        while(ent != NULL){
            if(ent->d_type == DT_DIR && !(ent->d_name[1] != '.' && ent->d_name[0] == '.')){
                if(i>=cur && i<cur+amount){
                    di = i-cur;
                    if(di == selection){
                        rgb[0] = (unsigned char)_frame*15;
                        rgb[1] = rgb[0];
                        rgb[2] = rgb[0];
                        rect(1, 394, 8+di*7-1, 8+di*7+6, makergb888(rgb));
                        if(kbd_kdown(KX) && strlen(ent->d_name)+1+strlen(_path) < PATH_MAX){
                            strcat(_path, "/");
                            strcat(_path, ent->d_name);
                        }
                    }
                    rect(2, 393, 8+di*7, 8+di*7+5, 0xF8FCF8);
                    if(strlen(ent->d_name)+3 < 94) sprintf(dsp, "[%.94s]", ent->d_name);
                    else sprintf(dsp, "[%.88s...]", ent->d_name);
                    stext(2, 8+di*7, 3, 5, dsp, milifont);
                }
                i++;
            }
            ent = readdir(dir);
        }
        closedir(dir);
    }
    dir = opendir(_path);
    if(dir != NULL){
        ent = readdir(dir);
        while(ent != NULL){
            if(ent->d_type == DT_REG){
                if(i>=cur && i<cur+amount){
                    di = i-cur;
                    if(di == selection){
                        rgb[0] = (unsigned char)_frame*15;
                        rgb[1] = rgb[0];
                        rgb[2] = rgb[0];
                        rect(1, 394, 8+di*7-1, 8+di*7+6, makergb888(rgb));
                        if(kbd_kdown(KX) && PATH_MAX+NAME_MAX>strlen(_path)+strlen(ent->d_name)+1){
                            memset(_file, '\0', PATH_MAX+NAME_MAX);
                            strcpy(_file, _path);
                            strcat(_file, "/");
                            strcat(_file, ent->d_name);
                            r = 1;
                        }
                    }
                    rect(2, 393, 8+di*7, 8+di*7+5, 0xF8FCF8);
                    if(strlen(ent->d_name)+3 < 96) sprintf(dsp, "%.96s", ent->d_name);
                    else sprintf(dsp, "%.90s...", ent->d_name);
                    stext(2, 8+di*7, 3, 5, dsp, milifont);
                }
                i++;
            }
            ent = readdir(dir);
        }
        closedir(dir);
    }
    rect(1, 393, 1, 6, 0xF8FCF8);
    stext(1, 1, 3, 5, _path, milifont);
    return r;
}

int pathchooser(int cur, int amount, int selection, Limg *milifont) {
    DIR *dir;
    struct dirent *ent;
    int i = 0, di;
    char dsp[97];
    unsigned char rgb[3];
    dir = opendir(_path);
    uClear((uint32_t)0xC8FC90);
    selection = selection-cur;
    if(dir != NULL){
        ent = readdir(dir);
        while(ent != NULL){
            if(ent->d_type == DT_DIR && !(ent->d_name[1] != '.' && ent->d_name[0] == '.')){
                if(i>=cur && i<cur+amount){
                    di = i-cur;
                    if(di == selection){
                        rgb[0] = (unsigned char)_frame*15;
                        rgb[1] = rgb[0];
                        rgb[2] = rgb[0];
                        rect(1, 394, 8+di*7-1, 8+di*7+6, makergb888(rgb));
                        if(kbd_kdown(KX) && strlen(ent->d_name)+1+strlen(_path) < PATH_MAX){
                            strcat(_path, "/");
                            strcat(_path, ent->d_name);
                        }
                    }
                    rect(2, 393, 8+di*7, 8+di*7+5, 0xF8FCF8);
                    if(strlen(ent->d_name)+3 < 94) sprintf(dsp, "[%.94s]", ent->d_name);
                    else sprintf(dsp, "[%.88s...]", ent->d_name);
                    stext(2, 8+di*7, 3, 5, dsp, milifont);
                }
                i++;
            }
            ent = readdir(dir);
        }
        closedir(dir);
    }
    dir = opendir(_path);
    if(dir != NULL){
        ent = readdir(dir);
        while(ent != NULL){
            if(ent->d_type == DT_REG){
                if(i>=cur && i<cur+amount){
                    di = i-cur;
                    if(di == selection){
                        rgb[0] = (unsigned char)_frame*15;
                        rgb[1] = rgb[0];
                        rgb[2] = rgb[0];
                        rect(1, 394, 8+di*7-1, 8+di*7+6, makergb888(rgb));
                    }
                    rect(2, 393, 8+di*7, 8+di*7+5, 0xF8FCF8);
                    if(strlen(ent->d_name)+3 < 96) sprintf(dsp, "%.96s", ent->d_name);
                    else sprintf(dsp, "%.90s...", ent->d_name);
                    stext(2, 8+di*7, 3, 5, dsp, milifont);
                }
                i++;
            }
            ent = readdir(dir);
        }
        closedir(dir);
    }
    rect(1, 393, 1, 6, 0xF8FCF8);
    stext(1, 1, 3, 5, _path, milifont);
    if(kbd_kdown(KV)) return 1;
    return 0;
}
