//
//  editor.c
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

/*
 * This function unlocks the door if there is not monster alive in the map.
 *
*/
void unlock_door(Global* global)
{
    int i;
    
    for(i=0; i<global->maps.columns; i++)
    {
        if(global->maps.room[1][i] == CLOSED)
            global->maps.room[1][i] = OPENED;
    }
}


/*
 * This function loads the map for the game and for the editor.
 *
*/
int load_map(Global *global)
{
    FILE* fichier = NULL;
    int i=0, j=0;
    char lines_fichier[(HEIGHT/HEIGHT_TILES)*(WIDTH/WIDTH_TILES)+1] = {0};

    fichier = fopen(global->maps.cur_map, "r");
    if(fichier == NULL)
        return 0;

    fgets(lines_fichier, (global->maps.lines*global->maps.columns)+1, fichier);
    
    printf("%c\n", lines_fichier[0]);
    
    for(i=0; i<global->maps.lines; i++)
    {
        for(j=0; j<global->maps.columns; j++)
        {
            switch(lines_fichier[(i*global->maps.lines)+j])
            {
                case '0':
                    global->maps.room[i][j] = VIDE;
                    break;

                case '1':
                    global->maps.room[i][j] = ROCK;
                    break;

                case '2':
                    global->maps.room[i][j] = WATER;
                    break;
                
                case '3':
                    global->maps.room[i][j] = MONSTER;
                    break;
                    
                case '4':
                    global->maps.room[i][j] = WALL;
                    break;
                
                case '5':
                    global->maps.room[i][j] = OPENED;
                    break;
                    
                case '6':
                    global->maps.room[i][j] = CLOSED;
                    break;
                    
                case '7':
                    global->maps.room[i][j] = OBJECT;
                    break;
                    
            }
        }
    }

    fclose(fichier);

    return 1;
}



int save_map(Global *global)
{
    FILE* fichier = NULL;
    int i=0, j=0;

    fichier = fopen(global->maps.cur_map, "w");
    if(fichier == NULL)
        return 0;

    for(i=0; i<global->maps.lines; i++)
    {
        for(j=0; j<global->maps.columns; j++)
        {
            fprintf(fichier, "%d", global->maps.room[i][j]);
        }
    }

    fclose(fichier);

    return 1;
}

void edit_inputs(Global *global)
{
    int reste, carte_x, carte_y;

    if(global->input.rock)
        global->edit.select_item = ROCK;
    else if(global->input.water)
        global->edit.select_item = WATER;
    else if(global->input.monster)
        global->edit.select_item = MONSTER;
    else if(global->input.wall)
        global->edit.select_item = WALL;
    else if(global->input.opened_door)
        global->edit.select_item = OPENED;
    else if(global->input.closed_door)
        global->edit.select_item = CLOSED;
    else if(global->input.object)
        global->edit.select_item = OBJECT;
    
    if(global->input.save)
        save_map(global);

    if(global->input.pressed_mouse_left || global->input.pressed_mouse_right)
    {
        reste = global->input.event_button_x%WIDTH_TILES;
        carte_x = (global->input.event_button_x - reste)/WIDTH_TILES;

        reste = global->input.event_button_y%HEIGHT_TILES;
        carte_y = (global->input.event_button_y - reste)/HEIGHT_TILES;

        if(global->input.pressed_mouse_left)
        {
            switch(global->edit.select_item)
            {
                case ROCK:
                    global->maps.room[carte_y][carte_x] = ROCK;
                    break;

                case WATER:
                    global->maps.room[carte_y][carte_x] = WATER;
                    break;
                
                case MONSTER:
                    global->maps.room[carte_y][carte_x] = MONSTER;
                    break;
                    
                case WALL:
                    global->maps.room[carte_y][carte_x] = WALL;
                    break;
                
                case OPENED:
                    global->maps.room[carte_y][carte_x] = OPENED;
                    break;
                    
                case CLOSED:
                    global->maps.room[carte_y][carte_x] = CLOSED;
                    break;
                    
                case OBJECT:
                    global->maps.room[carte_y][carte_x] = OBJECT;
            }
        }
        else
            global->maps.room[carte_y][carte_x] = VIDE;
    }
}
