/*Comecocos 12 estable*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <time.h>

#define FILAS 33 //cantidad filas
#define COLUMNAS 28//cantidad columnas
#define ENEMIGOS 4//enemigos
#define USUARIO 2//fila y col de usuario
#define MCOCOS 246//cantidad de cocos que hay
#define COORDENADAS 2//cantidad de coordenadas que hay x o y
#define ASTERISCOS 4//cantidad de asteriscos

enum TipoOpcion {jugar=1, instrucciones, top, salir};


enum TipoOpcion menu(){
    int opcion;
    system("clear");
    printf("\t\t\tPAC-MAN\n"
	    "\t\t1-Jugar\n"
	    "\t\t2-Instrucciones\n"
	    "\t\t3-Top 10 jugadores\n"
	    "\t\t4-Salir\n");
    printf("\tSu opcion: ");
    scanf(" %i", &opcion);
    __fpurge(stdin);
    return (enum TipoOpcion) opcion;
}

//actualiza la matriz matriz con la matriz info
void actualizar_matrices(char info[FILAS][COLUMNAS], char matriz[FILAS][COLUMNAS]){
    for(int fila=0; fila<FILAS; fila++)
	for(int col=0; col<COLUMNAS; col++)
	    //pone el valor de la matriz info en la matriz matriz
	    matriz[fila][col] = info[fila][col];
}//fin actualizar_matrices

//muestra el manual del juego
void manual(){
    FILE *archivo;
    char caracter,
	 salir;

    system("clear");

    archivo = fopen("manual.txt","r");

    if (archivo == NULL){

	printf("\nEl archivo manual.txt no existe\n\n");
    }
    else{

	while (feof(archivo) == 0)
	{
	    caracter = fgetc(archivo);
	    printf("%c",caracter);
	}
	fclose(archivo);

    }
    printf("Pulse enter para continuar\n");
    salir = getchar();
}//fin manual

//muestra las puntuaciones.
void top_puntuaciones(){
    FILE *archivo;
    char caracter,
	 salir;

    system("clear");

    archivo = fopen("puntuaciones.txt","r");

    if (archivo == NULL){

	printf("\nEl archivo puntuaciones.txt no existe\n\n");
    }
    else{

	while (feof(archivo) == 0)
	{
	    caracter = fgetc(archivo);
	    printf("%c",caracter);
	}
	fclose(archivo);
    }//fin else
    printf("Pulse enter para continuar\n");
    salir = getchar();

}//fin top_puntuaciones

//carga el mapa desde el archivo mapa_comecocos.txt
void cargar_mapa(char matriz[FILAS][COLUMNAS], char info[FILAS][COLUMNAS]){

    FILE *fichero;
    char salir;

    fichero = fopen("mapa_comecocos.txt", "r");
    if(fichero == NULL){
	printf("No existe el archivo mapa_comecocos.txt\n"
		"Si no posee este archivo usted no puede jugar al come-cocos\n");
	salir = getchar();
	exit(EXIT_SUCCESS);
    }
    else{
	for(int fila=0; fila<FILAS; fila++)
	    for(int col=0; col<COLUMNAS; col++){
		//guarda el mapa en la matriz info
		fscanf(fichero, " %c", &info[fila][col]);
	    }
	fclose(fichero);
    }
}//fin cargar_mapa

//especifica la posicion inicial del usuario y los fantasmas
void posiciones_jugadores(char matriz[FILAS][COLUMNAS], int pos_usuario[USUARIO], int pos_maquina[ENEMIGOS][2], char dibujo_enemigo[ENEMIGOS]){
    //se especifican todas las posiciones de los fantasmas y el comecocos
    pos_usuario[0] = 25;//fila
    pos_usuario[1] = 13;//columna
    pos_maquina[0][0] = 1;//fila
    pos_maquina[0][1] = 26;//columnas
    pos_maquina[1][0] = 1;//fila
    pos_maquina[1][1] = 1;//columna
    pos_maquina[2][0] = 31;//fila
    pos_maquina[2][1] = 1;//col
    pos_maquina[3][0] = 31;//fila
    pos_maquina[3][1] = 26;//col



    //se coloca a los fantasmas y al usuario en matriz
    matriz[pos_usuario[0]][pos_usuario[1]] = 'C';
    matriz[pos_maquina[0][0]][pos_maquina[0][1]] = dibujo_enemigo[0];
    matriz[pos_maquina[1][0]][pos_maquina[1][1]] = dibujo_enemigo[1];
    matriz[pos_maquina[2][0]][pos_maquina[2][1]] = dibujo_enemigo[2];
    matriz[pos_maquina[3][0]][pos_maquina[3][1]] = dibujo_enemigo[3];
}

/*DEBE MEJORARSE*/
//posiciones iniciales de la maquina
void posiciones_iniciales_maquina(int pos_inicial_maquina[ENEMIGOS][COORDENADAS]){
    pos_inicial_maquina[0][0] = 1; 
    pos_inicial_maquina[0][1] = 26;
    pos_inicial_maquina[1][0] = 1;
    pos_inicial_maquina[1][1] = 1;
    pos_inicial_maquina[2][0] = 31;
    pos_inicial_maquina[2][1] = 1;
    pos_inicial_maquina[3][0] = 31;
    pos_inicial_maquina[3][1] = 26;
}//fin posiciones_iniciales_maquina

