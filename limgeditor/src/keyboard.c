#include "keyboard.h"

bool _keys_already_down[KEYS];
bool _keys_repeat[KEYS];
int _keys[KEYS] = {KUP, KDOWN, KRIGHT, KLEFT, KX, KC, KV};

bool kbd_kdown(int key) {
    int i, pos = -1;
    /* Get the key index */
    for(i=0;i!=KEYS;i++){
        if(key == _keys[i]){
            pos = i;
            break;
        }
    }
    /* We return 0 if she's not in _keys */
    if(pos == -1) return 0;
    /* Check if repeat is enabled for this key */
    if(_keys_repeat[pos]){
        _keys_already_down[pos] = 1;
        return uKeydown(key);
    }else{
        if(uKeydown(key)){
            if(!_keys_already_down[pos]){
                _keys_already_down[pos] = 1;
                return 1;
            }
        }else if(_keys_already_down[pos]){
            _keys_already_down[pos] = 0;
        }
    }
    return 0;
}

void kbd_setrepeat(int key, bool repeat) {
    int i, pos = -1;
    /* Get the key index */
    for(i=0;i!=KEYS;i++){
        if(key == _keys[i]){
            pos = i;
            break;
        }
    }
    /* We return if she's not in _keys */
    if(pos == -1) return;
    /* We set repeat */
    _keys_repeat[pos] = repeat;
}
