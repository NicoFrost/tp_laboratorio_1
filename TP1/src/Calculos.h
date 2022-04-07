/*
 * calculos.h
 *
 *  Created on: 7 abr. 2022
 *      Author: Javier
 */

#ifndef CALCULOS_H_
#define CALCULOS_H_

void MostrarResultados(char nombre[30],float precio,float prcTD,float prcTC,float prcBTC,float prcUnit);
float PrcTD(int precio);
float PrcTC(int precio);
float PrcBTC(int precio);
float PrcUnit(int km,int precio);
float DifPrc(int precioA,int precioB);

#endif /* CALCULOS_H_ */
