//
//  Header.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 26/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef DeadDungeon_Header_h
#define DeadDungeon_Header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
///#include <SDL2/SDL_image.h> WINDOWS
///#include <SDL2/SDL_ttf.h> WINDOWS
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "structures.h"
#include "init.h"
#include "menu.h"
#include "input.h"
#include "editor.h"
#include "play.h"
#include "ball.h"
#include "ia_monster.h"
#include "draw.h"
#include "listes.h"
#include "fin.h"

/*
 * This enum serves for the direction of the entities.
 *
*/
enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};


/*
 * This enum serves for the type of the tiles on the map.
 *
*/
enum
{
    VIDE,
    ROCK,
    WATER,
    MONSTER,
    WALL,
    OPENED,
    CLOSED,
    OBJECT,
    HEALTH_GLOBE,
    INC_MOVEMENT_SPEED,
    INC_ATTACK_SPEED
    
};


/*
 * This enum serves for the menu type.
 *
*/
enum
{
    MENU,
    MULTIPLAYER,
    PAUSE,
    PLAY,
    EDIT,
    GAME_OVER,
    END_GAME
};


/*
 * This enum serves to detect the type of the entity.
 *
*/
enum
{
    IS_PLAYER,
    IS_MONSTER,
    IS_BALL
};


/*
 * This enum serves to detect the type of the multiplayers menu.
 *
*/
enum
{
    NO_MODE,
    COOPERATIVE,
    PVP
};

#endif
