/**
 * @brief This module is a description of any city.
 * @author Raao-tech
 * @date 05/30/2026
 * @version 0.0
 */

#ifndef CITY_H
#define CITY_H

#include "types.h"

typedef struct _City City;


City* city_create  (Id id, char * name, int pop_init, Position pos);
void  city_destroy (City* city);

/*This funtion permit to increment  population of this city*/
Status   city_add_pop (City * city);
/*This funtion permit to remove population of this city*/
Status   city_rem_pop (City * city);

Position city_get_position (City * city);

int      city_get_population (City * city);





#endif