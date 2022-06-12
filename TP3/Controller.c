#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "FuncionesABM.h"

#define TAM 50
/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	FILE* pArchivo;
	pArchivo = fopen(path,"r");
		parser_PassengerFromText(pArchivo, pArrayListPassenger);
	fclose(pArchivo);
	return 1;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
	FILE* pArchivob;
	pArchivob = fopen(path,"rb");
		parser_PassengerFromBinary(pArchivob, pArrayListPassenger);
	fclose(pArchivob);
    return 1;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger)
{
	Passenger* nuevoPasajero = Passenger_new();
	int lastId;
	if(setPaxData(nuevoPasajero)){
		Passenger_getLastId(pArrayListPassenger, &lastId);
		Passenger_add(pArrayListPassenger,nuevoPasajero,lastId);
	}
    return 1;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int sId;
	Passenger_list(pArrayListPassenger);
	printf("\nIngrese un ID para modificar: ");
	scanf("%d",&sId);
	Passenger_mod(pArrayListPassenger,sId);
    return 1;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int sId;
	Passenger_list(pArrayListPassenger);
	printf("\nIngrese un ID para eliminar: ");
	scanf("%d",&sId);
	Passenger_delete(pArrayListPassenger,sId);
    return 1;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */

int controller_ListPassenger(LinkedList* pArrayListPassenger)
{

	Passenger_list(pArrayListPassenger);

    return 1;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int order;
	int option;
	if(pArrayListPassenger != NULL){
		printf("Seleccione Filtro\n");
		printf("1.Por Apellido\n2.Por codigo de vuelo\n");
		scanf("%d",&option);
		printf("Orden ascendente(1),Orden descendente(0)\n");
		setbuf(stdin,NULL);
		scanf("%d",&order);
		printf("Ordenando espere...");
		switch (option){
		case 1:
			ll_sort(pArrayListPassenger,Passenger_sortByLastname, order);
			break;
		case 2:
			ll_sort(pArrayListPassenger,Passenger_sortByCode,order);
			break;
		}
	}

    return 1;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = 0;
	FILE* pArchivo;
	if(path != NULL && pArrayListPassenger != NULL){
		pArchivo = fopen(path,"w");
		if(pArchivo != NULL){
			if(GuardarTxt(pArchivo,pArrayListPassenger)){
				retorno = 1;
			} else {
				printf("ERROR, no se pudo escribir el archivo\n");
			}
			fclose(pArchivo);
		} else {
			printf("ERROR, no se pudo abrir el archivo\n");
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno;
	FILE *parchivob;
	Passenger* pasajeroAux;
	int cantidadEscritos;
	int len = ll_len(pArrayListPassenger);

	parchivob = fopen(path,"wb");
	if (parchivob != NULL && pArrayListPassenger != NULL){
		for(int i = 0;i < len;i++){
			pasajeroAux = ll_get(pArrayListPassenger, i);
			printf("->%s %s\n",pasajeroAux->nombre,pasajeroAux->apellido);
			cantidadEscritos = fwrite(pasajeroAux,sizeof(Passenger),1,parchivob);
		}
		if(cantidadEscritos == len){
			retorno = 1;
		}
		fclose(parchivob);
	}

	return retorno;
}

