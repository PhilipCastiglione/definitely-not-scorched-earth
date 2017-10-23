#ifndef GAME_H_
#define GAME_H_ 

#include "shared.h"

#define MAX_PLAYERS 4
#define MIN_PLAYER_GAP 60
#define PLAYER_NAME_LENGTH 8

/**
 * Create and return a new game with IN_MENU state.
 *
 * @returns  the new game
 */
game new_game();

/**
 * Initialize the game, ready for playing.
 *
 * @param   the game to initialize
 */
void initialize_game(game &g);

/**
 * Runs the game loop, which, while the game isn't being quit, switches on game
 * state and handles input and draws the game to match the context.
 *
 * @param   the game to run
 */
void game_loop(game &g);

#endif
