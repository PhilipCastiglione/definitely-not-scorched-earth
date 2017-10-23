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
