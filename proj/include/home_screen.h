#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include "raylib.h"
#include "utils.h"
#include "stdio.h"
#include "main.h"

extern Font actual_font;
extern Texture2D background;
extern Texture2D button;
extern Texture2D button_pressed;
extern Texture2D banners;


void HomeScreen(ActualScreen *screen,int window_h, int window_w,bool settings_open);



#endif 