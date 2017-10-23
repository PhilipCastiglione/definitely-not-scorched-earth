#ifndef SHARED_H_
#define SHARED_H_ 

#include "splashkit.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BACKGROUND_COLOR COLOR_LIGHT_BLUE

#define TEXT_FONT "menu_font"
#define BIG_FONT_SIZE 36
#define FONT_SIZE 18

#include "types.h"

/**
 * Shared procedure to draw a ui element.
 *
 * @param   the ui element to be drawn
 */
void draw_ui_element(const ui_element &e);

/**
 * Has this ui element been clicked on?
 *
 * @param   the ui element that might have been clicked on
 */
bool clicked_on(const ui_element &e);

/**
 * Has this ui element been clicked outside of?
 *
 * @param   the ui element that might have been clicked outside of
 */
bool clicked_outside(const ui_element &e);

#endif
