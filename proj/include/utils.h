#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "stdbool.h"
#include "math.h"
#include "stdio.h"
#include <string.h>

extern Font actual_font;
extern int window_h;
#define SPACEMENT (10.0f*window_h/WINDOW_HEIGHT)


typedef enum{
    HOME_SCREEN,
    DIFICULTY_1,
    PLAY_1,
    SELECT_PLAYERS,
    DIFICULTY_2,
    PLAY_2,
    EXIT
} ActualScreen;

typedef enum {
    WIN_WINDOWED = 0,
    WIN_BORDERLESS = 1,
    WIN_FULLSCREEN = 2
} WindowMode;

typedef struct{
    int x;
    int y;
    float radius;
    Color color;
} Circle;

typedef enum{
    IDLE,
    OPEND
} State;

bool rect_button(Rectangle rect);
bool circle_button(Circle circle);
void FitText(char *dest, const char *src, int maxWidth, int fontSize);
int clamp_int(int v, int min, int max);
#endif 