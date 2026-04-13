#include "../include/main.h"


Texture2D button_pressed;
Texture2D button;
Texture2D background;
Texture2D banners;
Texture2D settings_button; 
Texture2D close_button; 
Texture2D options_arrow; 

WindowMode wind_mode = WIN_WINDOWED;

LoadTextures 
but_pressed = {"assets/utils/button_pressed.png", &button_pressed},
but = {"assets/utils/button.png", &button},
bckg = {"assets/GUI/background.png", &background},
set_bt = {"assets/utils/settings2.png", &settings_button},
opt_arr = {"assets/utils/download_but.png", &options_arrow},
cls_bt = {"assets/utils/close_button.png", &close_button},
ban = {"assets/utils/banners.png", &banners};


LoadTextures *tex_to_load[] = {&but_pressed,&but,&bckg,&set_bt,&cls_bt,&ban,&opt_arr,NULL};

int volume = 100;
int music_volume = 100;
Font actual_font;
Music actual_music;
int window_w = WINDOW_WIDTH;
int window_h = WINDOW_HEIGHT;


int main(void)
{  
    #ifdef DEV
        init_console();
    #endif

    printf("1 - Init console OK\n");
    fflush(stdout);
    
    printf("2 - Init Window...\n");
    fflush(stdout);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Jogo da Memória");
    printf("3 - Init Window Ok\n");
    fflush(stdout);
    
    SetTargetFPS(30);
    printf("4 - FPS Config\n");
    fflush(stdout);
    
    printf("5 - Loading textures...\n");
    fflush(stdout);
    TextureLoad(tex_to_load);
    printf("6 - Tectures Loaded\n");
    fflush(stdout);

    printf("=============GAME START=============\n");
    InitAudioDevice();
    actual_music = LoadMusicStream("assets/Audio/Chickens_In_The_Meadow.wav");
    actual_font = LoadFont("assets/Fonts/buddychampion.ttf");

    // Verifica se carregou
    if (actual_music.stream.buffer != NULL) {
        PlayMusicStream(actual_music);
        printf("Playing nusic!\n");
    } else {
        printf("Load music faild\n");
    }
    
    ActualScreen screen = DIFICULTY_1;
    static int last_wind_mode = 0;

    static int original_w = WINDOW_WIDTH;
    static int original_h = WINDOW_HEIGHT;
    static int original_x = 0;
    static int original_y = 0;
    static int current_w, current_h;
    bool exit_button_can_be_use = false;
    bool settings_open= false;
    bool stop= WindowShouldClose();
    PlayMusicStream(actual_music);
    original_x = GetWindowPosition().x;
    original_y = GetWindowPosition().y;

    while (!stop)
    {  
        UpdateMusicStream(actual_music);
        SetMusicVolume(actual_music, music_volume<=volume?(float)music_volume/100:(float)volume/100);
        
        if (WindowShouldClose()) {
            stop = true;
            break;
        }
        window_w = GetScreenWidth();
        window_h = GetScreenHeight();

        BeginDrawing();
        ClearBackground(BLACK);
    if (wind_mode != last_wind_mode) {
        current_w = GetScreenWidth();
        current_h = GetScreenHeight();
        
        switch (wind_mode) {
            case WIN_WINDOWED:
                if (IsWindowFullscreen()) {
                    ToggleFullscreen();
                }
                if (last_wind_mode == 1) {
                    ToggleBorderlessWindowed();
                }

                SetWindowSize(original_w, original_h);
                SetWindowPosition(original_x, original_y);  
                window_w = original_w;
                window_h = original_h;
                last_wind_mode = 0;
                break;
                
            case WIN_BORDERLESS:
                if (IsWindowFullscreen()) {
                    ToggleFullscreen();
                }
                
                Vector2 pos = GetWindowPosition();
                original_x = pos.x;
                original_y = pos.y;
                
                SetWindowPosition(0, 0);
                SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
                ToggleBorderlessWindowed();
                window_w = GetMonitorWidth(0);
                window_h = GetMonitorHeight(0);
                last_wind_mode = 1;
                break;
                
            case WIN_FULLSCREEN:
                if (!IsWindowFullscreen()) {
                    if (last_wind_mode == 0) {
                        original_w = current_w;
                        original_h = current_h;
                        Vector2 pos = GetWindowPosition();
                        original_x = pos.x;
                        original_y = pos.y;
                    }
                    
                    int monitor = GetCurrentMonitor();
                    int mon_w = GetMonitorWidth(monitor);
                    int mon_h = GetMonitorHeight(monitor);
                    
                    SetWindowSize(mon_w, mon_h);
                    ToggleFullscreen();
                    window_w = mon_w;
                    window_h = mon_h;
                }
                //last_wind_mode = 2;
                break;
        }
    }
        
        

        switch (screen)
        {
            case HOME_SCREEN:
                exit_button_can_be_use = true;
                HomeScreen(&screen, window_h,  window_w, settings_open);
            break;
            case DIFICULTY_1:
                exit_button_can_be_use = false;
                Dificulty1(&screen, window_h,  window_w, settings_open);
            case DIFICULTY_2:
                exit_button_can_be_use = false;
                //Dificulty2(&screen, window_h,  window_w, settings_open);
            case EXIT:
                if(exit_button_can_be_use)
                {
                stop = true;
                printf("Exit button pressed");}
                break;
        }
        
        SetMenu(&settings_open, window_w, window_h);
        
        EndDrawing();
}
    
    CloseAudioDevice();
    printf("Unloading textures...\n");
    TexturesUnload(tex_to_load);
    UnloadMusicStream(actual_music);
    UnloadFont(actual_font);
    CloseWindow();
    printf("Press enter to continue...\n");
    fflush(stdout);
    getchar();


    
    #ifdef DEV
        close_console();
    #endif
    return 0;
}
