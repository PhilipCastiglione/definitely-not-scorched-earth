#ifndef WON_SCREEN_H_
#define WON_SCREEN_H_ 

#include "shared.h"

/**
 * Create and return a new won ui object containing won menu related ui elements.
 *
 * @param    the game for which to draw a new menu
 * @returns  the new won_screen
 */
won_screen new_won_screen(const game &g);

/**
 * Has the game been won? This will be true if the active tank is teh only tank
 * remaining alive.
 *
 * @param   the game that might have been won
 */
bool game_won(const game &g);

/**
 * Make change to game state to reflect that it has been won.
 *
 * @param   the game that has been won
 */
void win_game(game &g);

/**
 * Handles input on the won screen and decides whether anything needs to happen.
 *
 * @param   the game on the won screen
 */
void handle_won_screen_input(game &g);

/**
 * Draw the won screen on the window, using the provided game elements.
 *
 * @param   the game containing elements to be drawn
 */
void draw_won_screen(const game &g);

#endif
