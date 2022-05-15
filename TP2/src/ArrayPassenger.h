/*
 * Generales.h
 *
 *  Created on: 9 may. 2022
 *      Author: Nicolas
 */
#include "Estructuras.h"


#ifndef GENERALES_H_
#define GENERALES_H_

int initPassengers(Passenger* list, int len);
int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[],int statusFlight);
int findPassengerById(Passenger* list, int len,int id);
int removePassenger(Passenger* list, int len, int id);
int printPassenger(Passenger* list, int length);
int sortPassengersByName(Passenger* list, int len, int order);
int sortPassengersByCode(Passenger* list, int len, int order);
#endif /* GENERALES_H_ */
