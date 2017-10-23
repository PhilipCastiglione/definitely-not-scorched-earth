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
