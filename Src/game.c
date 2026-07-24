/**
 * @brief This module is a set of utility types for the program
 * @author Raao-tech
 * @version 0.0
 * @date 05/30/2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "types.h"

struct _Game
{
    City**	cities;
	Route**	routes;
    Plane**	planes;

    int		n_cities;
	int		n_routes;
	int		n_planes;

    int     day;
    float   cash;
};




/**
*	======================== Private Functions ====================================
*/

Bool	_game_is_weekend  (int day);
int		_game_day_on_week (int day);
char*	_game_name_day 	  (int day);

/**
*	======================== Public Functions ====================================
*/
Game*  game_create (float cash_init);
void   game_destroy (Game* game);

Status game_next_day    (Game* game);
Status game_build_route (Game* game, City* city_1, City* city_2);
Status game_buy_plane   (Game* game,Id route);

Status game_upgrade_route   (Game* game,Id route);
Status game_upgrade_plane   (Game* game,Id plane);

/*==================================================================================*/


Game*  game_create (float cash_init)
{
	Game* n_game = NULL;
	if (cash_init < 0) return NULL;

	n_game = (Game*) calloc (1, sizeof (Game));
	if (!n_game) return NULL;

	n_game->cities   = NULL;
	n_game->routes   = NULL;
	n_game->planes   = NULL;
	n_game->n_cities = 0;
	n_game->n_routes = 0;
	n_game->n_planes = 0;
	n_game->day      = 0;
	n_game->cash     = cash_init;

	return n_game;
}

void   game_destroy (Game* game)
{
	int i;
	if (!game) return;

	for (i = 0; i < game->n_cities; i++) city_destroy (game->cities[i]);
	if (game->cities) free (game->cities);

	for (i = 0; i < game->n_routes; i++) route_destroy (game->routes[i]);
	if (game->routes) free (game->routes);

	/*Los aviones ya se destruyen junto a su ruta, aquí solo liberamos el registro*/
	if (game->planes) free (game->planes);

	free (game);
	return;
}


Status game_next_day    (Game* game)
{

	if(!game || game->day < 0) return ERROR;



}

Bool	_game_is_weekend (int day)
{
	if(day <0) return FALSE;
	if(((day + 1)%7) > 2 )  return FALSE;
	return TRUE;
}

int _game_day_on_week (int day)
{
	if (day < 0) return -1;
	return day % 7;
}

char*	_game_name_day 	  (int day)
{
	char* names[7] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
	int   day_week;

	day_week = _game_day_on_week (day);
	if (day_week < 0) return NULL;

	return names[day_week];
}







/*Route*/
Status game_build_route (Game* game, City* city_1, City* city_2)
{
	Route** aux     = NULL;
	Route*  n_route = NULL;

	if (!game || !city_1 || !city_2) return ERROR;

	n_route = route_create (city_1, city_2);
	if (!n_route) return ERROR;

	aux = (Route**) realloc (game->routes, (game->n_routes + 1) * sizeof (Route*));
	if (!aux)
	{
		route_destroy (n_route);
		return ERROR;
	}

	game->routes = aux;
	game->routes[game->n_routes] = n_route;
	game->n_routes++;

	return OK;
}

Status game_buy_plane   (Game* game,Id route)
{
	Plane** aux     = NULL;
	Plane*  n_plane = NULL;

	if (!game || route < 0 || route >= game->n_routes) return ERROR;
	if (route_add_plane (game->routes[route]) == ERROR) return ERROR;

	n_plane = route_get_plane (game->routes[route], route_get_planes (game->routes[route]) - 1);
	if (!n_plane) return ERROR;

	aux = (Plane**) realloc (game->planes, (game->n_planes + 1) * sizeof (Plane*));
	if (!aux) return ERROR;

	game->planes = aux;
	game->planes[game->n_planes] = n_plane;
	game->n_planes++;

	return OK;
}



Status game_upgrade_route   (Game* game,Id route)
{
	float cost;

	if (!game || route < 0 || route >= game->n_routes) return ERROR;

	cost = route_get_upgrade_cost (game->routes[route]);
	if (route_upgrade (game->routes[route], game->cash) == ERROR) return ERROR;

	game->cash -= cost;
	return OK;
}

Status game_upgrade_plane   (Game* game,Id plane)
{
	if (!game || plane < 0 || plane >= game->n_planes) return ERROR;
	return plane_upgrade (game->planes[plane]);
}
