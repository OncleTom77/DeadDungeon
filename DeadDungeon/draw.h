//
//  draw.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef __DeadDungeon__draw__
#define __DeadDungeon__draw__

void draw_menu(Global*);
void draw_multiplayers_menu(Global*);
void draw_pause(Global*);
void draw_game_over(Global*);
void draw_end_game(Global*);
void draw_status_bar(Global*);
void draw_area(Global*);
void draw_map(Global*);
void draw_character(Window *, Position*, CharTexture *);
void draw_ball(Global*, Ball*);

#endif /* defined(__DeadDungeon__draw__) */
