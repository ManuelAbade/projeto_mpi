#include "../include/settings.h"

const int options = 4;
const int spacement = INCREMENT*2;
const int options_height = 20;
const int options_width = 80;
char title[] = "SETTINGS";
static DropMenu songs = {16,{"Chickens In The Meadow", "Cuddle Clouds", "Drifting Memories", "Evening Harmony", "Floating Dream", "Forgotten Biomes", "Gentle Breeze", "Golden Gleam", "Gymnopedie No 1","Minuet (Slower)","Minuet" ,"Pineapple Under The Sea", "Polar Lights", "Strange Worlds", "Sunlight Through Leaves", "Tales From The V. W."},
        {"assets/Audio/Chickens_In_The_Meadow.wav","assets/Audio/Cuddle_Clouds.wav","assets/Audio/Drifting_Memories.wav","assets/Audio/Evening_Harmony.wav","assets/Audio/Floating_Dream.wav","assets/Audio/Forgotten_Biomes.wav","assets/Audio/Gentle_Breeze.wav","assets/Audio/Golden_Gleam.wav","assets/Audio/Gymnopedie_No_1.wav","assets/Audio/Minuet_(Slower).wav","assets/Audio/Minuet.wav","assets/Audio/Pineapple_Under_The_Sea.wav","assets/Audio/Polar_Lights.wav","assets/Audio/Strange_Worlds.wav","assets/Audio/Sunlight_Through_Leaves.wav","assets/Audio/Tales_From_The_Vienna_Woods.wav"},"Chickens In The Meado",0,false,0};
static DropMenu fonts = {13,
    {"buddychampion","buddychampion3d","buddychampion3dital","buddychampionbold","buddychampionboldital","buddychampioncond","buddychampioncondital","buddychampionexpand","buddychampionexpandital","buddychampionital","buddychampionleft","buddychampionrotal","buddychampionrotate"},
    {"assets/Fonts/buddychampion.ttf","assets/Fonts/buddychampion3d.ttf","assets/Fonts/buddychampion3dital.ttf","assets/Fonts/buddychampionbold.ttf","assets/Fonts/buddychampionboldital.ttf","assets/Fonts/buddychampioncond.ttf","assets/Fonts/buddychampioncondital.ttf","assets/Fonts/buddychampionexpand.ttf","assets/Fonts/buddychampionexpandital.ttf","assets/Fonts/buddychampionital.ttf","assets/Fonts/buddychampionleft.ttf","assets/Fonts/buddychampionrotal.ttf","assets/Fonts/buddychampionrotate.ttf"},
    "buddychampion",0,false,0
};


