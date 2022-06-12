#ifndef INPUT_H_
#define INPUT_H_

int MenuGeneral(int submenu,char mensaje1[], char mensaje2[], char mensaje3[], char mensaje4[], char mensaje5[], char mensaje6[],char mensaje7[],char mensaje8[],char salida);
/**\fn int MenuGeneral("","","","","","");
 * \brief Ejecuta un menu general y devuelve la respuesta
 * \param ninguno
 * \return respuesta de 1-6 para iniciar una accion detallada en el menu
 */

int IngresarEntero(char mensaje[],int verif);

float IngresarFlotante(char mensaje[],int verif);

void getString(char cadena[],char mensaje[],int tam);

void OrdenamientoBurbujaAscendente(int numero[],int cant,int *puntero);

void OrdenamientoBurbujaDescendente(int numero[],int cant,int *puntero);

int validarIntervalo(int numero, int min, int max,int flag);

void InicializarArray(int array[],int cantidad);

int BuscarEspacio(int array[],int cantidad);

int isStrAlpha(char string[]);

int flyCodeVerif(char* codigo);
#endif
