/*
 * Funciones.h
 *
 *  Created on: 9 may. 2022
 *      Author: Nicolas
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

int MenuGeneral(int submenu,char mensaje1[], char mensaje2[], char mensaje3[], char mensaje4[], char mensaje5[], char mensaje6[]);
void ClearPax(Passenger* pax);
int findFreeSpace(Passenger* list,int cantidad);

int setNameLastname();
float setPrice();
int setTypePassanger();
void setFlycode(char flycode[51]);
int SetStatusFlight();

int setMPaxData(Passenger* pasajero,Passenger* list);
int modPaxData(int id,Passenger pasajero,Passenger* list,int len);
int setPaxData(Passenger* pasajero);

int flyCodeVerif(char* codigo);
void MostrarUnPasajero(Passenger* list,int i);
void MostrarInformes(Passenger* list,int len);

#endif /* FUNCIONES_H_ */
