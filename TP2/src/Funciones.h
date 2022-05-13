/*
 * Funciones.h
 *
 *  Created on: 9 may. 2022
 *      Author: Nicolas
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

int MenuGeneral(int submenu,char mensaje1[], char mensaje2[], char mensaje3[], char mensaje4[], char mensaje5[], char mensaje6[]);
int findFreeSpace(Passenger* list,int cantidad);

int setNameLastname();
float setPrice();
int setTypePassanger();
void setFlycode(char flycode[51]);
int setPaxData(char* nombre,char* apellido,float* price,char* typePassanger,char* flycode);

int flyCodeVerif(char* codigo);
int modPaxData(int id,Passenger* list, int len);

#endif /* FUNCIONES_H_ */
