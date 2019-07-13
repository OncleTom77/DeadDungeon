//
//  editor.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 27/10/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

void unlock_door(Global*);
int load_map(Global*);
int save_map(Global*);
void edit_inputs(Global*);
void menu_edit(Global*);

#endif /* defined(__DeadDungeon__editor__) */
