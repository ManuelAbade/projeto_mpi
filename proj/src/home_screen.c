#include "../include/home_screen.h"
#define NUMBER_OF_BUTTONS 3


void HomeScreen(ActualScreen *screen,int window_h, int window_w, bool settings_open){

        float ratio_h = (float)window_h/WINDOW_HEIGHT;
        float ratio_w = (float)window_w/WINDOW_WIDTH;
        #define FIRST_BUTTON_W window_w/4.0f + (window_w/2.0f-window_w/4.0f)/2.0f
        #define FIRST_BUTTON_H window_h/4.0f+window_h/6.0f+3*INCREMENT
        #define BUTTON_W (window_w/2.0f-window_w/4.0f)
        #define BUTTON_H window_h/4.0f-window_h/8.0f
        #define SECOND_BUTTON_H (FIRST_BUTTON_H + BUTTON_H + SPACEMENT)
        #define THIRD_BUTTON_H (FIRST_BUTTON_H + BUTTON_H + BUTTON_H + SPACEMENT + SPACEMENT) //FIRST_BUTTON_H + BUTTON_H + BUTTON_H + SPACEMENT + SPACEMEN != FIRST_BUTTON_H + 2*BUTTON_H + 2*SPACEMENT IDK WHY, THIS PC IS CRAZY
        
        

        
        Rectangle buttons[NUMBER_OF_BUTTONS] = {
            (Rectangle){ 
                //Play Solo
                FIRST_BUTTON_W,
                FIRST_BUTTON_H,
                BUTTON_W,
                BUTTON_H
            },
            (Rectangle){
                //Play Duo
                FIRST_BUTTON_W,
                SECOND_BUTTON_H,
                BUTTON_W,
                BUTTON_H    
            },
            (Rectangle){
                //Exit
                FIRST_BUTTON_W,
                THIRD_BUTTON_H,
                BUTTON_W,
                BUTTON_H    
            }
        };
        char text[NUMBER_OF_BUTTONS][10] = {"Play Solo", "Play Duo", "Exit"};
        ActualScreen buttons_screens[NUMBER_OF_BUTTONS] = {DIFICULTY_1,DIFICULTY_2,EXIT};

        static bool waiting[NUMBER_OF_BUTTONS] = {false, false, false};
        static float cooldown_timer[NUMBER_OF_BUTTONS] = {0.0f,0.0f,0.0f};
        
        int player = 1;

        DrawTexturePro(
            background,
            (Rectangle){0,0,background.width,background.height},
            (Rectangle){0,0,GetScreenWidth(),GetScreenHeight()},
            (Vector2){0,0},
            0.0f,
            WHITE
        );

        Rectangle banner = (Rectangle){
            window_w/4.0f,window_h/8.0f,window_w/2.0f,window_h/4.0f
        };
        Vector2 mouse = GetMousePosition();
        if(CheckCollisionPointRec(mouse,banner) && !settings_open)
        {
        DrawTexturePro( banners,
            (Rectangle){
                banners.width/3+25,
                3,
                banners.width/6-10,
                banners.height/7-10,
            },
            (Rectangle){
                banner.x-(2.5f)*ratio_w,
                banner.y-(2.5f)*ratio_h,
                banner.width+(5.0f)*ratio_w,
                banner.height+(5.0f)*ratio_h,
            },
            (Vector2){0,0},
            0.0f,
            WHITE
        );
        DrawTextEx(
            actual_font,
            GAME_NAME,
            (Vector2){banner.x+(banner.width-MeasureTextEx(actual_font,GAME_NAME,35.0f*ratio_h,ratio_w).x)/2.0f,
            banner.y+(banner.height-35.0f*ratio_h)/2.0f},
            35*ratio_h,
            ratio_w,
            BLACK
        );
        }else
        {
            DrawTexturePro( banners,
                (Rectangle){
                    banners.width/3+25,
                    3,
                    banners.width/6-10,
                    banners.height/7-10,
                },
                banner,
                (Vector2){0,0},
                0.0f,
                WHITE
            );
            DrawTextEx(
                actual_font,
                GAME_NAME,
                (Vector2){
                banner.x+(banner.width-MeasureTextEx(actual_font,GAME_NAME,30.0f*ratio_h,ratio_w).x)/2.0f,
                banner.y+(banner.height-30*ratio_h)/2.0f},
                30*ratio_h,
                ratio_h,
                BLACK
            );
        }
        
        for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
        {
            bool is_pressed = rect_button(buttons[i]) && !waiting[i] && !settings_open;
            
            if (is_pressed && !waiting[i])
            {
                DrawTexturePro(
                    button_pressed,
                    (Rectangle){0,0,button.width,button.height},
                    buttons[i],
                    (Vector2){0,0},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                Vector2 mouse = GetMousePosition();
                if(CheckCollisionPointRec(mouse,buttons[i]) && !settings_open){
                    // DrawTexturePro(
                    //     button,
                    //     (Rectangle){0,0,button.width,button.height},
                    //     (Rectangle){buttons[i].x-(2.5*ratio_w),buttons[i].y-(2.5*ratio_h),buttons[i].width+(5.0*ratio_w),buttons[i].height+(5.0*ratio_h)},
                    //     (Vector2){0,0},
                    //     0.0f,
                    //     WHITE
                    // );
                   
                    // DrawTextEx(
                    //     actual_font,
                    //     text[i],
                    //     (Vector2){buttons[i].x+(buttons[i].width-MeasureTextEx(actual_font,text[i],buttons[i].height/(2*ratio_h)+4*ratio_h,ratio_w*1.2).x)/2.0f,
                    //     buttons[i].y+buttons[i].height/(4*ratio_h)-5*ratio_h},
                    //     buttons[i].height/(2*ratio_h)+4*ratio_h,
                    //     ratio_w*1.2,
                    //     BLACK
                    // );
                   float scale = 1.0f + (5.0f * ratio_h / buttons[i].height); // fator de expansão

DrawTexturePro(
    button,
    (Rectangle){0,0,button.width,button.height},
    (Rectangle){buttons[i].x - (2.5f * ratio_w), 
                buttons[i].y - (2.5f * ratio_h), 
                buttons[i].width + (5.0f * ratio_w), 
                buttons[i].height + (5.0f * ratio_h)},
    (Vector2){0,0},
    0.0f,
    WHITE
);

float font_size = (buttons[i].height / 2.0f) * scale;
Vector2 text_size = MeasureTextEx(actual_font, text[i], font_size, ratio_w);
Vector2 text_pos = {
    buttons[i].x - (2.5f * ratio_w) + (buttons[i].width + (5.0f * ratio_w) - text_size.x) / 2.0f,
    buttons[i].y - (2.5f * ratio_h) + (buttons[i].height + (5.0f * ratio_h) - text_size.y) / 3.0f
};
DrawTextEx(actual_font, text[i], text_pos, font_size, ratio_w, BLACK);
                }else
                {
                        DrawTexturePro(
                            button,
                            (Rectangle){0,0,button.width,button.height},
                            buttons[i],
                            (Vector2){0,0},
                            0.0f,
                            WHITE
                        );
                        DrawTextEx(
                            actual_font,
                            text[i],
                            (Vector2){buttons[i].x+(buttons[i].width-MeasureTextEx(actual_font,text[i],buttons[i].height/2.0f,ratio_w).x)/2.0f,
                            buttons[i].y+buttons[i].height/4.0f-5*ratio_h},
                            buttons[i].height/2.0f,
                            ratio_w,
                            BLACK
                        );
                }
                
            }   
            
            if (!settings_open && !waiting[i] && is_pressed)
            {
                waiting[i] = true;
                cooldown_timer[i] = 0.5f;
                printf("Button %d pressed: %s\n", i, text[i]);
                fflush(stdout);
            }
        }
        
       
        for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
        {
            if (waiting[i])
            {
               
                cooldown_timer[i] -= GetFrameTime();
                
         
                DrawText("Loading...", window_w / 2 - 40, window_h / 2 + 100, 20, WHITE);
                
                if (cooldown_timer[i] <= 0.0f)
                {
                    printf("Changing to screen: %d\n", buttons_screens[i]);
                    fflush(stdout);
                    *screen = buttons_screens[i];
                    waiting[i] = false;
                    break;  
                }
            }
        }
        
}