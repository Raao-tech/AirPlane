/**
 * @brief This module is a description of any route.
 * @author Raao-tech
 * @date 05/30/2026
 * @version 0.0
 */

#ifndef ROUTE_H
#define ROUTE_H
#include "city.h"
#include "plane.h"
#include "types.h"

typedef struct _Route Route;

Route* route_create (City* city_a, City* city_b);
void   route_destroy (Route* route);

Level  route_get_level   (Route* route);
int    route_get_planes  (Route* route);
Plane* route_get_plane   (Route* route, int index);
Status route_add_plane   (Route* route);



float  route_get_upgrade_cost (Route* route);
Status route_upgrade     (Route* route, float cash);
Status route_downgrade   (Route* route);



#endif