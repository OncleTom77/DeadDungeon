//
//  init.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file initializes the variables of the game
 *
*/

#include "includes.h"

/*
 * This function reinitializes the variables concerning the monsters, when the user returns to the menu
 *
*/
void reinit_vars(Global* global)
{
    int i, j;
    
    for(i=0; i<global->nb_monsters; i++)
    {
        //Init the position of the monsters
        global->monsters[i].position.rect.w             = WIDTH_PLAYER;
        global->monsters[i].position.rect.h             = HEIGHT_PLAYER;
        global->monsters[i].position.direction_global   = DOWN;
        global->monsters[i].position.direction_up       = 0;
        global->monsters[i].position.direction_down     = 0;
        global->monsters[i].position.direction_left     = 0;
        global->monsters[i].position.direction_right    = 0;
        
        global->monsters[i].nb_move                     = 0;
        global->monsters[i].max_move                    = 0;
        global->monsters[i].counter                     = 0;
        
        global->monsters[i].time_prec = 0;
        
        for(j=0; j<4; j++)
        {
            global->monsters[i].next_moves[j][0]        = 0;
            global->monsters[i].next_moves[j][1]        = 0;
        }
        
        //Init the game status of the monsters
        global->monsters[i].status.life                 = 100;
        
        //Init the ball status for the monsters
        for(j=0; j<MAX_BALL; j++)
        {
            global->monsters[i].ball.pos_ball[j].w      = WIDTH_BALL;
            global->monsters[i].ball.pos_ball[j].h      = HEIGHT_BALL;
            
            global->monsters[i].ball.pos_ball[j].x      = 0;
            global->monsters[i].ball.pos_ball[j].y      = 0;
            
            global->monsters[i].ball.nb_ball            = 0;
        }
    }
}

