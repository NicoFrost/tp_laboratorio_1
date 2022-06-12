#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "libreriaP.h"



/****************************************************
    Menu:
     1. Carga de datos
     	 A. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     	 B. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     2. Alta de pasajero
     3. Modificar datos de pasajero
     4. Baja de pasajero
     5. Listar pasajeros
     6. Ordenar pasajeros
	 7.
		 1. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
		 2. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    8. Salir
*****************************************************/



int main()
{
    int option = 0;
    int option2 = 0;
    int flagCarga = 0;
    int flagAlta = 0;
	int flagGuardar = 0;
    setbuf(stdout,NULL);
    LinkedList* listaPasajeros = ll_newLinkedList();

    do{
    	option = MenuGeneral(0, "1.Cargar los datos de pasajeros\n", "2.Alta de pasajeros\n", "3.Modificacion de pasajeros\n", "4.Baja de pasajeros\n", "5.Listar pasajeros\n", "6.Ordenar Pasajeros\n", "7.Guardar datos de pasajeros\n","",'8');
    	switch(option)
        {
            case 1:
            	if(flagCarga == 0 && flagAlta != 1){
						do{
							option2 = MenuGeneral(1, "1.Cargar desde archivo de texto\n", "2.Cargar desde archivo binario\n", "", "", "", "", "", "", '0');
							switch (option2) {
								case 1:
									controller_loadFromText("data.csv", listaPasajeros);
									flagCarga = 1;
									flagAlta = 1;
									flagGuardar = 0;
									break;
								case 2:

									controller_loadFromBinary("data.bin", listaPasajeros);
									flagCarga = 1;
									flagAlta = 1;
									flagGuardar = 0;
									break;
							}
						}while(option2 != 0);
					} else {
						printf("Ya se han cargado datos. No pueden cargarse de nuevo hasta que se guarden");
            	}
            	break;
            case 2:
            	if(flagCarga == 0 && flagAlta != 1){
            		controller_loadFromText("data.csv", listaPasajeros);
            		flagCarga = 1;
            	}
            	if(controller_addPassenger(listaPasajeros)){
            		flagAlta = 1;
            	}
            	break;
            case 3:
            	if(flagAlta == 1){
            		controller_editPassenger(listaPasajeros);
            	} else {
            		printf("Debe agregar al menos 1 pasajero para empezar\n");
            	}
            	break;
            case 4:
            	if(flagAlta == 1){
            		controller_removePassenger(listaPasajeros);
            	} else {
            		printf("Debe agregar al menos 1 pasajero para empezar\n");
            	}            	break;
            case 5:
            	if(flagAlta == 1){
            		controller_ListPassenger(listaPasajeros);
            	} else {
            		printf("Debe agregar al menos 1 pasajero para empezar\n");
            	}            	break;
            case 6:
            	if(flagAlta == 1){
            		controller_sortPassenger(listaPasajeros);
            	} else {
            		printf("Debe agregar al menos 1 pasajero para empezar\n");
            	}            	break;
            case 7:
            	if(flagCarga == 1){
            			do{
						option2 = MenuGeneral(1, "1.Guardar desde archivo de texto\n", "2.Guardar desde archivo binario\n", "", "", "", "", "", "", '0');
						switch (option2) {
							case 1:

								if(controller_saveAsText("data.csv",listaPasajeros)){
									flagCarga = 0;
									flagGuardar = 1;
								}
								break;
							case 2:

								if(controller_saveAsBinary("data.bin", listaPasajeros)){
									flagCarga = 0;
									flagGuardar = 1;
								}
								break;
						}
					}while(option2 != 0);
            	} else {
            		printf("debe cargar primero los Pasajeros antes de poder guardar");
            	}
            	break;
            case 8:
            	if(flagGuardar != 1){
            		option = 10;
            	}
            	break;
    		default:
    			printf("ERROR: numero fuera del rango de menu ingrese uno dentro de los mostrados");
        	}
        }while(option != 8);
    return 0;
}

