/**
 * @brief This module is a description of any route.
 * @author Raao-tech
 * @date 05/30/2026
 * @version 0.0
 */

#ifndef GAME_H
#define GAME_H
#include "types.h"
#include "city.h"
#include "plane.h"
#include "route.h"


typedef struct _Game Game;

Game*  game_create (float cash_init);
void   game_destroy (Game* game);

Status game_next_day    (Game* game);

/*Route*/
Status game_build_route (Game* game, City* city_1, City* city_2);
Status game_buy_plane   (Game* game,Id route);



Status game_upgrade_route   (Game* game,Id route);
Status game_upgrade_plane   (Game* game,Id plane);




#endif