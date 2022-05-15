/*
 * Funciones.c
 *
 *  Created on: 9 may. 2022
 *      Author: Nicolas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayPassenger.h"
#include "Estructuras.h"
#include "libreriaP.h"

int MenuGeneral(int submenu,char mensaje1[], char mensaje2[], char mensaje3[], char mensaje4[], char mensaje5[], char mensaje6[]){

	int respuesta;

	printf("\ningrese una opcion (en numeros)...\n");
	printf("%s", mensaje1);
	printf("%s", mensaje2);
	printf("%s", mensaje3);
	printf("%s", mensaje4);
	printf("%s", mensaje5);
	printf("%s", mensaje6);
	if(submenu){
		printf("o ingrese 0 para regresar\n");
	} else {
		printf("o ingrese 0 para salir\n");
	}
	setbuf(stdin, NULL);
	scanf("%d", &respuesta);
	return respuesta;
}

void ClearPax(Passenger* pax){
	pax->id = 0;
	strcpy(pax->name,"");
	strcpy(pax->lastname,"");
	pax->price = -1;
	pax->typePassenger = -1;
	strcpy(pax->flycode,"");
	pax->statusFlight = -1;
	pax->isEmpty = 1;
}

int findFreeSpace(Passenger* list,int cantidad){
	int i;
	for(i = 0;i < cantidad;i++){
		if(list[i].isEmpty == 1){
			break;
		} else {
			if(i == cantidad){
				i = -1;
			}
		}
	}
	return i;
}

int flyCodeVerif(char* codigo){

	int r = 0;
	int contadorL = 0,contadorN = 0;

	for(int i = 0;i< strlen(codigo);i++){
		if(isalpha(codigo[i])){
			contadorL++;
		}
		if(isdigit(codigo[i])){
			contadorN++;
		}

	}

	if(isalpha(codigo[0]) && isalpha(codigo[1]) && isalpha(codigo[2])){
		if(contadorL == 3 && contadorN == 4){
			r = 1;
		}
	}


	return r;
}

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

int setTypePassanger(){
	int typePassanger;
	do{
		printf("Tipo de Pasaje (1/2/3): ");
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

void setFlycode(char flycode[51]){
	do{
		printf("Codigo de Vuelo (AAAXXXX): ");
		setbuf(stdin,NULL);
		scanf("%s",flycode);
		for(int i = 0;i < 3;i++){
			flycode[i] = toupper(flycode[i]);
		}
		if(!(flyCodeVerif(flycode))){
			printf("ERROR, numero de vuelo invalido 3 letras y 4 numeros para identificadores de vuelo\n ej: ARG1875\n");
		}
	} while(!(flyCodeVerif(flycode)));
}

int SetStatusFlight(){
	int statusFlight;
	do{
		printf("Estado de vuelo (1/0): ");
		setbuf(stdin,NULL);
		scanf("%d",&statusFlight);
		if(isdigit(statusFlight)){
			printf("ERROR, los tipos no pueden ser una letra\n");
		} else {
			if(statusFlight != 1 && statusFlight != 0){
				printf("Solo se acepta 1 y 0\n");
			}
		}
	}while(isdigit(statusFlight) || (statusFlight != 1 && statusFlight != 0));

	return statusFlight;
}

int setPaxData(Passenger* pasajero){
	int option;
	char confirm;
	int n = 0,p = 0,t = 0,c = 0,sf = 0;

	do{
		option = MenuGeneral(1, "1.Nombre y Apellido\n", "2.Precio\n", "3.Tipo de pasaje\n" , "4.Codigo de Vuelo\n", "5.Estado de vuelo\n" , "6.Confirmar\n");
		switch(option){
		case 1:
			setNameLastname(pasajero->name, pasajero->lastname);
			n = 1;
			break;
		case 2:
			pasajero->price = setPrice();
			p = 1;
			break;
		case 3:
			pasajero->typePassenger = setTypePassanger();
			t = 1;
			break;
		case 4:
			setFlycode(pasajero->flycode);
			c = 1;
			break;
		case 5:
			pasajero->statusFlight = SetStatusFlight();
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

void setMPaxData(Passenger* pasajero,Passenger* list){
	int option;
	do{
		option = MenuGeneral(1, "1.Nombre y Apellido\n", "2.Precio\n", "3.Tipo de pasaje\n" , "4.Codigo de Vuelo\n", "5.Estado de Vuelo\n" , "6.Terminar modificacion\n");
		switch(option){
		case 1:
			setNameLastname(pasajero->name, pasajero->lastname);
			break;
		case 2:
			pasajero->price = setPrice();
			break;
		case 3:
			pasajero->typePassenger = setTypePassanger();
			break;
		case 4:
			setFlycode(pasajero->flycode);
			break;
		case 5:
			pasajero->statusFlight = SetStatusFlight();
			break;
		case 6:
				option = 9;
			break;
		case 0:
			ClearPax(pasajero);
			break;
		}
	} while(option != 0 && option != 9);
}

/**
 *
 *  \param id para encontrar
 *  \param direccion de lista de pasajeros
 *  \param largo de la lista de pasajeros
 *  \return retorna -1 por Error, 0 si esta todo bien
 *
 *
 */
