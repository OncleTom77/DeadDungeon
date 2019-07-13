//
//  draw.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This function draws the differents elements of the game.
 *
*/

#include "includes.h"


/*
 * This function draws the main menu of the game.
 *
*/
void draw_menu(Global *global)
{
    SDL_RenderCopy(global->window.renderer, global->window.text_menu_screen, NULL, &global->window.pos_background);
    
    //Write the inputs to use the menu
    sprintf(global->window.char_text, " P : Play | E : Edit | M : Multiplayer");
    
    draw_status_bar(global);
}


/*
 * This function draws the multiplayer menu to select the "cooperative" or the "player vs player" mode.
 *
*/
void draw_multiplayers_menu(Global *global)
{
    SDL_RenderCopy(global->window.renderer, global->window.text_multiplayer_screen, NULL, &global->window.pos_background);
    
    //Write the inputs to use the multiplayers menu
    sprintf(global->window.char_text, "   C : Cooperative mode  |  V : Player vs Player mode");
    
    draw_status_bar(global);
}


/*
 * This function draws the game_over screen.
 *
*/
void draw_game_over(Global *global)
{
    SDL_RenderCopy(global->window.renderer, global->window.text_game_over_screen, NULL, &global->window.pos_background);
    
    //Write the inputs to go back to menu
    sprintf(global->window.char_text, "Press any key to continue...");
    
    draw_status_bar(global);
}


/*
 * This function draws the end of the game.
 *
*/
void draw_end_game(Global *global)
{
    SDL_RenderCopy(global->window.renderer, global->window.text_end_game_screen, NULL, &global->window.pos_background);
    
    //Write the inputs to go back to menu
    sprintf(global->window.char_text, "Press any key to continue...");
    
    draw_status_bar(global);
}


/*
 * This function draws the pause menu.
 *
*/
void draw_pause(Global *global)
{
    SDL_RenderCopy(global->window.renderer, global->window.text_pause_screen, NULL, &global->window.pos_background);
    
    //Write the inputs to use to menu
    sprintf(global->window.char_text, " P : Play | S : Save the progression");
    
    draw_status_bar(global);
}


/*
 * This function draws the status bar in the bottom of the screen.
 *
*/
void draw_status_bar(Global *global)
{
    global->window.write_surf = TTF_RenderText_Solid(global->window.write_police, global->window.char_text, global->window.write_color);
    
    global->window.write_pos.x = 10;
    global->window.write_pos.y = 650;
    global->window.write_pos.w = global->window.write_surf->w;
    global->window.write_pos.h = global->window.write_surf->h;
    
    global->window.write_text = SDL_CreateTextureFromSurface(global->window.renderer, global->window.write_surf);
    SDL_RenderCopy(global->window.renderer, global->window.write_text, NULL, &global->window.write_pos);
    
    SDL_DestroyTexture(global->window.write_text);
}


/*
 * This function draws the area when the user is playing.
 * It draws the map and saves what the status bar will be display.
*/
void draw_area(Global *global)
{
    draw_map(global);
    
    if(global->menu.menu_type == PLAY)
    {
        if(global->menu.multiplayer)
        {
            global->window.write_color.r = 0;
            global->window.write_color.g = 0;
            global->window.write_color.b = 0;
            
            //Write information about the two players
            sprintf(global->window.char_text, "Life: %d| Move: %d| Att: %d  MOINE | SQUELETTE  Life: %d| Move: %d| Att: %d",
                    global->players[0].status.life,
                    DEFAULT_MOVEMENT - global->players[0].movement_speed + 10,
                    DEFAULT_ATTACK - global->players[0].attack_speed + 10,
                    global->players[1].status.life,
                    DEFAULT_MOVEMENT - global->players[1].movement_speed + 10,
                    DEFAULT_ATTACK - global->players[1].attack_speed + 10);
        }
        else
        {
            //Write the life of the main player
            sprintf(global->window.char_text, "Life : %d life | Movement : %d | Attack : %d",
                    global->players[0].status.life,
                    DEFAULT_MOVEMENT - global->players[0].movement_speed + 10,
                    DEFAULT_ATTACK - global->players[0].attack_speed + 10);
        }
    }
    else if(global->menu.menu_type == EDIT)
    {
        //Write the inputs to use to edit maps
        sprintf(global->window.char_text, "A:Wall|C:Closed Door|M:Monster|O:Object|R:Rock|S:Save|V:Opened Door|W:Water");
    }
    
    draw_status_bar(global);
}


