
#include <stdio.h>
#include <time.h>  //Esta lebreria permite que la funcion srand() pueda utilizar el tiempo de la computafora como semilla
#include <stdlib.h> //Esta es la que permite utilizar las funciones srand() y rand() para darle aleatoriedad al codigo

//Defino un numero razonable de filas y columnas
#define max_filas 41  
#define max_columnas 41

//Defino variables globales para poder usar en las funciones
int filas_actuales;
int columnas_actuales;


// Creo a la la estructura que me permite crear la matriz
typedef struct 
{
    char matriz[max_filas][max_columnas];
}Laberinto;


//Creo la funcion que me permite imprimir la matriz
void imprimir_laberinto(Laberinto laberinto) {
    for (int fila = 0; fila < filas_actuales; fila++) {
        for (int columna = 0; columna < columnas_actuales; columna++) {
            printf("%c ", laberinto.matriz[fila][columna]);
        }
        printf("\n");
    }
}

//Funcion para saber opciones disponibles, pasando exclusivamente por las disponibles en impares. Es decir de dos en dos. Voy a encontrar el numero de espacios con una funcion
//Bajo el esquema actual todos los espacios estan con paredes

int vecinos_disponibles (int fila_actual, int columna_actual, int vecinos_filas[], int vecinos_columnas[], Laberinto laberinto) {
    int cantidad_vecinos = 0; //Inicia en cero la cantidad de vecinos

    //Movimiento para arriba
    if (((fila_actual - 2) > 0) && (laberinto.matriz[fila_actual - 2][columna_actual] == '#')) {
        vecinos_filas[cantidad_vecinos] = fila_actual - 2; //esto me permite en la posicion [0] almacenar esa fila actualizada
        vecinos_columnas[cantidad_vecinos] = columna_actual; // en la posicion [0] mantengo la misma columna
        cantidad_vecinos++;
    }


    //Movimiento para abajo
    if (((fila_actual + 2) < (filas_actuales - 1)) && (laberinto.matriz[fila_actual + 2][columna_actual] =='#')) {
        vecinos_filas[cantidad_vecinos] = fila_actual + 2;
        vecinos_columnas[cantidad_vecinos] = columna_actual;
        cantidad_vecinos++;
    }

    //Movimiento para la izquierda 
    if (((columna_actual - 2) > 0) && (laberinto.matriz[fila_actual][columna_actual - 2] == '#')) {
        vecinos_filas[cantidad_vecinos] = fila_actual;
        vecinos_columnas[cantidad_vecinos] = columna_actual - 2;
        cantidad_vecinos++;
    }

    //Movimiento para la derecha
    if (((columna_actual + 2) < (columnas_actuales - 1)) && (laberinto.matriz[fila_actual][columna_actual + 2] == '#')) {
        vecinos_filas[cantidad_vecinos] = fila_actual;
        vecinos_columnas[cantidad_vecinos] = columna_actual + 2; 
        cantidad_vecinos++;
    }

    return cantidad_vecinos;
}

// CREO FUNCION PARA RESOLVER EL LABERINTO 
int resolver_laberinto (Laberinto *laberinto, int fila_actual, int columna_actual) //Aqui uso el puntero de laberinto 
{
    //Escenario ideal, encontrar a 's'
    if (laberinto->matriz[fila_actual][columna_actual] == 's') 
    {
        return 1; //Alli se terminaria
    }

    //Camino que no sea espacio, bloquear
    if (laberinto->matriz[fila_actual][columna_actual] != ' ')
    {
        return 0; //Convencion para no exito
    }

    laberinto->matriz[fila_actual][columna_actual] = '*';  //Para que marque el camino con *

    //LLAMO AHORA RECURSIVAMENTE PARA CADA DIRECCION
    //Para arriba
    if (resolver_laberinto(laberinto, fila_actual - 1, columna_actual))
    {
        return 1;
    }

    //Para abajo
    if (resolver_laberinto(laberinto, fila_actual + 1, columna_actual))
    {
        return 1;
    }

    //Izquierda
    if (resolver_laberinto(laberinto, fila_actual, columna_actual - 1))
    {
        return 1;
    }

    //Derecha
    if (resolver_laberinto(laberinto, fila_actual, columna_actual + 1))
    {
        return 1;
    }

    //Cuando ninguna direccion ha sido valida
    laberinto->matriz[fila_actual][columna_actual] = ' ';
    return 0;    

}


//INICIA LA EJECUCION-------------------------------------------------------------------------------------------

