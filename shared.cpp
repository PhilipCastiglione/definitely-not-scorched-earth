#include "shared.h"

void draw_ui_element(const ui_element &e)
{
    draw_bitmap(e.bmp, e.coords.x, e.coords.y);
}

bool clicked_on(const ui_element &e)
{
    return mouse_clicked(LEFT_BUTTON) and
        bitmap_point_collision(e.bmp, e.coords, mouse_position());
}

bool clicked_outside(const ui_element &e)
{
    return mouse_clicked(LEFT_BUTTON) and
        not bitmap_point_collision(e.bmp, e.coords, mouse_position());
}
