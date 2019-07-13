//
//  ball.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 24/11/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef __DeadDungeon__ball__
#define __DeadDungeon__ball__

void ball_input(Global*, Player*, Ball*);
void move_ball(Global*, Ball*);
int areTouching(SDL_Rect*, SDL_Rect*);
void compute_ball_collision(Global*, Player*);

#endif /* defined(__DeadDungeon__ball__) */
