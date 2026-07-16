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

#define NO_POS -1.00
#define NO_DIS -1.00

typedef enum{
    OK,
    ERROR
}Status;


typedef enum{
    FALSE,
    TRUE
}Bool;


/* ========== Position ==========*/
typedef struct _Position {
    float x;
    float y;
}Position;



/*Create a new position data*/
Position position_new (float x, float y);

/*Validate if a position is permite*/
Bool position_is_valid (Position pos);

/*Calculate distance betwen pos a and pos b*/
float position_distance (Position pos_a, Position pos_b);


#endif
