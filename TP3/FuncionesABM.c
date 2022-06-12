/*
 * Funciones.c
 *
 *  Created on: 10 jun. 2022
 *      Author: Nicolas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Passenger.h"
#include "FuncionesABM.h"
#include "libreriaP.h"
#define TAM 50

/**
 * @brief agrega un pasajero pasado por newpax a la linkedlist
 * @param lList - linkedlist
 * @param newPax - pasajero nuevo
 * @param idActual - ultimo ID registrado
 * @return 1 en cualquier caso
 */
int Passenger_add(LinkedList* lList,Passenger* newPax,int idActual){

	char idStr[10];
	sprintf(idStr,"%d",idActual);

	char tipoPasajeroStr[50];
	char estadoVueloStr[40];
	char precioStr[20];
	sprintf(precioStr,"%f",newPax->precio);
	int tipoAux = newPax->tipoPasajero;
	int estadoAux = newPax->estadoVuelo;

	itocTipoPasajero(tipoAux, tipoPasajeroStr);
	itocEstadoVuelo(estadoAux, estadoVueloStr);

	ll_add(lList,Passenger_newParametros(idStr, newPax->nombre, newPax->apellido, precioStr, newPax->codigoVuelo, tipoPasajeroStr, estadoVueloStr));


	return 1;
}

/**
 * @brief modificador de pasajeros dentro de la linkedList
 * @param lList LinkedList
 * @param sId id buscada
 * @return retorna 1 como siempre
 */
int Passenger_mod(LinkedList* lList,int sId){

	int index = Passenger_findId(lList,sId);
	int option;
	Passenger* pasajeroAModificar = ll_get(lList, index);
	Passenger* pasajeroAux = Passenger_new();
	char stringAux[TAM];

	do{
		option = MenuGeneral(2, "1.Nombre y Apellido\n", "2.Precio\n", "3.Codigo de vuelo\n", "4.Tipo de vuelo\n","5.Estado de Vuelo\n", "6.Terminar modificacion\n", "", "", '0');
		switch (option){
		case 1:
			printf("Nombre y apellido actual: %s %s\n",pasajeroAModificar->nombre,pasajeroAModificar->apellido);
			setNameLastname(pasajeroAux->nombre, pasajeroAux->apellido);
			break;
		case 2:
			printf("Precio Actual: %f\n",pasajeroAModificar->precio);
			 pasajeroAux->precio = setPrice();
			break;
		case 3:
			printf("Codigo actual: %s\n",pasajeroAModificar->codigoVuelo);
			setFlycode(pasajeroAux->codigoVuelo);
			break;
		case 4:
			itocTipoPasajero(pasajeroAModificar->tipoPasajero, stringAux);
			printf("tipo de pasajero actual: %s\n",stringAux);
			pasajeroAux->tipoPasajero = setTypePassanger();
			break;
		case 5:
			itocEstadoVuelo(pasajeroAModificar->estadoVuelo, stringAux);
			printf("Estado de vuelo actual: %s\n",stringAux);
			pasajeroAux->estadoVuelo = SetStatusFlight();
			break;
		case 6:
			if(strcmp(pasajeroAux->nombre," ") != 0){
				Passenger_setNombre(pasajeroAModificar, pasajeroAux->nombre);
			}
			if(strcmp(pasajeroAux->apellido," ") != 0){
				Passenger_setApellido(pasajeroAModificar, pasajeroAux->apellido);
			}
			if(pasajeroAux->precio != 0){
				Passenger_setPrecio(pasajeroAModificar, pasajeroAux->precio);
			}
			if(strcmp(pasajeroAux->codigoVuelo," ") != 0){
				Passenger_setCodigoVuelo(pasajeroAModificar, pasajeroAux->codigoVuelo);
			}
			if(pasajeroAux->tipoPasajero != 0){
				Passenger_setTipoPasajero(pasajeroAModificar, pasajeroAux->tipoPasajero);
			}
			if(pasajeroAux->estadoVuelo != 0){
				Passenger_setEstadoVuelo(pasajeroAModificar, pasajeroAux->estadoVuelo);
			}
			option = 0;
		}

	}while(option != 0);

	return 1;
}

/**
 * @brief encuentra las ID de los Pasajeros
 * @param lList
 * @param id
 * @return
 */
int Passenger_findId(LinkedList* lList,int id){

	Passenger* PasajeroAux;
	int index;
	if(lList != NULL && id > 0){
		for(int i = 0;i < ll_len(lList);i++){
			PasajeroAux = ll_get(lList, i);
			if(PasajeroAux->id == id){
				index = ll_indexOf(lList, PasajeroAux);
			}
		}
	}
	return index;
}


//SETERS PERSONALES

/**
 * @brief pregunta al usuario nombre y apellido
 * @param string del nombre
 * @param string del apellido
 */
