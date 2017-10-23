#ifndef MENU_SCREEN_H_
#define MENU_SCREEN_H_ 

#include "shared.h"

// shared constants
// structure
#define OUTER_RECT_X WINDOW_WIDTH / 8
#define OUTER_RECT_Y WINDOW_HEIGHT / 8
#define OUTER_RECT_WIDTH WINDOW_WIDTH * 3 / 4
#define OUTER_RECT_HEIGHT WINDOW_HEIGHT * 3 / 4

// section x values
#define TEXT_X OUTER_RECT_X + 20
#define CONTROLS_X TEXT_X + 20
#define LESS_TANKS_X TEXT_X
#define NUM_TANKS_X LESS_TANKS_X + 30
#define MORE_TANKS_X NUM_TANKS_X + 30
#define PLAY_BUTTON_X OUTER_RECT_X + OUTER_RECT_WIDTH / 2 - PLAY_BUTTON_WIDTH / 2

// section y values
#define TITLE_Y OUTER_RECT_Y + 14
#define INTRO1_Y TITLE_Y + BIG_FONT_SIZE + 34
#define INTRO2_Y INTRO1_Y + FONT_SIZE + 12
#define INTRO3_Y INTRO2_Y + FONT_SIZE + 12
#define TANK_QTY_HEADER_Y INTRO3_Y + FONT_SIZE + 32
#define TANK_QTY_Y TANK_QTY_HEADER_Y + FONT_SIZE + 22
#define TANKS_Y TANK_QTY_Y + FONT_SIZE + 47
#define CONTROLS_Y OUTER_RECT_Y + OUTER_RECT_HEIGHT - FONT_SIZE - 10
#define PLAY_BUTTON_Y CONTROLS_Y - 20 - BIG_FONT_SIZE

// element sizes
#define PLAY_BUTTON_WIDTH 100
#define NAME_BOX_WIDTH 113
#define NAME_BOX_HEIGHT BIG_FONT_SIZE - 8

/**
 * Create and return a new menu ui object containing menu related ui elements.
 *
 * @param    the game for which to draw a new menu
 * @returns  the new menu_screen
 */
menu_screen new_menu_screen(const game &g);

/**
 * Manage the menu music loop.
 */
void play_menu_screen_music();

/**
 * Draw the menu screen on the window, using the provided game elements.
 *
 * @param   the game containing elements to be drawn
 */
void draw_menu_screen(game &g);

/**
 * Handles input on the menu screen and decides whether anything needs to happen.
 *
 * @param   the game containing the menu screen
 */
void handle_menu_screen_input(game &g);

#endif
