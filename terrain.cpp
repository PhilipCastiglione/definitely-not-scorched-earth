#include "terrain.h"

#include <algorithm> // max
#include <cstdlib>   // abs
#include <cmath>     // pow

// constants
#define TERRAIN_DEPTH_RANGE 300
#define TERRAIN_INFLECTION_INTERVAL_RANGE 105
#define TERRAIN_INFLECTION_INTERVAL_FLOOR 55

// Forward declarations
void generate_terrain_structure(terrain &t);
void generate_new_function(point_2d &start_coords, point_2d &end_coords, double &slope);
void draw_terrain_bitmap(terrain &t);

terrain new_terrain()
{
    terrain t;

    t.bmp = create_bitmap("terrain", WINDOW_WIDTH, WINDOW_HEIGHT);

    generate_terrain_structure(t);

    return t;
}

/**
 * Generate the structure for a terrain. The structure is composed of a series of
 * hills and valleys of varying height/depth at irregular intervals. Stucture is
 * generated using a series of linear functions with random slope. The values are
 * stored in the tops attribute of the terrain.
 *
 * This function draws the structure onto the terrain bmp as it is generated. This
 * is done as an optimisation, so it doesn't need to be regenerated or redrawn
 * after the first time.
 */
void generate_terrain_structure(terrain &t)
{
    point_2d start_coords, end_coords;
    double slope;

    // the initial end coords will become the starting coordinates for the first function
    end_coords.x = 0;
    end_coords.y = WINDOW_HEIGHT / 3 + rnd(TERRAIN_DEPTH_RANGE + 1);

    generate_new_function(start_coords, end_coords, slope);

    for ( int x = 0; x < WINDOW_WIDTH; x++ )
    {
        // y = m x + c (calculate the current value of y for the current x)
        t.tops[x] = slope * (x - start_coords.x) + start_coords.y;

        // if we have reached the end of the current function, generate a new one
        if ( x >= end_coords.x )
        {
            generate_new_function(start_coords, end_coords, slope);
        }
    }

    draw_terrain_bitmap(t);
}

/**
 * Generates a linear function to generate terrain and sets the starting coordinates,
 * ending coordinates and slope.
 */
void generate_new_function(point_2d &start_coords, point_2d &end_coords, double &slope)
{
    // the new start coordinates are the old end coordinates
    start_coords.x = end_coords.x;
    start_coords.y = end_coords.y;
    end_coords.x += rnd(TERRAIN_INFLECTION_INTERVAL_RANGE + 1) + TERRAIN_INFLECTION_INTERVAL_FLOOR;
    end_coords.y = WINDOW_HEIGHT / 3 + rnd(TERRAIN_DEPTH_RANGE + 1);
    slope = (end_coords.y - start_coords.y) / (end_coords.x - start_coords.x);
}

/**
 * Draws the terrain structure onto its bitmap
 */
void draw_terrain_bitmap(terrain &t)
{
    clear_bitmap(t.bmp, BACKGROUND_COLOR);
    for ( int x = 0; x < WINDOW_WIDTH; x++ )
    {
        // draw the whole column of pixels from the current top to the bottom of the terrain bmp
        draw_line_on_bitmap(t.bmp, COLOR_GREEN, x, t.tops[x], x, WINDOW_HEIGHT);
    }
}

void draw_terrain(const terrain &t)
{
    draw_bitmap(t.bmp, 0, 0);
}

bool touches_ground(const terrain &t, const point_2d &point)
{
    int bounded_x = int(point.x);
    bounded_x = max(bounded_x, 0);
    bounded_x = min(bounded_x, WINDOW_WIDTH - 1);
    return t.tops[bounded_x] < int(point.y);
}

void destroy_terrain(terrain &t, const point_2d coords, int impact_radius)
{
    int terrain_x, impact, new_x, explosion_floor, terrain_floor;
    for ( int i = -impact_radius; i < impact_radius; i++ )
    {
        terrain_x = coords.x + i;
        if ( terrain_x >= 0 and terrain_x < WINDOW_WIDTH )
        {
            impact = (int)round(sqrt(pow(impact_radius, 2) - pow(abs(i), 2)) * 1.3);
            explosion_floor = (int)round(coords.y + impact);
            terrain_floor = t.tops[terrain_x] + impact;
            new_x = max(t.tops[terrain_x], min(explosion_floor, terrain_floor));
            t.tops[terrain_x] = min(new_x, WINDOW_HEIGHT);
        }
    }
    draw_terrain_bitmap(t);
}
