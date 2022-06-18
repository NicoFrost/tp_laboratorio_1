#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
#define TAM 50
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	char fid[20];
	char fnombre[TAM];
	char flastname[TAM];
	char fprecio[TAM];
	char fcodigoVuelo[8];
	char ftipoPasajero[TAM];
	char festadoVuelo[TAM];
	Passenger* pasajeroAux;

	//Lectura Fantasma
	fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",fid,fnombre,flastname,fprecio,fcodigoVuelo,ftipoPasajero,festadoVuelo);


	do{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",fid,fnombre,flastname,fprecio,fcodigoVuelo,ftipoPasajero,festadoVuelo);
		pasajeroAux = Passenger_newParametros(fid, fnombre, flastname, fprecio, fcodigoVuelo, ftipoPasajero, festadoVuelo);
		ll_add(pArrayListPassenger, pasajeroAux);
	}while(!feof(pFile));
	return 1;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1,cantidadLeidos;
	Passenger* pasajeroAux;
	if(pFile != NULL){
		while(!feof(pFile)){
			pasajeroAux = Passenger_new();
			cantidadLeidos = fread(pasajeroAux,sizeof(Passenger),1,pFile);
			if(cantidadLeidos == 1){
			ll_add(pArrayListPassenger, pasajeroAux);
			printf("-> %s %s\n",pasajeroAux->nombre,pasajeroAux->apellido);
			retorno = 0;
			}
		}
	}
	return retorno;
}
