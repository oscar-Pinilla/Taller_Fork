/********************************************************************************
 * 			PONTIFICIA UNIVERSIDAD JAVERIANA
 * Autores: Oscar Pinilla, David Pedraza y Johan Barreto
 * Facultad de Ingeniería - Sistemas Operativos
 * * TALLER 02 Fork
 * Archivo: procesos.h
 * * DESCRIPCIÓN:
 * En este archivo se define la estructura necesaria para crear la jerarquía de 
 * procesos solicitada en el taller. Permite coordinar la comunicación entre 
 * el proceso Padre, los dos procesos Hijos y el Grand Hijo (Nieto) mediante 
 * el uso de tuberías pipes para el envío de los resultados de las sumatorias.
 ********************************************************************************/

#ifndef PROCESOS_H
#define PROCESOS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ficheros.h"

/*
 * Su función es ejecutar las llamadas al sistema fork() para generar los 4 procesos requeridos
 * Ademas gestiona la creación de tuberías para que el Grand Hijo, el 
 * Segundo Hijo y el Primer Hijo puedan enviar sus cálculos de suma de vuelta 
 * al Padre, quien se encargará de recibirlos e imprimirlos. También asegura 
 * el manejo correcto de la memoria dinámica, arregloA y arregloB, durante 
 * la vida de los procesos.
 */
void crear_procesos(int *arregloA, int N1, int *arregloB, int N2);

#endif
