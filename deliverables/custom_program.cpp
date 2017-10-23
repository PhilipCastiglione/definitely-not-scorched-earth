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
#ifndef HUD_H_
#define HUD_H_ 

#include "shared.h"

/**
 * Draw the hud on the window, using the provided game elements.
 *
 * @param   the game containing elements to be drawn
 */
void draw_hud(const game &g);

#endif
#ifndef MENU_SCREEN_H_
#define MENU_SCREEN_H_ 

#include "shared.h"

// shared constants
// structure
#define OUTER_RECT_X WINDOW_WIDTH / 8
#define OUTER_RECT_Y WINDOW_HEIGHT / 8
#define OUTER_RECT_WIDTH WINDOW_WIDTH * 3 / 4
#define OUTER_RECT_HEIGHT WINDOW_HEIGHT * 3 / 4

// section x values
#define TEXT_X OUTER_RECT_X + 20
#define CONTROLS_X TEXT_X + 20
#define LESS_TANKS_X TEXT_X
#define NUM_TANKS_X LESS_TANKS_X + 30
#define MORE_TANKS_X NUM_TANKS_X + 30
#define PLAY_BUTTON_X OUTER_RECT_X + OUTER_RECT_WIDTH / 2 - PLAY_BUTTON_WIDTH / 2

// section y values
#define TITLE_Y OUTER_RECT_Y + 14
#define INTRO1_Y TITLE_Y + BIG_FONT_SIZE + 34
#define INTRO2_Y INTRO1_Y + FONT_SIZE + 12
#define INTRO3_Y INTRO2_Y + FONT_SIZE + 12
#define TANK_QTY_HEADER_Y INTRO3_Y + FONT_SIZE + 32
#define TANK_QTY_Y TANK_QTY_HEADER_Y + FONT_SIZE + 22
#define TANKS_Y TANK_QTY_Y + FONT_SIZE + 47
#define CONTROLS_Y OUTER_RECT_Y + OUTER_RECT_HEIGHT - FONT_SIZE - 10
#define PLAY_BUTTON_Y CONTROLS_Y - 20 - BIG_FONT_SIZE

// element sizes
#define PLAY_BUTTON_WIDTH 100
#define NAME_BOX_WIDTH 113
#define NAME_BOX_HEIGHT BIG_FONT_SIZE - 8

/**
 * Create and return a new menu ui object containing menu related ui elements.
 *
 * @param    the game for which to draw a new menu
 * @returns  the new menu_screen
 */
menu_screen new_menu_screen(const game &g);

/**
 * Manage the menu music loop.
 */
void play_menu_screen_music();

/**
 * Draw the menu screen on the window, using the provided game elements.
 *
 * @param   the game containing elements to be drawn
 */
void draw_menu_screen(game &g);

/**
 * Handles input on the menu screen and decides whether anything needs to happen.
 *
 * @param   the game containing the menu screen
 */
void handle_menu_screen_input(game &g);

#endif
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
#ifndef SHARED_H_
#define SHARED_H_ 

#include "splashkit.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BACKGROUND_COLOR COLOR_LIGHT_BLUE

#define TEXT_FONT "menu_font"
#define BIG_FONT_SIZE 36
#define FONT_SIZE 18

#include "types.h"

/**
 * Shared procedure to draw a ui element.
 *
 * @param   the ui element to be drawn
 */
void draw_ui_element(const ui_element &e);

/**
 * Has this ui element been clicked on?
 *
 * @param   the ui element that might have been clicked on
 */
bool clicked_on(const ui_element &e);

/**
 * Has this ui element been clicked outside of?
 *
 * @param   the ui element that might have been clicked outside of
 */
bool clicked_outside(const ui_element &e);

#endif
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
#ifndef TYPES_H_
#define TYPES_H_ 

// forward declarations
struct tank;

/**
 * The current state the game is in.
 */
enum game_state
{
    IN_MENU,
    PLAYING,
    PAUSED,
    WON
};

/**
 * The current state a brain is in.
 */
enum brain_state
{
    THINKING,
    READY,
    WAITING
};

/**
 * Terrain represents the landscape on which the tank battle takes place
 */
struct terrain
{
    bitmap bmp;
    int tops[WINDOW_WIDTH];
};

/**
 * Shot is a shot fired from a tank.
 */
struct shot
{
    double initial_y;
    double initial_x;
    color clr;
    int initial_angle;
    double power;
    double distance;
    point_2d coords;
};

/**
 * Brain, makes smart.
 */
struct brain
{
    brain_state state;
    tank *target;
    shot *last_shot;
    int target_angle;
    int target_power;
};

/**
 * Tanks. Enough said.
 */
struct tank
{
    int id;
    string name;
    bool is_ai;
    brain ai;
    color clr;
    int health;
    bool alive;
    bitmap bmp;
    point_2d coords;
    int turret_angle;
    point_2d turret_end;
    int power;
    int base_angle;
    bool shooting;
    shot active_shot;
};

/**
 * An element of the ui that knows where it is and what it looks like.
 */
struct ui_element
{
    point_2d coords;
    bitmap bmp;
    color clr;
};

/**
 * A toggle used to swap between a human and AI player.
 */
struct player_toggle
{
    ui_element human;
    ui_element robot;
};

/**
 * The set of ui elements in the menu ui.
 */
struct menu_screen
{
    ui_element less_tanks;
    ui_element more_tanks;
    ui_element play;
    vector<ui_element> name_boxes;
    vector<player_toggle> player_toggles;
    bool editing_name;
    tank *editing_tank;
    ui_element *editing_box;
};

/**
 * The set of ui elements in the won ui.
 */
struct won_screen
{
    ui_element restart;
};

/**
 * The game object manages all relevant state for the game.
 */
struct game
{
    terrain game_terrain;
    vector<tank> tanks;
    tank *active_tank;
    game_state state;
    menu_screen menu_ui;
    won_screen won_ui;
    double wind_strength;
};

#endif
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
#include "game.h"
#include "brain.h"
#include "menu_screen.h"
#include "pause_screen.h"
#include "hud.h"
#include "tank.h"
#include "terrain.h"
#include "shot.h"
#include "won_screen.h"

#include <cstdlib> // abs

// forward declarations
void draw_tanks(game &g);
void ai_tick(game &g);
void tank_tick(game &g);
void shot_tick(game &g);
void wind_tick(game &g);
bool shot_impact(const game &g);
bool shot_missed(const game &g);
void next_player(game &g);
void activate_random_tank(game &g);
void initialize_tanks(game &g);
bool tanks_too_close(const tank &t1, const tank &t2);
bool touches_tank(const vector<tank> &tanks, const point_2d &coords);

/**
 * manages the game music loop
 */
