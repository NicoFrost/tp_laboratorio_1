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
//	char cont;
	int id = 1,flag = 0;
	int fid;
	int sid;

	Passenger ListPax[TAMLIST];
	Passenger pax;
	ClearPax(&pax);
	initPassengers(ListPax, TAMLIST);


	do{
		option = MenuGeneral(0, "1.ALTA\n", "2.MODIFICACION\n", "3.BAJA\n", "4.INFORMAR\n", "5.ALTA FORZADA\n", "");
		switch(option){
		case 1:
			if(setPaxData(&pax)){
				if(!(addPassenger(ListPax, TAMLIST, id, pax.name, pax.lastname, pax.price, pax.typePassenger, pax.flycode, pax.statusFlight))){
					flag = 1;
					id++;
					printf("GUARDADO");
				}
			}
			ClearPax(&pax);
			break;
		case 2:
			if(flag == 1){
				printPassenger(ListPax, TAMLIST);
				printf("\nINGRESE ID DEL pax: ");
				scanf("%d",&fid);
				sid = findPassengerById(ListPax, TAMLIST, fid);
				if(sid != -1){
					setMPaxData(&pax,ListPax);
					if(!(modPaxData(sid,pax, ListPax, TAMLIST))){
						printf("ERROR, modificacion no hecha");
					}
				} else {
					printf("ERROR, ID no encontrado");
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
				scanf("%d",&fid);
				sid = findPassengerById(ListPax, TAMLIST, fid);
				if(sid != -1){
					removePassenger(ListPax, TAMLIST, sid);
				} else {
					printf("ERROR, ID no encontrado");
				}
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		case 4:
			if(flag == 1){
				MostrarInformes(ListPax, TAMLIST);
			} else {
				printf("Debe ingresar al menos un Pasajero");
			}
			break;
		case 5:
			addPassenger(ListPax, TAMLIST, id, "Nicolas", "Gorza", 7000, 2, "ARG1200", 1);
			id++;
			addPassenger(ListPax, TAMLIST, id, "Javier", "Gorza", 7500, 2, "ARG1200", 1);
			id++;
			addPassenger(ListPax, TAMLIST, id, "Martin", "Minochieti", 5930, 3, "FBZ1223", 0);
			id++;
			addPassenger(ListPax, TAMLIST, id, "Maria ", "Lopez", 15500, 1, "WIX8925", 1);
			id++;
			addPassenger(ListPax, TAMLIST, id, "Alberto", "Gutierrez", 6012, 3, "FBZ1244", 0);
			id++;
			addPassenger(ListPax, TAMLIST, id, "Fernando", "Lacosta", 6012,3, "LAN2123", 1);
			id++;
			if(flag != 1){
				flag = 1;
				printf("DATOS CARGADOS");
			}
			break;
		}
	} while(option != 0);

	return EXIT_SUCCESS;
}
