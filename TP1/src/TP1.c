/*
 ============================================================================
 Name        : TP1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreriaP.h"
#include "Calculos.h"


int main(void) {
	setbuf(stdout,NULL);

	char menu,menu2;
	int x = 0;
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	float y,z = 0;
	float prcAerolineasTD,
		  prcAerolineasTC,
		  prcAerolineasBTC,
		  prcAerolineasUnit,
		  prcLatamTD,
		  prcLatamTC,
		  prcLatamBTC,
		  prcLatamUnit,
		  difPrc;

	do{
		printf("\n\nVuelos Aerolineas: %.2f\nVuelos LATAM: %.2f",y,z);
		menu = MenuGeneral(0,"1.Ingresar Kilometros\n", "2.Ingresar Precio de vuelos\n", "3.Calcular todos los costos\n", "4.Informar resultados\n", "5.Carga forzada de datos\n", "");
		switch (menu) {
		case 1:
			setbuf(stdin,NULL);
			x = IngresarEntero("Ingrese Km totales del viaje:",1);
			//evito dividir por 0
			if(!(x == 0)){
				flag1 = 1;
			}
			break;
		case 2:
			do{
				printf("Y. Precio Vuelo por Aerolineas Argentinas\n");
				printf("Z. Precio Vuelo por LATAM\n");
				printf("o ingresa 0 para regresar\n");
				setbuf(stdin,NULL);
				scanf("%c",&menu2);
				switch (menu2){
				case 'y':
					y = IngresarFlotante("Ingrese Precio:",1);
					break;
				case 'z':
					z = IngresarFlotante("Ingrese Precio:",1);
					break;
				default:
					printf("ERROR: numero fuera del rango de menu ingrese uno dentro de los mostrados\n");
				}
				if(!(y == 0 || z == 0 )){
					flag2 = 1;
				}
			}while(menu2 != '0');

			break;
		case 3:
			if(flag1 && flag2){

				prcAerolineasTD = PrcTD(y);
				prcAerolineasTC = PrcTC(y);
				prcAerolineasBTC = PrcBTC(y);
				prcAerolineasUnit = PrcUnit(x, y);

				prcLatamTD = PrcTD(z);
				prcLatamTC = PrcTC(z);
				prcLatamBTC = PrcBTC(z);
				prcLatamUnit = PrcUnit(x, z);

				difPrc = DifPrc(y, z);

				flag3 = 1;
			} else {
				printf("no se ingreso alguno de los datos necesarios\nCONSEJOS:\n");
				if(!flag1){
					printf("vaya al punto 1 del menu\n");
				}
				if(!flag2){
					printf("vaya al punto 2 del menu\n");
				}
			}
			break;
		case 4:
			if(flag3){

				printf("KMs ingresados: %d km\n\n",x);

				MostrarResultados("Aerolineas", y, prcAerolineasTD, prcAerolineasTC, prcAerolineasBTC, prcAerolineasUnit);
				MostrarResultados("LATAM", z, prcLatamTD, prcLatamTC, prcLatamBTC, prcLatamUnit);

				printf("\nLa diferencia de precio es: $ %.2f", difPrc);


				printf("\n\n\nPresione cualquier letra para continuar...\n");
				setbuf(stdin,NULL);
				scanf("%c",&menu);

			} else {
				printf("No hay datos para mostrar, calcule datos primero '3' en el menu");
			}

			break;
		case 5:
			x = 7090;
			y = 162965;
			z = 159339;

			prcAerolineasTD = PrcTD(y);
			prcAerolineasTC = PrcTC(y);
			prcAerolineasBTC = PrcBTC(y);
			prcAerolineasUnit = PrcUnit(x, y);

			prcLatamTD = PrcTD(z);
			prcLatamTC = PrcTC(z);
			prcLatamBTC = PrcBTC(z);
			prcLatamUnit = PrcUnit(x, z);

			difPrc = DifPrc(y, z);

			printf("KMs ingresados: %d km\n\n",x);

			MostrarResultados("Aerolineas", y, prcAerolineasTD, prcAerolineasTC, prcAerolineasBTC, prcAerolineasUnit);
			MostrarResultados("LATAM", z, prcLatamTD, prcLatamTC, prcLatamBTC, prcLatamUnit);
			x = 0;
			y = 0;
			z = 0;

			printf("\nLa diferencia de precio es: $ %.2f", difPrc);

			printf("\n\n\nPresione cualquier letra para continuar...\n");
			setbuf(stdin,NULL);
			scanf("%c",&menu);
			break;
		case 0:
			printf("Saliendo...");
			break;
		default:
			printf("ERROR: numero fuera del rango de menu ingrese uno dentro de los mostrados");
		}
	}while(menu != 0);

	return EXIT_SUCCESS;
}