//int modPaxData(int id,Passenger pasajero,Passenger* list, int len){
int modPaxData(int sid,Passenger pasajero,Passenger* list, int len){
	int r = -1;

	if(sid != -1){
		if(strcmp(pasajero.name,"") != 0){
			strcpy(list[sid].name,pasajero.name);
		}
		if(strcmp(pasajero.lastname,"") != 0){
			strcpy(list[sid].lastname,pasajero.lastname);
		}
		if(pasajero.price != -1){
			list[sid].price = pasajero.price;
		}
		if(pasajero.typePassenger != -1){
		list[sid].typePassenger = pasajero.typePassenger;

		}
		if(strcmp(pasajero.flycode,"") != 0){
			strcpy(list[sid].flycode,pasajero.flycode);
		}
		if(pasajero.statusFlight != -1){
			list[sid].statusFlight = pasajero.statusFlight;
		}
		r = 1;
	}

	return r;
}

void MostrarUnPasajero(Passenger* list,int i){

	char statusflight[10] = "";
	char typePassenger[20] = "";

	if(list[i].isEmpty == 0){
		switch (list[i].typePassenger){
		case 1:
			strcpy(typePassenger,"Primera Clase");
			break;
		case 2:
			strcpy(typePassenger,"Segunda Clase");
			break;
		case 3:
			strcpy(typePassenger,"Tercera Clase");
			break;
		}
		switch(list[i].statusFlight){
			case -1:
				strcpy(statusflight,"ERROR");
				break;
			case 0:
				strcpy(statusflight,"CANCELADO");
				break;
			case 1:
				strcpy(statusflight,"ACTIVO");
				break;
		}


		printf("| %*d\t| %*s | %*s \t| $%*.2f\t| %*s\t| %*s\t| %s\t\t|\n",4,list[i].id,12,list[i].name,12,list[i].lastname,12,list[i].price,12,typePassenger,12,list[i].flycode,statusflight);
	}



}

void MostrarInformes(Passenger* list,int len){

	int option;
	int order;
	float totalPrecio = 0;
	int paxActivos = 0;
	int superadores = 0;

	option = MenuGeneral(1, "1.Listado por apellido y tipo de pasajeros\n", "2.Total y promedio de precios\n", "3.Listado de los pasajeros (Vuelo y estado)\n", "", "", "");
	switch(option){
	case 1:
//		1. Listado de los pasajeros ordenados alfabéticamente
//	    por Apellido y Tipo de pasajero.
		do{
			printf("Orden ascendente (1), Orden descendente (0) o cancelar proceso? (2): ");
			scanf("%d",&order);
			if(order <= 0 && order >= 2){
				printf("ERROR,numero no aceptado");
			}
		}while(order <= 0 && order >= 2);
		if(order != 2){
			sortPassengersByName(list, len, order);
		} else {
			printf("Cancelado ordenamiento");
		}
	break;
	case 2:
		for(int i = 0;i < len;i++){
			if(list[i].isEmpty == 0){
				totalPrecio += list[i].price;
				paxActivos++;
			}
		}
		float promedio = totalPrecio / paxActivos;
		for(int i = 0;i < len;i++){
			if(list[i].price > promedio && list[i].isEmpty == 0){
				superadores++;
			}
		}
		printf("Promedio: %.2f\n",promedio);
		printf("Total: %.2f\n",totalPrecio);
		printf("Cantidad que superan el promedio: %d\n",superadores);
	break;
	case 3:
		//		3. Listado de los pasajeros por Código de vuelo y
		//		estados de vuelos ‘ACTIVO’
		do{
			printf("Orden ascendente (1), Orden descendente (0) o cancelar proceso? (2): ");
			scanf("%d",&order);
			if(order <= 0 && order >= 2){
				printf("ERROR,numero no aceptado");
			}
		}while(order <= 0 && order >= 2);
		if(order != 2){
			sortPassengersByCode(list, len, order);
		} else {
			printf("Cancelado ordenamiento");
		}
	break;
//					printPassenger(ListPax, TAMLIST);
//					printf("Presione cualquier LETRA para continuar ");
//					setbuf(stdin,NULL);
//					scanf("%c",&cont);
	}
}