/*
 *This function initializes all the variables of the game, when the game is launched
 *
*/
 void init_vars(Global *global)
{
    int i, j;
    
    srand(time(NULL));
    
    for(i=0; i<NMAXPLAYER; i++)
    {
        ///Init the position of the players
        global->players[i].position.rect.w              = WIDTH_PLAYER;
        global->players[i].position.rect.h              = HEIGHT_PLAYER;
        global->players[i].position.direction_global    = DOWN;
        global->players[i].position.direction_up        = 0;
        global->players[i].position.direction_down      = 0;
        global->players[i].position.direction_left      = 0;
        global->players[i].position.direction_right     = 0;
        
        //Init by default the control status of the players
        global->players[i].controlsStatus.keyDown       = 0;
        global->players[i].controlsStatus.keyUp         = 0;
        global->players[i].controlsStatus.keyLeft       = 0;
        global->players[i].controlsStatus.keyRight      = 0;
        global->players[i].controlsStatus.spell         = 0;
        
        global->players[i].id_player                    = i;
        
        //Init the game status of the players
        global->players[i].status.life                  = 100;
        
        global->players[i].movement_speed               = DEFAULT_MOVEMENT;
        global->players[i].attack_speed                 = DEFAULT_ATTACK;
        
        global->players[i].time_prec_movement           = 0;
        global->players[i].time_prec_attack             = 0;
        global->players[i].start_invincible             = 0;
        
        //Init the ball status for the players
        for(j=0; j<MAX_BALL; j++)
        {
            global->players[i].ball.pos_ball[j].w       = WIDTH_BALL;
            global->players[i].ball.pos_ball[j].h       = HEIGHT_BALL;
            
            global->players[i].ball.pos_ball[j].x       = 0;
            global->players[i].ball.pos_ball[j].y       = 0;
            
            global->players[i].ball.nb_ball             = 0;
        }
    }
    
    for(i=0; i<NMAXMONSTER; i++)
    {
        //Init the position of the monsters
        global->monsters[i].position.rect.w             = WIDTH_PLAYER;
        global->monsters[i].position.rect.h             = HEIGHT_PLAYER;
        global->monsters[i].position.direction_global   = DOWN;
        global->monsters[i].position.direction_up       = 0;
        global->monsters[i].position.direction_down     = 0;
        global->monsters[i].position.direction_left     = 0;
        global->monsters[i].position.direction_right    = 0;
        
        global->monsters[i].nb_move                     = 0;
        global->monsters[i].max_move                    = 0;
        global->monsters[i].counter                     = 0;
        
        global->monsters[i].time_prec = 0;
        
        for(j=0; j<4; j++)
        {
            global->monsters[i].next_moves[j][0]        = 0;
            global->monsters[i].next_moves[j][1]        = 0;
        }
        
        //Init the game status of the monsters
        global->monsters[i].status.life                 = 100;
        
        //Init the ball status for the monsters
        for(j=0; j<MAX_BALL; j++)
        {
            global->monsters[i].ball.pos_ball[j].w      = WIDTH_BALL;
            global->monsters[i].ball.pos_ball[j].h      = HEIGHT_BALL;
            
            global->monsters[i].ball.pos_ball[j].x      = 0;
            global->monsters[i].ball.pos_ball[j].y      = 0;
            
            global->monsters[i].ball.nb_ball            = 0;
        }
    }

    //Init by default the tile of the map
    for(i=0; i<HEIGHT/HEIGHT_TILES; i++)
        for(j=0; j<WIDTH/WIDTH_TILES; j++)
            global->maps.room[i][j]                     = VIDE;

    global->maps.lines                                  = HEIGHT/HEIGHT_TILES;
    global->maps.columns                                = WIDTH/WIDTH_TILES;

    global->window.pos_background.x                     = 0;
    global->window.pos_background.y                     = 0;
    global->window.pos_background.w                     = WIDTH;
    global->window.pos_background.h                     = HEIGHT;

    global->window.write_text = NULL;
    
    global->menu.menu_type                              = MENU;
    global->edit.select_item                            = ROCK;

    //Init the controls of the players
    global->players[0].controls.keyUp                   = SDLK_UP;
    global->players[0].controls.keyDown                 = SDLK_DOWN;
    global->players[0].controls.keyLeft                 = SDLK_LEFT;
    global->players[0].controls.keyRight                = SDLK_RIGHT;
    global->players[0].controls.spell                   = SDLK_m;
    
    global->players[1].controls.keyUp                   = SDLK_z;
    global->players[1].controls.keyDown                 = SDLK_s;
    global->players[1].controls.keyLeft                 = SDLK_q;
    global->players[1].controls.keyRight                = SDLK_d;
    global->players[1].controls.spell                   = SDLK_g;
    
    global->nb_monsters = 0;
    global->level = 1;
    
    sprintf(global->maps.cur_map, "maps/level_%d.txt", global->level);
}

