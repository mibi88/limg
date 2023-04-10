#include "../../../src/filechooser.h"
#include <gint/gint.h>

extern int _frame;

char _path[PATH_MAX+1];
char *_tmppath;
char _file[PATH_MAX+NAME_MAX+1];
char *filelist = NULL;
bool *filetypes = NULL;
int *filepos = NULL;
int *filelen = NULL;
int filelistsz = 0, filetypessz = 0, filepossz = 0, filelensz = 0;
int filesamount;

bool _checkfileexists(char *file) {
    FILE *fp;
    fp = fopen(file, "rb");
    if(fp){
        fclose(fp);
        return 1;
    }
    return 0;
}

bool checkfileexists(char *file) {
    return gint_world_switch(GINT_CALL(_checkfileexists, file));
}

int getdirsize(void) {
    return filesamount;
}

void initfilechooser(char *dir_str) {
    strcpy(_path, dir_str);
    _tmppath = NULL;
    _tmppath = fs_path_normalize(_path);
    if(_tmppath){
        memset(_path, '\0', PATH_MAX);
        memcpy(_path, _tmppath, strlen(_tmppath));
        free(_tmppath);
    }
    makefilelist();
}

int _makefilelist(void) {
    DIR *dir;
    struct dirent *ent;
    int sz, i;
    if(filelist){
        free(filelist);
        filelistsz = 0;
        filelist = NULL;
    }
    if(filetypes){
        free(filetypes);
        filetypessz = 0;
        filetypes = NULL;
    }
    if(filepos){
        free(filepos);
        filepossz = 0;
        filepos = NULL;
    }
    if(filelen){
        free(filelen);
        filelensz = 0;
        filelen = NULL;
    }
    filesamount = 0;
    dir = opendir(_path);
    /* Add ".." dir */
    sz = 2;
    filelist = realloc(filelist, (filelistsz+sz)*sizeof(char));
    if(!filelist) return -1;
    for(i=0;i<sz;i++) filelist[filelistsz+i] = '.';
    /* alloc 1 done */
    filepos = realloc(filepos, (filetypessz+1)*sizeof(int));
    if(!filepos) return -1;
    filepos[filepossz] = filelistsz;
    filepossz += 1;
    /* alloc 2 done */
    filelistsz += sz*sizeof(char);
    filetypes = realloc(filetypes, (filetypessz+1)*sizeof(bool));
    if(!filetypes) return -1;
    filetypes[filetypessz] = 0;
    filetypessz += 1;
    /* alloc 3 done */
    filelen = realloc(filelen, (filetypessz+1)*sizeof(int));
    if(!filelen) return -1;
    filelen[filelensz] = sz;
    filelensz += 1;
    /* alloc 4 done */
    filesamount++;
    if(dir != NULL){
        ent = readdir(dir);
        while(ent != NULL){
            if(ent->d_type == DT_DIR && !(ent->d_name[0] == '.' && strlen(ent->d_name) <= 2)){
                sz = strlen(ent->d_name);
                filelist = realloc(filelist, (filelistsz+sz)*sizeof(char));
                if(!filelist) return -1;
                for(i=0;i<sz;i++) filelist[filelistsz+i] = ent->d_name[i];
                /* alloc 1 done */
                filepos = realloc(filepos, (filetypessz+1)*sizeof(int));
                if(!filepos) return -1;
                filepos[filepossz] = filelistsz;
                filepossz += 1;
                /* alloc 2 done */
                filelistsz += sz*sizeof(char);
                filetypes = realloc(filetypes, (filetypessz+1)*sizeof(bool));
                if(!filetypes) return -1;
                filetypes[filetypessz] = 0;
                filetypessz += 1;
                /* alloc 3 done */
                filelen = realloc(filelen, (filetypessz+1)*sizeof(int));
                if(!filelen) return -1;
                filelen[filelensz] = sz;
                filelensz += 1;
                /* alloc 4 done */
                filesamount++;
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
                sz = strlen(ent->d_name);
                filelist = realloc(filelist, (filelistsz+sz)*sizeof(char));
                if(!filelist) return -1;
                for(i=0;i<sz;i++) filelist[filelistsz+i] = ent->d_name[i];
                /* alloc 1 done */
                filepos = realloc(filepos, (filetypessz+1)*sizeof(int));
                if(!filepos) return -1;
                filepos[filepossz] = filelistsz;
                filepossz += 1;
                /* alloc 2 done */
                filelistsz += sz*sizeof(char);
                filetypes = realloc(filetypes, (filetypessz+1)*sizeof(bool));
                if(!filetypes) return -1;
                filetypes[filetypessz] = 1;
                filetypessz += 1;
                /* alloc 3 done */
                filelen = realloc(filelen, (filetypessz+1)*sizeof(int));
                if(!filelen) return -1;
                filelen[filelensz] = sz;
                filelensz += 1;
                /* alloc 4 done */
                filesamount++;
            }
            ent = readdir(dir);
        }
        closedir(dir);
    }
    if(!filelist || !filetypes || !filepos || !filelen) return -2;
    return 0;
}

int makefilelist(void) {
    return gint_world_switch(GINT_CALL(_makefilelist));
}

