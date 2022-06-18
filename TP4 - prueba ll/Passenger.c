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

/**
 * @brief crea en memoria dinamica un pasajero y lo setea vacio para luego ser llenado por otra funcion
 * @return pasajero vacio
 */
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


/**
 * @brief usa funcion passenger_new() para crear un pasajero y luego lo rellena con datos pasados por parametros
 * @param idStr id como string
 * @param nombreStr nombre
 * @param apellidoStr apellido
 * @param precioStr precio pasado como string
 * @param codigoStr codigo de vuelo
 * @param tipoPasajeroStr tipo de pasajero pasado como string (contertidos a texto)
 * @param estadoVueloStr estado de vuelo pasado como string (convertido a texto)
 * @return pasajero lleno con datos aportados por parametros
 */
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
/**
 * @brief borrar pasajeros en el LinkedList
 * @param lList LinkedList
 * @param delId id elegido para eliminar
 */
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

/**
 * @attention esta funcion esta hecha para solo funcionar con el ll_sort
 * @brief funcion criterio que compara codigos de vuelo de los pasajero pasados por parametro, para usar en ll_sort
 * @param Pasajero1
 * @param Pasajero2
 * @return numero de comparacion para ll_sort
 */
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

/**
 * @attention esta funcion esta hecha para solo funcionar con el ll_sort
 * @brief funcion criterio que compara apellidos de los pasajero pasados por parametro, para usar en ll_sort
 * @param Pasajero1
 * @param Pasajero2
 * @return numero de comparacion para ll_sort
 */
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



/**
 * @brief obtiene datos y muestra 1 pasajero por pantalla
 * @param this pasajero a mostrar
 * @param pArrayListPassenger LinkedList
 */
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
/**
 * @brief muestra una lista de todos los pasajeros
 * @param pArrayListPassenger LinkedList
 */
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

/**
 * @brief funcion para guardar linkedlist en archivo pasado
 * @param pFile puntero a archivo
 * @param lList puntero a linkedlist
 * @return retorna 1 si se guarda bien sino 0 si no se guardaron correctamente
 */
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
			}
		}
	}

	return retorno;
}

/**
 * @brief se usa para poder convertir tipo de pasajero en numero a su contraparte en cadena de texto
 * @param tipoPasajero numero referenciando a uno de sus modos en texto
 * @param tipoPasajeroC cadena de texto a la que referencia el numero con el que se guarda en la estructura
 * @return retorna siempre 1
 */
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

/**
 * @brief se usa para poder convertir estados de vuelo en numero a su contraparte en cadena de texto
 * @param estadoVuelo numero referenciando a uno de sus modos en texto
 * @param estadoVueloC cadena de texto a la que referencia el numero con el que se guarda en la estructura
 * @return retorna siempre 1
 */
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

//----------
//SETERS

/**
 * @brief setea un id en el pasajero
 * @param this pasajero
 * @param id numero de id
 * @return devuele 1 si se hizo bien 0 si hubo un error
 */
int Passenger_setId(Passenger* this,int id){

	int retorno = 0;

	if(this != NULL && id > 0){
		this->id = id;
		retorno = 1;
	}

	return retorno;
}
/**
 * @brief setea un nombre en el pasajero
 * @param this pasajero
 * @param nombre cadena de texto de nombre
 * @return devuele 1 si se hizo bien 0 si hubo un error
 */
int Passenger_setNombre(Passenger* this,char* nombre){
	int retorno = 0;

	if(this != NULL ){
		strcpy(this->nombre,nombre);
		retorno = 1;
	}

	return retorno;
}
/**
 * @brief setea un apellido en el pasajero
 * @param this pasajero
 * @param apellido cadena de texto de apellido
 * @return devuele 1 si se hizo bien 0 si hubo un error
 */
int Passenger_setApellido(Passenger* this,char* apellido){
	int retorno = 0;

	if(this != NULL ){
		strcpy(this->apellido,apellido);
		retorno = 1;
	}

	return retorno;
}
/**
 * @brief setea un precio en el pasajero
 * @param this pasajero
 * @param precio numero flotante
 * @return devuele 1 si se hizo bien 0 si hubo un error
 */
