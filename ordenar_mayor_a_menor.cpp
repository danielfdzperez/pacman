#include <stdlib.h>
#include <stdio.h>

void comprobacion(int argc, char *argv[]){
    //comprueba que hay parametros sufivientes
    if(argc < 5 ){
	fprintf(stderr, "uso: %s <numero> <numero> <numero> <numero> \n", argv[0]);
	exit (EXIT_FAILURE);
    }
}//fin comprobacion

void ordenar(int argc, int var[], int numeros[]){
    //coloca los numeros en orden de mayor a menor
    int con [argc - 1];

    for(int numero=0; numero<argc-1; numero++){
	con[numero] = 0;
	for (int comparador=0; comparador<argc-1; comparador++)
	    if(numeros[numero] < numeros[comparador])
		con[numero] ++;
	var[con[numero]] = numeros[numero];
    }
}//fin ordenar

void imprimir(int var[], int argc){
    //imprime los numeros
    for(int imprime=0; imprime<argc-1; imprime++){
	printf("%iº - %i\n", imprime+1, var[imprime]);
    }
}//fin imprimir
int main (int argc, char *argv[]){
    //define las variables
    int numeros[argc - 1],	
	var    [argc - 1];

    comprobacion(argc, argv);

    for(int a=0; a<argc-1; a++)
	numeros[a] = atoi(argv[a+1]);
    
    ordenar(argc, var, numeros);
    imprimir(var, argc);

	return EXIT_SUCCESS;
}
