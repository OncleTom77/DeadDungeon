//
//  menu.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file controls the start-up of the different section, according with the variables modify with the keyboard inputs.
 *
*/

#include "includes.h"

/*
 * It is called when the game load a map. If the case of the map is an object, the function loads a real object, randomly
 *
*/
int get_random_object()
{
    int number, object = 0;
    
    number = rand()%10;
    
    if(number < 5)
        object = INC_MOVEMENT_SPEED;
    else if(number < 10)
        object = INC_ATTACK_SPEED;
    
    return object;
}


/*
 * This function is called when the user starts to play.
 * It gets the intial position of the monsters and the player(s), according with the opened door.
 *
*/
void start_playing(Global* global)
{
    int i, j;
    
    global->menu.menu_type = PLAY;
    
    load_map(global);
    
    //Get the initial position of each monster and player
    for(i=0; i<global->maps.lines; i++)
    {
        for(j=0; j<global->maps.columns; j++)
        {
            if(global->maps.room[i][j] == MONSTER)
            {
                global->monsters[global->nb_monsters].position.rect.x = j*WIDTH_TILES;
                global->monsters[global->nb_monsters].position.rect.y = i*HEIGHT_TILES - 16;
                global->monsters[global->nb_monsters].status.life = 100;
                global->monsters[global->nb_monsters].id_monster = global->nb_monsters;
                
                global->nb_monsters++;
            }
            else if(global->maps.room[i][j] == OPENED)
            {
                global->players[0].position.rect.x = j*WIDTH_TILES;
                global->players[0].position.rect.y = (i-1)*HEIGHT_TILES - 16;
                if(global->level == 1)
                    global->players[0].status.life = 100;
                
                if(global->menu.multiplayer == 1 && global->menu.multiplayer_mode == COOPERATIVE)
                {
                    global->players[1].position.rect.x = (j+1)*WIDTH_TILES;
                    global->players[1].position.rect.y = (i-1)*HEIGHT_TILES - 16;
                    if(global->level == 1)
                        global->players[1].status.life = 100;
                }
            }
            else if(global->maps.room[i][j] == CLOSED && global->menu.multiplayer_mode == PVP)
            {
                global->players[1].position.rect.x = j*WIDTH_TILES;
                global->players[1].position.rect.y = (i+1)*HEIGHT_TILES - 16;
                if(global->level == 1)
                    global->players[1].status.life = 100;
            }
            //Convert the term "OBJECT" in a real object randomly
            else if(global->maps.room[i][j] == OBJECT)
            {
                global->maps.room[i][j] = get_random_object();
            }
        }
    }
}


/*
 * This function launch the edit menu, the solo mode or the multiplayers menu according with the received inputs
 *
*/
void menu_inputs(Global *global)
{
    char temp[50];
    
    if(global->input.edit_menu)
    {
        global->menu.menu_type = EDIT;

        SDL_RenderClear(global->window.renderer);
        SDL_RenderCopy(global->window.renderer, global->window.text_edit_screen, NULL, &global->window.pos_background);
        SDL_RenderPresent(global->window.renderer);

        printf("Ecrivez le nom du fichier a charger : \n");
        fgets(temp, 30, stdin);
        if(strlen(temp) < 30)
            temp[strlen(temp) - 1] = '\0';
        
        strcpy(global->maps.cur_map, "maps/");
        global->maps.cur_map[strlen(global->maps.cur_map)] = '\0';
        strcat(global->maps.cur_map, temp);
        
        printf("%s\n", global->maps.cur_map);

        global->window.write_surf = TTF_RenderText_Solid(global->window.write_police, global->maps.cur_map, global->window.write_color);

        global->window.write_pos.x = 250;
        global->window.write_pos.y = 380;
        global->window.write_pos.w = global->window.write_surf->w;
        global->window.write_pos.h = global->window.write_surf->h;

        global->window.write_text = SDL_CreateTextureFromSurface(global->window.renderer, global->window.write_surf);
        SDL_RenderCopy(global->window.renderer, global->window.write_text, NULL, &global->window.write_pos);
        SDL_RenderPresent(global->window.renderer);

        SDL_Delay(1000);
        
        //Load the map to edit
        load_map(global);
        
        //Save the map
        save_map(global);
    }

    if(global->input.play_menu)
    {
        global->menu.multiplayer = 0;
        init_vars(global);
        start_playing(global);
    }
    
    if(global->input.multiplayer_menu)
    {
        global->menu.menu_type = MULTIPLAYER;
        global->menu.multiplayer = 1;
        global->menu.multiplayer_mode = NO_MODE;
    }
    
    if(global->input.pause_menu)
    {
        global->menu.menu_type = PAUSE;
    }
}
