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