void play_game_music()
{
    if ( not music_playing() )
    {
        play_music(music_named("atmosphere"), 1, 0.4);
    }
}

/**
 * handles input for the game when in playing state
 */
void handle_game_input(game &g)
{
    if ( not g.active_tank->is_ai )
    {
        handle_tank_input(*(g.active_tank), g.game_terrain);
    }

    if ( key_typed(ESCAPE_KEY) )
    {
        pause_game(g);
    }
}

/**
 * draws the game when in playing state
 */
void draw_game(game &g)
{
    draw_terrain(g.game_terrain);
    draw_tanks(g);
}

/**
 * draw all tanks
 */
void draw_tanks(game &g)
{
    for ( int i = 0; i < g.tanks.size(); i++ )
    {
        draw_tank(g.tanks[i]);
    }
}

/**
 * a game tick passes a unit of time
 */
void tick(game &g)
{
    ai_tick(g);
    tank_tick(g);
    shot_tick(g);
    wind_tick(g);
}

/**
 * ai does ai things for one tick
 */
void ai_tick(game &g)
{
    if ( g.active_tank->is_ai and not g.active_tank->shooting )
    {
        // think is synchronous so lets just get tick happening before and after
        if ( g.active_tank->ai.state == READY )
        {
            act(g);
        }
        if ( g.active_tank->ai.state == THINKING )
        {
            think(g);
        }
        if ( g.active_tank->ai.state == WAITING )
        {
            g.active_tank->ai.state = THINKING;
        }
    }
}

/**
 * tanks fall for one tick
 */
void tank_tick(game &g)
{
    for ( int i = 0; i < g.tanks.size(); i++ )
    {
        fall(g.tanks[i], g.game_terrain);
    }
}

/**
 * any active shot continues on its trajectory for one tick
 */
void shot_tick(game &g)
{
    if ( g.active_tank->shooting )
    {
        if ( shot_impact(g) )
        {
            g.active_tank->shooting = false;
            explode(g.active_tank->active_shot, g.tanks, g.game_terrain);
            next_player(g);
        }
        else if ( shot_missed(g) )
        {
            g.active_tank->shooting = false;
            next_player(g);
        }
        else
        {
            move_shot(g.active_tank->active_shot, g.wind_strength);
            draw_shot(g.active_tank->active_shot);
        }
    }
}

/**
 * the wind shifts randomly over time
 */
void wind_tick(game &g)
{
    double chance = rnd();

    // the wind shouldn't adjust excessively quickly
    if ( chance < 0.03 and g.wind_strength > -1.0 )
    {
        g.wind_strength -= 0.01;
    }
    else if ( chance < 0.06 and g.wind_strength < 1.0 )
    {
        g.wind_strength += 0.01;
    }
}

/**
 * the shot has has the ground or the base of the window
 */
bool shot_impact(const game &g)
{
    return touches_ground(g.game_terrain, g.active_tank->active_shot.coords) or
           touches_tank(g.tanks, g.active_tank->active_shot.coords) or
           g.active_tank->active_shot.coords.y >= WINDOW_HEIGHT - 2;
}

/**
 * the shot is off the horizontal edge of the window
 */
bool shot_missed(const game &g)
{
    return g.active_tank->active_shot.coords.x >= WINDOW_WIDTH or
           g.active_tank->active_shot.coords.x <= 0;
}

/**
 * select the next player, unless the game has been won
 */
void next_player(game &g)
{
    if ( game_won(g) )
    {
        win_game(g);
    }
    else
    {
        if ( g.active_tank->id == g.tanks.size() )
        {
            g.active_tank = &(g.tanks[0]);
        }
        else
        {
            g.active_tank = &(g.tanks[g.active_tank->id]);
        }
        if ( not g.active_tank->alive )
        {
            next_player(g);
        }
    }
}

game new_game()
{
    game g;

    g.state = IN_MENU;
    g.game_terrain = new_terrain();
    g.tanks.push_back(new_tank(1));
    g.tanks.push_back(new_tank(2));
    g.menu_ui = new_menu_screen(g);
    g.won_ui = new_won_screen(g);
    g.wind_strength = 0.0;

    return g;
}

void initialize_game(game &g)
{
    stop_music();
    activate_random_tank(g);
    initialize_tanks(g);
}

/**
 * perform menu loop actions related to menu screen
 */
void menu_loop(game &g)
{
    play_menu_screen_music();
    handle_menu_screen_input(g);
    draw_menu_screen(g);
}

/**
 * perform playing loop actions for the main game
 */
void playing_loop(game &g)
{
    play_game_music();
    handle_game_input(g);
    draw_game(g);
    draw_hud(g);
    tick(g);
}

/**
 * perform pause loop actions for when the game is paused
 */
void paused_loop(game &g)
{
    handle_pause_screen_input(g);
    draw_game(g);
    draw_pause_screen(g);
}

/**
 * perform won loop actions for when the game has just been won
 */
void won_loop(game &g)
{
    draw_game(g);
    draw_won_screen(g);
    handle_won_screen_input(g);
}

void game_loop(game &g)
{
    while ( not quit_requested() )
    {
        process_events();

        clear_screen(BACKGROUND_COLOR);

        switch( g.state )
        {
            case IN_MENU:
                menu_loop(g);
                break;
            case PLAYING:
                playing_loop(g);
                break;
            case PAUSED:
                paused_loop(g);
                break;
            case WON:
                won_loop(g);
                break;
        }

        refresh_screen(60);
    }
}

/**
 * picks a random tank to start the game
 */
void activate_random_tank(game &g)
{
    g.active_tank = &(g.tanks[rnd(g.tanks.size())]);
}

/**
 * repeatedly reinitialize tanks until they're not too close to each other
 */
void initialize_tanks(game &g)
{
    bool acceptable;
    int i = 0;
    while ( i < g.tanks.size() )
    {
        initialize_tank(g.tanks[i]);
        acceptable = true;
        for ( int j = 0; j < i; j++ )
        {
            if ( tanks_too_close(g.tanks[j], g.tanks[i]) )
            {
                acceptable = false;
            }
        }
        if ( acceptable ) i++;
    }
}

/**
 * are these tanks too close to spawn at this range?
 */
bool tanks_too_close(const tank &t1, const tank &t2)
{
    return abs(int(t1.coords.x - t2.coords.x)) < MIN_PLAYER_GAP;
}

/**
 * does this point touch any tank
 */
bool touches_tank(const vector<tank> &tanks, const point_2d &coords)
{
    bool touches = false;
    for ( tank t: tanks )
    {
        if ( bitmap_point_collision(t.bmp, t.coords, coords) )
        {
            touches = true;
        }
    }
    return touches;
}
#include "hud.h"

#include <cstdlib> // abs

