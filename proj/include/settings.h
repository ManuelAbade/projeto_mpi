#ifndef SETTINGS_H
#define SETTINGS_H
#include "utils.h"
#include "drop_menu.h"
#include "raylib.h"
#include "string.h"
#include "main.h"
#include "slide_bar.h"


#define SETTINGS_MENU_COLOR GRAY
#define SETTINGS_MENU_BUTTON_RADIUS 15
#define FONT_HEIGHT 20
#define FONT_SIZE 20
#define INCREMENT 4

extern Texture2D banners;
extern Texture2D settings_button;
extern Texture2D background;
extern Texture2D close_button; 
extern int volume;
extern int music_volume;
extern Font actual_font;
extern Music actual_music;
extern WindowMode wind_mode;

typedef struct 
{
    Color color;
    char* text;
} Settings;

bool SetMenu(bool *setting_old_open_state, int window_w, int window_h);



#endif 