//inicializa la matriz
void inicializar_matriz(char matriz[FILAS][COLUMNAS], int pos_usuario[USUARIO], int pos_maquina[ENEMIGOS][2], char info[FILAS][COLUMNAS],
	char dibujo_enemigo[ENEMIGOS]){

    //se cambian los caracteres del mapa por unos mas faciles de distinguir
    for(int fila=0; fila<FILAS; fila++)
	for(int col=0; col<COLUMNAS; col++)
	    if(info[fila][col] == '0')
		info[fila][col] = '.';
	    else
		if(info[fila][col] == '8')
		    info[fila][col] = ' ';
		else
		    if(info[fila][col] == '2')
			info[fila][col] = 'H';
		    else
			if (info[fila][col] == '1')
			    info[fila][col] = '*';

    //se actualizan las matrices
    actualizar_matrices(info, matriz); 
    posiciones_jugadores(matriz, pos_usuario, pos_maquina, dibujo_enemigo);  
}//fin inicializar matriz

//recuenta los cocos
int recuento_cocos(char info[FILAS][COLUMNAS]){
    int cocos_totales = 0;
    //recorre la mamtriz info contando los cocos que hay
    for(int filas=0; filas<FILAS; filas++)
	for(int col=0; col<COLUMNAS; col++)
	    if(info[filas][col] == '.')
		cocos_totales ++;
    //retorna un entero
    return cocos_totales;
}//fin recuento_cocos

//comprueba si el usuario se ha comido todos los cocos y pasa de nivel
int comprobar_fin_nivel(char info[FILAS][COLUMNAS]){
    int cocos_totales = 0,
	final_nivel = 0;
    //resta cocos que hay en total menos los que hay actualmente
    cocos_totales = recuento_cocos(info);
    //si la resta da 0 se pasa de lvl.
    if (cocos_totales < 1 ){
	final_nivel = 1;
    }
    //no se pasa de nivel en otro caso
    else
	final_nivel = 0;
    //retorna un entero
    return final_nivel;
}//fin comprobar_fin_nivel

//Captura el movimiento escogido por el usuario.
char movimiento(){
    char respuesta;
    //coge los caracteres introducidos por el usuario
    do{
	system("/bin/stty raw");//permite que no se tenga que introducir el espacio para coger un caracter
	respuesta = getchar();//coge los caracteres
	system("/bin/stty cooked");

	__fpurge(stdin);
	//comprueba que los caracteres introducidos sean los correctos
    }while(respuesta != 'a' && respuesta != 'd' && respuesta != 's' && respuesta != 'w' && respuesta != 'q');
    //retorna un char
    return respuesta;
}//fin movimiento