/*
 * This function draws the map. It draws the differents parts of the map, according the value in the room's tab.
 *
*/
void draw_map(Global *global)
{
    int i, j;
    
    SDL_Rect position;
    
    position.w = WIDTH_TILES;
    
    for(i=0; i<global->maps.lines; i++)
    {
        for(j=0; j<global->maps.columns; j++)
        {
            position.h = HEIGHT_TILES;
            
            position.x = j*WIDTH_TILES;
            position.y = i*HEIGHT_TILES;
            
            if(global->maps.room[i][j] == ROCK)
                SDL_RenderCopy(global->window.renderer, global->edit.text_rock, NULL, &position);
            else if(global->maps.room[i][j] == WATER)
                SDL_RenderCopy(global->window.renderer, global->edit.text_water, NULL, &position);
            else if(global->maps.room[i][j] == WALL)
                SDL_RenderCopy(global->window.renderer, global->edit.text_wall, NULL, &position);
            else if(global->maps.room[i][j] == OBJECT)
                SDL_RenderCopy(global->window.renderer, global->edit.text_object, NULL, &position);
            else if(global->maps.room[i][j] == HEALTH_GLOBE)
                SDL_RenderCopy(global->window.renderer, global->edit.text_health_globe, NULL, &position);
            else if(global->maps.room[i][j] == INC_MOVEMENT_SPEED)
                SDL_RenderCopy(global->window.renderer, global->edit.text_inc_movement_speed, NULL, &position);
            else if(global->maps.room[i][j] == INC_ATTACK_SPEED)
                SDL_RenderCopy(global->window.renderer, global->edit.text_inc_attack_speed, NULL, &position);
            else
            {
                position.h = HEIGHT_PLAYER;
                position.y = i*HEIGHT_TILES - 16;
                
                if(global->maps.room[i][j] == CLOSED)
                    SDL_RenderCopy(global->window.renderer, global->edit.text_closed_door, NULL, &position);
                
                else if(global->maps.room[i][j] == OPENED)
                    SDL_RenderCopy(global->window.renderer, global->edit.text_opened_door, NULL, &position);
                
                else if(global->menu.menu_type == EDIT && global->maps.room[i][j] == MONSTER)
                    SDL_RenderCopy(global->window.renderer, global->monsters[0].charTexture.down[0], NULL, &position);
            }
        }
    }
}


/*
 * This function draws the differents characters of the game (monsters and players).
 *
*/
void draw_character(Window *window, Position *pos,  CharTexture *chartext)
{
    switch(pos->direction_global)
    {
        case UP:
            SDL_RenderCopy(window->renderer, chartext->up[pos->direction_up%9], NULL, &pos->rect);
            break;

        case DOWN:
            SDL_RenderCopy(window->renderer, chartext->down[pos->direction_down%9], NULL, &pos->rect);
            break;

        case LEFT:
            SDL_RenderCopy(window->renderer, chartext->left[pos->direction_left%9], NULL, &pos->rect);
            break;

        case RIGHT:
            SDL_RenderCopy(window->renderer, chartext->right[pos->direction_right%9], NULL, &pos->rect);
            break;
    }
}


/*
 * This function draws the balls.
 *
*/
void draw_ball(Global *global, Ball *ball)
{
    int i;

    for(i=0; i<ball->nb_ball; i++)
        SDL_RenderCopy(global->window.renderer, ball->text_ball, NULL, &ball->pos_ball[i]);
}
