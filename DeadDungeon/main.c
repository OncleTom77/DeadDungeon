//
//  main.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 26/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * The main function controls the game. 
 * It controls the framerate, and calls the right function according the section of the game.
*/

#include "includes.h"

int main(int argc, char **argv)
{
    int framelimit, continuer = 1, test;

    Global global;

    //Init the SDL environment and the window
    init_SDL(&global);
    
    //Init the variables of the game
    init_vars(&global);
    
    framelimit = SDL_GetTicks() + 16;
    global.monsters[0].time_prec = SDL_GetTicks();

    while(continuer)
    {
        SDL_RenderClear(global.window.renderer);
        
        continuer = gestion_inputs(&global);

        if(global.menu.menu_type == EDIT)
        {
            //Draw the map
            draw_area(&global);
            
            //Read the inputs concerning the edition menu
            edit_inputs(&global);
        }
        else if(global.menu.menu_type == PLAY)
        {
            if(global.menu.multiplayer_mode == PVP && global.menu.multiplayer)
            {
                
            }
            else if(global.nb_monsters == 0)
            {
                unlock_door(&global);
                
                test = check_next_level(&global);
                
                //Change level
                if(test)
                {
                    if(global.level < NMAXLEVEL)
                    {
                        global.level++;
                    
                        sprintf(global.maps.cur_map, "maps/level_%d.txt", global.level);
                    
                        start_playing(&global);
                    
                        reinit_vars(&global);
                    }
                    else //End of the game, Good Job !
                    {
                        global.menu.menu_type = END_GAME;
                        
                        SDL_RenderClear(global.window.renderer);
                        draw_end_game(&global);
                        SDL_RenderPresent(global.window.renderer);
                        
                        SDL_Delay(2000);
                    }
                }
            }
            
            //Call the main function to play
            play(&global);
        }
        else if(global.menu.menu_type == MULTIPLAYER)
        {
            draw_multiplayers_menu(&global);
            
            if(global.menu.multiplayer_mode != NO_MODE)
            {
                init_vars(&global);
                
                if(global.menu.multiplayer_mode == PVP)
                {
                    sprintf(global.maps.cur_map, "maps/level_pvp.txt");
                }

                start_playing(&global);
            }
        }
        else if(global.menu.menu_type == PAUSE)
        {
            draw_pause(&global);
        }
        else if(global.menu.menu_type == MENU)
        {
            //Draw the menu
            draw_menu(&global);
            
            //Read the inputs concerning the menu
            menu_inputs(&global);
        }
        else if(global.menu.menu_type == GAME_OVER)
        {
            draw_game_over(&global);
        }
        else if(global.menu.menu_type == END_GAME)
        {
            draw_end_game(&global);
        }
        
        SDL_RenderPresent(global.window.renderer);
        
        SDL_Delay(16);
    }

    end_game(&global);

    return 0;
}
