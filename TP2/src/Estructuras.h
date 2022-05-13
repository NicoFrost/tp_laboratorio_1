/*
 * Estructuras.h
 *
 *  Created on: 9 may. 2022
 *      Author: Nicolas
 */

#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_
#define TAMSTR 51

typedef struct {
	int id;
	char name[TAMSTR];
	char lastname[TAMSTR];
	float price;
	char flycode[10];
	int typePassenger;
	int isEmpty;
} Passenger;

#endif /* ESTRUCTURAS_H_ */
