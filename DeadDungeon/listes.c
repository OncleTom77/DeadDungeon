//
//  listes.c
//  DeadDungeon
//
//  Created by Thomas Fouan on 29/11/2014.
//  Copyright (c) 2014 Thomas Fouan. All rights reserved.
//

/*
 * This file controls the chained list for the algorithm A*.
 *
*/

#include "includes.h"

/*
 * This function returns the last element of the list.
 *
*/
Liste* get_last_liste(Liste **liste)
{
    Liste *temp = *liste;
    
    if(temp != NULL)
    {
        while(temp->next != NULL)
            temp = temp->next;
        
        return temp;
    }
    else
        return NULL;
}


/*
 * This function add an element in the list.
 *
*/
void insert_into_liste(Liste **liste, Node node)
{
    Liste *temp = NULL;
    
    temp = malloc(sizeof(Liste));
    
    temp->element.x = node.x;
    temp->element.y = node.y;
    temp->element.g = node.g;
    temp->element.h = node.h;
    temp->element.f = node.f;
    temp->element.parent_x = node.parent_x;
    temp->element.parent_y = node.parent_y;
    
    temp->next = *liste;
    *liste = temp;
}


/*
 * This function returns the position of the node in the list.
 *
*/
int searchList(Liste *list, Node node)
{
    int i=0;
    Liste *temp = list;
    
    while(temp != NULL)
    {
        if(temp->element.x == node.x && temp->element.y == node.y)
            return i;
        
        temp = temp->next;
        i++;
    }
    return -1;
}


/*
 * This function returns the element in position "index" in the list.
 *
*/
Liste *getListeByIndex(Liste *liste, int index)
{
    unsigned short i;
    
    Liste *temp = liste;
    
    for(i=0; i<index; i++)
    {
        temp = temp->next;
    }
    
    return temp;
}


/*
 * This function delete an element in the list.
 *
*/
void delete_from_liste(Liste **liste, Node node)
{
    int search = searchList(*liste, node);
    
    if(search != -1)
    {
        if(search != 0)
        {
            Liste *prev = getListeByIndex(*liste, search-1);
            Liste *current = getListeByIndex(*liste, search);
            Liste *next = getListeByIndex(*liste, search+1);
            
            prev->next = next;
            free(current);
        }
        else
        {
            Liste *current = getListeByIndex(*liste, search);
            if(current->next != NULL)
                *liste = current->next;
            else
                *liste = NULL;
            
            free(current);
        }
    }
    else
        printf("Erreur de recherche");
}


/*
 * This function frees all the list.
 *
*/
void free_all_liste(Liste **liste)
{
    while(*liste != NULL)
    {
        Liste *temp = (*liste)->next;
        free(*liste);
        *liste = temp;
    }
}


/*
 * This function display the list.
 * It is unused in the game. It serves for debugging.
*/
void print_liste(Liste *liste)
{
    Liste *temp = liste;
    
    while(temp != NULL)
    {
        printf("f : %d, x : %d, y : %d, ", temp->element.f, temp->element.x, temp->element.y);
        printf("PARENT : x : %d, y : %d", temp->element.parent_x, temp->element.parent_y);
        printf("\n");
        
        temp = temp->next;
    }
    
    printf("NULL\n");
}


/*
 * This function returns the node with the smallest f value.
 *
*/
Liste *get_small_f(Liste *liste)
{
    Liste *temp = liste;
    Liste *small_f = temp;
    
    while(temp != NULL)
    {
        if(temp->element.f < small_f->element.f)
            small_f = temp;
        
        temp = temp->next;
    }
    
    return small_f;
}


/*
 * This function returns 1 if the node is in the list or 0 if is not.
 *
*/
int is_in_liste(Liste *liste, Node node)
{
    Liste *temp;
    
    if(liste != NULL)
    {
        temp = liste;
        while(temp != NULL)
        {
            if(temp->element.x == node.x && temp->element.y == node.y)
                return 1;
            
            temp = temp->next;
        }
    }
    
    return 0;
}


/*
 * This function returns the h value according with the xN, yN, xB, yB values 
 *
*/
int get_h(int xN, int yN, int xB, int yB)
{
    int h = 0;
    
    if(xN < xB)
        h += xB - xN;
    else
        h += xN - xB;
    
    if(yN < yB)
        h += yB - yN;
    else
        h += yN - yB;
    
    return h;
}
