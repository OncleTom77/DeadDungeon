//
//  structures.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 26/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef DeadDungeon_structures_h
#define DeadDungeon_structures_h

#define WIDTH               640
#define HEIGHT              640
#define WIDTH_TILES         32
#define HEIGHT_TILES        32

#define NMAXPLAYER          2
#define NMAXMONSTER         10
#define MAX_BALL            20
#define MOVE_MAX            2
#define NMAXLEVEL           6

#define WIDTH_PLAYER        32
#define HEIGHT_PLAYER       48
#define DEFAULT_MOVEMENT    30
#define DEFAULT_ATTACK      35

#define WIDTH_BALL          16
#define HEIGHT_BALL         16

#define ELEMENTARY_SPEED    8

#define TIME_INVINCIBLE     1500
#define DEFAULT_WAITING     50

#define TITLE   "DeadDungeon"

typedef struct Node
{
    int             x;
    int             y;
    int             f;
    int             g;
    int             h;
    int             parent_x;
    int             parent_y;
    
}Node;


typedef struct Liste
{
    //Structure for the pathfinder, corresponding to the map cases
    Node            element;
    struct Liste    *next;
    
}Liste;


typedef struct Position
{
    SDL_Rect        rect;

    unsigned short  direction_global;
    unsigned short  direction_up;
    unsigned short  direction_down;
    unsigned short  direction_left;
    unsigned short  direction_right;
    
} Position;


typedef struct CharTexture
{
    SDL_Texture     *up[9];
    SDL_Texture     *down[9];
    SDL_Texture     *left[9];
    SDL_Texture     *right[9];
    SDL_Texture     *invincible;
    
} CharTexture;


typedef struct Controls
{
    int             keyUp;
    int             keyDown;
    int             keyLeft;
    int             keyRight;
    
    int             spell;
    
} Controls;


typedef struct Status
{
    unsigned short  life;
    unsigned short  nbSpellCast;
    
} Status;

typedef struct Ball
{
    unsigned short  direction[MAX_BALL];
    unsigned short  nb_ball;
    
    SDL_Rect        pos_ball[MAX_BALL];
    
    SDL_Texture     *text_ball;
    
}Ball;

typedef struct Monster
{
    Position        position;
    CharTexture     charTexture;
    
    //Status of the monster (life, number of spell cast, attack strenght, ....)
    Status          status;
    
    Ball            ball;
    
    int             next_moves[MOVE_MAX][2];
    unsigned short  nb_move;
    unsigned        time_act;
    unsigned        time_prec;
    unsigned short  max_move;
    unsigned short  counter;
    unsigned short  id_monster;
    
}Monster;


typedef struct Player
{
    Position        position;
    
    //Contain the textures of the player to draw
    CharTexture     charTexture;
    
    //Status of the player (life, number of spell cast, attack strenght, ....)
    Status          status;
    
    //Define wich key has to be press to interact with the game
    Controls        controls;
    
    //Define if a key has been pressed during the current cycle of the game
    Controls        controlsStatus;
    
    Ball            ball;
    
    unsigned short  id_player;
    
    int             movement_speed;
    unsigned        time_prec_movement;
    unsigned        time_act_movement;
    
    int             attack_speed;
    unsigned        time_prec_attack;
    unsigned        time_act_attack;
    
    unsigned        start_invincible;
    unsigned        end_invincible;
    
} Player;


typedef struct Maps
{
    unsigned short  room[HEIGHT/HEIGHT_TILES][WIDTH/WIDTH_TILES];
    unsigned short  lines;
    unsigned short  columns;
    char            cur_map[50];
    
}Maps;


typedef struct Edit
{
    unsigned short  select_item;
    
    SDL_Texture     *text_rock;
    SDL_Texture     *text_water;
    SDL_Texture     *text_wall;
    SDL_Texture     *text_opened_door;
    SDL_Texture     *text_closed_door;
    SDL_Texture     *text_object;
    
    SDL_Texture     *text_health_globe;
    SDL_Texture     *text_inc_movement_speed;
    SDL_Texture     *text_inc_attack_speed;
    
}Edit;


typedef struct Input
{
    unsigned short  edit_menu;
    unsigned short  play_menu;
    unsigned short  pause_menu;
    unsigned short  multiplayer_menu;
    unsigned short  rock;
    unsigned short  water;
    unsigned short  wall;
    unsigned short  closed_door;
    unsigned short  opened_door;
    unsigned short  object;
    unsigned short  save;
    unsigned short  monster;
    unsigned short  pressed_mouse_left;
    unsigned short  pressed_mouse_right;
    unsigned short  event_button_x;
    unsigned short  event_button_y;
    
}Input;


typedef struct Menu
{
    unsigned short  menu_type;
    unsigned short  multiplayer;
    unsigned short  multiplayer_mode;
    
}Menu;


typedef struct Window
{
    SDL_Window      *screen;
    SDL_Renderer    *renderer;
    
    
    SDL_Texture     *text_background;
    SDL_Texture     *text_menu_screen;
    SDL_Texture     *text_multiplayer_screen;
    SDL_Texture     *text_end_screen;
    SDL_Texture     *text_edit_screen;
    SDL_Texture     *text_pause_screen;
    SDL_Texture     *text_game_over_screen;
    SDL_Texture     *text_end_game_screen;
    
    
    SDL_Rect        pos_background;
    
    TTF_Font        *write_police;
    SDL_Color       write_color;
    SDL_Surface     *write_surf;
    SDL_Texture     *write_text;
    SDL_Rect        write_pos;
    char            char_text[200];
    
}Window;


typedef struct Global
{
    Window          window;
    
    Menu            menu;
    Input           input;
    Edit            edit;
    Maps            maps;
    
    Player          players[NMAXPLAYER];
    Monster         monsters[NMAXMONSTER];
    
    unsigned short  nb_monsters;
    unsigned short  level;

} Global;

#endif
