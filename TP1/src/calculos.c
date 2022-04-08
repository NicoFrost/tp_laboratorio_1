#include <stdio.h>
#include <stdlib.h>
#include "Calculos.h"

float BTC = 4606954.55;

void MostrarResultados(char nombre[30],float precio,float prcTD,float prcTC,float prcBTC,float prcUnit){

	printf("Precio %s: %.2f\n",nombre,precio);
	printf("a) Precio de tarjeta de debito: $ %.2f\n",prcTD);
	printf("b) Precio de tarjeta de credito: $ %.2f\n",prcTC);
	printf("c) Precio pagando con bitcoin: $ %.2f BTC\n",prcBTC);
	printf("d) Mostrar Precio unitario: $ %.2f\n\n",prcUnit);


}

float PrcTD(float precio){
	return precio - (precio * .10);
}

float PrcTC(float precio){
	return precio + (precio * .25);
}

float PrcBTC(float precio){
	return precio / BTC;
}

float PrcUnit(int km,float precio){
	return precio / km;
}

float DifPrc(float precioA,float precioB){
	int retorno;
	if(precioA > precioB){
		retorno = precioA - precioB;
	} else {
		retorno = precioB - precioA;
	}
	return retorno;
}
