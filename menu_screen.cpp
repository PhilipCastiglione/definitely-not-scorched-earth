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
