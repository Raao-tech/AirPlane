/**
 * @brief This module is a set of utility types for the program
 * @author Raao-tech
 * @version 0.0
 * @date 05/30/2026
 */
#include <math.h>
#include "types.h"

/*Create a new position data*/
Position position_new (float x, float y)
{
    Position pos_new;
    pos_new.x = x;
    pos_new.y = y;
    return pos_new;
}

/*Validate if a position is permite*/
Bool position_is_valid (Position pos)
{
    if (pos.x <= NO_POS || pos.y <= NO_POS) return FALSE;
    return TRUE;
}

/*Calculate distance betwen pos a and pos b*/
float position_distance (Position pos_a, Position pos_b)
{
    float distance;
    float dis_x;
    float dis_y;

    if (position_is_valid(pos_a) == FALSE ||
        position_is_valid(pos_b) == FALSE ) return NO_DIS;

    distance = NO_DIS;

    dis_x = pos_a.x - pos_b.x;
    dis_y = pos_a.y - pos_b.y;

    distance = pow ( (dis_x*dis_x) + (dis_y*dis_y) ,0.5);

    return distance;
}
