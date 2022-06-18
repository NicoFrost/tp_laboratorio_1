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

/**
 * @brief muestra un menu con los mensajes pasados por parametro
 * @param submenu define mesaje final para pasar si quiere que diga salir, regresar o cancelar
 * @param mensaje1
 * @param mensaje2
 * @param mensaje3
 * @param mensaje4
 * @param mensaje5
 * @param mensaje6
 * @param mensaje7
 * @param mensaje8
 * @param salida define numero para salir del donde estes
 * @return retorna la opcion elegida
 */
int MenuGeneral(int submenu,char mensaje1[], char mensaje2[], char mensaje3[], char mensaje4[], char mensaje5[], char mensaje6[],char mensaje7[],char mensaje8[],char salida){

	char respuesta;
	int retorno;
	do{
		printf("\ningrese una opcion (en numeros)...\n");
		printf("%s", mensaje1);
		printf("%s", mensaje2);
		printf("%s", mensaje3);
		printf("%s", mensaje4);
		printf("%s", mensaje5);
		printf("%s", mensaje6);
		printf("%s", mensaje7);
		printf("%s", mensaje8);
		switch(submenu){
		case 0:
			printf("o ingrese %c para salir\n",salida);
			break;
		case 1:
			printf("o ingrese %c para regresar\n",salida);
			break;
		case 2:
			printf("o ingrese %c para cancelar\n",salida);
			break;
		}
		setbuf(stdin, NULL);
		scanf("%c", &respuesta);
		if(isalpha(respuesta)){
			printf("ERROR,SOLO SE ADMITEN NUMEROS");
		}
	}while(isalpha(respuesta));

	retorno = atoi(&respuesta);

	return retorno;
}

//NO SE USO
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

//NO SE USO
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

//NO SE USO
void setString(char cadena[],char mensaje[],int tam)
{
    char auxiliar[tam];
    printf("%s", mensaje);
    setbuf(stdin,NULL);
    scanf("%s", auxiliar);
    strcpy(cadena, auxiliar);
}

//NO SE USO
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

//NO SE USO
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

//NO SE USO
void InicializarArray(int array[],int cantidad){

	for(int i = 0;i<cantidad;i++){
		array[i] = -1;
	}

}

//NO SE USO
int BuscarEspacio(int array[],int cantidad){

	int i;
	for(i = 0;i < cantidad;i++){
		if(array[i] == -1){
			break;
		}
	}
	return i;
}

/**
 * @brief revisa si la cadena es completamente letras
 * @param string cadena de texto
 * @return retorna 1 si no hay numeros en la cadena o 0 si hay alguno
 */
int isStrAlpha(char string[]){

	int r = 0;
	int contador = 0;

	for(int i = 0;i < strlen(string);i++){
		if(isalpha(string[i])){
			contador++;
		}
	}
	if(contador == strlen(string)){
		r = 1;
	}
	return r;
}

/**
 * @brief verifica el codigo de vuelo para que no se ingrese de mal manera
 * @param codigo a verificar
 * @return retorna 1 si esta todo bien sino 0 por error
 */
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

	if(isalpha(codigo[0]) && isalpha(codigo[1]) && isalpha(codigo[6])){
		if(contadorL == 3 && contadorN == 4){
			r = 1;
		}
	}


	return r;
}
