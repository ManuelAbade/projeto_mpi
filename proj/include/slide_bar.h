#ifndef SLIDE_BAR_H
#define SLIDE_BAR_H
#include "main.h"
#include "raylib.h"
#include "utils.h"
#include "stdio.h"
#include "stdbool.h"


extern int window_h;
extern int window_w;
extern Font actual_font;
void slideBar(int x, int y, int width, int height, int *value, bool *dragging);//,Color color_1, Color color_2, Color Color_v)

#endif