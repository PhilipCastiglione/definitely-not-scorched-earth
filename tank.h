#ifndef TANK_H_
#define TANK_H_ 

#include "shared.h"

// constants
#define TANK_MAX_ANGLE 175
#define TANK_MIN_ANGLE 5
#define TANK_MAX_POWER 120
#define TANK_MIN_POWER 20

/**
 * Create and return a new tank with a known integer id.
 *
 * @param    the id
 * @returns  the new tank
 */
tank new_tank(int id);

/**
 * Initialize the tank, ready for a game.
 *
 * @param   the tank to initialize
 */
void initialize_tank(tank &t);

/**
 * Sets the tank name to a generated AI name.
 *
 * @param   the tank to generate a name for
 */
void generate_name(tank &t);

/**
 * Return the center point of a tank.
 *
 * @param    the tank to find the center of
 * @returns  a point_2d representing the tank center
 */
point_2d tank_center(const tank &t);

/**
 * Draw the tank on the window.
 *
 * @param    the tank to be drawn
 */
void draw_tank(tank &t);

/**
 * Increase the tank power.
 *
 * @param    the tank whose power should increase
 */
void power_up(tank &t);

/**
 * Decrease the tank power.
 *
 * @param    the tank whose power should decrease
 */
void power_down(tank &t);

/**
 * Increase the tank angle.
 *
 * @param    the tank whose angle should increase
 */
void angle_up(tank &t);

/**
 * Decrease the tank angle.
 *
 * @param    the tank whose angle should decrease
 */
void angle_down(tank &t);

/**
 * Handle input that modifies the tank.
 * 
 * @param    the tank related to the input
 */
void handle_tank_input(tank &t, terrain &ground);

/**
 * Shoot gun!
 * 
 * @param    the tank doing the shooting
 */
void shoot(tank &t);

/**
 * The tank falls towards the ground, simulating gravity. If the tank
 * is just partly touching the ground but has not finished falling then
 * the tank's base angle will adjust til it is resting on the ground.
 *
 * @param    the tank that is falling
 * @param    the ground that it is falling towards
 */
void fall(tank &t, const terrain &ground);

/**
 * Damages a tank from an explosion point. The closer the explosion is
 * to the center of the tank, the greater the damage.
 *
 * @param    the tank to be damaged
 * @param    the coordinates of the center of the explosion
 * @param    the impact radius of the explosion
 */
void damage_tank(tank &t, const point_2d coords, int impact_radius);

/**
 * Is the tank still falling?
 *
 * @param   the tank
 * @param   the ground
 * @returns whether the tank is falling or stable
 */
bool falling(const tank &t, const terrain &ground);

#endif
