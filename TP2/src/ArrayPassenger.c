#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estructuras.h"
#include "Funciones.h"
/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initPassengers(Passenger* list, int len){
	int r = -1;
	if(len > 0 && list != NULL ){
		for(int i = 0; i < len;i++){
			list[i].isEmpty = 1;
		}
		r = 0;
	}
	return r;
}

/** \brief add in a existing list of passengers the values received as parameters
* in the first empty position
* \param list passenger*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param price float
* \param typePassenger int
* \param flycode[] char
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*/
int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[]){
	int r = -1;
	int i = findFreeSpace(list, len);

	if(i != -1 && len > 0 && list != NULL && name != NULL && lastName != NULL && flycode != NULL){
		list[i].id = id;
		strcpy(list[i].name,name);
		strcpy(list[i].lastname,lastName);
		list[i].price = price;
		list[i].typePassenger = typePassenger;
		strcpy(list[i].flycode,flycode);
		list[i].isEmpty = 0;
		r = 0;
	}

	return r;
}

/** \brief find a Passenger by Id en returns the index position in array.
*
* \param list Passenger*
* \param len int
* \param id int
* \return Return passenger index position or (-1) if [Invalid length or
NULL pointer received or passenger not found]
*
*/
int findPassengerById(Passenger* list, int len,int id)
{
	int i = -1;

	if(len > 0 && list != NULL && id > 0){
		for(i = 0;i < len;i++){
			if(list[i].isEmpty == 0 && list[i].id == id){
				break;
			}
		}
		if(i == len){
			i = -1;
		}
	}

	return i;
}

/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*
*/
int removePassenger(Passenger* list, int len, int id){

	int i = findPassengerById(list, len, id);

	if(i != -1){
		list[i].isEmpty = 1;
		i = 0;
	}

	return i;
}

/** \brief Sort the elements in the array of passengers, the argument order
indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortPassengersByName(Passenger* list, int len, int order){

	if(order == 0 || order == 1){
		char strAux[51];
		int iAux;
		float fAux;
		for(int i = 0;i < len-1;i++){
			for(int j = i+1;j < len;j++){
				if(order == 1){
					if(strcmp(list[i].lastname,list[j].lastname) >= 0 && list[i].typePassenger >= list[j].typePassenger ){
						strcpy(strAux,list[i].name);
						strcpy(list[i].name,list[j].name);
						strcpy(list[j].name,strAux);

						strcpy(strAux,list[i].lastname);
						strcpy(list[i].lastname,list[j].lastname);
						strcpy(list[j].lastname,strAux);


						fAux = list[i].price;
						list[i].price = list[j].price;
						list[j].price = fAux;

						strcpy(strAux,list[i].flycode);
						strcpy(list[i].flycode,list[j].flycode);
						strcpy(list[j].flycode,strAux);

						iAux = list[i].typePassenger;
						list[i].typePassenger = list[j].typePassenger;
						list[j].typePassenger = iAux;

						iAux = list[i].isEmpty;
						list[i].isEmpty = list[j].isEmpty;
						list[j].isEmpty = iAux;

					}
				} else {
					if(strcmp(list[i].name,list[j].name) <= 0){
						strcpy(strAux,list[i].name);
						strcpy(list[i].name,list[j].name);
						strcpy(list[j].name,strAux);

						strcpy(strAux,list[i].lastname);
						strcpy(list[i].lastname,list[j].lastname);
						strcpy(list[j].lastname,strAux);


						fAux = list[i].price;
						list[i].price = list[j].price;
						list[j].price = fAux;

						strcpy(strAux,list[i].flycode);
						strcpy(list[i].flycode,list[j].flycode);
						strcpy(list[j].flycode,strAux);

						iAux = list[i].typePassenger;
						list[i].typePassenger = list[j].typePassenger;
						list[j].typePassenger = iAux;

						iAux = list[i].isEmpty;
						list[i].isEmpty = list[j].isEmpty;
						list[j].isEmpty = iAux;
					}
				}
			}
		}
	}

	return 0;
}

/** \brief print the content of passengers array
*
* \param list Passenger*
* \param length int
* \return int
*
*/

//sortPassengersByCode(Passenger* list, int len,int order){
//
//}


int printPassenger(Passenger* list, int length){

	printf("-------------------------------------------------------------------------\n");
	printf("| ID\t|     NOMBRE\t|    APELLIDO\t|    PRECIO\t| TIPO\t|     VUELO\t|\n");
	printf("-------------------------------------------------------------------------\n");
	for(int i = 0;i < length;i++){
		if(list[i].isEmpty == 0){
			printf("| %d\t| %s\t| %s \t| $%.2f\t| %d\t| %s\t|\n",list[i].id,list[i].name,list[i].lastname,list[i].price,list[i].typePassenger,list[i].flycode);
		}
	}
	printf("-------------------------------------------------------------------------\n");

	return 0;
}


