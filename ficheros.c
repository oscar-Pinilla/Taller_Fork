/********************************************************************************
 *			PONTIFICIA UNIVERSIDAD JAVERIANA
 * Facultad de Ingeniería - Sistemas Operativos
 * Autores: David Padraza, Oscar Pinilla y Johan Barreto
 * * TALLER 02 Fork
 * Archivo: ficheros.c
 * * DESCRIPCIÓN DE LA IMPLEMENTACIÓN:
 * Este archivo contiene las rutinas para la manipulación de datos en memoria 
 * y la lectura de archivos externos. Se implementa la carga de datos en vectores 
 * dinámicos de tamaño N1 y N2, permitiendo que los procesos creados 
 * mediante fork() realicen los cálculos de sumatoria .
 ********************************************************************************/

#include "ficheros.h"

/*
 * Esta función se encarga de abrir el archivo, validar su existencia y reservar memoria dinámica 
 * proporcional a la cantidad de elementos definida por el usuario sea N1 o N2. 
 * Luego utiliza un puntero doble para asignar la memoria de forma que sea accesible 
 * globalmente por el proceso, recorre el fichero leyendo enteros separados por 
 * espacios y los almacena en el vector dinámico, garantizando el cierre del 
 * archivo y la liberación de memoria en caso de error para evitar fallos de ejecución.
 */
int leer_arreglo(const char *nombre, int n, int **arreglo) {
    FILE *fp = fopen(nombre, "r");
    if (fp == NULL) {
        printf("Error: no se pudo abrir '%s'\n", nombre);
        return -1;
    }

    /* Reserva de memoria dinámica utilizando malloc según el tamaño N solicitado */
    *arreglo = (int *)malloc(n * sizeof(int));
    if (*arreglo == NULL) {
        printf("Error: no se pudo reservar memoria\n");
        fclose(fp);
        return -1;
    }

    /* Ciclo de lectura para procesar cada elemento entero del fichero */
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &(*arreglo)[i]) != 1) {
            printf("Error: no se pudo leer elemento %d de '%s'\n", i, nombre);
            free(*arreglo); // Liberación de memoria dinámica ante fallos
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}



/*
 * Esta función se encargada de realizar la aritmética de los arreglos. Recorre los 
 * vectores de punteros y acumula los valores para retornar el total de la suma. 
 * Esta función es fundamental para que el Grand hijo, el Segundo hijo y el 
 * Primer hijo realicen los cálculos de suma, sumaB y suma total respectivamente 
 * antes de enviar los resultados al proceso Padre
 */
int calcular_suma(int *arreglo, int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma += arreglo[i];
    }
    return suma;
}
