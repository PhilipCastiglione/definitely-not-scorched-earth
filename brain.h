#ifndef BRAIN_H_
#define BRAIN_H_ 

#include "shared.h"

/**
 * Create and return a new brain for a tank's ai to use.
 *
 * @returns  the new brain
 */
brain new_brain();

/**
 * The active tank thinks about things for a little while.
 *
 * @param   the game containing the active tank
 */
void think(game &g);

/**
 * The active tank acts on its decision! No procrastination here.
 *
 * @param   the game containing the active tank
 */
void act(game &g);

#endif
