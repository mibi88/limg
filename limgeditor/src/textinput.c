#include "textinput.h"

void intinput(char *text, int *cur, int len) {
    char c;
    int i;
    c = uGetchar();
    if(kbd_kdown(KLEFT) && *cur > 0) (*cur)--;
    if(kbd_kdown(KRIGHT) && *cur < len) if(text[*cur] != '\0') (*cur)++;
    if(c == 0x08 && *cur > 0){
        /* Shift text to the left */
        for(i=(*cur);i<len+1;i++){
            text[i-1] = i>=len ? '\0' : text[i];
        }
        (*cur)--;
    }else if(c>=0x30 && c<=0x39 && *cur<len){
        /* Shift text to the right */
        for(i=len-2;i>*cur-1;i--){
            text[i+1] = i<0 ? '\0' : text[i];
        }
        text[(*cur)] = c;
        (*cur)++;
    }
}

void fnameinput(char *text, int *cur, int len) {
    char c;
    int i;
    c = uGetchar();
    if(kbd_kdown(KLEFT) && *cur > 0) (*cur)--;
    if(kbd_kdown(KRIGHT) && *cur < len) if(text[*cur] != '\0') (*cur)++;
    if(c == 0x08 && *cur > 0){
        /* Shift text to the left */
        for(i=(*cur);i<len+1;i++){
            text[i-1] = i>=len ? '\0' : text[i];
        }
        (*cur)--;
    }else if(c>=0x20 && c<0x7F && c != '/' && *cur<len){
        /* Shift text to the right */
        for(i=len-2;i>*cur-1;i--){
            text[i+1] = i<0 ? '\0' : text[i];
        }
        text[(*cur)] = c;
        (*cur)++;
    }
}