// constants
#define PLAYER_HUD_X 10
#define PLAYER_HUD_NAME_Y 10
#define PLAYER_HUD_ANGLE_Y PLAYER_HUD_NAME_Y + FONT_SIZE
#define PLAYER_HUD_POWER_Y PLAYER_HUD_ANGLE_Y + FONT_SIZE
#define WIND_X WINDOW_WIDTH - 110
#define WIND_Y 10
#define HEALTH_X WINDOW_WIDTH - 110
#define HEALTH_Y 50
#define HEALTH_WIDTH 100
#define HEALTH_HEIGHT 20

// forward declarations
void draw_player_hud(const game &g);
void draw_game_hud(const game &g);
void draw_health_bars(const game &g);
void draw_wind(const game &g);

void draw_hud(const game &g)
{
    draw_player_hud(g);
    draw_game_hud(g);
}

/**
 * draw the player hud details
 */
void draw_player_hud(const game &g)
{
    string angle_text, power_text;
    int angle = g.active_tank->turret_angle;
    if ( angle > 90 )
    {
        angle_text = "ANGLE: < " + to_string(abs(angle - 90));
    }
    else if ( angle < 90 )
    {
        angle_text = "ANGLE: " + to_string(abs(angle - 90)) + " >";
    }
    else
    {
        angle_text = "ANGLE: 0";
    }
    power_text = "POWER: " + to_string(g.active_tank->power);

    draw_text(g.active_tank->name, g.active_tank->clr, TEXT_FONT, FONT_SIZE, PLAYER_HUD_X, PLAYER_HUD_NAME_Y);
    draw_text(angle_text, COLOR_BLACK, TEXT_FONT, FONT_SIZE, PLAYER_HUD_X, PLAYER_HUD_ANGLE_Y);
    draw_text(power_text, COLOR_BLACK, TEXT_FONT, FONT_SIZE, PLAYER_HUD_X, PLAYER_HUD_POWER_Y);
}

/**
 * draw the game hud details
 */
void draw_game_hud(const game &g)
{
    draw_wind(g);
    draw_health_bars(g);
}

/**
 * draw the wind
 */
void draw_wind(const game &g)
{
    string wind_text;

    if ( g.wind_strength < 0 )
    {
        wind_text = "WIND: < " + to_string(abs(int(g.wind_strength * 100)));
    }
    else if ( g.wind_strength > 0 )
    {
        wind_text = "WIND:   " + to_string(abs(int(g.wind_strength * 100))) + " >";
    }
    else
    {
        wind_text = "WIND:   0";
    }
    draw_text(wind_text, COLOR_BLACK, TEXT_FONT, FONT_SIZE, WIND_X, WIND_Y);
}

/**
 * draw the player health bars
 */
void draw_health_bars(const game &g)
{
    for ( int i = 0; i < g.tanks.size(); i++ )
    {
        fill_rectangle(COLOR_BLACK, HEALTH_X - 1, HEALTH_Y + (HEALTH_HEIGHT + 5) * i - 1,
                       HEALTH_WIDTH + 2, HEALTH_HEIGHT + 2);
        fill_rectangle(g.tanks[i].clr, HEALTH_X, HEALTH_Y + (HEALTH_HEIGHT + 5) * i,
                       g.tanks[i].health, HEALTH_HEIGHT);
    }
}
#include "shared.h"
#include "game.h"

void load_resources()
{
    load_font("menu_font", "SourceSansPro-Regular.ttf");
    load_bitmap("human", "human.png");
    load_bitmap("robot", "robot.png");
    load_sound_effect("angle", "angle.wav");
    load_sound_effect("backspace", "backspace.wav");
    load_sound_effect("click", "click.wav");
    load_sound_effect("destroy", "destroy.wav");
    load_sound_effect("explode", "explode.wav");
    load_sound_effect("letter", "letter.wav");
    load_sound_effect("power", "power.wav");
    load_sound_effect("shoot", "shoot.wav");
    load_sound_effect("win", "win.wav");
    load_music("atmosphere", "atmosphere.wav");
    load_music("menu", "menu.wav");
}

/**
 * The entry point for the program; loads resources and starts a new game
 */
int main()
{
    open_window("DEFINITELY NOT SCORCHED EARTH", WINDOW_WIDTH, WINDOW_HEIGHT);

    load_resources();

    game g = new_game();

    game_loop(g);

    return 0;
}
#include "menu_screen.h"
#include "game.h"
#include "tank.h"

// constants
#define TITLE_COPY "DEFINITELY NOT SCORCHED EARTH"
#define INTRO1_COPY "Welcome! This is an entirely original game where you are a tank."
#define INTRO2_COPY "Your friends, they also are tanks."
#define INTRO3_COPY "You should probably shoot each other."
#define TANK_QTY_HEADER_COPY "Select players and choose names:"
#define EDIT_TANK_NAME_COPY "Editing player name. Click outside the name box or press ESC to end."
#define CONTROLS_COPY "LEFT/RIGHT - aim      UP/DOWN - power      SPACE - fire      ESC - pause"
#define PLAY_COPY "PLAY"

// forward declarations
ui_element new_less_tanks_button();
ui_element new_more_tanks_button();
ui_element new_play_button();
vector<player_toggle> new_player_toggles(const vector<tank> &tanks);
vector<ui_element> new_name_boxes(const vector<tank> &tanks);
player_toggle new_player_toggle(const tank &t);
ui_element new_name_box(const tank &t);
void draw_frame();
void draw_fixed_copy();
void draw_tank_num_selection(const game &g);
void draw_tanks_on_menu_screen(game &g);
void draw_edit_name(const game &g);
void draw_player_toggle(const player_toggle &toggle, bool is_ai);
void draw_name_box(const ui_element &box, string name);
void handle_less_tanks(game &g);
void handle_more_tanks(game &g);
void handle_edit_name_input(game &g);
void handle_player_toggles(game &g);
void handle_name_boxes(game &g);
void backspace(string *name);
void type(string *name, string key);
void handle_player_toggle(player_toggle &toggle, tank &t);
void handle_name_box(menu_screen &m, ui_element &name_box, tank &t);
void handle_play(game &g);

menu_screen new_menu_screen(const game &g)
{
    menu_screen m;
    m.less_tanks = new_less_tanks_button();
    m.more_tanks = new_more_tanks_button();
    m.play = new_play_button();
    m.player_toggles = new_player_toggles(g.tanks);
    m.name_boxes = new_name_boxes(g.tanks);
    m.editing_name = false;
    m.editing_tank = NULL;
    return m;
}

void play_menu_screen_music()
{
    if (not music_playing())
    {
        play_music(music_named("menu"), 1, 0.4);
    }
}

/**
 * creates and returns the less tanks button
 */
