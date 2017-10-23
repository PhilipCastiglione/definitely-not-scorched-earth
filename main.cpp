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
