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
	int option,option2;
	char cont;
	int id = 1,flag = 0;
	int sid;
	int order;

	Passenger ListPax[TAMLIST];
	Passenger pax;

	initPassengers(ListPax, TAMLIST);


	do{
		option = MenuGeneral(0, "1.ALTA\n", "2.MODIFICACION\n", "3.BAJA\n", "4.INFORMAR\n", "5.HARCODEAR\n", "");
		switch(option){
		case 1:
			setPaxData(&pax);
			if(!(addPassenger(ListPax, TAMLIST, id, pax.name, pax.lastname, pax.price, pax.typePassenger, pax.flycode))){
				flag = 1;
				id++;
				printf("GUARDADO");
			}
			break;
		case 2:
			if(flag == 1){
				printPassenger(ListPax, TAMLIST);
				printf("\nINGRESE ID DEL pax: ");
				scanf("%d",&sid);
				setMPaxData(&pax,ListPax);
				if(modPaxData(sid,pax, ListPax, TAMLIST)){
					printf("ERROR, modificacion no hecha");
				}
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		case 3:
			if(flag == 1){
				printPassenger(ListPax, TAMLIST);
				printf("INGRESE ID DE PASAJERO A BORRAR: ");
				setbuf(stdin,NULL);
				scanf("%d",&sid);
				removePassenger(ListPax, TAMLIST, sid);
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		case 4:
			/*
			 4. INFORMAR:
				1. Listado de los pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero.
				2. Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio
				promedio.
				3. Listado de los pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’
			 */
			if(flag == 1){
				option2 = MenuGeneral(1, "1.Listado por apellido y tipo de pasajeros\n", "2.Total y promedio de precios\n", "3.Listado de los pasajeros (Vuelo y estado)\n", "", "", "");
				switch(option2){
				case 1:
					do{
						printf("Orden ascendente (1) o descendente (0)");
						scanf("%d",&order);
						if(order != 1 || order != 0){
							printf("")
						}
					}while(order != 1 || order != 0);
					sortPassengersByName(ListPax, TAMLIST, order);
				break;
//					printPassenger(ListPax, TAMLIST);
//					printf("Presione cualquier LETRA para continuar ");
//					setbuf(stdin,NULL);
//					scanf("%c",&cont);
				}
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		case 5:

			break;
		}
	} while(option != 0);

	return EXIT_SUCCESS;
}