int main () 
{
    //Piido las dimensiones al usuario
    printf("Ingrese el numero de filas para el laberinto: \n");
    scanf("%d", &filas_actuales); //uso punteros para modificar la variable global
    printf("Ingrese numero de columnas: \n");
    scanf("%d", &columnas_actuales);

    
    //Validacion en caso de nmumero PAR
    if (filas_actuales % 2 == 0)
    {
        filas_actuales = filas_actuales + 1;
    }
    
    if (columnas_actuales % 2 == 0)
    {
        columnas_actuales = columnas_actuales + 1;
    }
    


    Laberinto laberintoi;

    //Primero lab solo con paredes
    for (int fila = 0; fila < filas_actuales; fila++) {
        for (int columna = 0; columna < columnas_actuales; columna++) {
            laberintoi.matriz[fila][columna] = '#';
        }
    }


    //Hago la entrada y la salida
    laberintoi.matriz[0][1] = 'e'; //Entrada
    laberintoi.matriz[filas_actuales -1][columnas_actuales - 2] = 's';  //salida


    //Comienzo en la celda [1][1] 

    int fila_actual = 1;
    int columna_actual = 1;
    laberintoi.matriz[fila_actual][columna_actual] = ' ';

    //Llamo a la funcion que va a ejecutar las posiciones disponibles
    int vecinos_filas[4];  // creo las arrays que contendran a a las direciones (coordenadas)
    int vecinos_columnas[4];

    //Planto la semilla fuera del bucle
    srand(time(NULL));

    //Creo condiciones para que el backtraking pueda ser posible
    int historal_filas[columnas_actuales * filas_actuales];    //Creo una lista vacia con una cantidad grande de espacios producyo de la multiplicacion de todas las filas y las columnas
    int historal_columnas[filas_actuales * columnas_actuales];  //aqui se guarda el historial de columnas

    int tope_de_pila = 0; //aqui se va a ir guardando el numero de elementos de la pila, lo inicio en 0 para que se pueda ir sumando 

    // Inicio aqui las repetciones
        //Hago dos condiciones dentro del while, la segunda es que el numero resultante de la funcion sea mayor que 0, es decir hay vecinos por visitar
    while ((tope_de_pila > 0) || (vecinos_disponibles(fila_actual,columna_actual, vecinos_filas, vecinos_columnas, laberintoi) > 0)) {
    
        //Llamo a la funcion que verifica los vecinos y almaceno en una variable
        int cantidad_vecinos = vecinos_disponibles(fila_actual, columna_actual, vecinos_filas, vecinos_columnas, laberintoi); // mantengo el nombre dado en la funcion
        
        
        if (cantidad_vecinos > 0) {  //Agrego este condicional 

            //Antes que realice el movimiento hago que se guarden las posiciones actuales
            historal_columnas[tope_de_pila] = columna_actual; //tope de pila se convierte en la posicion que tiene este valor en el array
            historal_filas[tope_de_pila] = fila_actual;  //Para el caso inicial va a ser indice 0 (cero)
            tope_de_pila++ ; //y que se sume uno 

            //Hago que la eleccion se de de manera aleatoria
            int vecino_randon = rand() % cantidad_vecinos + 0;

            // Una vez elegido un vecino RANDON defino las coordenadas del mismo
            int fila_vecino = vecinos_filas[vecino_randon];  //En vecino randon va el int elegido de random, entonces se accedera directamente al generado en la funcion
            int columna_vecino = vecinos_columnas[vecino_randon];

            //Una vez definido el par procedo a perforar los espacios
            laberintoi.matriz[fila_vecino][columna_vecino] = ' ';

            //Ahora quiero encontrar la pared que divide
            int fila_pared = (fila_actual + fila_vecino)/2;  //Al sumar ambas coordenadas siendo numeros impares el resultado siempre sera par
            int columna_pared = (columna_actual + columna_vecino)/2; // y la division estara en el medio de mi valor de partida y el de llegada

            //Perforo la pared
            laberintoi.matriz[fila_pared][columna_pared] = ' ';

            //Reasigno las variables, para que las coordenadas del vecino se conviertan en mi nueva posicion
            fila_actual = fila_vecino;
            columna_actual = columna_vecino;

            //Estas impresiones son opcionales, permiten ver como el backtracking va funcionando
            imprimir_laberinto(laberintoi);
            printf("Numero de tope %d, numero de vecino %d", tope_de_pila, cantidad_vecinos);
            printf("\n");
            printf("\n");
            
        } //aqui termina el primer if

        else if (cantidad_vecinos == 0) //es decir en el caso en el que no hay mas vecinos RETROCEDER
        {
            tope_de_pila = tope_de_pila - 1; //Resta uno al tope 
            fila_actual = historal_filas[tope_de_pila];  //Devuelvo a los valores hechos en la ultima actualizacion
            columna_actual = historal_columnas[tope_de_pila]; // Esto hace que vuelva a hacer el IF verdadero. 

            //Estas impresiones son opcionales, permiten ver como el backtracking va funcionando
            imprimir_laberinto(laberintoi);
            printf("Numero de tope %d, numero de vecino %d", tope_de_pila, cantidad_vecinos);
            printf("\n");
            printf("\n");
        }
        
        else 
        {
            printf("Sin vecinos para recorrer");
            break;
        }

    }

    //Despues de hacer el laberinto y salir del while. Llamo a la funcion para resolver
    printf("\n");
    printf("\n");
    printf("Ahora resolvemos el laberinto\n");
    resolver_laberinto(&laberintoi, 1, 1);
    

    //Imprimo para ver la resolucion final Expresada con (*)
    imprimir_laberinto(laberintoi);

    return 0;
}