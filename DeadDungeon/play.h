//
//  play.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef PLAY_H_INCLUDED
#define PLAY_H_INCLUDED

int check_next_level(Global*);
void update_stats(Global*, Player*, int, int);
int gestion_collisions(Global*, SDL_Rect*, int, int, int);
void play_inputs(Global*, Player*);
void play(Global*);

#endif /* defined(__DeadDungeon__play__) */
