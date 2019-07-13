//
//  play.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file controls the editor menu
 *
*/

#include "includes.h"

int check_next_level(Global* global)
{
    int i;
    SDL_Rect hitbox, hitbox_second;
    
    hitbox = global->players[0].position.rect;
    
    hitbox.y += 32;
    
    hitbox.x /= WIDTH_TILES;
    hitbox.y /= HEIGHT_TILES;
    
    if(global->menu.multiplayer)
    {
        hitbox_second = global->players[1].position.rect;
        
        hitbox_second.y += 32;
        
        hitbox_second.x /= WIDTH_TILES;
        hitbox_second.y /= HEIGHT_TILES;
    }
    
    for(i=0; i<global->maps.columns; i++)
    {
        if(global->maps.room[1][i] == OPENED)
        {
            if(hitbox.x == i && hitbox.y == 1)
                return 1;
            
            if(global->menu.multiplayer && hitbox_second.x == i && hitbox_second.y == 1)
                return 1;
        }
    }
    
    return 0;
}

void update_stats(Global* global, Player* player, int case_x, int case_y)
{
    switch(global->maps.room[case_y][case_x])
    {
        case HEALTH_GLOBE:
            if(player->status.life <= 90)
                player->status.life += 10;
            break;
            
        case INC_MOVEMENT_SPEED:
            if(player->movement_speed >= 10)
                player->movement_speed -= 5;
            break;
            
        case INC_ATTACK_SPEED:
            if(player->attack_speed >= 10)
                player->attack_speed -= 5;
            break;
    }
    
    global->maps.room[case_y][case_x] = VIDE;
}

