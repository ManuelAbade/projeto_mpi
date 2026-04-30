#include "../include/dificulty_1.h"


void Dificulty2(ActualScreen *screen, int window_h, int window_w, bool settings_open){
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
                45
        };
    Rectangle card = (Rectangle)
        {
            window_w/6,
            window_h/4,
            window_w/12,
            window_h/4
        };

    // for (int i = 0; i < 3; i++)
    // {
    //     DrawTexturePro(banners,banner_rect,(Rectangle){card.x + i*window_w/4,card.y,card.width,card.height},(Vector2){0,0},0.0f,WHITE);
    //     if(rect_button((Rectangle){card.x + i*window_w/4,card.y,card.width,card.height}))
    //     {
    //         dificulty = i+1;
    //         printf("DIFICULTY: %d", dificulty);
    //     }
    // }

    // for (int i = 0; i < 3; i++)
    // {
    //     DrawTexturePro(banners,banner_rect,(Rectangle){card.x + i*window_w/4,card.y+window_h/3,card.width,card.height},(Vector2){0,0},0.0f,WHITE);
    //     if(rect_button((Rectangle){card.x + i*window_w/4,card.y+window_h/3,card.width,card.height}))
    //     {
    //         size = 4*(i+1); 
    //         printf("SIZE: %d",size);
    //     }
//     }
//     Color color= Fade(BLACK,0.2);
//     if (dificulty != 0 )DrawRectangleRec((Rectangle){card.x + (dificulty-1)*window_w/4,card.y,card.width,card.height},color);
//     if(size !=0)DrawRectangleRec((Rectangle){card.x + (size/4-1)*window_w/4,card.y+window_h/3,card.width,card.height},color);
    
    

}