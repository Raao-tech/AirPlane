/**
 * @brief This module is a set of utility types for the program
 * @author Raao-tech
 * @version 0.0
 * @date 05/30/2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "city.h"
#include "types.h"


#define ADD_POP 100
#define REM_POP 100

struct _City
{
    char*       name;
    Id          id;
    Position    position;
    int         population;
};


/*
=======================================
*
*          Private Functions 
*
=======================================*/

char* word_cpy (char* orig)
{
    if (!orig) return NULL;

    int   tam = strlen (orig);
    char* dest = (char*) calloc (tam + 1, sizeof (char));
    if (!dest) return NULL;
    dest[tam] = '\0';

    return dest;
}



/*======================================*/



/*Si se le es pasado un name null dará error*/
City* city_create  (Id id, char * name, int pop_init, Position pos)
{
    City* n_city = NULL;
    if (!name || pop_init < 0 || position_is_valid (pos) == FALSE )  return NULL;
    n_city = (City*) calloc (1, sizeof (City));
    if (!n_city) return NULL;

    n_city->id = id;
    n_city->population = pop_init;
    n_city->position = pos;
    n_city->name = word_cpy (name);
    if (n_city->name) return NULL;
    
    return n_city;
}

void  city_destroy (City* city)
{
    if (!city)  return;
    if(city->name) free (city->name);
    free (city);
    return;
}

Status   city_add_pop (City * city)
{
    if (!city) return ERROR;
    city->population += ADD_POP;
    return OK;
}

Status   city_rem_pop (City * city)
{
    if (!city) return ERROR;
    city->population -= REM_POP;
    return OK;
}

Position city_get_position (City * city)
{
    Position no_pos = position_new (NO_POS, NO_POS);
    if (!city) return no_pos;
    return city->position;
}

int city_get_population (City * city)
{
    if (!city) return -1;
    return city->population;
}

