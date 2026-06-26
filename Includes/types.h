/**
 * @brief This module is a set of utility types for the program
 * @author Raao-tech
 * @version 0.0
 * @date 05/30/2026
 */
#include <math.h>
#ifndef TYPES_H
#define TYPES_H


typedef long Level;
#define NO_LEVEL -1;

typedef long Id;
#define NO_ID -1

typedef enum Status {
    OK,
    ERROR
};








/* ========== Position ==========*/
typedef struct _Position {
    float x;
    float y;
}Position;

#define NO_POS -1.00
#define NO_DIS -1.00

/*Create a new position data*/
Position position_new (float x, float y)
{
    Position pos_new;
    pos_new.x = x;
    pos_new.y = y;
    return pos_new;
}

/*Validate if a position is permite*/
bool position_is_valid (Position pos)
{
    if (pos.x <= NO_POS || pos.y <= NO_POS) return false;
    return true;
}

/*Calculate distance betwen pos a and pos b*/
float position_distance (Position pos_a, Position pos_b)
{
    float distance;
    float dis_x;
    float dis_y;

    if (position_is_valid(pos_a) == false || 
        position_is_valid(pos_b) == false ) return NO_DIS;
    
    distance = NO_DIS;

    dis_x = pos_a.x - pos_b.x;
    dis_y = pos_a.y - pos_b.y;

    distance = pow ( (dis_x*dis_x) + (dis_y*dis_y) ,0.5);

    return distance;
}


#endif
