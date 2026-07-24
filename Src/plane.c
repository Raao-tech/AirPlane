/**
 * @brief This module implements the planes that fly on a route.
 * @author Raao-tech
 * @date 07/22/2026
 * @version 0.1
 */
#include <stdlib.h>
#include "plane.h"

#define INIT_LEVEL           0
#define MIN_LEVEL             0
#define MAX_LEVEL                5
#define INIT_CAPACITY           50
#define CAPACITY_PER_LEVEL      50

struct _Plane
{
    Id      id;
    Level   level;
    int     capacity;
    int     on_board;
};


/**
 * @brief Creates a new plane at the initial level and capacity.
 * @param id the identifier for the new plane
 * @return the new plane, or NULL if there is no memory
 */
Plane* plane_new (Id id)
{
    Plane* n_plane = NULL;

    n_plane = (Plane*) calloc (1, sizeof (Plane));
    if (!n_plane) return NULL;

    n_plane->id       = id;
    n_plane->level    = INIT_LEVEL;
    n_plane->capacity = INIT_CAPACITY;
    n_plane->on_board = 0;

    return n_plane;
}

/**
 * @brief Destroys a plane.
 * @param plane the plane to destroy
 */
void plane_delete (Plane* plane)
{
    if (!plane) return;
    free (plane);
    return;
}

/**
 * @brief Gets the current level of a plane.
 * @param plane the plane to query
 * @return the level of the plane, or NO_LEVEL if plane is NULL
 */
Level plane_get_level (Plane* plane)
{
    if (!plane) return NO_LEVEL;
    return plane->level;
}

/**
 * @brief Gets the passenger capacity of a plane.
 * @param plane the plane to query
 * @return the capacity of the plane, or -1 if plane is NULL
 */
int plane_get_capacity (Plane* plane)
{
    if (!plane) return -1;
    return plane->capacity;
}

/**
 * @brief Gets the number of passengers currently on board a plane.
 * @param plane the plane to query
 * @return the number of passengers on board, or -1 if plane is NULL
 */
int plane_get_on_board (Plane* plane)
{
    if (!plane) return -1;
    return plane->on_board;
}

/**
 * @brief Upgrades a plane to the next level, increasing its capacity, as
 *        long as it has not reached the maximum level yet.
 * @param plane the plane to upgrade
 * @return OK if the plane was upgraded, ERROR otherwise
 */
Status plane_upgrade (Plane* plane)
{
    if (!plane || plane->level >= MAX_LEVEL) return ERROR;

    plane->level++;
    plane->capacity += CAPACITY_PER_LEVEL;

    return OK;
}
