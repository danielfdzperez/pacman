/*Este programa se encarga de leer un archivo, pedir al usuario un numero y ordenar los numeros de mayor a menor,
 mostrar los 10 mayores numeros por pantalla*/
#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *archivo;
  int numero[11],
      con[11],
      var[11];
  //abre el flujo de datos
  archivo = fopen ("numero.txt", "r");
  //recoge todas las puntuaciones
  for(int pasada=0; pasada<10; pasada++)
  fscanf(archivo, " %*i %i", &numero[pasada]);
  //se cierra el flujo
  fclose(archivo);

  //pide al usuario que introduzca un numero
  printf("Introduzca numero: ");
  scanf(" %i", &numero[10]);

  //ordena los numeros de mayor a menor, incluido el del usuario
  for(int numeros=0; numeros<11; numeros++){
    con[numeros] = 0;
    for (int comparador=0; comparador<11; comparador++)
      if(numero[numeros] < numero[comparador])
	 con[numeros] ++;

     var[con[numeros]] = numero[numeros];
  }//fin for numeros
  //imprime por pantalla los 10 mayores numeros
  for(int imprime=0; imprime<10; imprime++)
    printf("%iº \t%i\n", imprime+1, var[imprime]);

  return EXIT_SUCCESS;
}
