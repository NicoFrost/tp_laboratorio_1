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

	if(contadorL == 3 && contadorN == 4){
		r = 1;
	}

	return r;
}
void setNameLastname(char* nombre,char* apellido){
	do{
		printf("nombre y apellido: ");
		setbuf(stdin,NULL);
		scanf("%s %s",nombre,apellido);
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
		printf("Tipo de Pasajero: ");
		setbuf(stdin,NULL);
		scanf("%d",&typePassanger);
		if(isdigit(typePassanger)){
			printf("ERROR, los tipos no pueden ser una letra\n");
		}
	}while(isdigit(typePassanger));

	return typePassanger;
}

void setFlycode(char flycode[51]){
	do{
		printf("Codigo de Vuelo: ");
		setbuf(stdin,NULL);
		scanf("%s",flycode);
		if(!(flyCodeVerif(flycode))){
			printf("ERROR, numero de vuelo invalido 3 letras y 4 numeros para identificadores de vuelo\n ej: ARG1875\n");
		}
	} while(!(flyCodeVerif(flycode)));
}

int setPaxData(char* nombre,char* apellido,float* price,int* typePassanger,char* flycode){

	int option;
	char confirm;
	int n = 0,p = 0,t = 0,c = 0;

	do{
		option = MenuGeneral(1, "1.Nombre y Apellido\n", "2.Precio\n", "3.Tipo de pasaje\n" , "4.Codigo de Vuelo\n", "5.Confirmar\n" , "");
		switch(option){
		case 1:
			setNameLastname(nombre,apellido);
			n = 1;
			break;
		case 2:
			*price = setPrice();
			p = 1;
			break;
		case 3:
			*typePassanger = setTypePassanger();
			t = 1;
			break;
		case 4:
			setFlycode(flycode);
			c = 1;
			break;
		case 5:
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
				if(n && p && t && c){
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

/**
 *
 *  \param id para encontrar
 *  \param direccion de lista de pasajeros
 *  \param largo de la lista de pasajeros
 *  \return retorna -1 por Error, 0 si esta todo bien
 *
 */
int modPaxData(int id,Passenger* list, int len){
	int r = -1;
	int option;
	int sid = findPassengerById(list, len, id);
	do{
		option = MenuGeneral(1, "1.Nombre y Apellido\n", "2.Precio\n", "3.Tipo de pasaje\n" , "4.Codigo de Vuelo\n", "" , "");
		switch(option){
		case 1:
			setNameLastname(list[sid].name,list[sid].lastname);
			r = 0;
			break;
		case 2:
			list[sid].price = setPrice();
			r = 0;
			break;
		case 3:
			list[sid].typePassenger = setTypePassanger();
			r = 0;
			break;
		case 4:
			setFlycode(list[sid].flycode);
			r = 0;
			break;
		}
	}while(option != 0);
	return r;
}


