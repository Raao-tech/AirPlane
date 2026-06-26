/**
 * @brief This module is a description of any route.
 * @author Raao-tech
 * @date 05/30/2026
 * @version 0.0
 */

#ifndef PLANE_H
#define PLANE_H
#include "types.h"

typedef struct _Plane Plane;

Plane* plane_new (Id id);
void   plane_delete (Plane* plane);

Level  plane_get_level    (Plane* plane);
int    plane_get_capacity (Plane* plane);
int    plane_get_on_board (Plane* plane);

Status plane_upgrade (Plane* plane);

#endif