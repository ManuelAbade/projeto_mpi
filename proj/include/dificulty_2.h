#ifndef DIFICULTY_2_H
#define DIFICULTY_2_H


#include <stdbool.h>
#include <raylib.h>
#include "utils.h"

extern Texture2D background;
extern Texture2D banners;
extern int dificulty;
extern int size;


void Dificulty2(ActualScreen *screen, int window_h, int window_w, bool settings_open);

#endif