//imprime por pantalla la matriz
void refrescar(char matriz[FILAS][COLUMNAS], char info[FILAS][COLUMNAS], int vidas, int nivel, int puntuacion){
    //limpria la consola
    system("clear");
    //recorre la matriz y la imprime por pantalla
    for(int fila=0; fila<FILAS; fila++){
	for(int col=0; col<COLUMNAS; col++)
	    printf("%c ", matriz[fila][col]);
	printf("\n");
    }
    //imprime tantas vidas como le queden al usuario, el nivel y la puntuacion
    for(int comecocos=0; comecocos<vidas; comecocos++)
	printf("C ");

    printf("\t LVL%i  "
	    " Puntuacion:%i", nivel, puntuacion);
    printf("\n");
}//fin refrescar

//mueve al usuario
void mover_jugador(char respuesta, char info[FILAS][COLUMNAS], int pos_usuario[USUARIO], char matriz[FILAS][COLUMNAS]){
    //mueve al usuario dependiendo de la respuesta

    switch(respuesta){
	case 'd':
	    //comprueba que la siguiente posición no se un muro
	    if(info[pos_usuario[0]][pos_usuario[1] + 1] != 'H'){
		//pone un espacio y borra el coco de la matriz info del siguiente movimiento
		info[pos_usuario[0]][pos_usuario[1] + 1] = ' ';
		//actualiza las matrices
		actualizar_matrices(info, matriz);
		//pone al usuario en la siguiente posicion de la matriz matriz
		matriz[pos_usuario[0]][pos_usuario[1] + 1] = 'C';
		//suma uno a la posicion del usuario de las columnas
		pos_usuario[1] ++;
	    }
	    //si hay un muro en el siguiente movimiento
	    else{
		//actualiza las matrices
		actualizar_matrices(info, matriz);
		//pone al usuario en la posicion que estaba en la matriz matriz
		matriz[pos_usuario[0]][pos_usuario[1]] = 'C';
	    }
	    break;
	case 'a':
	    if(info[pos_usuario[0]][pos_usuario[1] - 1] != 'H'){
		info[pos_usuario[0]][pos_usuario[1] - 1] = ' ';
		actualizar_matrices(info, matriz);
		matriz[pos_usuario[0]][pos_usuario[1] - 1] = 'C';
		pos_usuario[1] --;
	    }
	    else{
		actualizar_matrices(info, matriz);
		matriz[pos_usuario[0]][pos_usuario[1]] = 'C';
	    }

	    break;
	case 's':
	    if(info[pos_usuario[0] + 1][pos_usuario[1]] != 'H'){
		info[pos_usuario[0] + 1][pos_usuario[1]] = ' ';
		actualizar_matrices(info, matriz);
		matriz[pos_usuario[0] + 1][pos_usuario[1]] = 'C';
		pos_usuario[0] ++;
	    }
	    else{
		actualizar_matrices(info, matriz);
		matriz[pos_usuario[0]][pos_usuario[1]] = 'C';
	    }
	    break;
	case 'w':
	    if(info[pos_usuario[0] - 1][pos_usuario[1]] != 'H'){
		info[pos_usuario[0] - 1][pos_usuario[1]] = ' ';
		actualizar_matrices(info, matriz);
		matriz[pos_usuario[0] - 1][pos_usuario[1]] = 'C';
		pos_usuario[0] --;
	    }
	    else{
		actualizar_matrices(info, matriz);
		matriz[pos_usuario[0]][pos_usuario[1]] = 'C';
	    }
	    break;
    }//fin switch

}//fin mover_jugador

//comprueba si el usuario se ha comido un coco
void recuento_puntuacion(char info[FILAS][COLUMNAS], int *cocos_anterior, int *puntuacion){
    //resta los cocos que habia con los cocos que hay actualmente
    //si el resultado es diferente de 0 se suma la puntuacion con la diferen de la resta
    //y resta 1 a los cocos anteriores
    if( *cocos_anterior - recuento_cocos(info) != 0){
	*puntuacion += *cocos_anterior - recuento_cocos(info);
	*cocos_anterior -= 1;
    }
}//fin recuento_puntuacion