void setNameLastname(char* nombre,char* apellido){
	do{
		printf("nombre y apellido: ");
		setbuf(stdin,NULL);
		scanf("%s %s",nombre,apellido);
		nombre[0] = toupper(nombre[0]);
		apellido[0] = toupper(apellido[0]);

		if(!(isStrAlpha(nombre) && isStrAlpha(apellido))){
			printf("ERROR, numeros ingresados, solo letras por favor\n");
		}
	}while(!(isStrAlpha(nombre) && isStrAlpha(apellido)));
}

/**
 *  @brief pregunta al usuario precio
 * @return el precio en modo flotante
 */
float setPrice(){
	float price;
	do{
		printf("precio de viaje: ");
		setbuf(stdin,NULL);
		scanf("%f",&price);
		if(price < 0){
			printf("ERROR, los precios no pueden ser negativos");
		}
	}while(price < 0);

	return price;
}

/**
 * @brief pregunta al usuario el tipo de pasajero
 * @attention pido los tipos mostrando 3 tipos y luego se debe seleccionar con 3 numeros
 * @return numero refiriendose al tipo de pasajero
 */
int setTypePassanger(){
	int typePassanger;
	do{
		printf("Tipo de Pasaje Primera/Segunda/Tercera (1/2/3): ");
		setbuf(stdin,NULL);
		scanf("%d",&typePassanger);
		if(isdigit(typePassanger)){
			printf("ERROR, los tipos no pueden ser una letra\n");
		} else {
			if(typePassanger != 1 && typePassanger != 2 && typePassanger != 3){
				printf("ERROR, solo se aceptan primera (1), segunda (2) o tercera clase (3)\n");
			}
		}

	}while(isdigit(typePassanger) || (typePassanger != 1 && typePassanger != 2 && typePassanger != 3));

	return typePassanger;
}

/**
 * @brief pide al usuario el codigo de vuelo
 * @param string para llenar con el flycode
 */
void setFlycode(char flycode[51]){
	do{
		printf("Codigo de Vuelo (AAXXXXA): ");
		setbuf(stdin,NULL);
		scanf("%s",flycode);
		for(int i = 0;i < 8;i++){
			flycode[i] = toupper(flycode[i]);
		}
		if(!(flyCodeVerif(flycode))){
			printf("ERROR, numero de vuelo invalido 2 letras, 4 numeros y 1 letra para identificadores de vuelo\n ej: AR1875E\n");
		}
	} while(!(flyCodeVerif(flycode)));
}

/**
 * @brief pregunta al usuario el estado de vuelo
 * @attention pide los estados de vuelo mostrando 4 modos y luego se debe seleccionar con 4 numeros
 * @return numero refiriendose al estado del vuelo
 */
int SetStatusFlight(){
	int statusFlight;
	do{
		printf("Estado de vuelo En Horario/En Vuelo/Aterrizado/Demorado (1/2/3/4): ");
		setbuf(stdin,NULL);
		scanf("%d",&statusFlight);
		if(isdigit(statusFlight)){
			printf("ERROR, los tipos no pueden ser una letra\n");
		} else {
			if(!(statusFlight >= 1 && statusFlight <= 4)){
				printf("Solo se acepta 1 y 0\n");
			}
		}
	}while(isdigit(statusFlight) || !(statusFlight >= 1 && statusFlight <= 4));

	return statusFlight;
}

/**
 * @brief setea un pasajero de que se pasa por parametro
 * @param pasajero que se quiere rellenar con datos
 * @return devuelve 1 si se creo correctamente y 0 si hubo un error
 */
int setPaxData(Passenger* pasajero){
	int option;
	char confirm;
	int n = 0,p = 0,t = 0,c = 0,sf = 0;

	do{
		option = MenuGeneral(1, "1.Nombre y Apellido\n", "2.Precio\n", "3.Tipo de pasaje\n" , "4.Codigo de Vuelo\n", "5.Estado de vuelo\n" , "6.Confirmar\n","","",'0');
		switch(option){
		case 1:
			setNameLastname(pasajero->nombre, pasajero->apellido);
			n = 1;
			break;
		case 2:
			pasajero->precio = setPrice();
			p = 1;
			break;
		case 3:
			pasajero->tipoPasajero = setTypePassanger();
			t = 1;
			break;
		case 4:
			setFlycode(pasajero->codigoVuelo);
			c = 1;
			break;
		case 5:
			pasajero->estadoVuelo = SetStatusFlight();
			sf = 1;
			break;
		case 6:
			printf("Confirme que todos los datos estan correctos\n");
			do{
			printf("Seguro que quiere subir los datos? (Y/N) ");
			setbuf(stdin,NULL);
			scanf("%c",&confirm);
			confirm = toupper(confirm);
			if(!(confirm == 'Y' || confirm == 'N')){
				printf("%c",confirm);
				printf("ERROR, Letras aceptadas Y o N\n");
			}
			}while(!(confirm == 'Y' || confirm == 'N'));
			if(confirm == 'Y'){
				if(n && p && t && c && sf){
					return 1;
				} else {
					printf("DATOS INCOMPLETOS");
				}
			}
			break;
		}
	} while(option != 0);
	return 0;
}
