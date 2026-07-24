/**
 * @brief This module implements the routes that connect two cities.
 * @author Raao-tech
 * @date 07/22/2026
 * @version 0.1
 */
#include <stdlib.h>
#include "route.h"
#include "types.h"


#define INIT_LEVEL          0
#define MIN_LEVEL            0
#define MAX_LEVEL              5
#define PLANES_PER_LEVEL         2
#define UPGRADE_COST_BASE  1000.00


struct _Route
{
    City*   city_a;
    City*   city_b;
    Level   level;
    Plane** planes;
    int     n_planes;
};


/*
=======================================
*
*          Private Functions
*
=======================================*/

/*Devuelve el número máximo de aviones permitidos según el nivel de la ruta*/
int _route_max_planes (Level level)
{
    return (int) ((level + 1) * PLANES_PER_LEVEL);
}

/*Devuelve el coste en efectivo de subir de nivel una ruta*/
float _route_upgrade_cost (Level level)
{
    return (float) UPGRADE_COST_BASE * (level + 1);
}

/*======================================*/


/**
 * @brief Creates a new route between two existing cities.
 * @param city_a first city of the route
 * @param city_b second city of the route
 * @return the new route, or NULL if a city is missing or there is no memory
 */
Route* route_create (City* city_a, City* city_b)
{
    Route* n_route = NULL;
    if (!city_a || !city_b) return NULL;

    n_route = (Route*) calloc (1, sizeof (Route));
    if (!n_route) return NULL;

    n_route->city_a   = city_a;
    n_route->city_b   = city_b;
    n_route->level    = INIT_LEVEL;
    n_route->planes   = NULL;
    n_route->n_planes = 0;

    return n_route;
}

/**
 * @brief Destroys a route and every plane assigned to it.
 * @param route the route to destroy
 */
void route_destroy (Route* route)
{
    int i;
    if (!route) return;

    for (i = 0; i < route->n_planes; i++)
    {
        plane_delete (route->planes[i]);
    }
    if (route->planes) free (route->planes);

    free (route);
    return;
}

/**
 * @brief Gets the current level of a route.
 * @param route the route to query
 * @return the level of the route, or NO_LEVEL if route is NULL
 */
Level route_get_level (Route* route)
{
    if (!route) return NO_LEVEL;
    return route->level;
}

/**
 * @brief Gets the number of planes currently assigned to a route.
 * @param route the route to query
 * @return the number of planes, or -1 if route is NULL
 */
int route_get_planes (Route* route)
{
    if (!route) return -1;
    return route->n_planes;
}

/**
 * @brief Gets the plane assigned to a route at the given position.
 * @param route the route to query
 * @param index the position of the plane inside the route
 * @return the plane at that position, or NULL if it does not exist
 */
Plane* route_get_plane (Route* route, int index)
{
    if (!route || index < 0 || index >= route->n_planes) return NULL;
    return route->planes[index];
}

/**
 * @brief Creates a new plane and assigns it to the route, as long as there
 *        is room left according to the route's current level.
 * @param route the route that will receive the new plane
 * @return OK if the plane was added, ERROR otherwise
 */
Status route_add_plane (Route* route)
{
    Plane** aux     = NULL;
    Plane*  n_plane = NULL;

    if (!route) return ERROR;
    if (route->n_planes >= _route_max_planes (route->level)) return ERROR;

    n_plane = plane_new ((Id) route->n_planes);
    if (!n_plane) return ERROR;

    aux = (Plane**) realloc (route->planes, (route->n_planes + 1) * sizeof (Plane*));
    if (!aux)
    {
        plane_delete (n_plane);
        return ERROR;
    }

    route->planes = aux;
    route->planes[route->n_planes] = n_plane;
    route->n_planes++;

    return OK;
}

/**
 * @brief Gets the cash needed to upgrade a route to its next level.
 * @param route the route to query
 * @return the upgrade cost, or -1.00 if route is NULL or already at the
 *         maximum level
 */
float route_get_upgrade_cost (Route* route)
{
    if (!route || route->level >= MAX_LEVEL) return -1.00;
    return _route_upgrade_cost (route->level);
}

/**
 * @brief Upgrades a route to the next level, if there is enough cash and
 *        the route has not reached the maximum level yet.
 * @param route the route to upgrade
 * @param cash  the cash available to pay for the upgrade
 * @return OK if the route was upgraded, ERROR otherwise
 */
Status route_upgrade (Route* route, float cash)
{
    if (!route || route->level >= MAX_LEVEL) return ERROR;
    if (cash < _route_upgrade_cost (route->level)) return ERROR;

    route->level++;
    return OK;
}

/**
 * @brief Downgrades a route to the previous level.
 * @param route the route to downgrade
 * @return OK if the route was downgraded, ERROR otherwise
 */
Status route_downgrade (Route* route)
{
    if (!route || route->level <= MIN_LEVEL) return ERROR;

    route->level--;
    return OK;
}
