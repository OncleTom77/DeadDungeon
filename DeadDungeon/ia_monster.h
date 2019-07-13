//
//  ia_monster.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 15/11/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef __DeadDungeon__ia_monster__
#define __DeadDungeon__ia_monster__

void move_monster(Global*, Monster*, int);
int val_abs(int, int);
int touch_monster(Global*, Monster*, int);
int ia_move(Global*, Monster*);

#endif /* defined(__DeadDungeon__ia_monster__) */
