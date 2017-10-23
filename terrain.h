#ifndef TERRAIN_H_
#define TERRAIN_H_ 

#include "shared.h"

/**
 * Generates and returns a new terrain object. The terrain structure is stored as
 * an array of integers representing the top (y) of the terain at each point along
 * the x axis.
 *
 * @returns  the generated terrain
 */
terrain new_terrain();

/**
 * Draw the terrain on the window.
 *
 * @param    the terrain to be drawn
 */
void draw_terrain(const terrain &t);

/**
 * Affirms whether or not a point touches the ground.
 *
 * @param    the terrain to check in
 * @param    the point to check for
 * @returns  whether the point touches the ground
 */
bool touches_ground(const terrain &t, const point_2d &point);

/**
 * Destroys terrain around a central point. Terrain closest to the point is
 * more destroyed, terrain farthest is least impacted.
 *
 * @param    the terrain to be damaged
 * @param    the coordinates of the center of the destruction
 * @param    the impact radius to be destroyed to
 */
void destroy_terrain(terrain &t, const point_2d coords, int impact_radius);

#endif
