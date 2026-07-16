/**
 * @brief This module is a set of utility types for the program
 * @author Raao-tech
 * @version 0.0
 * @date 05/30/2026
 */
#include <stdio.h>
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


Game*  game_create (float cash_init);
void   game_destroy (Game* game);







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

}

char*	_game_name_day 	  (int day)
{

}







/*Route*/
Status game_build_route (Game* game, City* city_1, City* city_2);
Status game_buy_plane   (Game* game,Id route);



Status game_upgrade_route   (Game* game,Id route);
Status game_upgrade_plane   (Game* game,Id plane);