bool SetMenu( bool *setting_old_open_state, int window_w, int window_h){
    float ratio_h = (float)window_h/WINDOW_HEIGHT;
    float ratio_w = (float)window_w/WINDOW_WIDTH;
    Settings set_window = {
            SETTINGS_MENU_COLOR,
            "DEFINICOES"
    };
    bool settings_open;
    if(!*setting_old_open_state){
        Rectangle set_but =(Rectangle){
                window_w-60*ratio_w,
                15*ratio_h,
                SETTINGS_MENU_BUTTON_RADIUS*2*ratio_w,
                SETTINGS_MENU_BUTTON_RADIUS*2*ratio_h,
        };
        Circle settings= {
                set_but.x+SETTINGS_MENU_BUTTON_RADIUS*ratio_w,
                set_but.y+SETTINGS_MENU_BUTTON_RADIUS*ratio_h,
                SETTINGS_MENU_BUTTON_RADIUS,
                GRAY
        };    
        Vector2 mouse = GetMousePosition();
        if(CheckCollisionPointCircle(mouse,(Vector2){settings.x,settings.y},settings.radius))
        {
            DrawTexturePro(
                settings_button,
                (Rectangle){0,0,settings_button.width,settings_button.height},
                (Rectangle){set_but.x-1*ratio_w,set_but.y-1*ratio_h,set_but.width+2*ratio_w,set_but.height+2*ratio_h},
                (Vector2){0,0},
                0.0f,WHITE);
          
        }else
        {
            DrawTexturePro(
                settings_button,
                (Rectangle){0,0,settings_button.width,settings_button.height},
                set_but,
                (Vector2){0,0},
                0.0f,
                WHITE);

        }
        settings_open = circle_button(settings);


    }
    
    *setting_old_open_state = settings_open? true:*setting_old_open_state;
    if (*setting_old_open_state)
    {
        
        
        Rectangle window_rect = (Rectangle){
            (window_w/2.0f - (window_w*2/3)/2.0f)*87.0f/86.0f,
            0,
            window_w*2.0f/3.0f,
            window_h
        };
        //DrawRectangleRec(window_rect,YELLOW);
        float close_but_x = window_rect.x + window_rect.width*11.0f/12.0f-SETTINGS_MENU_BUTTON_RADIUS;
        float close_but_y = window_h/(9.0f*ratio_h)-5.0f/4.0f*SETTINGS_MENU_BUTTON_RADIUS*2.0f/3.0f;
        
        Rectangle close_settings = (Rectangle){
            close_but_x,
            close_but_y,
            2*ratio_w*SETTINGS_MENU_BUTTON_RADIUS,
            2*ratio_h*SETTINGS_MENU_BUTTON_RADIUS
        };

        if (banners.id != 0) {
            DrawTexturePro( banners,
                (Rectangle){
                    banners.width/3+25,
                    3,
                    banners.width/6-11,
                    banners.height/7-10,
                },
                window_rect,
                (Vector2){0,0},
                0.0f,
                WHITE
            );
           
        } else {
            DrawTexturePro(background,
                (Rectangle){
                    0,
                    0,
                    background.width,
                    background.height,
                },
                (Rectangle){
                    window_rect.x,
                    window_rect.y + window_h/18,
                    window_rect.width,
                    window_rect.height-window_h/9,
                },
                (Vector2){0,0},
                0.0f,
                WHITE
            );
            DrawText("Texture not loaded!", window_rect.x + 20, window_rect.y + 50, 20, BLACK);
        }
        float title_font_size = 30.0f * ratio_h;
        Vector2 title_size = MeasureTextEx(actual_font, title, title_font_size, ratio_w);
        

        float board_distance = window_rect.y+(window_rect.width+17.5)/5;
        //float board_distance = window_rect.y + window_rect.height / 5.0f;
        DrawTextEx(
            actual_font,
            title,
            (Vector2){window_rect.x+window_rect.width/2-MeasureText(title,30)/2,
            board_distance},
            30*ratio_h,
            1*ratio_w,
            BLACK
        );
        /*
        float settings_rect_init_w = window_rect.x+1.5*board_distance/2;
        float settings_rect_final_w = settings_rect_init_w +window_rect.width*42/43-1.5*board_distance;

        float settings_rect_init_h = (board_distance+(15*ratio_h))*(6.0f/5.0f*ratio_h);
        float settings_rect_final_h = (settings_rect_init_h + window_rect.height-2*board_distance)*(8.0f/9.0f*ratio_h);

        
        float space = (10.0f*ratio_h);
        float space_btw_rect = space*ratio_h;
        float rect_h = (settings_rect_final_h-settings_rect_init_h-3.0f*space_btw_rect)/4.0f;

        float actual_rec_y = settings_rect_init_h-space_btw_rect;

        Rectangle Sets_rect[4];
        
        
        for(int i = 0; i< 4; i++)
                {
                    actual_rec_y += space_btw_rect; 
                    Sets_rect[i] = (Rectangle){
                        settings_rect_init_w,
                        actual_rec_y+rect_h*i,
                        settings_rect_final_w-settings_rect_init_w,
                        rect_h};
                    
                }
        
        */
        
        
        float settings_rect_init_w = window_rect.x+1.5*board_distance/2;
        float settings_rect_final_w = settings_rect_init_w +window_rect.width*42/43-1.5*board_distance;

        float settings_rect_init_h = (board_distance+(15*ratio_h))*(6.0f/5.0f);
        float settings_rect_final_h = (settings_rect_init_h + window_rect.height-2*board_distance)*(8.0f/9.0f);

        
        float space = (10.0f*ratio_h);
        float space_btw_rect = space;
        float rect_h = (settings_rect_final_h-settings_rect_init_h-3.0f*space_btw_rect)/4.0f;

        float actual_rec_y = settings_rect_init_h-space_btw_rect;

        Rectangle Sets_rect[4];
        
        
        for(int i = 0; i< 4; i++)
                {
                    actual_rec_y += space_btw_rect; 
                    Sets_rect[i] = (Rectangle){
                        settings_rect_init_w,
                        actual_rec_y+rect_h*i,
                        settings_rect_final_w-settings_rect_init_w,
                        rect_h};
                    
                }
       
        
        printf("window_h: %d, window_w: %d\n", window_h, window_w);
        printf("Sets_rect[0].y: %f, Sets_rect[3].y: %f\n", Sets_rect[0].y, Sets_rect[3].y);
        printf("Sets_rect[3].height: %f\n", Sets_rect[3].height);

    

        printf("window_rect: x=%f y=%f w=%f h=%f\n", window_rect.x, window_rect.y, window_rect.width, window_rect.height);
        printf("Sets_rect[0]: x=%f y=%f w=%f h=%f\n", Sets_rect[0].x, Sets_rect[0].y, Sets_rect[0].width, Sets_rect[0].height);
        
        Color color = Fade(BLACK,0.2);
        Color color2 = Fade(BLACK,0.3);

        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(Sets_rect[i],color);
            DrawRectangleLinesEx(Sets_rect[i],1*ratio_w,color2);
        }
        
        
        float slides_bar_start = settings_rect_init_w + (settings_rect_final_w - settings_rect_init_w) / 3.0f;
        static bool music_dragging = false;
        static bool dragging = false;

        
        slideBar(Sets_rect[0].x + (Sets_rect[0].width /3.0f),
                Sets_rect[0].y + Sets_rect[0].height / 2.0f - Sets_rect[0].height / 16.0f,
                Sets_rect[0].width /2.0f,
                Sets_rect[0].height /8.0f,
                &music_volume,
                &music_dragging);

        slideBar(Sets_rect[1].x + (Sets_rect[1].width /3.0f),
                Sets_rect[1].y + Sets_rect[1].height /2.0f - Sets_rect[1].height / 16.0f,
                Sets_rect[1].width /2.0f,
                Sets_rect[1].height / 8.0f,
                &volume,
                &dragging);

        float font_size= 14.0f*(float)window_h/WINDOW_HEIGHT;
        DrawTextEx(actual_font,"Music Volume  %", (Vector2){settings_rect_init_w+(settings_rect_final_w-Sets_rect[0].x - (Sets_rect[0].width / 3.0f)-MeasureText("Music Volume %",font_size))/43.0f,Sets_rect[0].y + (rect_h-font_size)/2.0f}, font_size, ratio_h,WHITE);
        DrawTextEx(actual_font,"Global Volume %",  (Vector2){settings_rect_init_w+(settings_rect_final_w-Sets_rect[1].x - (Sets_rect[1].width /3.0f)-MeasureText("Global Volume %",font_size))/43.0f,Sets_rect[1].y + (rect_h-font_size)/2.0f}, font_size, ratio_h,WHITE);

        float dorp_music_menu_text_x = settings_rect_init_w+(settings_rect_final_w-Sets_rect[0].x - (Sets_rect[2].width / 3.0f)-MeasureText("Music Selected",font_size/1.3f))/43.0f;
        float drop_music_menu_width = MeasureText("Music Selected",font_size/1.3f);
        
        float drop_music_width = Sets_rect[2].width/4.0f;
        
        if(dropMenu(&songs,dorp_music_menu_text_x+drop_music_menu_width*6.0/5.0,Sets_rect[2].y+Sets_rect[2].height/8.0f,drop_music_width,Sets_rect[2].height*6.0f/8.0f)){
                    UnloadMusicStream(actual_music);
                    actual_music = LoadMusicStream(songs.options[songs.selected_id]);
                    if (actual_music.stream.buffer != NULL) {
                        PlayMusicStream(actual_music);
                        printf("New Music Loaded: %s\n", songs.selected);
                    } else {
                        printf("Error Loading New Music: %s\n", songs.options[songs.selected_id]);
                    }
        }
        float drop_fonts_menu_width = MeasureText("Font Selected",font_size/1.3f);
        float dorp_fonts_menu_text_x = dorp_music_menu_text_x+drop_music_menu_width*6.0/5.0 + drop_music_width*6.0f/5.0f;
        if (dropMenu(&fonts,dorp_fonts_menu_text_x+drop_fonts_menu_width,Sets_rect[2].y+Sets_rect[2].height/8.0f,drop_music_width,Sets_rect[2].height*6.0f/8.0f))
        {
            UnloadFont(actual_font);
            actual_font = LoadFont(fonts.options[fonts.selected_id]);
            if (actual_font.baseSize != 0) {
                printf("New Font Loaded: %s\n", fonts.selected);
            } else {
                printf("Error Loading New Font: %s\n", fonts.options[fonts.selected_id]);
            }
        }
        
        DrawTextEx(actual_font,"Music Selected", (Vector2){settings_rect_init_w+(settings_rect_final_w-Sets_rect[0].x - (Sets_rect[2].width / 3.0f)-MeasureText("Music Selected",font_size/1.3f))/43.0f,Sets_rect[2].y + (rect_h-font_size)/2.0f}, font_size/1.3f, ratio_h,WHITE);
        DrawTextEx(actual_font,"Font Selected", (Vector2){settings_rect_init_w+(settings_rect_final_w-Sets_rect[0].x - (Sets_rect[2].width / 3.0f)-MeasureText("Music Selected",font_size/1.3f))/43.0f+drop_music_menu_width+drop_music_width+20*ratio_w,Sets_rect[2].y + (rect_h-font_size)/2.0f}, font_size/1.3f, ratio_h,WHITE);


        static char screen_sizes[3][25] = {"Windowed","Windowed B.","FullScreen"};
        
       
        for (int i = 0; i < 3; i++)
        {
            float rect_x = Sets_rect[3].x + i * Sets_rect[3].width / 3.0f;
            float rect_w = Sets_rect[3].width / 3.0f;
            
            DrawRectangleLines(rect_x, Sets_rect[3].y, rect_w, Sets_rect[3].height, Fade(LIGHTGRAY, 0.3f));
            
            Vector2 text_size = MeasureTextEx(actual_font, screen_sizes[i], font_size/1.5f, ratio_w);
            Vector2 text_pos = {
                rect_x + rect_w - text_size.x - 15,
                Sets_rect[3].y + (Sets_rect[3].height - text_size.y) / 2.0f
            };
            float box_size = text_size.y;
            
            Rectangle check_box= (Rectangle){
                text_pos.x - box_size - 10,
                text_pos.y,
                box_size,
                box_size
            };
            
            
            DrawRectangleLines(text_pos.x - box_size - 10, text_pos.y, box_size, box_size, BLACK);
            if (i == wind_mode)
            {
                DrawRectangle(text_pos.x - box_size - 10, text_pos.y, box_size, box_size, BLACK);
            }
            if(rect_button(check_box))
            {
                switch (i)
                {
                case 0:
                    wind_mode = WIN_WINDOWED;
                    break;
                case 1:
                    wind_mode = WIN_BORDERLESS;
                    break;
                case 2:
                    wind_mode = WIN_FULLSCREEN;
                    break;
                default:
                    break;
                }
            }
          
           DrawTextEx(actual_font, screen_sizes[i], text_pos, font_size/1.5f, ratio_w, BLACK);
        }


        Vector2 mouse = GetMousePosition();
        if(CheckCollisionPointRec(mouse,close_settings))
        {
            DrawTexturePro(close_button,(Rectangle){0,0,close_button.width,close_button.height},(Rectangle){close_settings.x-1,close_settings.y-1*ratio_h,close_settings.width+2,close_settings.height+2*ratio_w},(Vector2){0,0},0.0f,WHITE);
          
        }else
        {
            DrawTexturePro(close_button,(Rectangle){0,0,close_button.width,close_button.height},close_settings,(Vector2){0,0},0.0f,WHITE);

        }
        
        if (rect_button(close_settings))
        {
            *setting_old_open_state = false;
        }
        
        return true;
    }
    return false;
}