/*
 * It initializes the SDL to run the game. I creates the window and load the textures.
 *
*/
void init_SDL(Global *global)
{
    int i, j;
    char chemin[50] = {0};

    SDL_Surface *surf_temp;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr,"Échec de l'initialisation de la SDL : %s\n",SDL_GetError());
        exit(0);
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(0);
    }

    global->window.screen = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT+HEIGHT_TILES, SDL_WINDOW_SHOWN);

    if(global->window.screen == NULL)
    {
        fprintf(stderr,"Échec de l'initialisation de la fenetre de la SDL (%s)\n",SDL_GetError());
        exit(0);
    }
    
    global->window.renderer = SDL_CreateRenderer(global->window.screen, -1, SDL_RENDERER_ACCELERATED);
    if(global->window.renderer == NULL)
    {
        fprintf(stderr,"Échec de l'initialisation du rendu de la SDL (%s)\n",SDL_GetError());
        exit(0);
    }
    
    SDL_SetRenderDrawColor(global->window.renderer, 255, 255, 255, 255);

    ///TTF
    global->window.write_police = TTF_OpenFont("arial.ttf", 17);
    if(global->window.write_police == NULL)
    {
        fprintf(stderr, "Erreur de chargement de la police d'ecriture : %s\n", TTF_GetError());
        exit(0);
    }

    global->window.write_color.r = 0;
    global->window.write_color.g = 0;
    global->window.write_color.b = 0;
    global->window.write_color.a = 255;
    
    
    //------------------------------- MENU TEXTURES -------------------------------
    
    
    //Load the pictures
    surf_temp = SDL_LoadBMP("images/fond.bmp");
    //Create textures with pictures
    global->window.text_background = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/ecran_menu.png");
    global->window.text_menu_screen = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/ecran_multijoueurs.png");
    global->window.text_multiplayer_screen = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/ecran_fin.png");
    global->window.text_end_screen = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/ecran_edit.png");
    global->window.text_edit_screen = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/ecran_pause.png");
    global->window.text_pause_screen = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/game_over.png");
    global->window.text_game_over_screen = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/end_game.png");
    global->window.text_end_game_screen = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    
    
    //----------------------------- EDITION TEXTURES -----------------------------
    
    
    surf_temp = IMG_Load("images/rock.png");
    global->edit.text_rock = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/water.png");
    global->edit.text_water = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/wall.png");
    global->edit.text_wall = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/opened_door.png");
    global->edit.text_opened_door = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/closed_door.png");
    global->edit.text_closed_door = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/object.png");
    global->edit.text_object = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/health_globe.png");
    global->edit.text_health_globe = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/inc_movement_speed.png");
    global->edit.text_inc_movement_speed = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    surf_temp = IMG_Load("images/inc_attack_speed.png");
    global->edit.text_inc_attack_speed = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    
    
    //-------------------------- MAIN CHARACTER TEXTURES --------------------------
    
    
    for(i=0; i<9; i++)
    {
        sprintf(chemin, "images/moine/move/haut/haut_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[0].charTexture.up[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
        
        sprintf(chemin, "images/moine/move/bas/bas_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[0].charTexture.down[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
            
        sprintf(chemin, "images/moine/move/gauche/gauche_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[0].charTexture.left[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
            
        sprintf(chemin, "images/moine/move/droite/droite_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[0].charTexture.right[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    }
    
    surf_temp = IMG_Load("images/ball.png");
    global->players[0].ball.text_ball = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    
    surf_temp = IMG_Load("images/moine/invincible.png");
    global->players[0].charTexture.invincible = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    
    
    //------------------------- SECOND CHARACTER TEXTURES -------------------------
    
    
    for(i=0; i<9; i++)
    {
        sprintf(chemin, "images/skeleton/move/haut/haut_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[1].charTexture.up[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
        
        sprintf(chemin, "images/skeleton/move/bas/bas_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[1].charTexture.down[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
        
        sprintf(chemin, "images/skeleton/move/gauche/gauche_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[1].charTexture.left[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
        
        sprintf(chemin, "images/skeleton/move/droite/droite_%d.png", i+1);
        surf_temp = IMG_Load(chemin);
        global->players[1].charTexture.right[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    }
    
    surf_temp = IMG_Load("images/blueball.png");
    global->players[1].ball.text_ball = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    
    surf_temp = IMG_Load("images/skeleton/invincible.png");
    global->players[1].charTexture.invincible = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
    
    
    //----------------------------- MONSTERS TEXTURES -----------------------------
    
    
    for(j=0;j<NMAXMONSTER;j++)
    {
        surf_temp = IMG_Load("images/blueball.png");
        global->monsters[j].ball.text_ball = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
        
        surf_temp = IMG_Load("images/skeleton/invincible.png");
        global->monsters[j].charTexture.invincible = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
        
        for(i=0; i<9; i++)
        {
            sprintf(chemin, "images/skeleton/move/haut/haut_%d.png", i+1);
            surf_temp = IMG_Load(chemin);
            global->monsters[j].charTexture.up[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
            
            sprintf(chemin, "images/skeleton/move/bas/bas_%d.png", i+1);
            surf_temp = IMG_Load(chemin);
            global->monsters[j].charTexture.down[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
            
            sprintf(chemin, "images/skeleton/move/gauche/gauche_%d.png", i+1);
            surf_temp = IMG_Load(chemin);
            global->monsters[j].charTexture.left[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
            
            sprintf(chemin, "images/skeleton/move/droite/droite_%d.png", i+1);
            surf_temp = IMG_Load(chemin);
            global->monsters[j].charTexture.right[i] = SDL_CreateTextureFromSurface(global->window.renderer, surf_temp);
        }
    }
    
    
    //Destruction of the temp surface
    SDL_FreeSurface(surf_temp);
}
