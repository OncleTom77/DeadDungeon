//
//  ia_monster.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 15/11/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file controls the movement of the monsters
 *
*/

#include "includes.h"


/*
 * This function moves the monster if it is possible.
 *
*/
void move_monster(Global *global, Monster* monster, int direction)
{
    int test;
    
    switch(direction)
    {
        case UP:
            if(monster->position.direction_global != UP)
            {
                monster->position.direction_global = UP;
                monster->position.direction_down = 0;
                monster->position.direction_left = 0;
                monster->position.direction_right = 0;
            }
            else
                monster->position.direction_up++;
            
            test = gestion_collisions(global, &monster->position.rect, monster->position.direction_global, IS_MONSTER, 0);
        
            if(test != 1 || test != 2)
                monster->position.rect.y -= ELEMENTARY_SPEED;

            break;
            
        case DOWN:
            if(monster->position.direction_global != DOWN)
            {
                monster->position.direction_global = DOWN;
                monster->position.direction_up = 0;
                monster->position.direction_left = 0;
                monster->position.direction_right = 0;
            }
            else
                monster->position.direction_down++;
                
            test = gestion_collisions(global, &monster->position.rect, monster->position.direction_global, IS_MONSTER, 0);
                
            if(test != 1 || test != 2)
                monster->position.rect.y += ELEMENTARY_SPEED;
            
            break;
            
        case LEFT:
            if(monster->position.direction_global != LEFT)
            {
                monster->position.direction_global = LEFT;
                monster->position.direction_up = 0;
                monster->position.direction_down = 0;
                monster->position.direction_right = 0;
            }
            else
                monster->position.direction_left++;
            
            test = gestion_collisions(global, &monster->position.rect, monster->position.direction_global, IS_MONSTER, 0);
            
            if(test != 1 || test != 2)
                monster->position.rect.x -= ELEMENTARY_SPEED;
            
            break;
            
        case RIGHT:
            if(monster->position.direction_global != RIGHT)
            {
                monster->position.direction_global = RIGHT;
                monster->position.direction_up = 0;
                monster->position.direction_down = 0;
                monster->position.direction_left = 0;
            }
            else
                monster->position.direction_right++;
            
            test = gestion_collisions(global, &monster->position.rect, monster->position.direction_global, IS_MONSTER, 0);
            
            if(test != 1 || test != 2)
                monster->position.rect.x += ELEMENTARY_SPEED;
            
            break;
    }
}

/*
 * This function gets the absolute value of a and b
 *
*/
int val_abs(int a, int b)
{
    if(a >= b)
        return a-b;
    else
        return b-a;
}


/*
 * This function controls if two monsters are in contact.
 * It is unused for now.
*/
int touch_monster(Global* global, Monster* monster, int direction)
{
    int i;
    SDL_Rect hitbox_other, hitbox_monster;
    
    //hitbox_monster contains the next position of the current monster in room's table
    hitbox_monster.x = monster->position.rect.x;
    hitbox_monster.y = monster->position.rect.y + 32;
    
    if(direction == UP)
        hitbox_monster.y -= ELEMENTARY_SPEED;
    else if(direction == DOWN)
        hitbox_monster.y += ELEMENTARY_SPEED;
    else if(direction == LEFT)
        hitbox_monster.x -= ELEMENTARY_SPEED;
    else
        hitbox_monster.x += ELEMENTARY_SPEED;
    
    hitbox_monster.x /= WIDTH_TILES;
    hitbox_monster.y /= HEIGHT_TILES;
    
    for(i=0; i<global->nb_monsters; i++)
    {
        if(monster->id_monster != i)
        {
            //hitbox_other contains the position of monsters[i] in room's table
            hitbox_other.x = global->monsters[i].position.rect.x;
            hitbox_other.y = global->monsters[i].position.rect.y + 32;
            
            hitbox_other.x /= WIDTH_TILES;
            hitbox_other.y /= HEIGHT_TILES;
            
            if(hitbox_other.x == hitbox_monster.x && hitbox_other.y == hitbox_monster.y)
                return 0;
        }
    }
    
    return 1;
}


