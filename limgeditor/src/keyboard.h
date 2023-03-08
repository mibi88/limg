#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYS 7

#include <libudraw.h>
#include <stdbool.h>

bool kbd_kdown(int key);
void kbd_setrepeat(int key, bool repeat);

#endif
