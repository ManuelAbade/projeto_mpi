#include "../include/drop_menu.h"

bool dropMenu(DropMenu *menu,int x, int y, int width, int height)
{   
    int max;
    int remaining = menu->len - menu->actual_first;
    if (remaining > MAX_TAB_WIDGETS)
        max = MAX_TAB_WIDGETS - 1;
    else
        max = remaining - 1;

    if (max < 0) max = 0;

    Rectangle bar = (Rectangle)
    {
        x,
        y,
        width,
        height
    };
    Rectangle select = (Rectangle)
    {
        x,
        y,
        height,
        height
    };
    Rectangle option = (Rectangle)
    {
        x+height,
        y,
        width-height,
        height
    };
    
    static Rectangle tabs_open[MAX_TAB_WIDGETS];
    Vector2 mouse = GetMousePosition();
    if(!menu->is_tab_open)
    {
        Color color = Fade(LIGHTGRAY,0.2);
        DrawRectangleRec(bar,color);
        char short_text[50];
        FitText(short_text, menu->selected, width - height - 10, height/3);
        DrawText(short_text, bar.x + height + 5, bar.y + height/4, height/3, BLACK);
    }

    if(CheckCollisionPointRec(mouse,select))
    {
        Color color = Fade(DARKGRAY,0.2);
        DrawRectangleRec(select,color);
        DrawTexturePro(options_arrow,
            (Rectangle){0,0,options_arrow.width,options_arrow.height},
            select,
            (Vector2){0,0},
            0,
            BLACK
         );
    }else
    {
        Color color = Fade(WHITE,0.2);
        DrawRectangleRec(select,color);
        DrawTexturePro(options_arrow,
            (Rectangle){0,0,options_arrow.width,options_arrow.height},
            select,
            (Vector2){0,0},
            0,
            BLACK
         );
    }

    //printf("\nTab: %d\n",is_tab_open);
    if(rect_button(select) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        //printf("Opening...\n");
        menu->is_tab_open = !menu->is_tab_open;
    }

    for (int i = 0; i <= max; i++)
    {
        int real_i = menu->actual_first + i;
        if (real_i >= menu->len) break;
        tabs_open[i] = (Rectangle){
            option.x,
            option.y + i * option.height,
            option.width,
            option.height
        };

    }

    return menu->is_tab_open?OpenTab(menu,tabs_open,height,width,max):false;
}


bool OpenTab(DropMenu *menu,Rectangle tabs_open[], int height, int width, int max)
{
    for (int i = menu->actual_first; i <= menu->actual_first + max && i < menu->len; i++)
            {
                int idx = i - menu->actual_first;
               
                DrawTabs(menu,tabs_open,idx, i, height,BLUE,DARKGRAY,GRAY);

                if(React(menu,tabs_open,idx,i)) return true;
            }
        float scroll = GetMouseWheelMove();

        int max_start = menu->len - MAX_TAB_WIDGETS;
        if (max_start < 0) max_start = 0;

        menu->actual_first = clamp_int(menu->actual_first - (int)scroll, 0, max_start);

        return false;
}

bool React(DropMenu *menu,Rectangle tabs_open[], int idx,int i)
{
    if(rect_button(tabs_open[idx]))
        {
                    menu->selected_id=i;
                    strcpy(menu->selected, menu->options_names[i]);
                    menu->is_tab_open =false;
                    printf("ID real: %d, Nome: %s\n", menu->selected_id, menu->selected);
                    return true;
        }
    return false;
}

Color DrawTabsColor(DropMenu *menu,Rectangle tabs_open[],int idx,int i,Color color1,Color color2, Color color3)
{
    Vector2 mouse = GetMousePosition();
    bool selected = (i == menu->selected_id);
    bool hover = CheckCollisionPointRec(mouse, tabs_open[idx]);
    if (selected) return color1;
    else if(hover) return color2;
    else return color3;
}

void DrawTabs(DropMenu *menu,Rectangle tabs_open[],int idx, int i, int height, Color color1,Color color2, Color color3)
{
        Color color = Fade(DrawTabsColor(menu,tabs_open,idx,i,color1, color2,  color3),0.2);
        DrawRectangleRec(tabs_open[idx], color);      
        char short_text[50];
        FitText(short_text, menu->options_names[i], tabs_open[idx].width - 10, height/3);
        DrawText(short_text, tabs_open[idx].x + 5, tabs_open[idx].y + height/4, height/3, BLACK);
    
    DrawRectangleLinesEx(tabs_open[idx], 1, BLACK);
}
