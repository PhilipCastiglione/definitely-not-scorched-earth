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
