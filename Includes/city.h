/**
 * @brief This module is a description of any city.
 * @author Raao-tech
 * @date 05/30/2026
 * @version 0.0
 */

#ifndef CITY_H
#define CITY_H

#include "types.h"

typedef struct _City City;

/** ===============
 *    Create / Destroy
 ** ==============  */

/**
 * @brief Create  a new City
 * @return a pointer to the new city
 */
City* city_create  ();

/**
 * @brief destroy a city
 * @param city pointer to city to free
 */
void  city_destroy (City* city);

/** ===============
 *   name / Id
 ** ==============  */

 /**
  * @brief Set a name for city
  * @param city pointer to city
  * @param name string whit the name to sets
  * @return OK if everything works perfectly, if not, then ERROR.
  */
Status city_set_name    (City* city, char* name);

 /**
  * @brief get a name of city
  * @param city pointer to city
  * @return A copy of pointer 
  */
char*  city_get_name    (City* city);

Status city_set_id      (City* city, Id id );
Id     city_get_id      (City* city, Id id );

/** ===============
 *   Build / Destroy / improve 
 ** ==============  */

/**
* @brief Build a new airport on a city
* @param city pointer to city
* @return OK if everything works perfectly, if not, then ERROR.
*/
Status city_build_airpot    (City* city);
/**
* @brief Improve airport on a city
* @note  the city Must  have an airport
* @param city pointer to city
* @return OK if everything works perfectly, if not, then ERROR.
*/
Status city_improve_airpot  (City* city);
/**
* @brief Destroy airport on a city
* @note  the city Must  have an airport
* @param city pointer to city
* @return OK if everything works perfectly, if not, then ERROR.
*/
Status city_destroy_airpot  (City* city);


 


#endif