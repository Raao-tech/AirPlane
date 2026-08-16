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

#define FAC 1
#define NOR 2
#define DIF 3

#define money_fac 10000
#define money_nor 5000
#define money_dif 2500

float  menu_main (void);
Status init_game (int mode);

int main (void)
{
    int mode;


    mode = menu_main();

    if (init_game (mode) == ERROR)
    {
        fprintf (stderr,"ERROR: Some wrong on initializing game");
        return 1;
    }

    return 0;
}


float menu_main (void)
{
    int option;

    option = -1;
    printf ("=================================\n");
    printf ("====\t          \t\t====\n");
    printf ("====\tTYCOON AIR\t\t====\n");
    printf ("====\t          \t\t====\n");
    printf ("=================================\n");

    sleep (2);

    while (option <= 0)
    {
        printf ("¿En qué modo deseas comenzar?\n");
        printf ("==== 1. Facil\n");
        printf ("==== 2. Normal\n");
        printf ("==== 3. Dificil\n");
        printf ("Respuesta (1,2,3):  \n");

        scanf ("%d", &option);

        if (option < FAC || option > DIF)
        {
            printf ("Please, you must type a integer between number 1 and 3\n\n");
            option = -1;
            sleep (1);
        }
        while (getchar() != '\n'); 
        
    }

    return (float) option;
}


Status init_game (int mode)
{
    switch (mode)
    {
        case FAC: game_create (money_fac); break; 
        case NOR: game_create (money_nor); break; 
        case DIF: game_create (money_dif); break; 
        default:  return ERROR;
    }

 return OK;
}