//revisar
//mueve a la maquina
void mover_maquina(char matriz[FILAS][COLUMNAS], int pos_maquina[ENEMIGOS][2], int pos_usuario[USUARIO], char dibujo_enemigo[ENEMIGOS], bool asterisco_comido){
    int respuesta;

    for(int maquina=0; maquina<ENEMIGOS; maquina++)
	//comprueba que el usuario no se alla comido un asterisco
	if (asterisco_comido == false && dibujo_enemigo[maquina] == 'M'){
	    //comprueba si el usuario esta en la misma columna que la maquina
	    //misma columna
	    if(pos_usuario[1] == pos_maquina[maquina][1]){
		if(pos_maquina[maquina][0] - pos_usuario[0] > 0){
		    if(matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != 'H' && 
			    matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
			matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
			pos_maquina[maquina][0] --;
		    }
		    else
			//ir a repetir2
			goto repetir2;
		}else
		    if(matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != 'H' && 
			    matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
			matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
			pos_maquina[maquina][0] ++;
		    }
		    else
			goto repetir2;
	    }else
		//misma fila
		if(pos_usuario[0] == pos_maquina[maquina][0]){
		    if(pos_maquina[maquina][1] - pos_usuario[1] > 0){
			if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != 'H' && 
				matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != dibujo_enemigo[maquina]){
			    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] = dibujo_enemigo[maquina];
			    pos_maquina[maquina][1] --;
			}
			else
			    goto repetir2;
		    }else
			if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != 'H' && 
				matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != dibujo_enemigo[maquina]){
			    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] = dibujo_enemigo[maquina];
			    pos_maquina[maquina][1] ++;
			}
			else
			    goto repetir2;
		}else
		    //*************comprobar IA*********************
		    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		    /*Comprueba en que fila esta el usuario y la maquina y mueve a la maquina a la fila del usuario*/
		    if(pos_usuario[0] < pos_maquina[0][0] || pos_usuario[0] < pos_maquina[2][0])
			if(matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != 'H' && 
				matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
			    matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
			    pos_maquina[maquina][0] --;
			}
			else
			    goto repetir2;
		    else
			if(pos_usuario[0] > pos_maquina[0][0] || pos_usuario[0] > pos_maquina[2][0])
			    if(matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != 'H' && 
				    matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
				matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
				pos_maquina[maquina][0] ++;
			    }
			    else
				goto repetir2;
	    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
			else
			    /************************************************************************************/
			    /*Comprueba en que col esta el usuario y mueve a la maquina hacia el*/
			    if(pos_usuario[1] < pos_maquina[1][1] || pos_usuario[1] < pos_maquina[3][1])
				if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != 'H' && 
					matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != dibujo_enemigo[maquina]){
				    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] = dibujo_enemigo[maquina];
				    pos_maquina[maquina][1] --;
				}
				else
				    goto repetir2;
			    else
				if(pos_usuario[1] > pos_maquina[1][1] || pos_usuario[1] > pos_maquina[3][1])
				    if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != 'H' && 
					    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != dibujo_enemigo[maquina]){
					matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] = dibujo_enemigo[maquina];
					pos_maquina[maquina][1] ++;
				    }
				    else
					goto repetir2;
	    /*******************************************************************************************/
				else{


				    //genera una direccion aleatoria
//cambiar de nombre
repetir2:
				    respuesta = rand() % 4;
				    switch(respuesta){
					case 0:
					    //comprueba que el siguiente movimiento no sea en un muro
					    if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != 'H' && 
						    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != dibujo_enemigo[maquina]){
						//pone a la maquina en la siguiente posicion de la matriz matriz
						matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] = dibujo_enemigo[maquina];
						//suma uno a la coluimna de los fantasmas
						pos_maquina[maquina][1] ++;
					    }
					    else//si hay muro
						//guarda al fantasma en la posicion que estaba en la matriz matriz
						goto repetir2;
					    //matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1]] = 'M';
					    break;
					case 1:
					    if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != 'H' && 
						    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != dibujo_enemigo[maquina]){
						matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] = dibujo_enemigo[maquina];
						pos_maquina[maquina][1] --;
					    }
					    else
						goto repetir2;
					    //matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1]] = 'M';
					    break;
					case 2:
					    if(matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != 'H' && 
						    matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
						matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
						pos_maquina[maquina][0] ++;
					    }
					    else
						goto repetir2;
					    //matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1]] = 'M';
					    break;
					case 3:
					    if(matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != 'H' && 
						    matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
						matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
						pos_maquina[maquina][0] --;
					    }
					    else
						goto repetir2;
					    break;
				    }//fin switch
				}// fin else
	}//fin if
	else
	    //el usuario se comio un asterisco
	    //la maquina uye del usuario
	    //misma columna
	    if(pos_usuario[1] == pos_maquina[maquina][1]){
		if(pos_maquina[maquina][0] - pos_usuario[0] < 0){
		    if(matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != 'H' && 
			    matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
			matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
			pos_maquina[maquina][0] --;
		    }
		    else
			goto repetir;
		}else
		    if(matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != 'H' && 
			    matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
			matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
			pos_maquina[maquina][0] ++;
		    }
		    else
			goto repetir;
	    }else
		//misma fila
		if(pos_usuario[0] == pos_maquina[maquina][0]){
		    if(pos_maquina[maquina][1] - pos_usuario[1] < 0){
			if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != 'H' && 
				matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != dibujo_enemigo[maquina]){
			    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] = dibujo_enemigo[maquina];
			    pos_maquina[maquina][1] --;
			}
			else
			    goto repetir;
		    }else
			if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != 'H' && 
				matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != dibujo_enemigo[maquina]){
			    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] = dibujo_enemigo[maquina];
			    pos_maquina[maquina][1] ++;
			}
			else
			    goto repetir;
		}else
		    //*************comprobar IA*********************
		    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		    /*Comprueba en que fila esta el usuario y la maquina y mueve a la maquina a la fila del usuario*/
		    if(pos_usuario[0] > pos_maquina[0][0] || pos_usuario[0] > pos_maquina[2][0])
			if(matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != 'H' && 
				matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
			    matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
			    pos_maquina[maquina][0] --;
			}
			else
			    goto repetir;
		    else
			if(pos_usuario[0] < pos_maquina[0][0] || pos_usuario[0] < pos_maquina[2][0])
			    if(matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != 'H' && 
				    matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
				matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
				pos_maquina[maquina][0] ++;
			    }
			    else
				goto repetir;
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
			else
			    /************************************************************************************/
			    /*Comprueba en que col esta el usuario y mueve a la maquina hacia el*/
			    if(pos_usuario[1] > pos_maquina[1][1] || pos_usuario[1] > pos_maquina[3][1])
				if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != 'H' && 
					matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != dibujo_enemigo[maquina]){
				    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] = dibujo_enemigo[maquina];
				    pos_maquina[maquina][1] --;
				}
				else
				    goto repetir;
			    else
				if(pos_usuario[1] < pos_maquina[1][1] || pos_usuario[1] < pos_maquina[3][1])
				    if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != 'H' && 
					    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != dibujo_enemigo[maquina]){
					matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] = dibujo_enemigo[maquina];
					pos_maquina[maquina][1] ++;
				    }
				    else
					goto repetir;
    /*******************************************************************************************/
				else{


				    //genera una direccion aleatoria
//cambiar nombre
repetir:
				    respuesta = rand() % 4;
				    switch(respuesta){
					case 0:
					    //comprueba que el siguiente movimiento no sea en un muro
					    if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != 'H' && 
						    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] != dibujo_enemigo[maquina]){
						//pone a la maquina en la siguiente posicion de la matriz matriz
						matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] + 1] = dibujo_enemigo[maquina];
						//suma uno a la coluimna de los fantasmas
						pos_maquina[maquina][1] ++;
					    }
					    else//si hay muro
						//guarda al fantasma en la posicion que estaba en la matriz matriz
						goto repetir;
					    //matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1]] = 'M';
					    break;
					case 1:
					    if(matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != 'H' && 
						    matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] != dibujo_enemigo[maquina]){
						matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1] - 1] = dibujo_enemigo[maquina];
						pos_maquina[maquina][1] --;
					    }
					    else
						goto repetir;
					    //matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1]] = 'M';
					    break;
					case 2:
					    if(matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != 'H' && 
						    matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
						matriz[pos_maquina[maquina][0] + 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
						pos_maquina[maquina][0] ++;
					    }
					    else
						goto repetir;
					    //matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1]] = 'M';
					    break;
					case 3:
					    if(matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != 'H' && 
						    matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] != dibujo_enemigo[maquina]){
						matriz[pos_maquina[maquina][0] - 1][pos_maquina[maquina][1]] = dibujo_enemigo[maquina];
						pos_maquina[maquina][0] --;
					    }
					    else
						goto repetir;
					    //matriz[pos_maquina[maquina][0]][pos_maquina[maquina][1]] = 'M';
					    break;
				    }//fin switch
				}// fin else
}//fin mover maquina

