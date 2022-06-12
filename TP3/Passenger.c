/*
 * Passenger.c
 *
 *  Created on: 19 may. 2022
 *      Author: Maru
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Passenger.h"
#include "FuncionesABM.h"
#include "LinkedList.h"
#include "libreriaP.h"
#define TAM 50

Passenger* Passenger_new(){

    Passenger* nuevoPasajero = NULL;
    nuevoPasajero= (Passenger*) malloc(sizeof(Passenger));

    if(nuevoPasajero != NULL)
    {
        nuevoPasajero->id=0;
        strcpy(nuevoPasajero->nombre, " ");
        strcpy(nuevoPasajero->apellido, " ");
        strcpy(nuevoPasajero->codigoVuelo, " ");
        nuevoPasajero->tipoPasajero=0;
        nuevoPasajero->precio=0;
        nuevoPasajero->estadoVuelo=0;
    }

    return nuevoPasajero;
}

//no modificable
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* apellidoStr,char* precioStr,char* codigoStr,char* tipoPasajeroStr,char* estadoVueloStr){

	Passenger* nuevoPasajero = Passenger_new();

	if(nuevoPasajero != NULL){

		float precioFlt = atof(precioStr);
		int idInt = atoi(idStr);
		int tipoPasajeroInt;
		int estadoVueloInt;
		if(strcmp(tipoPasajeroStr,"FirstClass") == 0){
			tipoPasajeroInt = 1;
		} else {
			if(strcmp(tipoPasajeroStr,"ExecutiveClass") == 0){
				tipoPasajeroInt = 2;

			} else {
				if(strcmp(tipoPasajeroStr,"EconomyClass") == 0){
					tipoPasajeroInt = 3;
				}
			}
		}
		if(strcmp(estadoVueloStr,"En Horario") == 0){
			estadoVueloInt = 1;
		} else {
			if(strcmp(estadoVueloStr,"En Vuelo") == 0){
				estadoVueloInt = 2;
			} else {
				if(strcmp(estadoVueloStr,"Aterrizado") == 0){
					estadoVueloInt = 3;
				} else {
					if(strcmp(estadoVueloStr,"Demorado") == 0){
						estadoVueloInt = 4;
					}
				}
			}
		}
	    if(!(
	    		Passenger_setId(nuevoPasajero, idInt)
				&& Passenger_setNombre(nuevoPasajero, nombreStr)
	       		&& Passenger_setApellido(nuevoPasajero, apellidoStr)
				&& Passenger_setPrecio(nuevoPasajero,precioFlt)
				&& Passenger_setCodigoVuelo(nuevoPasajero, codigoStr)
				&& Passenger_setTipoPasajero(nuevoPasajero, tipoPasajeroInt)
				&& Passenger_setEstadoVuelo(nuevoPasajero, estadoVueloInt)
	    ))
	    {
	    	printf("ERROR,Uno o varios datos no se puedieron procesar\n");
	    	printf("DATOS ENVIADOS: %d %s %s %f %s %d %d",idInt,nombreStr,apellidoStr,precioFlt,codigoStr,tipoPasajeroInt,estadoVueloInt);
	    }
	}

   	return nuevoPasajero;
}


//FUNCIONES AGREGADAS

void Passenger_delete(LinkedList* lList,int delId){
	if(lList != NULL && delId > 0){
		Passenger* pax;
		int len = ll_len(lList);
		int id;
		char resp;
		for(int i = 0;i < len;i++){
			pax = ll_get(lList, i);
			Passenger_getId(pax, &id);
			if(id == delId){
				Passenger_OnePassenger(pax, lList);
				printf("esta seguro que quiere eliminar este Pasajero? (Y/N)\n");
				scanf("%c",&resp);
				if(resp == 'y'){
					ll_remove(lList, i);
				}
			}
		}
	}
}

int Passenger_sortByCode(void* Pasajero1,void* Pasajero2){
	int retorno;

	if(Pasajero1 != NULL && Pasajero2 != NULL){
		char codigo1[TAM];
		char codigo2[TAM];

		Passenger_getCodigoVuelo(Pasajero1, codigo1);
		Passenger_getCodigoVuelo(Pasajero2, codigo2);

		if(codigo1 != NULL && codigo2 != NULL){
			retorno = strcmp(codigo1,codigo2);
		}
	}

	return retorno;
}

int Passenger_sortByLastname(void* Pasajero1,void* Pasajero2){

	int retorno;

	if(Pasajero1 != NULL && Pasajero2 != NULL){
		char apellido1[TAM];
		char apellido2[TAM];

		Passenger_getApellido(Pasajero1, apellido1);
		Passenger_getApellido(Pasajero2, apellido2);

		if(apellido1 != NULL && apellido2 != NULL){
			retorno = strcmp(apellido1,apellido2);
		}
	}

	return retorno;
}




void Passenger_OnePassenger(Passenger* this,LinkedList* pArrayListPassenger){
	int id,estadoAux,tipoAux;
	float precio;
	char nombre[TAM],apellido[TAM],codigoVuelo[TAM],tipoPasajero[TAM],estadoVuelo[TAM];
	if(
			   Passenger_getId(this, &id)
			&& Passenger_getNombre(this, nombre)
			&& Passenger_getApellido(this, apellido)
			&& Passenger_getPrecio(this, &precio)
			&& Passenger_getCodigoVuelo(this, codigoVuelo)
			&& Passenger_getTipoPasajero(this, &tipoAux)
			&& Passenger_getEstadoVuelo(this, &estadoAux)
	){

		itocTipoPasajero(tipoAux, tipoPasajero);
		itocEstadoVuelo(estadoAux, estadoVuelo);

		printf("|| %5d | %-16s\t | %-12s\t | %10.2f\t | %14s\t | %15s\t | %16s\t ||\n",id,nombre,apellido,precio,codigoVuelo,tipoPasajero,estadoVuelo);
	} else {
		printf("ERROR, al traer uno o varios datos desdde Linkedlist");
	}
}

void Passenger_list(LinkedList* pArrayListPassenger){
	char res;
	int corte = 250;
	Passenger* pasajeroAux = NULL;
	printf("_|=======================================================================================================================================|_\n");
	printf("||  ID   |         Nombre        |    Apellido   |    Precio     |    Codigo de Vuelo    |   Tipo de pasajero    |    Estado de Vuelo    ||\n");
	printf("||-------+-----------------------+---------------+---------------+-----------------------+-----------------------+-----------------------||\n");
	for(int i = 0;i < ll_len(pArrayListPassenger);i++){
		pasajeroAux = ll_get(pArrayListPassenger, i);
		Passenger_OnePassenger(pasajeroAux, pArrayListPassenger);
		if(i == corte-1 && i != 1000-1){
			printf("\nPresione V para continuar\n");
			setbuf(stdin,NULL);
			scanf("%c",&res);
			corte = corte + 125;
		}
	}
	printf("===========================================================================================================================================\n");
}

int getLenFile(char* path){

	FILE* pArchivo;
	int i = 1;
	char fantasma[100];

	pArchivo = fopen(path,"r");
		while(!feof(pArchivo)){
			fscanf(pArchivo,"%[^\n]\n",fantasma);
			i++;
		}
		printf("cantidad %d",i);
	fclose(pArchivo);

	return 1;
}


int GuardarTxt(FILE* pFile,LinkedList* lList){
	int retorno = 0;
	if(pFile != NULL && lList != NULL){
		Passenger* pasajeroAux;
		int id;
		char nombre[TAM];
		char apellido[TAM];
		float precio;
		int intAux;
		char tipoPasajero[TAM];
		char codigoVuelo[TAM];
		char estadoVuelo[TAM];
		int len,cantidadEscrita;
		len = ll_len(lList);
		printf("len: %d \n",len);

		if(len > 0){
			fprintf(pFile,"id,name,lastname,price,flycode,typePassenger,statusFlight\n");

			for(int i = 0 ;i < len;i++){
				pasajeroAux = ll_get(lList, i);
				if(pasajeroAux != NULL){
					Passenger_getId(pasajeroAux, &id);
					Passenger_getNombre(pasajeroAux, nombre);
					Passenger_getApellido(pasajeroAux, apellido);
					Passenger_getPrecio(pasajeroAux, &precio);
					Passenger_getCodigoVuelo(pasajeroAux, codigoVuelo);

					Passenger_getTipoPasajero(pasajeroAux, &intAux);
					itocTipoPasajero(intAux, tipoPasajero);

					Passenger_getEstadoVuelo(pasajeroAux, &intAux);
					itocEstadoVuelo(intAux, estadoVuelo);
					cantidadEscrita = fprintf(pFile,"%d,%s,%s,%.2f,%s,%s,%s\n",id,nombre,apellido,precio,codigoVuelo,tipoPasajero,estadoVuelo);
					if(cantidadEscrita != 0){
						retorno = 1;
					}
				}
				printf("cant: %d\n",cantidadEscrita);
			}
		}
	}

	return retorno;
}


//----------

int itocTipoPasajero(int tipoPasajero,char* tipoPasajeroC){

	if(tipoPasajero == 1){
		strcpy(tipoPasajeroC,"FirstClass");
	} else {
		if(tipoPasajero == 2){
			strcpy(tipoPasajeroC,"ExecutiveClass");
		} else {
			if(tipoPasajero == 3){
				strcpy(tipoPasajeroC,"EconomyClass");
			}
		}
	}
	return 1;
}

int itocEstadoVuelo(int estadoVuelo,char* estadoVueloC){

	if(estadoVuelo == 1){
			strcpy(estadoVueloC,"En Horario");
	} else {
		if(estadoVuelo == 2){
			strcpy(estadoVueloC,"En Vuelo");
		} else {
			if(estadoVuelo == 3){
				strcpy(estadoVueloC,"Aterrizado");
			} else {
				if(estadoVuelo == 4){
					strcpy(estadoVueloC,"Demorado");
				}
			}
		}
	}
	return 1;
}
//SETERS

int Passenger_setId(Passenger* this,int id){

	int retorno = 0;

	if(this != NULL && id > 0){
		this->id = id;
		retorno = 1;
	}

	return retorno;
}

int Passenger_setNombre(Passenger* this,char* nombre){
	int retorno = 0;

	if(this != NULL ){
		strcpy(this->nombre,nombre);
		retorno = 1;
	}

	return retorno;
}

int Passenger_setApellido(Passenger* this,char* apellido){
	int retorno = 0;

	if(this != NULL ){
		strcpy(this->apellido,apellido);
		retorno = 1;
	}

	return retorno;
}

int Passenger_setPrecio(Passenger* this,float precio){
	int retorno = 0;

	if(this != NULL && precio > 0){
		this->precio = precio;
		retorno = 1;
	}

	return retorno;
}

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo){

	int retorno = 0;
	if(this != NULL && flyCodeVerif(codigoVuelo)){
		strcpy(this->codigoVuelo,codigoVuelo);
		retorno = 1;
	}
	return retorno;
}

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero){
	int retorno = 0;

	if(this != NULL && tipoPasajero > 0 && tipoPasajero <= 3){
		this->tipoPasajero = tipoPasajero;
		retorno = 1;
	}

	return retorno;
}

int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo){
	int retorno = 0;

	if(this != NULL && estadoVuelo > 0 && estadoVuelo <= 4){
		this->estadoVuelo = estadoVuelo;
		retorno = 1;
	}

	return retorno;
}

//GETERS


int Passenger_getId(Passenger* this,int* id){
	int retorno = 0;
	if(this != NULL && id > 0){
		*id = this->id;
		retorno = 1;
	}
		return retorno;
}

int Passenger_getNombre(Passenger* this,char* nombre){
	int retorno = 0;
	if(this != NULL && nombre != NULL){
		strcpy(nombre,this->nombre);
		retorno = 1;
	}


	return retorno;
}

int Passenger_getApellido(Passenger* this,char* apellido){

	int retorno = 0;
	if(this != NULL && apellido != NULL){
		strcpy(apellido,this->apellido);
		retorno = 1;
	}


	return retorno;
}

int Passenger_getPrecio(Passenger* this,float* precio){
	int retorno = 0;
	if(this != NULL && precio != NULL){
		*precio = this->precio;
		retorno = 1;
	}

	return retorno;
}

int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo){
	int retorno = 0;
	if(this != NULL && codigoVuelo != NULL){
		strcpy(codigoVuelo,this->codigoVuelo);
		retorno = 1;
	}

	return retorno;
}

int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero){
	int retorno = 0;
	if(this != NULL && tipoPasajero != NULL){
		*tipoPasajero = this->tipoPasajero;
		retorno = 1;
	}
		return retorno;
}


int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo){
	int retorno = 0;
	if(this != NULL && estadoVuelo != NULL){
		*estadoVuelo = this->estadoVuelo;
		retorno = 1;
	}
		return retorno;
}

int Passenger_getLastId(LinkedList* lList,int* sid){

	if(lList != NULL && sid != NULL){
		int len = ll_len(lList);
		int idMax = 0;
		int paxId;
		Passenger* pax;

		for(int i = 0;i < len;i++){
			pax = ll_get(lList, i);
			Passenger_getId(pax, &paxId);
			if(paxId > idMax){
				idMax = paxId;
			}
		}
		*sid = idMax + 1;
	}
	return 1;
}