/*
 * This BIG function gets the direction where the monster has to go.
 *
*/
int ia_move(Global *global, Monster* monster)
{
    int direction = 0, i, continuer = 1, index = 0, test_move = 1;
    int xA, yA, xB, yB, xC, yC, x_abs, y_abs, x_abs2, y_abs2;
    SDL_Rect hitbox_player, hitbox_monster, hitbox_second;
    
    
    hitbox_player.x = global->players[0].position.rect.x;
    hitbox_player.y = global->players[0].position.rect.y + 32;
    
    xA = hitbox_player.x/WIDTH_TILES;
    yA = hitbox_player.y/HEIGHT_TILES;
    
    hitbox_monster.x = monster->position.rect.x;
    hitbox_monster.y = monster->position.rect.y + 32;
    
    xB = hitbox_monster.x/WIDTH_TILES;
    yB = hitbox_monster.y/HEIGHT_TILES;
    
    x_abs = val_abs(xA, xB);
    y_abs = val_abs(yA, yB);
    
    
    if(global->menu.multiplayer)
    {
        hitbox_second.x = global->players[1].position.rect.x;
        hitbox_second.y = global->players[1].position.rect.y + 32;
        
        xC = hitbox_second.x/WIDTH_TILES;
        yC = hitbox_second.y/HEIGHT_TILES;
        
        x_abs2 = val_abs(xC, xB);
        y_abs2 = val_abs(yC, yB);
        
        //If the second player is the closest to the monster, the monster tries to attack the second player
        if((x_abs + y_abs) > (x_abs2 + y_abs2))
        {
            x_abs = x_abs2;
            y_abs = y_abs2;
            
            xA = xC;
            yA = yC;
        }
    }
    
    //Try to shoot the player if the situation is suitable
    if(x_abs < 5 && y_abs < 5)
    {
        //printf("Shoot !!\n");
        
        if(y_abs <= x_abs)
        {
            //Shoot over the monster
            if(yB > yA)
            {
            
            }
            //Shoot below the monster
            else
            {
                
            }
        }
        else
        {
            //Shoot to the left of the monster
            if(xB > xA)
            {
                
            }
            //Shoot to the right of the monster
            else
            {
                
            }
        }
    }
    
    monster->counter--;
    
    //x_abs = val_abs(hitbox_player.x, hitbox_monster.y);
    //y_abs = val_abs(hitbox_player.y, hitbox_monster.y);
    
    if(x_abs == 0 && y_abs == 0)
    {
        //printf("STOP !!\n");
        monster->counter = 0;
        monster->nb_move = 0;
        
        return 1;
    }
    
    //The current monster moves 4 times for one direction. After 4 movments, he tries to find a new path and a new direction.
    if(monster->counter%4 != 0)
    {
        test_move = touch_monster(global, monster, monster->position.direction_global);
        
        test_move = 1;
        
        if(test_move)
        {
            //Move the monster in the right direction if it is possible
            move_monster(global, monster, monster->position.direction_global);
        }
        else
        {
            monster->counter = 0;
            monster->nb_move = 0;
        }
        
        return 1;
    }
    
    //Search a new path between the player and the current monster.
    if(monster->nb_move == 0)
    {
        Liste *opened_liste = NULL;
        Liste *closed_liste = NULL;
        Liste *current;
        Liste *temp;
        Node adj_node[4];
        Node *start = malloc(sizeof(*start));
        Node *end_node = malloc(sizeof(*end_node));
        
        //--------------------------- ALGO A* ---------------------------
        
        //printf("xA : %d, yA : %d\n", xA, yA);
        //printf("xB : %d, yB : %d\n", xB, yB);
        
        start->x = xA;
        start->y = yA;
        start->h = get_h(xA, yA, xB, yB);
        start->g = 0;
        start->f = start->g + start->h;
        start->parent_x = -1;
        start->parent_y = -1;
        
        end_node->x = xB;
        end_node->y = yB;
        end_node->h = 0;
        end_node->g = 0;
        end_node->f = 0;
        end_node->parent_x = -1;
        end_node->parent_y = -1;
        
        //Add the starting point to the opened_liste
        insert_into_liste(&opened_liste, *start);
        
        while(opened_liste != NULL)
        {
            //Get the node with the smallest f
            current = get_small_f(opened_liste);
            
            if(current->element.x == end_node->x && current->element.y == end_node->y)
            {
                continuer = 0;
                break;
            }
            
            ///UP square of the current node
            adj_node[0].x = current->element.x;
            adj_node[0].y = current->element.y - 1;
            
            ///DOWN square
            adj_node[1].x = current->element.x;
            adj_node[1].y = current->element.y + 1;
            
            ///LEFT square
            adj_node[2].x = current->element.x - 1;
            adj_node[2].y = current->element.y;
            
            ///RIGHT square
            adj_node[3].x = current->element.x + 1;
            adj_node[3].y = current->element.y;
            
            for(i=0; i<4; i++)
            {
                adj_node[i].g = current->element.g + 1;
                adj_node[i].h = get_h(adj_node[i].x, adj_node[i].y, end_node->x, end_node->y);
                adj_node[i].f = adj_node[i].g + adj_node[i].h;
                adj_node[i].parent_x = current->element.x;
                adj_node[i].parent_y = current->element.y;
                
                if(adj_node[i].x < 0 ||
                   adj_node[i].x >= WIDTH/WIDTH_TILES ||
                   adj_node[i].y < 0 ||
                   adj_node[i].y >= HEIGHT/HEIGHT_TILES ||
                   global->maps.room[adj_node[i].y][adj_node[i].x] == ROCK ||
                   global->maps.room[adj_node[i].y][adj_node[i].x] == WATER ||
                   global->maps.room[adj_node[i].y][adj_node[i].x] == WALL ||
                   global->maps.room[adj_node[i].y][adj_node[i].x] == CLOSED)
                    continue;
                
                //Check if the analized node is in the opened_liste : if there is a node in the opened_liste with the same coordinates as the annalized node
                if(is_in_liste(opened_liste, adj_node[i]))
                {
                    //Search the node with the same coordinates of the analized node
                    index = searchList(opened_liste, adj_node[i]);
                    //Get this node
                    temp = getListeByIndex(opened_liste, index);
                    
                    if(temp->element.f <= adj_node[i].f)
                        continue;
                    
                    //Delete temp from the opened_liste if the analized node has a smallest f than temp
                    delete_from_liste(&opened_liste, temp->element);
                }
                
                //Same thing for the closed_liste
                if(is_in_liste(closed_liste, adj_node[i]))
                {
                    index = searchList(closed_liste, adj_node[i]);
                    temp = getListeByIndex(closed_liste, index);
                    
                    if(temp->element.f <= adj_node[i].f)
                        continue;
                    
                    delete_from_liste(&closed_liste, temp->element);
                }
                
                //Add the analized node to the opened_liste
                insert_into_liste(&opened_liste, adj_node[i]);
            }
            
            //Check if the current node is already in the closed_liste
            if(is_in_liste(closed_liste, current->element))
            {
                index = searchList(closed_liste, current->element);
                temp = getListeByIndex(closed_liste, index);
                
                if(temp->element.f > current->element.f)
                {
                    insert_into_liste(&closed_liste, current->element);
                    delete_from_liste(&closed_liste, temp->element);
                }
            }
            else
                insert_into_liste(&closed_liste, current->element);
            
            //Delete the current node in the opened_liste
            delete_from_liste(&opened_liste, current->element);
        }
        
        if(continuer == 1)
        {
            //printf("Fail to find a path.\n");
            monster->nb_move = 0;
            monster->counter = 1;
            return 0;
        }
        else
        {
            //printf("Path found.\n");
            
            temp = closed_liste;
            
            monster->nb_move = 0;
            
            //Get the N first movements to do for the monster and save them in the "next_moves" array.
            for(i=0; i<MOVE_MAX; i++)
            {
                if(temp == NULL)
                    break;
                
                monster->nb_move++;
                
                monster->next_moves[i][0] = temp->element.x;
                monster->next_moves[i][1] = temp->element.y;
                
                adj_node[0].x = temp->element.parent_x;
                adj_node[0].y = temp->element.parent_y;
                
                if(temp->element.x == xA && temp->element.y == yA)
                    break;
                
                index = searchList(closed_liste, adj_node[0]);
                temp = getListeByIndex(closed_liste, index);
            }
            
            monster->max_move = monster->nb_move;
            
            monster->counter = 4;
        }
        
        free_all_liste(&opened_liste);
        free_all_liste(&closed_liste);
        
        //------------------------- END ALGO A* -------------------------
    }
    
    index = monster->max_move - monster->nb_move;
    
    if(monster->next_moves[index][1] < yB)
        direction = UP;
    else if(monster->next_moves[index][1] > yB)
        direction = DOWN;
    else if(monster->next_moves[index][0] < xB)
        direction = LEFT;
    else if(monster->next_moves[index][0] > xB)
        direction = RIGHT;
    
    //printf("direction : %d\n", direction);
    
    test_move = touch_monster(global, monster, direction);
    test_move = 1;
    
    if(test_move)
    {
        //Move the monster in the right direction if it is possible
        move_monster(global, monster, direction);
        
        monster->nb_move--;
        monster->counter = 4;
    }
    else
    {
        monster->counter = 0;
        monster->nb_move = 0;
    }
    
    return 1;
}
