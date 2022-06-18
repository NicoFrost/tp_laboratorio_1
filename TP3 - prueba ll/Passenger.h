/*
 * Passenger.h
 *
 *  Created on: 19 may. 2022
 *
 */
#include "LinkedList.h"

#ifndef PASSENGER_H_
#define PASSENGER_H_

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	char codigoVuelo[10];
	int tipoPasajero;
	int estadoVuelo;

}Passenger;

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* apellidoStr,char* precioStr,char* codigoStr,char* tipoPasajeroStr,char* estadoVueloStr);
void Passenger_delete(LinkedList* lList,int delId);
//Funciones Agregadas

int Passenger_sortByLastname(void* Pasajero1,void* Pasajero2);
int Passenger_sortByCode(void* Pasajero1,void* Pasajero2);

void Passenger_OnePassenger(Passenger* this,LinkedList* pArrayListPassenger);
void Passenger_list(LinkedList* pArrayListPassenger);

int itocTipoPasajero(int tipoPasajero,char* tipoPasajeroC);
int itocEstadoVuelo(int estadoVuelo,char* estadoVueloC);

int Passenger_Ordenarlista(LinkedList* Llist);

int GuardarTxt(FILE* pFile,LinkedList* lList);
//int getLenFile(char* path);

//----------------------
int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo);
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo);
int Passenger_getLastId(LinkedList* lList,int* id);

#endif /* PASSENGER_H_ */