//comprueba si el usuario o la maquina se han comido
void comprobacion(char matriz[FILAS][COLUMNAS],  char info[FILAS][COLUMNAS], int pos_usuario[USUARIO], int pos_maquina[ENEMIGOS][2], 
	int vidas, int nivel, int puntuacion, char dibujo_enemigo[ENEMIGOS],  bool asterisco_comido, int *vidas_jugador){

    //declara variables
    int pos_inicial_maquina[ENEMIGOS][COORDENADAS];

    for(int enemigo=0; enemigo<ENEMIGOS; enemigo++)
	//comprueba que el usuario y la maquina estan en las mismas coordenas

	//en el primer caso la maquina se come al usuario
	if(pos_usuario[0] == pos_maquina[enemigo][0] && pos_usuario[1] == pos_maquina[enemigo][1] && (dibujo_enemigo[enemigo] == 'M')){
	    //se actualizan las matrices
	    actualizar_matrices(info, matriz);
	    //se ponen todos los enemigos en su forma normal
	    for(int i=0; i<ENEMIGOS; i++)
		dibujo_enemigo[i] = 'M';
	    //se reinicia la posicion de los jugadores
	    posiciones_jugadores(matriz, pos_usuario, pos_maquina, dibujo_enemigo);
	    //se resta una vida
	    *vidas_jugador -= 1;
	    //se refresca la pantalla
	    refrescar(matriz, info, vidas, nivel, puntuacion);
	}
	else
	    //en este segundo caso el usuario se come a la maquina
	    if(pos_usuario[0] == pos_maquina[enemigo][0] && pos_usuario[1] == pos_maquina[enemigo][1]){
		//se pone al bueno con valor 0
		posiciones_iniciales_maquina(pos_inicial_maquina);
		pos_maquina[enemigo][0] = pos_inicial_maquina[enemigo][0];
		pos_maquina[enemigo][1] = pos_inicial_maquina[enemigo][1];
		dibujo_enemigo[enemigo] = 'M';
	    }
}// fin comprobacion