ui_element new_less_tanks_button()
{
    ui_element less_tanks;

    less_tanks.coords.x = LESS_TANKS_X;
    less_tanks.coords.y = TANK_QTY_Y + 4;
    less_tanks.clr = COLOR_LIGHT_GREEN;
    less_tanks.bmp = create_bitmap("less_tanks", BIG_FONT_SIZE / 2, BIG_FONT_SIZE);
    fill_triangle_on_bitmap(less_tanks.bmp, less_tanks.clr, BIG_FONT_SIZE / 2,
                            0, BIG_FONT_SIZE / 2, BIG_FONT_SIZE, 0, BIG_FONT_SIZE / 2);
    setup_collision_mask(less_tanks.bmp);
    return less_tanks;
}

/**
 * creates and returns the more tanks button
 */
ui_element new_more_tanks_button()
{
    ui_element more_tanks;

    more_tanks.coords.x = MORE_TANKS_X;
    more_tanks.coords.y = TANK_QTY_Y + 4;
    more_tanks.clr = COLOR_LIGHT_GREEN;
    more_tanks.bmp = create_bitmap("more_tanks", BIG_FONT_SIZE / 2, BIG_FONT_SIZE);
    fill_triangle_on_bitmap(more_tanks.bmp, more_tanks.clr, 0, 0, 0,
                            BIG_FONT_SIZE, BIG_FONT_SIZE / 2, BIG_FONT_SIZE / 2);
    setup_collision_mask(more_tanks.bmp);

    return more_tanks;
}

/**
 * creates and returns the play button
 */
ui_element new_play_button()
{
    ui_element play;

    play.coords.x = PLAY_BUTTON_X;
    play.coords.y = PLAY_BUTTON_Y;
    play.clr = COLOR_LIGHT_GREEN;
    play.bmp = create_bitmap("play", PLAY_BUTTON_WIDTH, BIG_FONT_SIZE);

    // this increases the hitbox for clicks
    fill_rectangle_on_bitmap(play.bmp, COLOR_BLACK, 0, 0, PLAY_BUTTON_WIDTH, BIG_FONT_SIZE);

    draw_text_on_bitmap(play.bmp, PLAY_COPY, play.clr, TEXT_FONT, BIG_FONT_SIZE, 0, 0);
    setup_collision_mask(play.bmp);

    return play;
}

/**
 * creates and returns the name boxes for tanks
 */
vector<player_toggle> new_player_toggles(const vector<tank> &tanks)
{
    vector<player_toggle> player_toggles;

    for ( tank t: tanks )
    {
        player_toggles.push_back(new_player_toggle(t));
    }

    return player_toggles;
}

/**
 * creates and returns the name boxes for tanks
 */
vector<ui_element> new_name_boxes(const vector<tank> &tanks)
{
    vector<ui_element> name_boxes;

    for ( tank t: tanks )
    {
        name_boxes.push_back(new_name_box(t));
    }

    return name_boxes;
}

/**
 * creates and returns a player_toggle for a tank
 */
player_toggle new_player_toggle(const tank &t)
{
    player_toggle toggle;

    ui_element human_toggle;
    human_toggle.coords.x = t.coords.x + 40;
    human_toggle.coords.y = t.coords.y - bitmap_height(t.bmp) - 20;
    human_toggle.bmp = bitmap_named("human");

    ui_element robot_toggle;
    robot_toggle.coords.x = t.coords.x + 40;
    robot_toggle.coords.y = t.coords.y - bitmap_height(t.bmp) - 20;
    robot_toggle.bmp = bitmap_named("robot");

    toggle.human = human_toggle;
    toggle.robot = robot_toggle;

    return toggle;
}

/**
 * creates and returns a name_box for a tank
 */
ui_element new_name_box(const tank &t)
{
    ui_element name_box;

    name_box.coords.x = t.coords.x + bitmap_width(t.bmp) / 2 - NAME_BOX_WIDTH / 2;
    name_box.coords.y = t.coords.y + bitmap_height(t.bmp) + 10;
    name_box.clr = t.clr;
    name_box.bmp = create_bitmap("name_box" + to_string(t.id), NAME_BOX_WIDTH, NAME_BOX_HEIGHT);        

    // this increases the hitbox for clicks
    fill_rectangle_on_bitmap(name_box.bmp, COLOR_BLACK, 0, 0, NAME_BOX_WIDTH, NAME_BOX_HEIGHT);

    fill_rectangle_on_bitmap(name_box.bmp, t.clr, 0, 0, NAME_BOX_WIDTH, 2);
    fill_rectangle_on_bitmap(name_box.bmp, t.clr, 0, 0, 2, NAME_BOX_HEIGHT);
    fill_rectangle_on_bitmap(name_box.bmp, t.clr, NAME_BOX_WIDTH - 2, 0, NAME_BOX_WIDTH, NAME_BOX_HEIGHT);
    fill_rectangle_on_bitmap(name_box.bmp, t.clr, 0, NAME_BOX_HEIGHT - 2, NAME_BOX_WIDTH, NAME_BOX_WIDTH);
    setup_collision_mask(name_box.bmp);

    return name_box;
}

void draw_menu_screen(game &g)
{
    draw_frame();
    draw_fixed_copy();
    if ( g.menu_ui.editing_name )
    {
        draw_edit_name(g);
    }
    else
    {
        draw_tank_num_selection(g);
        draw_ui_element(g.menu_ui.play);
        draw_tanks_on_menu_screen(g);
    }
}

/**
 * draw a black background with a green box
 */