int Passenger_setPrecio(Passenger* this,float precio){
	int retorno = 0;

	if(this != NULL && precio > 0){
		this->precio = precio;
		retorno = 1;
	}

	return retorno;
}
/**
 * @brief setea un codigo de vuelo en el pasajero
 * @param this pasajero
 * @param codigoVuelo cadena de texto de codigo de vuelo
 * @return devuele 1 si se hizo bien 0 si hubo un error
 */
int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo){

	int retorno = 0;
	if(this != NULL && flyCodeVerif(codigoVuelo)){
		strcpy(this->codigoVuelo,codigoVuelo);
		retorno = 1;
	}
	return retorno;
}
/**
 * @brief setea un tipo de pasajero en el pasajero
 * @param this pasajero
 * @param tipoPasajero numero de tipo de pasajero
 * @return devuele 1 si se hizo bien 0 si hubo un error
 */
int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero){
	int retorno = 0;

	if(this != NULL && tipoPasajero > 0 && tipoPasajero <= 3){
		this->tipoPasajero = tipoPasajero;
		retorno = 1;
	}

	return retorno;
}
/**
 * @brief setea un estado de vuelo en el pasajero
 * @param this pasajero
 * @param estadoVuelo numero de estado vuelo
 * @return devuele 1 si se hizo bien 0 si hubo un error
 */
int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo){
	int retorno = 0;

	if(this != NULL && estadoVuelo > 0 && estadoVuelo <= 4){
		this->estadoVuelo = estadoVuelo;
		retorno = 1;
	}

	return retorno;
}

//GETERS

/**
 * @brief obtiene el id y lo pasa por parametro
 * @param this
 * @param id
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */
int Passenger_getId(Passenger* this,int* id){
	int retorno = 0;
	if(this != NULL && id > 0){
		*id = this->id;
		retorno = 1;
	}
		return retorno;
}
/**
 * @brief obtiene el nombre y lo pasa por parametro
 * @param this
 * @param nombre
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */

int Passenger_getNombre(Passenger* this,char* nombre){
	int retorno = 0;
	if(this != NULL && nombre != NULL){
		strcpy(nombre,this->nombre);
		retorno = 1;
	}


	return retorno;
}
/**
 * @brief obtiene el apellido y lo pasa por parametro
 * @param this
 * @param apellido
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */
int Passenger_getApellido(Passenger* this,char* apellido){

	int retorno = 0;
	if(this != NULL && apellido != NULL){
		strcpy(apellido,this->apellido);
		retorno = 1;
	}


	return retorno;
}
/**
 * @brief obtiene el precio y lo pasa por parametro
 * @param this
 * @param precio en flotante
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */
int Passenger_getPrecio(Passenger* this,float* precio){
	int retorno = 0;
	if(this != NULL && precio != NULL){
		*precio = this->precio;
		retorno = 1;
	}

	return retorno;
}
/**
 * @brief obtiene el codigo de vuelo y lo pasa por parametro
 * @param this
 * @param codigo de vuelo
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo){
	int retorno = 0;
	if(this != NULL && codigoVuelo != NULL){
		strcpy(codigoVuelo,this->codigoVuelo);
		retorno = 1;
	}

	return retorno;
}
/**
 * @brief obtiene el tipo de pasajero (en numero) y lo pasa por parametro
 * @param this
 * @param tipo de pasajero (en numero)
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero){
	int retorno = 0;
	if(this != NULL && tipoPasajero != NULL){
		*tipoPasajero = this->tipoPasajero;
		retorno = 1;
	}
		return retorno;
}

/**
 * @brief obtiene el estado de vuelo (en numero) y lo pasa por parametro
 * @param this
 * @param estado de vuelo (en numero)
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo){
	int retorno = 0;
	if(this != NULL && estadoVuelo != NULL){
		*estadoVuelo = this->estadoVuelo;
		retorno = 1;
	}
		return retorno;
}
/**
 * @brief obtiene el obtiene ultimo ID registrado
 * @param this
 * @param id id buscado
 * @return retorna 1 si devuelve bien y 0 si hay un error
 */
int Passenger_getLastId(LinkedList* lList,int* sid){

	int retorno = 0;
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
		retorno = 1;
	}
	return retorno;
}
