/*Este programa se encarga de leer un archivo, pedir al usuario un numero y ordenar los numeros de mayor a menor,
  mostrar los 10 mayores numeros por pantalla*/
#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD_DE_NUMEROS 11
int main(){
    FILE *archivo, 
	 *archivo2;
    int numero[CANTIDAD_DE_NUMEROS],
	temporal;
    //abre el flujo de datos
    archivo = fopen ("numero.txt", "r");
    //recoge todas las puntuaciones
    if(archivo == NULL){
	archivo = fopen ("numero.txt", "w+");
	for(int imprime=0; imprime<10; imprime++)
	    fprintf(archivo, "%i \t0\n", imprime+1);
	fclose(archivo);
	archivo = fopen ("numero.txt", "r");
    }

    for(int pasada=0; pasada<10; pasada++){
	fscanf(archivo, " %*i %i", &numero[pasada]);
	printf("%i\n", numero[pasada]);
    }
    //se cierra el flujo
    fclose(archivo);


    //pide al usuario que introduzca un numero
    printf("Introduzca numero: ");
    scanf(" %i", &numero[10]);

    //ordena los numeros de mayor a menor, incluido el del usuario
    for(int mayor=CANTIDAD_DE_NUMEROS; mayor>=0; mayor--){
	for (int menor=mayor-1; menor>=0; 
		menor--){
	    if(numero[mayor] > numero[menor]){
		temporal = numero[menor];
		numero[menor] = numero[mayor];
		numero[mayor] = temporal;

	    }//fin if
	}//fin for menor
    }//fin for mayor
    //imprime por pantalla los 10 mayores numeros
    archivo2 = fopen("numero.txt", "w");
    for(int menor=1; menor<CANTIDAD_DE_NUMEROS; menor++)
	fprintf(archivo2, "%i \t%i\n", menor, numero[menor]);
    fclose(archivo2);

    return EXIT_SUCCESS;
}
