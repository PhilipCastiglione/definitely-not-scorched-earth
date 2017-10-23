#ifndef PAUSE_SCREEN_H_
#define PAUSE_SCREEN_H_ 

#include "shared.h"

/**
 * Pauses the game.
 *
 * @param   the game to be paused
 */
void pause_game(game &g);

/**
 * Handles input on the pause screen and decides whether anything needs to happen.
 *
 * @param   the game that is paused
 */
void handle_pause_screen_input(game &g);

/**
 * Draw the pause screen on the window, using the provided game elements.
 *
 * @param   the game containing elements to be drawn
 */
void draw_pause_screen(const game &g);

#endif
