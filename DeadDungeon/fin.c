//
//  fin.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file frees all the textures, stop SDL_ttf, stop SDL and quit the game.
 *
*/

#include "includes.h"

void end_game(Global *global)
{
    int i,j;

    //temporary screen
    SDL_RenderClear(global->window.renderer);
    SDL_RenderCopy(global->window.renderer, global->window.text_end_screen, NULL, &global->window.pos_background);
    SDL_RenderPresent(global->window.renderer);

    //Textures destruction
    SDL_DestroyTexture(global->window.text_background);

    for(j=0; j<NMAXPLAYER; j++)
    {
        SDL_DestroyTexture(global->players[j].ball.text_ball);
        
        for(i=0; i<9; i++)
        {
            SDL_DestroyTexture(global->players[j].charTexture.up[i]);
            SDL_DestroyTexture(global->players[j].charTexture.down[i]);
            SDL_DestroyTexture(global->players[j].charTexture.left[i]);
            SDL_DestroyTexture(global->players[j].charTexture.right[i]);
        }
    }
    
    for(j=0; j<NMAXMONSTER; j++)
    {
        for(i=0; i<9; i++)
        {
            SDL_DestroyTexture(global->monsters[j].charTexture.up[i]);
            SDL_DestroyTexture(global->monsters[j].charTexture.down[i]);
            SDL_DestroyTexture(global->monsters[j].charTexture.left[i]);
            SDL_DestroyTexture(global->monsters[j].charTexture.right[i]);
        }
        
        SDL_DestroyTexture(global->monsters[j].ball.text_ball);
    }

    SDL_DestroyTexture(global->edit.text_rock);
    SDL_DestroyTexture(global->edit.text_water);
    SDL_DestroyTexture(global->edit.text_wall);
    SDL_DestroyTexture(global->edit.text_opened_door);
    SDL_DestroyTexture(global->edit.text_closed_door);
    
    if(global->window.write_surf != NULL)
        SDL_FreeSurface(global->window.write_surf);

    if(global->window.write_text != NULL)
        SDL_DestroyTexture(global->window.write_text);

    SDL_DestroyTexture(global->window.text_menu_screen);
    SDL_DestroyTexture(global->window.text_end_screen);
    SDL_DestroyTexture(global->window.text_edit_screen);
    SDL_DestroyTexture(global->window.text_pause_screen);
    SDL_DestroyTexture(global->window.text_multiplayer_screen);
    SDL_DestroyTexture(global->window.text_game_over_screen);
    SDL_DestroyTexture(global->window.text_end_game_screen);
    
    //Destruction of the main renderer and the window
    SDL_DestroyRenderer(global->window.renderer);
    SDL_DestroyWindow(global->window.screen);

    TTF_CloseFont(global->window.write_police);

    TTF_Quit();

    SDL_Quit();

    exit(0);
}
