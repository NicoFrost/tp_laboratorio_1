/*
 * Funciones.h
 *
 *  Created on: 10 jun. 2022
 *      Author: Nicolas
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

//Alta
int Passenger_add(LinkedList* lList,Passenger* newPax,int idActual);
int Passenger_mod(LinkedList* lList,int sId);
int Passenger_findId(LinkedList* lList,int id);

void setNameLastname(char* nombre,char* apellido);
float setPrice();
int setTypePassanger();
void setFlycode(char flycode[51]);
int SetStatusFlight();
int setPaxData(Passenger* pasajero);


#endif /* FUNCIONES_H_ */
