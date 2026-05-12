/********************************************************************************
 * 		PONTIFICIA UNIVERSIDAD JAVERIANA
 * Autores: Oscar Pinilla, David Pedraza y Johan Barreto
 * Facultad de Ingeniería - Sistemas Operativos
 * * TALLER 02 Fork
 * Archivo: ficheros.h
 * * DESCRIPCIÓN:
 * Esta interfaz define las funciones necesarias para la gestión de datos del taller.
 * Se encarga de la lectura de ficheros externos y el procesamiento de arreglos
 * mediante el uso de memoria dinámica, permitiendo que cada proceso (padre, hijos
 * y nieto) trabaje con los datos cargados en vectores de punteros.
 ********************************************************************************/

#ifndef FICHEROS_H
#define FICHEROS_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Esta función abre el fichero indicado, reserva 
 * espacio en memoria dinámica usando malloc, de tamaño N1 o N2 según sea el caso, 
 * y carga los enteros separados por espacios en el vector. Es importante para 
 * asegurar que los datos estén disponibles para los procesos que se crearán con fork.
 */
int leer_arreglo(const char *nombre, int n, int **arreglo);

/*
 * Esta funcioón está encargada de recorrer los vectores cargados y realizar la sumatoria 
 * total de los elementos. Esta será ejecutada de forma independiente por 
 * el Gran hijo que es el fichero00, el Segundo hijo fichero01 y el Primer hijo (ambos), 
 * para luego enviar estos resultados al padre.
 */
int calcular_suma(int *arreglo, int n);

#endif
