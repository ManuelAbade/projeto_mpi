#include "../include/dificulty_1.h"



void Dificulty1(ActualScreen *screen, int window_h, int window_w, bool settings_open){
    DrawTexturePro(
            background,
            (Rectangle){0,0,background.width,background.height},
            (Rectangle){0,0,GetScreenWidth(),GetScreenHeight()},
            (Vector2){0,0},
            0.0f,
            WHITE
        );

        Rectangle banner_rect = (Rectangle){
                84,
                22*8,
                25,
                45//42
        };
        Rectangle card = (Rectangle)
        {
            window_w/2,
            window_h/2,
            window_w/8,
            window_h/3
        };
    DrawRectangleRec(card,YELLOW);
    DrawTexturePro(banners,banner_rect,card,(Vector2){0,0},0.0f,WHITE);
}