void draw_frame()
{
    fill_rectangle(COLOR_BLACK, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    draw_rectangle(COLOR_GREEN, OUTER_RECT_X, OUTER_RECT_Y, OUTER_RECT_WIDTH, OUTER_RECT_HEIGHT);
    draw_rectangle(COLOR_GREEN, OUTER_RECT_X - 1, OUTER_RECT_Y - 1, OUTER_RECT_WIDTH + 2, OUTER_RECT_HEIGHT + 2);
}

/**
 * draw the fixed text: title, intro, tank quantity header and controls
 */
void draw_fixed_copy()
{
    draw_text(TITLE_COPY, COLOR_GREEN, TEXT_FONT, BIG_FONT_SIZE, TEXT_X, TITLE_Y);
    draw_text(INTRO1_COPY, COLOR_GREEN, TEXT_FONT, FONT_SIZE, TEXT_X, INTRO1_Y);
    draw_text(INTRO2_COPY, COLOR_GREEN, TEXT_FONT, FONT_SIZE, TEXT_X, INTRO2_Y);
    draw_text(INTRO3_COPY, COLOR_GREEN, TEXT_FONT, FONT_SIZE, TEXT_X, INTRO3_Y);
    draw_text(TANK_QTY_HEADER_COPY, COLOR_GREEN, TEXT_FONT, FONT_SIZE, TEXT_X, TANK_QTY_HEADER_Y);
    draw_text(CONTROLS_COPY, COLOR_GREEN, TEXT_FONT, FONT_SIZE, CONTROLS_X, CONTROLS_Y);
}

/**
 * draw the section where you select how many players there should be
 */
void draw_tank_num_selection(const game &g)
{
    int num_tanks = g.tanks.size();

    draw_text(to_string(g.tanks.size()), COLOR_LIGHT_GREEN, TEXT_FONT, BIG_FONT_SIZE, NUM_TANKS_X, TANK_QTY_Y);
    if ( num_tanks > 2 )
    {
        draw_ui_element(g.menu_ui.less_tanks);
    }
    if ( num_tanks < MAX_PLAYERS )
    {
        draw_ui_element(g.menu_ui.more_tanks);
    }
}

/**
 * draw the editing tank number overlay
 */
void draw_edit_name(const game &g)
{
    draw_text(EDIT_TANK_NAME_COPY, COLOR_LIGHT_GREEN, TEXT_FONT, FONT_SIZE, NUM_TANKS_X, TANK_QTY_Y);
    draw_tank(*(g.menu_ui.editing_tank));
    draw_name_box(*(g.menu_ui.editing_box), g.menu_ui.editing_tank->name);
}

/**
 * draw the tanks with name boxes
 */
void draw_tanks_on_menu_screen(game &g)
{
    for ( int i = 0; i < g.tanks.size(); i++ )
    {
        draw_player_toggle(g.menu_ui.player_toggles[i], g.tanks[i].is_ai);
        draw_tank(g.tanks[i]);
        draw_name_box(g.menu_ui.name_boxes[i], g.tanks[i].name);
    }
}

/**
 * draw the player toggle
 */
void draw_player_toggle(const player_toggle &toggle, bool is_ai)
{
    if ( is_ai )
    {
        draw_ui_element(toggle.robot);
    }
    else
    {
        draw_ui_element(toggle.human);
    }
}

/**
 * draw an individual name box with the current tank name
 */
void draw_name_box(const ui_element &box, string name)
{
    draw_ui_element(box);
    for ( int i = 0; i < PLAYER_NAME_LENGTH; i++ )
    {
        char c = (i < name.length()) ? name[i] : '_';
        double x = box.coords.x + 4 + (NAME_BOX_WIDTH - 9) * i / PLAYER_NAME_LENGTH;
        double y = box.coords.y + 2;
        draw_text(string(1, c), box.clr, TEXT_FONT, FONT_SIZE, x, y);
    }
}

void handle_menu_screen_input(game &g)
{
    handle_less_tanks(g);
    handle_more_tanks(g);
    handle_play(g);
    if ( g.menu_ui.editing_name ) handle_edit_name_input(g);
    handle_player_toggles(g);
    handle_name_boxes(g);
}

/**
 * handles the less tanks button being clicked on
 */
void handle_less_tanks(game &g)
{
    if ( clicked_on(g.menu_ui.less_tanks) and g.tanks.size() > 2 )
    {
        play_sound_effect("click");
        g.menu_ui.name_boxes.pop_back();
        g.menu_ui.player_toggles.pop_back();
        g.tanks.pop_back();
    }
}

/**
 * handles the more tanks button being clicked on
 */
void handle_more_tanks(game &g)
{
    if ( clicked_on(g.menu_ui.more_tanks) and g.tanks.size() < MAX_PLAYERS )
    {
        play_sound_effect("click");
        tank t = new_tank(g.tanks.size() + 1);
        g.menu_ui.name_boxes.push_back(new_name_box(t));
        g.menu_ui.player_toggles.push_back(new_player_toggle(t));
        g.tanks.push_back(t);
    }
}

/**
 * handles the player toggles being clicked on
 */
void handle_player_toggles(game &g)
{
    for ( int i = 0; i < g.menu_ui.player_toggles.size(); i++ )
    {
        handle_player_toggle(g.menu_ui.player_toggles[i], g.tanks[i]);
    }
}

/**
 * handles the names boxes being clicked on
 */
void handle_name_boxes(game &g)
{
    for ( int i = 0; i < g.menu_ui.name_boxes.size(); i++ )
    {
        handle_name_box(g.menu_ui, g.menu_ui.name_boxes[i], g.tanks[i]);
    }
}

/**
 * handles input when in editing name mode
 */
void handle_edit_name_input(game &g)
{
    string *name = &(g.menu_ui.editing_tank->name);
    if ( (*name).size() > 0 )
    {
        if ( key_typed(BACKSPACE_KEY) ) backspace(name);
    }
    if ( (*name).size() < PLAYER_NAME_LENGTH )
    {
        if ( key_typed(NUM_0_KEY) or key_typed(KEYPAD_0) ) type(name, "0");
        if ( key_typed(NUM_1_KEY) or key_typed(KEYPAD_1) ) type(name, "1");
        if ( key_typed(NUM_2_KEY) or key_typed(KEYPAD_2) ) type(name, "2");
        if ( key_typed(NUM_3_KEY) or key_typed(KEYPAD_3) ) type(name, "3");
        if ( key_typed(NUM_4_KEY) or key_typed(KEYPAD_4) ) type(name, "4");
        if ( key_typed(NUM_5_KEY) or key_typed(KEYPAD_5) ) type(name, "5");
        if ( key_typed(NUM_6_KEY) or key_typed(KEYPAD_6) ) type(name, "6");
        if ( key_typed(NUM_7_KEY) or key_typed(KEYPAD_7) ) type(name, "7");
        if ( key_typed(NUM_8_KEY) or key_typed(KEYPAD_8) ) type(name, "8");
        if ( key_typed(NUM_9_KEY) or key_typed(KEYPAD_9) ) type(name, "9");
        if ( key_typed(Q_KEY) ) type(name, "Q");
        if ( key_typed(W_KEY) ) type(name, "W");
        if ( key_typed(E_KEY) ) type(name, "E");
        if ( key_typed(R_KEY) ) type(name, "R");
        if ( key_typed(T_KEY) ) type(name, "T");
        if ( key_typed(Y_KEY) ) type(name, "Y");
        if ( key_typed(U_KEY) ) type(name, "U");
        if ( key_typed(I_KEY) ) type(name, "I");
        if ( key_typed(O_KEY) ) type(name, "O");
        if ( key_typed(P_KEY) ) type(name, "P");
        if ( key_typed(A_KEY) ) type(name, "A");
        if ( key_typed(S_KEY) ) type(name, "S");
        if ( key_typed(D_KEY) ) type(name, "D");
        if ( key_typed(F_KEY) ) type(name, "F");
        if ( key_typed(G_KEY) ) type(name, "G");
        if ( key_typed(H_KEY) ) type(name, "H");
        if ( key_typed(J_KEY) ) type(name, "J");
        if ( key_typed(K_KEY) ) type(name, "K");
        if ( key_typed(L_KEY) ) type(name, "L");
        if ( key_typed(Z_KEY) ) type(name, "Z");
        if ( key_typed(X_KEY) ) type(name, "X");
        if ( key_typed(C_KEY) ) type(name, "C");
        if ( key_typed(V_KEY) ) type(name, "V");
        if ( key_typed(B_KEY) ) type(name, "B");
        if ( key_typed(N_KEY) ) type(name, "N");
        if ( key_typed(M_KEY) ) type(name, "M");
    }
}

/**
 * remove the last character of a name
 */
void backspace(string *name)
{
    play_sound_effect("backspace");
    (*name).pop_back();
}

/**
 * add a character to a name
 */
void type(string *name, string key)
{
    play_sound_effect("letter");
    *name += key;
}

/**
 * handles an individual player toggle being clicked on
 */
void handle_player_toggle(player_toggle &toggle, tank &t)
{
    if ( clicked_on(toggle.human) )
    {
        play_sound_effect("click");
        t.is_ai = !t.is_ai;
        if ( t.is_ai )
        {
            generate_name(t);
        }
    }
}

/**
 * handles an individual name box being clicked on
 */
void handle_name_box(menu_screen &m, ui_element &name_box, tank &t)
{
    // enter name mode
    if ( clicked_on(name_box) and m.editing_name == false )
    {
        m.editing_name = true;
        m.editing_tank = &t;
        m.editing_box = &name_box;
    }

    // if in edit name mode and click out of the box or type esc, exit edit name mode
    if ( (clicked_outside(name_box) or key_typed(ESCAPE_KEY) )
        and m.editing_name == true and m.editing_tank->id == t.id)
    {
        m.editing_name = false;
        m.editing_tank = NULL;
        m.editing_box = NULL;
    }
}

/**
 * handles the play button being clicked on
 */
void handle_play(game &g)
{
    if ( clicked_on(g.menu_ui.play) and g.menu_ui.editing_name == false )
    {
        play_sound_effect("click");
        initialize_game(g);
        g.state = PLAYING;
    }
}
#include "pause_screen.h"

// constants
#define PAUSED_COPY "PAUSED"
#define PAUSED_X WINDOW_WIDTH / 2 - 85

// forward declaration
void resume_game(game &g);

void pause_game(game &g)
{
    pause_music();
    play_sound_effect("click");
    g.state = PAUSED;
}

void handle_pause_screen_input(game &g)
{
    if ( key_typed(ESCAPE_KEY) or mouse_clicked(LEFT_BUTTON) )
    {
        resume_game(g);
    }
}

void draw_pause_screen(const game &g)
{
    draw_text(PAUSED_COPY, COLOR_RED, TEXT_FONT, BIG_FONT_SIZE, PAUSED_X, 0);
}

/**
 * Returns the game to the playing state.
 */
void resume_game(game &g)
{
    resume_music();
    play_sound_effect("click");
    g.state = PLAYING;
}
#include "shared.h"

void draw_ui_element(const ui_element &e)
{
    draw_bitmap(e.bmp, e.coords.x, e.coords.y);
}

bool clicked_on(const ui_element &e)
{
    return mouse_clicked(LEFT_BUTTON) and
        bitmap_point_collision(e.bmp, e.coords, mouse_position());
}

bool clicked_outside(const ui_element &e)
{
    return mouse_clicked(LEFT_BUTTON) and
        not bitmap_point_collision(e.bmp, e.coords, mouse_position());
}
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
#include "tank.h"
#include "brain.h"
#include "terrain.h"
#include "shot.h"
#include "menu_screen.h"

#include <cmath> // geometry

// constants
#define TANK_RADIUS 12
#define TANK_EFFECT_VOLUME 0.6

// forward declarations
color tank_color(int id);
bitmap generate_tank_bmp(const tank &t);
string random_name();
bool is_touching_ground(const tank &t, const terrain &ground);
void draw_turret(const tank &t);
bool left_higher(const tank &t, const terrain &ground);
bool right_higher(const tank &t, const terrain &ground);
point_2d left_base_point(const tank &t);
point_2d mid_base_point(const tank &t);
point_2d right_base_point(const tank &t);
void set_turret_position(tank &t);
bool tank_hit(const tank &t, const point_2d coords, int impact_radius);
void destroy_tank(tank &t);

tank new_tank(int id)
{
    tank t;

    t.id = id;
    t.name = "TANK" + to_string(id);
    t.is_ai = false;
    t.ai = new_brain();
    t.clr = tank_color(id);
    t.health = 100;
    t.alive = true;
    t.bmp = generate_tank_bmp(t);
    // the initial starting position is on the menu
    t.coords.x = OUTER_RECT_X + OUTER_RECT_WIDTH * id / 5;
    t.coords.y = TANKS_Y;
    t.turret_angle = 90;
    t.power = 50;
    t.base_angle = 0;
    t.shooting = false;

    return t;
}

/**
 * Provide the color for the tank based on it's id.
 */
color tank_color(int id)
{
    switch ( id )
    {
        case 1: return COLOR_BLUE;
        case 2: return COLOR_RED;
        case 3: return COLOR_ORANGE;
        case 4:
        default: return COLOR_PURPLE;
    }
}

/**
 * Fill a circle on a bitmap half it's size, so only a semicircle displays.
 */
bitmap generate_tank_bmp(const tank &t)
{
    bitmap bmp = create_bitmap("tank" + to_string(t.id), int(2 * TANK_RADIUS), int(TANK_RADIUS));

    fill_circle_on_bitmap(bmp, t.clr, TANK_RADIUS, TANK_RADIUS, TANK_RADIUS);
    setup_collision_mask(bmp);

    return bmp;
}

void initialize_tank(tank &t)
{
    t.coords.x = 10 + rnd(WINDOW_WIDTH - bitmap_width(t.bmp) - 20);
    t.coords.y = 0;
}

void generate_name(tank &t)
{
    t.name = random_name();
}

/**
 * Returns a random tank name.
 */
string random_name()
{
    vector<string> names;

    names.push_back("SKYNET");
    names.push_back("SMARTANK");
    names.push_back("DUMBTANK");
    names.push_back("TANKDUDE");
    names.push_back("TANKGUY");
    names.push_back("TANKETTE");
    names.push_back("TANKGIRL");
    names.push_back("TANKSTER");
    names.push_back("FISH");
    names.push_back("SEPTIC");
    names.push_back("THOMAS");
    names.push_back("AIMBOT");
    names.push_back("PANZER");
    names.push_back("SHERMAN");
    names.push_back("ACAIN");

    return names[rnd(names.size())];
}

void draw_tank(tank &t)
{
    draw_bitmap(t.bmp, t.coords.x, t.coords.y, option_rotate_bmp(t.base_angle, 0, TANK_RADIUS / 2));
    set_turret_position(t);
    draw_turret(t);
}

point_2d tank_center(const tank &t)
{
    point_2d center;

    point_2d mbp = mid_base_point(t);
    if ( t.base_angle >= 0 )
    {
        center.x = mbp.x + cosine(90 - t.base_angle) * TANK_RADIUS / 2;
        center.y = mbp.y - sine(90 - t.base_angle) * TANK_RADIUS / 2;
    }
    else
    {
        center.x = mbp.x - cosine(90 - t.base_angle) * TANK_RADIUS / 2;
        center.y = mbp.y - sine(90 - t.base_angle) * TANK_RADIUS / 2;
    }

    return center;
}

/**
 * Set the turret position (turrent end) to match the turret angle.
 */
void set_turret_position(tank &t)
{
    point_2d center = mid_base_point(t);

    if ( t.turret_angle <= 90 )
    {
        t.turret_end.x = cosine(t.turret_angle) * 1.5 * TANK_RADIUS + center.x;
        t.turret_end.y = center.y - sine(t.turret_angle) * 1.5 * TANK_RADIUS;
    }
    else
    {
        t.turret_end.x = -cosine(180 - t.turret_angle) * 1.5 * TANK_RADIUS + center.x;
        t.turret_end.y = center.y - sine(180 - t.turret_angle) * 1.5 * TANK_RADIUS;
    }
}

/**
 * Draw 9 lines that make up the turret in a grid so it appears there is a 3
 * pixel width block from any angle. Adjusts the base if the tank is on a
 * large angle to make it appear more central.
 */
void draw_turret(const tank &t)
{
    point_2d center = mid_base_point(t);

    if ( t.base_angle > 45 )
    {
        draw_line(t.clr, t.turret_end.x + 1, t.turret_end.y - 3, center.x + 1, center.y - 3);
        draw_line(t.clr, t.turret_end.x + 1, t.turret_end.y - 2, center.x + 1, center.y - 2);
        draw_line(t.clr, t.turret_end.x + 1, t.turret_end.y - 1, center.x + 1, center.y - 1);
        draw_line(t.clr, t.turret_end.x + 2, t.turret_end.y - 3, center.x + 2, center.y - 3);
        draw_line(t.clr, t.turret_end.x + 2, t.turret_end.y - 2, center.x + 2, center.y - 2);
        draw_line(t.clr, t.turret_end.x + 2, t.turret_end.y - 1, center.x + 2, center.y - 1);
    }
    else if ( t.base_angle < -45 )
    {
        draw_line(t.clr, t.turret_end.x - 2, t.turret_end.y - 3, center.x - 2, center.y - 3);
        draw_line(t.clr, t.turret_end.x - 2, t.turret_end.y - 2, center.x - 2, center.y - 2);
        draw_line(t.clr, t.turret_end.x - 2, t.turret_end.y - 1, center.x - 2, center.y - 1);
        draw_line(t.clr, t.turret_end.x - 1, t.turret_end.y - 3, center.x - 1, center.y - 3);
        draw_line(t.clr, t.turret_end.x - 1, t.turret_end.y - 2, center.x - 1, center.y - 2);
        draw_line(t.clr, t.turret_end.x - 1, t.turret_end.y - 1, center.x - 1, center.y - 1);
    }
    else
    {
        draw_line(t.clr, t.turret_end.x - 1, t.turret_end.y - 3, center.x - 1, center.y - 3);
        draw_line(t.clr, t.turret_end.x - 1, t.turret_end.y - 2, center.x - 1, center.y - 2);
        draw_line(t.clr, t.turret_end.x - 1, t.turret_end.y - 1, center.x - 1, center.y - 1);
        draw_line(t.clr, t.turret_end.x + 1, t.turret_end.y - 3, center.x + 1, center.y - 3);
        draw_line(t.clr, t.turret_end.x + 1, t.turret_end.y - 2, center.x + 1, center.y - 2);
        draw_line(t.clr, t.turret_end.x + 1, t.turret_end.y - 1, center.x + 1, center.y - 1);
    }
    draw_line(t.clr, t.turret_end.x, t.turret_end.y - 3, center.x, center.y - 3);
    draw_line(t.clr, t.turret_end.x, t.turret_end.y - 2, center.x, center.y - 2);
    draw_line(t.clr, t.turret_end.x, t.turret_end.y - 1, center.x, center.y - 1);
}

void handle_tank_input(tank &t, terrain &ground)
{
    if ( not t.shooting and not falling(t, ground) )
    {
        if ( key_typed(SPACE_KEY) )
        {
            shoot(t);
        }
        if ( key_down(UP_KEY) and t.power < TANK_MAX_POWER )
        {
            power_up(t);
        }
        if ( key_down(DOWN_KEY) and t.power > TANK_MIN_POWER )
        {
            power_down(t);
        }
        if ( key_down(LEFT_KEY) and t.turret_angle + t.base_angle < TANK_MAX_ANGLE )
        {
            angle_up(t);
        }
        if ( key_down(RIGHT_KEY) and t.turret_angle + t.base_angle > TANK_MIN_ANGLE )
        {
            angle_down(t);
        }
    }
}

void power_up(tank &t)
{
    if ( not sound_effect_playing("power") )
    {
        play_sound_effect("power", 1, TANK_EFFECT_VOLUME);
    }
    t.power++;
}

void power_down(tank &t)
{
    if ( not sound_effect_playing("power") )
    {
        play_sound_effect("power", 1, TANK_EFFECT_VOLUME);
    }
    t.power--;
}

void angle_up(tank &t)
{
    if ( not sound_effect_playing("angle") )
    {
        play_sound_effect("angle", 1, TANK_EFFECT_VOLUME / 3);
    }
    t.turret_angle++;
}

void angle_down(tank &t)
{
    if ( not sound_effect_playing("angle") )
    {
        play_sound_effect("angle", 1, TANK_EFFECT_VOLUME / 3);
    }
    t.turret_angle--;
}

void shoot(tank &t)
{
    play_sound_effect("shoot");
    t.active_shot = new_shot(t);
    t.shooting = true;
}

void fall(tank &t, const terrain &ground)
{
    if ( not is_touching_ground(t, ground) and t.coords.y < WINDOW_HEIGHT - 2 )
    {
        t.coords.y += 3;
    }
    if ( left_higher(t, ground) )
    {
        t.base_angle++;
    }
    if ( right_higher(t, ground) )
    {
        t.base_angle--;
    }
}

bool falling(const tank &t, const terrain &ground)
{
    return not is_touching_ground(t, ground) or left_higher(t, ground) or right_higher(t, ground);
}

/**
 * Is the tank touching the ground?
 */
bool is_touching_ground(const tank &t, const terrain &ground)
{
    bool left_base_point_touching = touches_ground(ground, left_base_point(t));
    bool mid_base_point_touching = touches_ground(ground, mid_base_point(t));
    bool right_base_point_touching = touches_ground(ground, right_base_point(t));

    return left_base_point_touching or mid_base_point_touching or right_base_point_touching;
}

/**
 * Given that the tank is touching the ground, is the left side above the ground?
 */
bool left_higher(const tank &t, const terrain &ground)
{
    bool left_base_point_touching = touches_ground(ground, left_base_point(t));
    bool mid_base_point_touching = touches_ground(ground, mid_base_point(t));
    bool right_base_point_touching = touches_ground(ground, right_base_point(t));

    return left_base_point_touching and not mid_base_point_touching and not right_base_point_touching;
}

/**
 * Given that the tank is touching the ground, is the right side above the ground?
 */
bool right_higher(const tank &t, const terrain &ground)
{
    bool left_base_point_touching = touches_ground(ground, left_base_point(t));
    bool mid_base_point_touching = touches_ground(ground, mid_base_point(t));
    bool right_base_point_touching = touches_ground(ground, right_base_point(t));

    return right_base_point_touching and not left_base_point_touching and not mid_base_point_touching;
}

/**
 * The left base point of the tank as visually displayed, including rotation.
 */
point_2d left_base_point(const tank &t)
{
    point_2d lbp;

    if ( t.base_angle >= 0 )
    {
        lbp.x = t.coords.x + TANK_RADIUS - cosine(t.base_angle) * TANK_RADIUS;
        lbp.y = t.coords.y + TANK_RADIUS - sine(t.base_angle) * TANK_RADIUS;
    }
    else
    {
        lbp.x = t.coords.x + TANK_RADIUS - cosine(-t.base_angle) * TANK_RADIUS;
        lbp.y = t.coords.y + TANK_RADIUS + sine(-t.base_angle) * TANK_RADIUS;
    }

    return lbp;
}

/**
 * The mid base point of the tank as visually displayed, including rotation.
 */
point_2d mid_base_point(const tank &t)
{
    line l;
    l.start_point = left_base_point(t);
    l.end_point = right_base_point(t);

    return line_mid_point(l);
}

/**
 * The right base point of the tank as visually displayed, including rotation.
 */
point_2d right_base_point(const tank &t)
{
    point_2d rbp;

    if ( t.base_angle >= 0 )
    {
        rbp.x = t.coords.x + TANK_RADIUS + cosine(t.base_angle) * TANK_RADIUS;
        rbp.y = t.coords.y + TANK_RADIUS + sine(t.base_angle) * TANK_RADIUS;
    }
    else
    {
        rbp.x = t.coords.x + TANK_RADIUS + cosine(-t.base_angle) * TANK_RADIUS;
        rbp.y = t.coords.y + TANK_RADIUS - sine(-t.base_angle) * TANK_RADIUS;
    }

    return rbp;
}

void damage_tank(tank &t, const point_2d coords, int impact_radius)
{
    if ( tank_hit(t, coords, impact_radius) and t.alive )
    {
        int damage = 5 * (TANK_RADIUS + impact_radius - point_point_distance(coords, tank_center(t)));
        if ( damage > 0 )
        {
            t.health -= damage;
        }
        if ( t.health <= 0 )
        {
            destroy_tank(t);
        }
    }
}

/**
 * Does the explosion touch the tank?
 */
bool tank_hit(const tank &t, const point_2d coords, int impact_radius)
{
    circle explosion;
    explosion.center = coords;
    explosion.radius = impact_radius;

    return bitmap_circle_collision(t.bmp, t.coords, explosion);
}

/**
 * Oh no!
 */
void destroy_tank(tank &t)
{
    play_sound_effect("destroy");
    t.health = 0;
    t.alive = false;
    t.clr = COLOR_BLACK;
    fill_circle_on_bitmap(t.bmp, t.clr, TANK_RADIUS, TANK_RADIUS, TANK_RADIUS);
}
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
#include "won_screen.h"
#include "game.h"

// constants
#define WINNER_COPY "WINNER: "
#define WINNER_TEXT_X WINDOW_WIDTH / 2 - 115
#define WINNER_TEXT_Y 30
#define RESTART_COPY "PLAY AGAIN"
#define RESTART_X WINDOW_WIDTH / 2 - 85
#define RESTART_Y 200
#define RESTART_BUTTON_WIDTH 200

// forward declarations
ui_element new_restart_button();
void handle_restart(game &g);

won_screen new_won_screen(const game &g)
{
    won_screen w;
    w.restart = new_restart_button();
    return w;
}

/**
 * creates and returns the less tanks button
 */
ui_element new_restart_button()
{
    ui_element restart_button;

    restart_button.coords.x = RESTART_X;
    restart_button.coords.y = RESTART_Y;
    restart_button.clr = COLOR_BLACK;
    restart_button.bmp = create_bitmap("play", RESTART_BUTTON_WIDTH, BIG_FONT_SIZE);

    // this increases the hitbox for clicks
    fill_rectangle_on_bitmap(restart_button.bmp, BACKGROUND_COLOR, 0, 0,
                             RESTART_BUTTON_WIDTH, BIG_FONT_SIZE);

    draw_text_on_bitmap(restart_button.bmp, RESTART_COPY, restart_button.clr,
                        TEXT_FONT, BIG_FONT_SIZE, 0, 0);
    setup_collision_mask(restart_button.bmp);

    return restart_button;
}

bool game_won(const game &g)
{
    int alive = 0;

    for ( int i = 0; i < g.tanks.size(); i++ )
    {
        if ( g.tanks[i].alive )
        {
            alive++;
        }
    }

    return alive == 1;
}

void win_game(game &g)
{
    for ( int i = 0; i < g.tanks.size(); i++ )
    {
        if ( g.tanks[i].alive )
        {
            g.active_tank = &(g.tanks[i]);
        }
    }

    play_sound_effect("win");
    g.state = WON;
}

void handle_won_screen_input(game &g)
{
    handle_restart(g);
}

void draw_won_screen(const game &g)
{
    draw_text(WINNER_COPY + g.active_tank->name, g.active_tank->clr, TEXT_FONT,
              BIG_FONT_SIZE, WINNER_TEXT_X, WINNER_TEXT_Y);
    draw_ui_element(g.won_ui.restart);
}

/**
 * Reset game state to the initial menu screen state.
 */
void handle_restart(game &g)
{
    if ( clicked_on(g.won_ui.restart) )
    {
        stop_music();
        play_sound_effect("click");
        g = new_game();
    }
}