int gestion_collisions(Global *global, SDL_Rect *pos, int direction, int type, int id_player)
{
    int case_x, case_y, reste, fix_ball;
    SDL_Rect hitbox;
    
    fix_ball = (type == IS_BALL) ? 4 : 0;
    
    hitbox.x = pos->x;
    hitbox.y = pos->y;
    hitbox.h = pos->h;
    
    if(type != IS_BALL)
    {
        hitbox.y += 32;
        hitbox.h -= 32;
    }

    //UP or DOWN
    if(direction == UP || direction == DOWN)
    {
        if(direction == UP)
        {
            reste = (hitbox.y - ELEMENTARY_SPEED + fix_ball)%HEIGHT_TILES;
            case_y = (hitbox.y - ELEMENTARY_SPEED - reste + fix_ball)/HEIGHT_TILES;
            
            reste = hitbox.x%WIDTH_TILES;
            case_x = (hitbox.x - reste)/WIDTH_TILES;
            
            if(pos->y - ELEMENTARY_SPEED < 0)
                return 1;
        }
        else
        {
            reste = (pos->y + ELEMENTARY_SPEED + pos->h - 1 - fix_ball)%HEIGHT_TILES;
            case_y = (pos->y + ELEMENTARY_SPEED + pos->h - reste - fix_ball)/HEIGHT_TILES;
            
            reste = pos->x%WIDTH_TILES;
            case_x = (pos->x - reste)/WIDTH_TILES;
            
            if(pos->y + ELEMENTARY_SPEED + pos->h > HEIGHT)
                return 1;
        }
        

        if(global->maps.room[case_y][case_x] == ROCK ||
           global->maps.room[case_y][case_x] == WALL ||
           global->maps.room[case_y][case_x] == CLOSED)
            return 1;
        else if(global->maps.room[case_y][case_x] == WATER)
            return 2;
        else if(type == IS_PLAYER)
        {
            if(global->maps.room[case_y][case_x] != OPENED)
            {
                if(global->maps.room[case_y][case_x] != VIDE)
                {
                    if(id_player == 0)
                        update_stats(global, &global->players[0], case_x, case_y);
                    else
                        update_stats(global, &global->players[1], case_x, case_y);
                    
                    return 0;
                }
            }
        }
        
        case_x += 1;

        //If the object to control is on 2 squares of the map
        if((type != IS_BALL && reste != 0) || (type == IS_BALL && reste == 24))
        {
            if(global->maps.room[case_y][case_x] == ROCK ||
               global->maps.room[case_y][case_x] == WALL ||
               global->maps.room[case_y][case_x] == CLOSED)
                return 1;
            else if(global->maps.room[case_y][case_x] == WATER)
                return 2;
            else if(type == IS_PLAYER)
            {
                if(global->maps.room[case_y][case_x] != OPENED)
                {
                    if(global->maps.room[case_y][case_x] != VIDE)
                    {
                        if(id_player == 0)
                            update_stats(global, &global->players[0], case_x, case_y);
                        else
                            update_stats(global, &global->players[1], case_x, case_y);
                        
                        return 0;
                    }
                }
            }
        }
    }
    else //LEFT or RIGHT
    {
        if(direction == LEFT)
        {
            reste = (pos->x - ELEMENTARY_SPEED + fix_ball)%WIDTH_TILES;
            case_x = (pos->x - ELEMENTARY_SPEED - reste + fix_ball)/WIDTH_TILES;
            
            reste = (hitbox.y)%HEIGHT_TILES;
            case_y = (hitbox.y - reste)/HEIGHT_TILES;
            
            if(pos->x - ELEMENTARY_SPEED < 0)
                return 1;
        }
        else
        {
            reste = (pos->x + ELEMENTARY_SPEED + pos->w - 1)%WIDTH_TILES;
            case_x = (pos->x + ELEMENTARY_SPEED + pos->w - reste)/WIDTH_TILES;
            
            reste = hitbox.y%HEIGHT_TILES;
            case_y = (hitbox.y - reste)/HEIGHT_TILES;
            
            if(pos->x + ELEMENTARY_SPEED + pos->w > WIDTH)
                return 1;
        }

        if(global->maps.room[case_y][case_x] == ROCK ||
           global->maps.room[case_y][case_x] == WALL ||
           global->maps.room[case_y][case_x] == CLOSED)
            return 1;
        else if(global->maps.room[case_y][case_x] == WATER)
            return 2;
        else if(type == IS_PLAYER)
        {
            if(global->maps.room[case_y][case_x] != OPENED)
            {
                if(global->maps.room[case_y][case_x] != VIDE)
                {
                    if(id_player == 0)
                        update_stats(global, &global->players[0], case_x, case_y);
                    else
                        update_stats(global, &global->players[1], case_x, case_y);
                    
                    return 0;
                }
            }
        }
        
        case_y += 1;
        
        //If the object to control is on 2 squares of the map
        if((type != IS_BALL && reste > 16) || (type == IS_BALL && reste == 24))
        {
            if(global->maps.room[case_y][case_x] == ROCK ||
               global->maps.room[case_y][case_x] == WALL ||
               global->maps.room[case_y][case_x] == CLOSED)
                return 1;
            else if(global->maps.room[case_y][case_x] == WATER)
                return 2;
            else if(type == IS_PLAYER)
            {
                if(global->maps.room[case_y][case_x] != OPENED)
                {
                    if(global->maps.room[case_y][case_x] != VIDE)
                    {
                        if(id_player == 0)
                            update_stats(global, &global->players[0], case_x, case_y);
                        else
                            update_stats(global, &global->players[1], case_x, case_y);
                        
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}

void play_inputs(Global *global, Player *player)
{
    int test = 0;

    if(player->controlsStatus.keyUp)
    {
        if(player->position.direction_global != UP)
        {
            player->position.direction_global = UP;
            player->position.direction_down = 0;
            player->position.direction_left = 0;
            player->position.direction_right = 0;
        }
        else
            player->position.direction_up++;
        
        test = gestion_collisions(global, &player->position.rect, player->position.direction_global, IS_PLAYER, player->id_player);

        if(test != 1)
            player->position.rect.y -= ELEMENTARY_SPEED;
    }

    if(player->controlsStatus.keyDown)
    {
        if(player->position.direction_global != DOWN)
        {
            player->position.direction_global = DOWN;
            player->position.direction_up = 0;
            player->position.direction_left = 0;
            player->position.direction_right = 0;
        }
        else
            player->position.direction_down++;
        
        test = gestion_collisions(global, &player->position.rect, player->position.direction_global, IS_PLAYER, player->id_player);

        if(test != 1)
            player->position.rect.y += ELEMENTARY_SPEED;
    }

    if(player->controlsStatus.keyLeft)
    {
        if(player->position.direction_global != LEFT)
        {
            player->position.direction_global = LEFT;
            player->position.direction_up = 0;
            player->position.direction_down = 0;
            player->position.direction_right = 0;
        }
        else
            player->position.direction_left++;
        
        test = gestion_collisions(global, &player->position.rect, player->position.direction_global, IS_PLAYER, player->id_player);

        if(test != 1)
            player->position.rect.x -= ELEMENTARY_SPEED;
    }

    if(player->controlsStatus.keyRight)
    {
        if(player->position.direction_global != RIGHT)
        {
            player->position.direction_global = RIGHT;
            player->position.direction_up = 0;
            player->position.direction_down = 0;
            player->position.direction_left = 0;
        }
        else
            player->position.direction_right++;
        
        test = gestion_collisions(global, &player->position.rect, player->position.direction_global, IS_PLAYER, player->id_player);

        if(test != 1)
            player->position.rect.x += ELEMENTARY_SPEED;
    }
    
    //If the player falls in the water, he loses 50pts of life
    if(test == 2)
    {
        player->position.rect.x = 9*WIDTH_TILES;
        player->position.rect.y = HEIGHT - HEIGHT_PLAYER - HEIGHT_TILES;
        
        player->status.life -= 50;
    }
}

void play(Global *global)
{
    int i, j, waiting_time;
    SDL_Rect hitbox_player, hitbox_monster;
    
    //Draw the background scene
    draw_area(global);
    
    
    //------------------------------------- PLAYERS ------------------------------------------------
    
    
    for(i=0; i<NMAXPLAYER; i++)
    {
        //Control the life of the players
        global->players[i].end_invincible = SDL_GetTicks();
        if(global->players[i].end_invincible - global->players[i].start_invincible > TIME_INVINCIBLE)
        {
            hitbox_player = global->players[i].position.rect;
            hitbox_player.w -= 1;
            hitbox_player.y += 32;
            hitbox_player.h -= 33;
            
            for(j=0; j<global->nb_monsters; j++)
            {
                hitbox_monster = global->monsters[j].position.rect;
                hitbox_monster.w -= 1;
                hitbox_monster.y += 32;
                hitbox_monster.h -= 33;
                
                if(areTouching(&hitbox_monster, &hitbox_player))
                {
                    global->players[i].status.life -= 10;
                    global->players[i].start_invincible = SDL_GetTicks();
                }
            }
        }
        
        //Game over. Try again !
        if(global->players[i].status.life <= 0 || global->players[i].status.life > 200)
        {
            if(global->menu.multiplayer_mode == PVP)
            {
                global->menu.menu_type = END_GAME;
                draw_end_game(global);
            }
            else
            {
                global->menu.menu_type = GAME_OVER;
                draw_game_over(global);
            }
        }
        
        global->players[i].time_act_movement = SDL_GetTicks();
        if(global->players[i].time_act_movement - global->players[i].time_prec_movement >= global->players[i].movement_speed)
        {
            //Read the control status concerning position and modify the status of the player accordingly
            play_inputs(global, &global->players[i]);
            
            global->players[i].time_prec_movement = global->players[i].time_act_movement;
        }
        
        global->players[i].end_invincible = SDL_GetTicks();
        if(global->players[i].end_invincible - global->players[i].start_invincible > TIME_INVINCIBLE)
        {
            //Draw the main character into the global window
            draw_character(&global->window, &global->players[i].position, &global->players[i].charTexture);
        }
        else
            SDL_RenderCopy(global->window.renderer, global->players[i].charTexture.invincible, NULL, &global->players[i].position.rect);
        
        global->players[i].time_act_attack = SDL_GetTicks();
        if(global->players[i].time_act_attack - global->players[i].time_prec_attack >= global->players[i].attack_speed)
        {
            //Move the balls
            move_ball(global, &global->players[i].ball);
            
            global->players[i].time_prec_attack = global->players[i].time_act_attack;
        }
        
        //Read the input concerning the casted spells
        ball_input(global, &global->players[i], &global->players[i].ball);
        
        //Control the collision between the balls and the players and the map
        compute_ball_collision(global, &global->players[i]);
        
        //Draw the balls
        draw_ball(global, &global->players[i].ball);
        
        //If the multiplayer mode is not selected, break
        if(!global->menu.multiplayer)
            break;
    }
    
    
    //------------------------------------ MONSTERS ------------------------------------------------
    
    
    //Draw the different monsters
    for(i=0; i<global->nb_monsters; i++)
    {
        waiting_time = DEFAULT_WAITING - i*7;
        if(waiting_time <= 20)
            waiting_time = 20;
        
        global->monsters[i].time_act = SDL_GetTicks();
        if(global->monsters[i].time_act - global->monsters[i].time_prec >= waiting_time)
        {
            //Control the movement of the AI characters
            ia_move(global, &global->monsters[i]);
            
            global->monsters[i].time_prec = global->monsters[i].time_act;
        }
        
        //Draw the monster
        draw_character(&global->window, &global->monsters[i].position, &global->monsters[i].charTexture);
    }
}
