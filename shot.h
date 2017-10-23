#ifndef SHOT_H_
#define SHOT_H_ 

#include "shared.h"

/**
 * Generate and return a new shot, shot by a given tank, based on it's attrs.
 *
 * @param    the tank doing the shooting.
 * @returns  the new shot
 */
shot new_shot(const tank &t);

/**
 * Move the shot to the next set of coordinates in it's trajectory.
 *
 * @param    the shot to move
 * @param    the strength of the wind; negative is left and positive is right
 */
void move_shot(shot &s, double wind);

/**
 * Draw the shot on the window. If the shot is above the top of the window,
 * it tracks along the top of the screen.
 *
 * @param    the shot to be drawn
 */
void draw_shot(const shot &s);

/**
 * A shot has hit the ground, and an explosion should occur. The terrain in
 * the radius of the shot will be damaged and any tanks hit will be destroyed.
 *
 * @param    the shot to explode
 * @param    all tanks
 * @param    the terrain
 */
void explode(const shot &s, vector<tank> &tanks, terrain &t);

#endif
