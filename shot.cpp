#include "shot.h"
#include "tank.h"
#include "terrain.h"

#include <cmath>     // geometry
#include <algorithm> // max
#include <chrono>    // sleep
#include <thread>    // milliseconds

// constants
#define SHOT_RADIUS 3
#define EXPLOSION_MAX_RADIUS 15
#define GRAVITATIONAL_ACCELERATION 9.81
#define SHOT_SPEED 4.0

// forward declarations
void move_shot_along_trajectory(shot &s);
void move_shot_vertically(shot &s);
void render_explosion(const shot &s);
void damage_tanks(vector<tank> &tanks, const point_2d coords, int impact_radius);

shot new_shot(const tank &t)
{
    shot s;

    s.initial_x = t.turret_end.x;
    s.initial_y = t.turret_end.y;
    s.clr = t.clr;
    s.initial_angle = t.turret_angle;
    s.power = t.power;
    s.distance = s.initial_x;
    s.coords.x = s.initial_x;
    s.coords.y = s.initial_y;

    return s;
}

void move_shot(shot &s, const double wind)
{
    if ( s.initial_angle != 90 )
    {
        move_shot_along_trajectory(s);
    }
    else
    {
        move_shot_vertically(s);
    }
    s.coords.x += wind;
}

/**
 * Trajectory of a projectile (with y axis inverted to draw):
 * https://en.wikipedia.org/wiki/Trajectory_of_a_projectile
 */
void move_shot_along_trajectory(shot &s)
{
    // move x based on a shot speed adjusted for angle and recalculate y
    s.distance += cosine(s.initial_angle) * SHOT_SPEED;
    s.coords.x += cosine(s.initial_angle) * SHOT_SPEED;

    int theta = s.initial_angle;
    double g = GRAVITATIONAL_ACCELERATION;
    double v = s.power;
    double y0 = s.initial_y;
    double d = s.distance - s.initial_x;

    // note that we increase height by subtracting y and visa versa
    s.coords.y = y0 - d * tangent(theta) + (g * d * d) / (2 * pow(v * cosine(theta), 2));
}

/**
 * If the angle is straight up, we calculate raw velocity and subtract
 * shot speed as the acceleration factor.
 */
void move_shot_vertically(shot &s)
{
    double previous_velocity = s.power;
    s.power -= 2 * SHOT_SPEED / GRAVITATIONAL_ACCELERATION;
    s.coords.y += (pow(s.power, 2) - pow(previous_velocity, 2)) / (2 * GRAVITATIONAL_ACCELERATION);
}

void draw_shot(const shot &s)
{
    fill_circle(s.clr, s.coords.x, max(0.0, s.coords.y), SHOT_RADIUS);
}

void explode(const shot &s, vector<tank> &tanks, terrain &t)
{
    render_explosion(s);
    play_sound_effect("explode");
    destroy_terrain(t, s.coords, EXPLOSION_MAX_RADIUS);
    damage_tanks(tanks, s.coords, EXPLOSION_MAX_RADIUS);
}

/**
 * Blocks execution and renders a sweet explosion!
 */
void render_explosion(const shot &s)
{
    for ( int i = 0; i < EXPLOSION_MAX_RADIUS; i++ )
    {
        fill_circle(COLOR_BLACK, s.coords.x, s.coords.y, i);
        refresh_screen(60);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        fill_circle(COLOR_YELLOW, s.coords.x, s.coords.y, i);
        refresh_screen(60);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        fill_circle(COLOR_ORANGE, s.coords.x, s.coords.y, i);
        refresh_screen(60);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

/**
 * Damage tanks as required based on the location of the explosion.
 */
void damage_tanks(vector<tank> &tanks, const point_2d coords, int impact_radius)
{
    for ( int i = 0; i < tanks.size(); i++ )
    {
        damage_tank(tanks[i], coords, impact_radius);
    }
}
