#ifndef DROP_MENU_H
#define DROP_MENU_H

#include "main.h"
#include "raylib.h"
#include "utils.h"
#include <stdbool.h>
#define MAX_PATH_SIZE 260
#define SONGS_NUMBER 16
#define FONTS_NUMBER 14
#define MAX_SONG_NAME_SIZE 35
#define MAX_FONT_NAME_SIZE 35
#define MAX_TAB_WIDGETS 6
#define NUMBER_OF_ITEMS (SONGS_NUMBER>=FONTS_NUMBER?SONGS_NUMBER:FONTS_NUMBER)
#define MAX_NAME_SIZE (MAX_SONG_NAME_SIZE>=MAX_FONT_NAME_SIZE?MAX_SONG_NAME_SIZE:MAX_FONT_NAME_SIZE)
extern Font actual_font;
extern Texture2D options_arrow; 


typedef struct 
{
    int len;
    char options_names[NUMBER_OF_ITEMS][MAX_NAME_SIZE];
    char options[NUMBER_OF_ITEMS][MAX_PATH_SIZE];
    char selected[MAX_NAME_SIZE];
    int selected_id;
    bool is_tab_open;
    int actual_first;
} DropMenu;

bool dropMenu(DropMenu *menu,int x, int y, int width, int height);
bool  OpenTab(DropMenu *menu,Rectangle tabs_open[], int height, int width,int max);
bool React(DropMenu *menu,Rectangle tabs_open[], int idx,int i);
Color DrawTabsColor(DropMenu *menu,Rectangle tabs_open[],int idx,int i ,Color color1,Color color2, Color color3);
void DrawTabs(DropMenu *menu,Rectangle tabs_open[],int idx, int i, int height, Color color1,Color color2, Color color3);

#endif