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
