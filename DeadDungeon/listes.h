//
//  listes.h
//  DeadDungeon
//
//  Created by Thomas Fouan on 29/11/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

#ifndef __DeadDungeon__listes__
#define __DeadDungeon__listes__

Liste* get_last_liste(Liste**);
void insert_into_liste(Liste**, Node);
int searchList(Liste*, Node);
Liste *getListeByIndex(Liste*, int);
void delete_from_liste(Liste**, Node);
void free_all_liste(Liste**);
void print_liste(Liste*);
Liste *get_small_f(Liste*);
int is_in_liste(Liste*, Node);
int get_h(int, int, int, int);

#endif /* defined(__DeadDungeon__listes__) */
