#include "../include/slide_bar.h"


void slideBar(int x, int y, int width, int height, int *value, bool *dragging)
{
    Rectangle bar = {x, y, width, height};
    float knob_width = 5;
    float knob_height = height*6;
    // Calcular posição do knob baseada no valor atual
    float knob_x = x + (*value * (width - knob_width) / 100);
    float knob_y = y + height/2.0f -knob_height/2.0f;
    Rectangle knob = {knob_x, knob_y, knob_width, knob_height};
    
    // Desenhar barra
    
    DrawRectangleRounded(bar,100,0,DARKGRAY);
    
    // Desenhar parte preenchida
    float filled_width = width * (*value / 100.0f);
    DrawRectangleRounded((Rectangle){x,y,filled_width, height},100,0,RED);
    
    // Detetar mouse
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, knob);
    
    // Desenhar knob
    if (*dragging) {
        DrawRectangleRounded(knob,100,0, YELLOW);
    } else if (hover) {
        DrawRectangleRounded(knob,100,0, LIGHTGRAY);
    } else {
        DrawRectangleRounded(knob,100,0, GRAY);
    }
    DrawRectangleRoundedLines((Rectangle){knob.x+1,knob.y+1,knob.width-2,knob.height-2},100,0,BLACK);
    
    // Lógica de arrasto - INÍCIO
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hover) {
        *dragging = true;
    }
    
    // Lógica de arrasto - FIM
    if (*dragging && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        *dragging = false;
    }
    
    // Lógica de arrasto - DURANTE
    if (*dragging) {
        // Calcular nova posição X baseada no rato
        float new_knob_x = mouse.x - (knob_width / 2);
        
        // Limitar à barra
        if (new_knob_x < bar.x) new_knob_x = bar.x;
        if (new_knob_x > bar.x + bar.width - knob_width) {
            new_knob_x = bar.x + bar.width - knob_width;
        }
        
        // Calcular novo valor (0-100)
        int new_value = (int)((new_knob_x - bar.x) * 100 / (bar.width - knob_width));
        
        // Limitar valor
        if (new_value < 0) new_value = 0;
        if (new_value > 100) new_value = 100;
        
        // Atualizar valor
        *value = new_value;
    }
    
    // Mostrar valor percentual

    float font_size= 14.0f*(float)window_h/WINDOW_HEIGHT;

    char text[16];
    sprintf(text, "%d%%", *value);
    DrawTextEx(actual_font,text, (Vector2){x + width + 15, y + (height - font_size) / 2}, font_size, font_size/4.0f,WHITE);
}