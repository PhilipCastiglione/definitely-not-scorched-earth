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
