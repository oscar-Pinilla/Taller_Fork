/********************************************************************************
 * 			PONTIFICIA UNIVERSIDAD JAVERIANA
 * Autores: Oscar Pinilla, Johan Barreto y David Pedraza
 * Facultad de Ingeniería - Sistemas Operativos
 * * TALLER 02 Fork
 * Archivo: main.c
 * * DESCRIPCIÓN DE LA IMPLEMENTACIÓN:
 * Este es el programa principal que actúa como controlador del sistema. 
 * Se encarga de validar los argumentos de entrada pasados por consola N1, N2 y 
 * nombres de los archivos, gestionar la reserva inicial de memoria dinámica y 
 * coordinar la ejecución de la jerarquía de procesos. Al finalizar los cálculos, 
 * asegura la liberación de recursos (free) para garantizar una ejecución limpia.
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ficheros.h"
#include "procesos.h"

/*
 *
 * Esta función hace inicio del taller validando que se reciban exactamente los 
 * 4 argumentos. Convierte los parámetros de texto a enteros (N1 y N2) para definir 
 * el tamaño de los vectores y utiliza las rutinas de ficheros para cargar la 
 * información en RAM. Posteriormente, delega la creación de los 4 procesos y la 
 * comunicación por pipes a la lógica de procesos.
 */
int main(int argc, char *argv[]) {

    /* Validación de argumentos: asegura que el programa reciba los ficheros y 
       valores de tamaño necesarios */
    if (argc != 5) {
        printf("Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        exit(1);
    }

    /* Mapeo de argumentos de la línea de comandos a variables locales */
    int    N1        = atoi(argv[1]); // Cantidad de elementos del primer fichero
    char *archivo00 = argv[2];       // Nombre del primer archivo
    int    N2        = atoi(argv[3]); // Cantidad de elementos del segundo fichero
    char *archivo01 = argv[4];       // Nombre del segundo archivo

    /* Inicialización de vectores de punteros para carga en memoria dinámica */
    int *arregloA = NULL;
    int *arregloB = NULL;

    /* Carga de datos: se invoca la lectura para llenar los vectores con memoria 
       dinámica de tamaño N1 o N2, conforme a los objetivos del taller. */
    if (leer_arreglo(archivo00, N1, &arregloA) != 0) exit(1);
    if (leer_arreglo(archivo01, N2, &arregloB) != 0) {
        free(arregloA);
        exit(1);
    }

    printf("Arreglo A: %d elementos desde '%s'\n", N1, archivo00);
    printf("Arreglo B: %d elementos desde '%s'\n\n", N2, archivo01);

    /*
     * Se invoca la función que implementa los 4 procesos fork() y gestiona las 
     * tuberías (pipes) para recibir e imprimir los resultados de las sumas.
     */
    crear_procesos(arregloA, N1, arregloB, N2);


    /* * LIBERACIÓN DE MEMORIA*/
    free(arregloA);
    free(arregloB);

    return 0;
}
