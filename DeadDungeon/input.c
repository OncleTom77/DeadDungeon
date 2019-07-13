//
//  input.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file controls the SDL_event and modify variables accordingly.
 *
*/

#include "includes.h"

int gestion_inputs(Global *global)
{
    SDL_Event event;
    int i;
    
    global->input.edit_menu             = 0;
    global->input.play_menu             = 0;
    global->input.pause_menu            = 0;
    global->input.multiplayer_menu      = 0;
    global->input.rock                  = 0;
    global->input.water                 = 0;
    global->input.wall                  = 0;
    global->input.opened_door           = 0;
    global->input.closed_door           = 0;
    global->input.object                = 0;
    global->input.save                  = 0;
    global->input.monster               = 0;
    global->input.pressed_mouse_left    = 0;
    global->input.pressed_mouse_right   = 0;
    
    
    for(i=0;i<NMAXPLAYER;i++)
        global->players[i].controlsStatus.spell = 0;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                end_game(global);
                break;
                
            case SDL_KEYUP:
                for(i=0;i<NMAXPLAYER;i++)
                {
                    if(event.key.keysym.sym == global->players[i].controls.keyUp)
                        global->players[i].controlsStatus.keyUp = 0;
                    else if(event.key.keysym.sym == global->players[i].controls.keyDown)
                        global->players[i].controlsStatus.keyDown = 0;
                    else if(event.key.keysym.sym == global->players[i].controls.keyLeft)
                        global->players[i].controlsStatus.keyLeft = 0;
                    else if(event.key.keysym.sym == global->players[i].controls.keyRight)
                        global->players[i].controlsStatus.keyRight = 0;
                }
                break;

            case SDL_KEYDOWN:
                if(global->menu.menu_type == GAME_OVER || global->menu.menu_type == END_GAME)
                {
                    global->menu.menu_type = MENU;
                    break;
                }
                
                for(i=0; i<NMAXPLAYER; i++)
                {
                    if(event.key.keysym.sym == global->players[i].controls.keyUp)
                        global->players[i].controlsStatus.keyUp = 1;
                    else if(event.key.keysym.sym == global->players[i].controls.keyDown)
                        global->players[i].controlsStatus.keyDown = 1;
                    else if(event.key.keysym.sym == global->players[i].controls.keyLeft)
                        global->players[i].controlsStatus.keyLeft= 1;
                    else if(event.key.keysym.sym == global->players[i].controls.keyRight)
                        global->players[i].controlsStatus.keyRight = 1;
                    else if(event.key.keysym.sym == global->players[i].controls.spell)
                        global->players[i].controlsStatus.spell = 1;
                }
                
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if(global->menu.menu_type == PLAY)
                            global->menu.menu_type = PAUSE;
                        else if(global->menu.menu_type == PAUSE)
                            global->menu.menu_type = MENU;
                        else if(global->menu.menu_type == EDIT)
                            global->menu.menu_type = MENU;
                        else
                            return 0;

                        break;
                    
                    case SDLK_a:
                        global->input.wall = 1;
                        break;
                        
                    case SDLK_c:
                        if(global->menu.menu_type == EDIT)
                            global->input.closed_door = 1;
                        else if(global->menu.menu_type == MULTIPLAYER)
                            global->menu.multiplayer_mode = COOPERATIVE;
                        break;
                        
                    case SDLK_e:
                        global->input.edit_menu = 1;
                        break;
                    
                    case SDLK_m:
                        if(global->menu.menu_type == EDIT)
                            global->input.monster = 1;
                        else if(global->menu.menu_type == PLAY)
                            global->players[0].controlsStatus.spell = 1;
                        else if(global->menu.menu_type == MENU)
                            global->input.multiplayer_menu = 1;
                        break;
                        
                    case SDLK_o:
                        global->input.object = 1;
                        break;

                    case SDLK_p:
                        if(global->menu.menu_type == MENU)
                            global->input.play_menu = 1;
                        else if(global->menu.menu_type == PAUSE)
                            global->menu.menu_type = PLAY;
                        break;

                    case SDLK_r:
                        global->input.rock = 1;
                        break;

                    case SDLK_s:
                        if(global->menu.menu_type == EDIT)
                            global->input.save = 1;
                        break;
                        
                    case SDLK_v:
                        if(global->menu.menu_type == EDIT)
                            global->input.opened_door = 1;
                        else if(global->menu.menu_type == MULTIPLAYER)
                            global->menu.multiplayer_mode = PVP;
                        break;

                    case SDLK_w:
                        global->input.water = 1;
                        break;
                        
                    default:
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        global->input.pressed_mouse_left = 1;
                        global->input.event_button_x = event.button.x;
                        global->input.event_button_y = event.button.y;
                        break;

                    case SDL_BUTTON_RIGHT:
                        global->input.pressed_mouse_right = 1;
                        global->input.event_button_x = event.button.x;
                        global->input.event_button_y = event.button.y;
                        break;
                }
                break;
        }
    }

    return 1;
}