//guarda la puntuacion en un fichero
void guardar_puntuacion(int puntuacion){
    FILE *archivo;

    archivo = fopen("puntuaciones.txt","a");

    fprintf(archivo, " %i\n", puntuacion);
    fclose(archivo);

}//fin guardar_puntuacion

//comprueba si el usuario se ha comido un asterisco.
void comprobar_asteriscos(int *asteriscos, char info[FILAS][COLUMNAS], char dibujo_enemigo[ENEMIGOS], int *turnos,bool *asterisco_comido){
    int resultado, recuento = 0;
    //recorre la matriz
    for(int filas=0; filas<FILAS; filas++)
	for(int col=0; col<COLUMNAS; col++)
	    if(info[filas][col] == '*')
		recuento ++;

    resultado = *asteriscos - recuento;
    if(resultado == 1){
	*asteriscos -= 1;
	*turnos = 20;
	*asterisco_comido = true;
	for(int i=0; i<ENEMIGOS; i++)
	    dibujo_enemigo[i] = 'm';
    }
}//fin comprobar_asteriscos

//funcion que se encarga de llamar a todas las funciones para poder jugar
void partida(){
    char matriz[FILAS][COLUMNAS], 
	 info[FILAS][COLUMNAS];
    char respuesta,
	 opcion;
    int vidas, 
	pos_usuario[USUARIO], 
	pos_maquina[ENEMIGOS][2], 
	nivel,
	puntuacion,
	cocos_anterior,
	asteriscos,
	turnos;
    bool asterisco_comido;
    /*---------------------------------------------------------------------------------------------*/
    /*Englobar en una funcion*/
    do{
	//iniciamos la partida
	char dibujo_enemigo[ENEMIGOS] = {'M', 'M', 'M', 'M'};
	asteriscos = 4;
	asterisco_comido = false;
	turnos = 0;
	vidas = 3;
	respuesta = 'j';
	nivel = 1;
	puntuacion = 0;
	cocos_anterior = MCOCOS;
	cargar_mapa(matriz, info);
	inicializar_matriz(matriz, pos_usuario, pos_maquina, info, dibujo_enemigo);
	refrescar(matriz, info, vidas, nivel, puntuacion);


	while(respuesta != 'q' && vidas > 0){
	    respuesta = movimiento();
	    mover_jugador(respuesta, info, pos_usuario, matriz);
	    comprobar_asteriscos(&asteriscos, info, dibujo_enemigo, &turnos, &asterisco_comido);
	    comprobacion(matriz, info, pos_usuario, pos_maquina, vidas, nivel, puntuacion, dibujo_enemigo, asterisco_comido, &vidas);

	    recuento_puntuacion(info, &cocos_anterior, &puntuacion);

	    mover_maquina(matriz, pos_maquina, pos_usuario, dibujo_enemigo, asterisco_comido);
	    comprobacion(matriz, info, pos_usuario, pos_maquina, vidas, nivel, puntuacion, dibujo_enemigo, asterisco_comido, &vidas);

	    /*----------------------------------------------------------------*/
	    /*Ponerlo como funcion*/
	    if(comprobar_fin_nivel(info) == 1){
		cargar_mapa(matriz, info);
		inicializar_matriz(matriz, pos_usuario, pos_maquina, info, dibujo_enemigo);
		nivel ++;
		cocos_anterior = MCOCOS;
		asterisco_comido = false;
		turnos = 0;
		asteriscos = 4;
	    }
	    /*---------------------------------------------------------------*/

	    refrescar(matriz, info, vidas, nivel, puntuacion);
	    if(turnos > 0 )
		turnos --;
	    else{
		for(int i=0; i<ENEMIGOS; i++)
		    dibujo_enemigo[i] = 'M';
		asterisco_comido = false;
	    }
	}
	if(vidas == 0){
	    guardar_puntuacion(puntuacion);
	    printf("\n\t\t\tGame Over\n");
	}

	printf("¿Quieres jugar de nuevo? s/n\n");
	scanf(" %c", &opcion);
    }while(opcion != 'n');
    /*--------------------------------------------------------------------------------------------------------*/
    //exit (EXIT_SUCCESS);
}//fin partida


int main(int argc, char *argv[]){
    //poner las variables que no se necesiten en el main en partida
    int opcion2;

    srand(time(NULL));

    do{
	switch(opcion2 = menu()){
	    case jugar:
		partida();
		break;
	    case instrucciones:
		manual();
		break;
	    case top:
		top_puntuaciones();
		break;
	    case salir:
		printf("Adios\n");
		break;
	}//fin switch
    }while(opcion2 != salir);
    return EXIT_SUCCESS;  
}
