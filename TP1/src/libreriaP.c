/*
 * libreria.c
 *
 *  Created on: 9 set. 2021
 *      Author: Javier
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
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


int IngresarEntero(char mensaje[],int verif)
{
    int numero;
	char respuesta;

    do{
		printf("%s",mensaje);
	    setbuf(stdin,NULL);
		scanf("%d",&numero );
		respuesta = 's';
		if(verif){
			printf("el valor de %d esta correcto? (S/N/C)", numero);
		    setbuf(stdin,NULL);
			scanf("%c",&respuesta);
			respuesta = tolower(respuesta);
			if(respuesta == 'c'){
				numero = 0;
				respuesta = 's';
			}
		}
    }while(respuesta != 's');
	return numero;
}


float IngresarFlotante(char mensaje[],int verif)
{
    float numero;
    char respuesta;
    do{
		printf("%s",mensaje);
		setbuf(stdin,NULL);
		scanf("%f",&numero );

		if(verif){
			printf("el valor de %.2f esta correcto? (S/N/C)", numero);
			setbuf(stdin,NULL);
			scanf("%c",&respuesta);
			respuesta = tolower(respuesta);
			if(respuesta == 'c'){
				numero = 0;
				respuesta = 's';
			}
		}
    }while(respuesta != 's');
	return numero;
}


void getString(char cadena[],char mensaje[],int tam)
{
    char auxiliar[tam];
    printf("%s", mensaje);
    fflush(stdin);
    scanf("%s", auxiliar);
    strcpy(cadena, auxiliar);
}


void OrdenamientoBurbujaAscendente(int numero[],int cant,int *puntero){

	int aux,i,j;

		for(i = 0; i < cant;i++){
			for(j = 1; j < cant; j++){
				if(numero[i] > numero[j]){
					aux = numero[i];
					numero[i] = numero[j];
					numero[j] = aux;
				}
			}
		}
	puntero = numero;
}


void OrdenamientoBurbujaDscendente(int numero[],int cant,int *puntero){

	int aux,i,j;

	for(i = cant-1; i > 0;i--){
		for(j = cant; j > 0;j--){
			if(numero[i] > numero[j]){
				aux = numero[j];
				numero[j] = numero[i];
				numero[i] = aux;
			}
		}
	}
	puntero = numero;
}