int filechooser(int cur, int amount, int selection, Limg *milifont) {
    int i = 0, di, r = 0;
    char dsp[97];
    unsigned char rgb[3];
    char name[NAME_MAX];
    uClear((uint32_t)0xC8FC90);
    selection = selection-cur;
    for(i=cur;i<cur+amount;i++){
        if(i < filesamount){
            memset(name, 0x00, NAME_MAX);
            memcpy(name, filelist+filepos[i], filelen[i]);
            if(filetypes[i] == 0){
                di = i-cur;
                if(di == selection){
                    rgb[0] = (unsigned char)_frame*15;
                    rgb[1] = rgb[0];
                    rgb[2] = rgb[0];
                    rect(1, 394, FILELIST_START+di*7-1, FILELIST_START+di*7+6, makergb888(rgb));
                    if(kbd_kdown(KX) && strlen(name)+1+strlen(_path) < PATH_MAX){
                        strcat(_path, "/");
                        strcat(_path, name);
                        _tmppath = NULL;
                        _tmppath = fs_path_normalize(_path);
                        if(_tmppath){
                            memset(_path, '\0', PATH_MAX);
                            memcpy(_path, _tmppath, strlen(_tmppath));
                            free(_tmppath);
                        }
                        makefilelist();
                    }
                }
                rect(2, 393, FILELIST_START+di*7, FILELIST_START+di*7+5, 0xF8FCF8);
                if(strlen(name)+3 < 94) sprintf(dsp, "[%.94s]", name);
                else sprintf(dsp, "[%.88s...]", name);
                stext(2, FILELIST_START+di*7, 3, 5, dsp, milifont);
            }else{
                di = i-cur;
                if(di == selection){
                    rgb[0] = (unsigned char)_frame*15;
                    rgb[1] = rgb[0];
                    rgb[2] = rgb[0];
                    rect(1, 394, FILELIST_START+di*7-1, FILELIST_START+di*7+6, makergb888(rgb));
                    if(kbd_kdown(KX) && PATH_MAX+NAME_MAX>strlen(_path)+strlen(name)+1){
                        memset(_file, '\0', PATH_MAX+NAME_MAX);
                        strcpy(_file, _path);
                        strcat(_file, "/");
                        strcat(_file, name);
                        r = 1;
                    }
                }
                rect(2, 393, FILELIST_START+di*7, FILELIST_START+di*7+5, 0xF8FCF8);
                if(strlen(name)+3 < 96) sprintf(dsp, "%.96s", name);
                else sprintf(dsp, "%.90s...", name);
                stext(2, FILELIST_START+di*7, 3, 5, dsp, milifont);
            }
        }
    }
    rect(1, 393, 1, 6, 0xF8FCF8);
    stext(1, 1, 3, 5, _path, milifont);
    return r;
}

int pathchooser(int cur, int amount, int selection, Limg *milifont) {
    int i = 0, di;
    char dsp[97];
    unsigned char rgb[3];
    char name[NAME_MAX];
    uClear((uint32_t)0xC8FC90);
    selection = selection-cur;
    for(i=cur;i<cur+amount;i++){
        if(i < filesamount){
            memset(name, 0x00, NAME_MAX);
            memcpy(name, filelist+filepos[i], filelen[i]);
            if(filetypes[i] == 0){
                di = i-cur;
                if(di == selection){
                    rgb[0] = (unsigned char)_frame*15;
                    rgb[1] = rgb[0];
                    rgb[2] = rgb[0];
                    rect(1, 394, FILELIST_START+di*7-1, FILELIST_START+di*7+6, makergb888(rgb));
                    if(kbd_kdown(KX) && strlen(name)+1+strlen(_path) < PATH_MAX){
                        strcat(_path, "/");
                        strcat(_path, name);
                        _tmppath = NULL;
                        _tmppath = fs_path_normalize(_path);
                        if(_tmppath){
                            memset(_path, '\0', PATH_MAX);
                            memcpy(_path, _tmppath, strlen(_tmppath));
                            free(_tmppath);
                        }
                        makefilelist();
                    }
                }
                rect(2, 393, FILELIST_START+di*7, FILELIST_START+di*7+5, 0xF8FCF8);
                if(strlen(name)+3 < 94) sprintf(dsp, "[%.94s]", name);
                else sprintf(dsp, "[%.88s...]", name);
                stext(2, FILELIST_START+di*7, 3, 5, dsp, milifont);
            }else{
                di = i-cur;
                if(di == selection){
                    rgb[0] = (unsigned char)_frame*15;
                    rgb[1] = rgb[0];
                    rgb[2] = rgb[0];
                    rect(1, 394, FILELIST_START+di*7-1, FILELIST_START+di*7+6, makergb888(rgb));
                }
                rect(2, 393, FILELIST_START+di*7, FILELIST_START+di*7+5, 0xF8FCF8);
                if(strlen(name)+3 < 96) sprintf(dsp, "%.96s", name);
                else sprintf(dsp, "%.90s...", name);
                stext(2, FILELIST_START+di*7, 3, 5, dsp, milifont);
            }
        }
    }
    rect(1, 393, 1, 6, 0xF8FCF8);
    stext(1, 1, 3, 5, _path, milifont);
    if(kbd_kdown(KV)) return 1;
    return 0;
}
