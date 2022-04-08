/*
 * calculos.h
 *
 *  Created on: 7 abr. 2022
 *      Author: Javier
 */

#ifndef CALCULOS_H_
#define CALCULOS_H_

void MostrarResultados(char nombre[30],float precio,float prcTD,float prcTC,float prcBTC,float prcUnit);
float PrcTD(float precio);
float PrcTC(float precio);
float PrcBTC(float precio);
float PrcUnit(int km,float precio);
float DifPrc(float precioA,float precioB);

#endif /* CALCULOS_H_ */
