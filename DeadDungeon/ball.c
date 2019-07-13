//
//  ball.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 24/11/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file controls the balls.
 *
*/

#include "includes.h"


/*
 * This function controls the balls. It creates balls and controls its movement.
 *
*/
void create_ball_monster(Global *global, Monster *monster, Ball *ball, int direction)
{
    
    switch(direction)
    {
        case UP:
            
            break;
            
        case DOWN:
            
            break;
            
        case LEFT:
            
            break;
            
        case RIGHT:
            
            break;
    }
    
    ball->nb_ball++;
}


/*
 * This function creates balls if the player pressed the concernig touch.
 *
*/
void ball_input(Global *global, Player *player, Ball *ball)
{
    if(player->controlsStatus.spell)
    {
        if(ball->nb_ball < MAX_BALL)
        {
            switch(player->position.direction_global)
            {
                case UP:
                    if(global->maps.room[player->position.rect.y/HEIGHT_TILES][player->position.rect.x/WIDTH_TILES] == VIDE)
                    {
                        ball->direction[ball->nb_ball] = UP;
                        ball->pos_ball[ball->nb_ball].x = player->position.rect.x;
                        ball->pos_ball[ball->nb_ball].y = player->position.rect.y - HEIGHT_BALL;
                    }
                    else
                        ball->nb_ball--;
                    break;
                    
                case DOWN:
                    ball->direction[ball->nb_ball] = DOWN;
                    ball->pos_ball[ball->nb_ball].x = player->position.rect.x;
                    ball->pos_ball[ball->nb_ball].y = player->position.rect.y + HEIGHT_PLAYER;
                    break;
                    
                case LEFT:
                    ball->direction[ball->nb_ball] = LEFT;
                    ball->pos_ball[ball->nb_ball].x = player->position.rect.x - WIDTH_BALL;
                    ball->pos_ball[ball->nb_ball].y = player->position.rect.y + HEIGHT_PLAYER/2 - HEIGHT_BALL/2;
                    break;
                    
                case RIGHT:
                    ball->direction[ball->nb_ball] = RIGHT;
                    ball->pos_ball[ball->nb_ball].x = player->position.rect.x + WIDTH_PLAYER;
                    ball->pos_ball[ball->nb_ball].y = player->position.rect.y + HEIGHT_PLAYER/2 - HEIGHT_BALL/2;
                    break;
            }
            
            ball->nb_ball++;
        }
    }
}


/*
 * This function moves all the balls in the window, according the direction.
 *
*/
void move_ball(Global *global, Ball *ball)
{
    int i;
    
    for(i=0; i<ball->nb_ball; i++)
    {
        switch(ball->direction[i])
        {
            case UP:
                ball->pos_ball[i].y -= ELEMENTARY_SPEED;
                break;
                
            case DOWN:
                ball->pos_ball[i].y += ELEMENTARY_SPEED;
                break;
                
            case LEFT:
                ball->pos_ball[i].x -= ELEMENTARY_SPEED;
                break;
                
            case RIGHT:
                ball->pos_ball[i].x += ELEMENTARY_SPEED;
                break;
        }
    }
}


/*
 * This file controls if 2 rects are being in contact.
 *
*/
int areTouching(SDL_Rect *r1, SDL_Rect *r2)
{
    if((r1->x <= r2->x) && (r1->x+r1->w >= r2->x))
        if((r1->y <= r2->y) && (r1->y+r1->h >= r2->y))
            return 1;
    
    if((r2->x <= r1->x) && (r2->x+r2->w >= r1->x))
        if((r1->y <= r2->y) && (r1->y+r1->h >= r2->y))
            return 1;
    
    if((r2->x <= r1->x) && (r2->x+r2->w >= r1->x))
        if((r2->y <= r1->y) && (r2->y+r2->h >= r1->y))
            return 1;
    
    if((r1->x <= r2->x) && (r1->x+r1->w >= r2->x))
        if((r2->y <= r1->y) && (r2->y+r2->h >= r1->y))
            return 1;
    
    return 0;
}


/*
 * This function controls the collision between the balls of the player, the environment, the other player and the monsters.
 *
*/
void compute_ball_collision(Global *global, Player* player)
{
    int i, j, k, touch = 0, random_nb;
    SDL_Rect rect_player, rect_ball;
    
    for(i=0; i<player->ball.nb_ball; i++)
    {
        touch = 0;
        
        rect_ball = player->ball.pos_ball[i];
        rect_ball.w -= 1;
        rect_ball.h -= 1;
        
        //Check if the ball touch a rock or water and control if the ball is out of the window
        if(gestion_collisions(global, &player->ball.pos_ball[i], player->ball.direction[i], IS_BALL, 0))
            touch = 1;
        else
        {
            //Check if the ball touch a monster
            for(j=0; j<global->nb_monsters; j++)
            {
                rect_player.x = global->monsters[j].position.rect.x;
                rect_player.y = global->monsters[j].position.rect.y + 32;
                rect_player.w = global->monsters[j].position.rect.w - 1;
                rect_player.h = global->monsters[j].position.rect.h - 33;
                
                if(areTouching(&rect_ball, &rect_player))
                {
                    global->monsters[j].status.life -= 10;
                    touch = 1;
                    
                    //Delete the monster if it is dead
                    if(global->monsters[j].status.life <= 0)
                    {
                        //Control the appearance of potion when a monster die (probability of 1/5)
                        random_nb = rand()%5;
                        if(random_nb == 0)
                        {
                            global->maps.room[rect_player.y/HEIGHT_TILES][rect_player.x/WIDTH_TILES] = HEALTH_GLOBE;
                        }
                        
                        for(k=j; k<global->nb_monsters-1; k++)
                            global->monsters[k] = global->monsters[k+1];
                        
                        j--;
                        global->nb_monsters--;
                    }
                }
            }
            
            rect_player.x = global->players[0].position.rect.x;
            rect_player.y = global->players[0].position.rect.y+32;
            rect_player.w = global->players[0].position.rect.w;
            rect_player.h = global->players[0].position.rect.h-32;
            
            //Check if the ball touch the main player
            if(areTouching(&rect_ball, &rect_player) && player->id_player != global->players[0].id_player && global->menu.multiplayer_mode == PVP)
            {
                global->players[0].status.life -= 10;
                touch = 1;
            }
            
            if(global->menu.multiplayer == 1 && global->menu.multiplayer_mode == PVP)
            {
                rect_player.x = global->players[1].position.rect.x;
                rect_player.y = global->players[1].position.rect.y+32;
                rect_player.w = global->players[1].position.rect.w;
                rect_player.h = global->players[1].position.rect.h-32;
                
                //Check if the ball touch the second player
                if(areTouching(&rect_ball, &rect_player) && player->id_player != global->players[1].id_player)
                {
                    global->players[1].status.life -= 10;
                    touch = 1;
                }
            }
        }
        
        if(touch == 1)
        {
            //If the ball is out of the window or touch something, we delete this ball
            for(j=i; j<player->ball.nb_ball-1; j++)
            {
                player->ball.pos_ball[j].x = player->ball.pos_ball[j+1].x;
                player->ball.pos_ball[j].y = player->ball.pos_ball[j+1].y;
            
                player->ball.direction[j] = player->ball.direction[j+1];
            }
        
            i--;
            player->ball.nb_ball--;
        }
    }
}
