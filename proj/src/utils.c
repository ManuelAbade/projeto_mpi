#include "../include/utils.h"


bool rect_button(Rectangle rect){
    Vector2 mouse_pos = GetMousePosition();
    bool colision = CheckCollisionPointRec(mouse_pos,rect);
    bool clicked =  IsMouseButtonPressed(MOUSE_LEFT_BUTTON)?colision:false;
    clicked?printf("\nButton Pressed\n"):printf("");
    return clicked;
}


bool circle_button(Circle circle){
    Vector2 mouse_pos = GetMousePosition();
    bool colision = CheckCollisionPointCircle(mouse_pos, (Vector2) {circle.x, circle.y},circle.radius);
    bool clicked =  IsMouseButtonPressed(MOUSE_LEFT_BUTTON)?colision:false;
    clicked?printf("\nButton Pressed\n"):printf("");
    return clicked;
}

void FitText(char *dest, const char *src, int maxWidth, int fontSize)
{
    strcpy(dest, src);

    while (MeasureText(dest, fontSize) > maxWidth)
    {
        int len = strlen(dest);
        if (len <= 3) break;
        dest[len - 1] = '\0';
    }

    if (strcmp(dest, src) != 0)
    {
        strcat(dest, "...");
    }
}
int clamp_int(int v, int min, int max)
{
    return (v < min) ? min : (v > max) ? max : v;
}
