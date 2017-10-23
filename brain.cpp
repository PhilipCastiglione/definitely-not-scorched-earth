#include "brain.h"
#include "tank.h"

#include <cstdlib> // abs int
#include <cmath>   // abs double, geometry
#include <chrono>  // sleep
#include <thread>  // milliseconds

#define LONG_RANGE 200
#define MEDIUM_RANGE 100
#define ANGLE_THRESHOLD 120

// forward declarations
void pick_target(game &g);
void set_target_angle(game &g);
void set_target_power(game &g);
void adjust_angle(tank &t);
void adjust_power(tank &t);
void adjust_for_wind(double &d, double wind);
void adjust_for_angle(double &power, int angle);
void adjust_aiming(game &g);
void bound_targets(tank &active_tank);
int distance_x(const tank *t1, const tank &t2);
bool no_or_dead_target(const tank *target);
double aim_adjustment(const tank &active_tank);

brain new_brain()
{
    brain b;

    b.state = WAITING;
    b.target = NULL;
    b.last_shot = NULL;

    return b;
}

void think(game &g)
{
    if ( not falling(*(g.active_tank), g.game_terrain) )
    {
        if ( no_or_dead_target(g.active_tank->ai.target) )
        {
            pick_target(g);
            set_target_angle(g);
            set_target_power(g);
        }
        else
        {
            adjust_aiming(g);
        }

        bound_targets(*(g.active_tank));

        g.active_tank->ai.state = READY;
    }
}

/**
 * picks a victim^H^H^H^H^H^Htarget to fire at
 */
void pick_target(game &g)
{
    int d;
    int closest = WINDOW_WIDTH;

    for ( int i = 0; i < g.tanks.size(); i++ )
    {
        if ( g.tanks[i].id != g.active_tank->id and g.tanks[i].alive )
        {
            d = distance_x(g.active_tank, g.tanks[i]);
            if ( abs(d) < closest )
            {
                g.active_tank->ai.target = &(g.tanks[i]);
                closest = d;
            }
        }
    }
}

/**
 * sets an initial target angle estimate for a new target
 */
void set_target_angle(game &g)
{
    int d = distance_x(g.active_tank, *(g.active_tank->ai.target));
    int angle;

    if ( d > LONG_RANGE )
    {
        angle = 55;
    }
    else if ( d > MEDIUM_RANGE )
    {
        angle = 65;
    }
    else if ( d > 0 )
    {
        angle = 80;
    }
    else if ( d > -MEDIUM_RANGE )
    {
        angle = 100;
    }
    else if ( d < -LONG_RANGE )
    {
        angle = 115;
    }
    else
    {
        angle = 125;
    }

    // random element for realism feel
    angle += rnd(11) - 5;
        
    g.active_tank->ai.target_angle = angle;
}

/**
 * sets an initial target power estimate for a new target
 */
void set_target_power(game &g)
{
    double d = distance_x(g.active_tank, *(g.active_tank->ai.target));
    adjust_for_wind(d, g.wind_strength);

    double power = sqrt(8 * abs(d));
    adjust_for_angle(power, g.active_tank->ai.target_angle);
    
    g.active_tank->ai.target_power = int(power);
}

/**
 * adjust distance for wind
 */
void adjust_for_wind(double &d, double wind)
{
    if ( abs(d + wind) > abs(d) )
    {
        d /= (1 + abs(wind));
    }
    else
    {
        d *= (1 + abs(wind));
    }
}

/**
 * adjust power for angle
 */
void adjust_for_angle(double &power, int angle)
{
    angle -= 90;
    angle = abs(angle);
    angle -= 45;
    angle = abs(angle);
    angle *= 2;
    power *= 1 + sine(angle) / 2;
}

/**
 * adjust the target angle by angle and power
 */
void adjust_aiming(game &g)
{
    double adjustment = aim_adjustment(*(g.active_tank));

    if ( adjustment > ANGLE_THRESHOLD )
    {
        if ( g.active_tank->turret_angle > 45 )
        {
            adjustment -= ANGLE_THRESHOLD;
            g.active_tank->ai.target_angle--;
        }
        else if ( g.active_tank->turret_angle < 45 )
        {
            adjustment -= ANGLE_THRESHOLD;
            g.active_tank->ai.target_angle++;
        }
    }
    if ( adjustment < -ANGLE_THRESHOLD )
    {
        if ( g.active_tank->turret_angle > 135 )
        {
            adjustment += ANGLE_THRESHOLD;
            g.active_tank->ai.target_angle--;
        }
        else if ( g.active_tank->turret_angle < 135 )
        {
            adjustment += ANGLE_THRESHOLD;
            g.active_tank->ai.target_angle++;
        }
    }
    if ( adjustment > 0 )
    {
        g.active_tank->ai.target_power += int(sqrt(adjustment));
    }
    else
    {
        g.active_tank->ai.target_power -= int(sqrt(abs(adjustment)));
    }
}

/**
 * bound to within tank limits
 */
void bound_targets(tank &active_tank)
{
    active_tank.ai.target_angle = max(active_tank.ai.target_angle,
                                      TANK_MIN_ANGLE + active_tank.base_angle + 2);
    active_tank.ai.target_angle = min(active_tank.ai.target_angle,
                                      TANK_MAX_ANGLE - active_tank.base_angle - 2);

    active_tank.ai.target_power = max(active_tank.ai.target_power, TANK_MIN_POWER);
    active_tank.ai.target_power = min(active_tank.ai.target_power, TANK_MAX_POWER);
}

void act(game &g)
{
    tank *t = g.active_tank;
    if ( t->turret_angle != t->ai.target_angle )
    {
        adjust_angle(*t);
    }
    else
    {
        if ( t->power != t->ai.target_power )
        {
            adjust_power(*t);
        }
        else
        {
            t->ai.state = WAITING;
            shoot(*t);
            t->ai.last_shot = &(t->active_shot);
        }
    }
}

/**
 * adjust the angle by one increment towards the target angle, delay for effect
 */
void adjust_angle(tank &t)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    ( t.turret_angle > t.ai.target_angle ) ? angle_down(t) : angle_up(t);
}

/**
 * adjust the power by one increment towards the target angle, delay for effect
 */
void adjust_power(tank &t)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    ( t.power > t.ai.target_power ) ? power_down(t) : power_up(t);
}

/**
 * return the horizontal distance between two tanks
 */
int distance_x(const tank *t1, const tank &t2)
{
    int d = int(max(t1->coords.x, t2.coords.x) - min(t1->coords.x, t2.coords.x));

    return ( t1->coords.x > t2.coords.x ) ? -d : d;
}

/**
 * is there no target, or a dead target?
 */
bool no_or_dead_target(const tank *target)
{
    return !target or not target->alive;
}

/**
 * calculate the aim adjustment factor
 */
double aim_adjustment(const tank &active_tank)
{
    point_2d source = active_tank.coords;
    point_2d target = tank_center(*(active_tank.ai.target));
    point_2d shot = active_tank.ai.last_shot->coords;

    double d;
    if ( (source.x < target.x and shot.x < target.x) or
         (source.x < target.x and shot.x > target.x) )
    {
        d = target.x - shot.x + (shot.y - target.y) / 4;
    }
    // lets be explicit because this is hard
    else if ( (source.x > target.x and shot.x < target.x) or
              (source.x > target.x and shot.x > target.x) )
    {
        d = shot.x - target.x + (shot.y - target.y) / 4;
    }

    return d;
}
