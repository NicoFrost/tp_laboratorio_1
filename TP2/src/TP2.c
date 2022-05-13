/*
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "libreriaP.h"
#include "Estructuras.h"
#include "ArrayPassenger.h"
#include "Funciones.h"

#define TAMSTR 51
#define TAMLIST 2000



int main(void) {
	setbuf(stdout,NULL);
	int option;
	char cont;
	int id = 1,flag = 0;
	int sid;
	char nombre[TAMSTR],apellido[TAMSTR],flycode[10],typePassenger;
	float price;

	Passenger ListPax[TAMLIST];

	initPassengers(ListPax, TAMLIST);


	do{
		option = MenuGeneral(0, "1.ALTA\n", "2.MODIFICACION\n", "3.BAJA\n", "4.INFORMAR\n", "5.HARCODEAR\n", "");
		switch(option){
		case 1:
			if((setPaxData(nombre, apellido, &price, &typePassenger, flycode))){
				if(!(addPassenger(ListPax,TAMLIST, id, nombre, apellido, price, typePassenger, flycode))){
					flag = 1;
					id++;
					printf("GUARDADO");
				}
			}
			break;
		case 2:
			if(flag == 1){
				printPassenger(ListPax, TAMLIST);
				printf("\nINGRESE ID DEL PASAJERO: ");
				scanf("%d",&sid);
				if(modPaxData(id, ListPax, TAMLIST)){
					printf("ERROR, modificacion no hecha");
				}
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		case 3:
			if(flag == 1){
				printPassenger(ListPax, TAMLIST);
				printf("INGRESE ID DE PASAJERO A BORRAR");
				setbuf(stdin,NULL);
				scanf("%d",&sid);
				removePassenger(ListPax, TAMLIST, sid);
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		case 4:
			if(flag == 1){
				printPassenger(ListPax, TAMLIST);
				printf("Presione cualquier LETRA para continuar");
				scanf("%c",&cont);
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		}
	} while(option != 0);

	return EXIT_SUCCESS;
}
