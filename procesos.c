/********************************************************************************
 *			PONTIFICIA UNIVERSIDAD JAVERIANA
 * Autores: Johan Barreto , David Pedraza y Oscar Pinilla
 * Facultad de Ingeniería - Sistemas Operativos
 * * TALLER 02 Fork
 * Archivo: procesos.c
 * * DESCRIPCIÓN DE LA IMPLEMENTACIÓN:
 * En este archivo se crean tres tuberias(pipes) para
 * establecer canales de comunicación unidireccionales entre 
 * los procesos. La jerarquía se organiza de modo que el Segundo hijo y el Primer 
 * hijo con su respectivo Grand hijo realicen cálculos en paralelo y utilicen 
 * las llamadas write() y read() para enviar y recibir los resultados finales.
 ********************************************************************************/

#include "procesos.h"

/*
 * Esta función hace la creación de los 4 procesos. Utiliza fork() 
 * para dividir la ejecución y pipes para el paso de argumentos. Gestiona el 
 * cierre selectivo de tubería en cada proceso para evitar bloqueos 
 * y asegurar que los datos fluyan correctamente desde el nivel más bajo Grand hijo 
 * hasta el nivel superior que es el Padre.
 */
void crear_procesos(int *arregloA, int N1, int *arregloB, int N2) {

    /* 
     * pipe_gh: Canal de comunicación del Grand hijo hacia el primer hijo (sumaA).
     * pipe_sh: Canal de comunicación del Segundo hijo hacia el padre (sumaB).
     * pipe_ph: Canal de comunicación del primer hijo hacia el padre (suma total).
     */
    int pipe_gh[2];
    int pipe_sh[2];
    int pipe_ph[2];

    /* Inicialización de las tuberías necesarias para la comunicación*/
    pipe(pipe_gh);
    pipe(pipe_sh);
    pipe(pipe_ph);

    /* SEGUNDO HIJO: Encargado de calcular la sumaB del arregloB  
     * Este proceso cierra todos los descriptores que no utiliza para mantener 
     * la integridad de los canales de comunicación. Realiza su cálculo y envía 
     * el resultado directamente al Padre a través de su respectiva tubería.
     */
    if (fork() == 0) {
        close(pipe_sh[0]); // Cierra lectura del pipe propio
        close(pipe_gh[0]);
        close(pipe_gh[1]);
        close(pipe_ph[0]);
        close(pipe_ph[1]);

        int sumaB = calcular_suma(arregloB, N2);
        printf("[Segundo hijo | PID %d] sumaB = %d\n", getpid(), sumaB);

        write(pipe_sh[1], &sumaB, sizeof(int));
        close(pipe_sh[1]);
        exit(1);
    }




    /*PRIMER HIJO: Crea al Grand hijo y consolida la suma total 
     * Este actúa como intermediario. Primero crea al Grand hijo, recibe 
     * el cálculo parcial de este, realiza su propia suma y finalmente envía el 
     * gran total al Padre.
     */
    if (fork() == 0) {
        close(pipe_ph[0]); // Cierra lectura del pipe hacia el padre
        close(pipe_sh[0]);
        close(pipe_sh[1]);




        /* GRAND HIJO: Calcula la sumaA del arregloA 
         * Este proceso nieto se encarga del 
         * primer fichero y le comunica el resultado a su proceso padre el cual es el Primer hijo.
         */
        if (fork() == 0) {
            close(pipe_gh[0]);
            close(pipe_ph[1]);

            int sumaA = calcular_suma(arregloA, N1);
            printf("[Grand hijo   | PID %d] sumaA = %d\n", getpid(), sumaA);

            write(pipe_gh[1], &sumaA, sizeof(int));
            close(pipe_gh[1]);
            exit(0);
        }


        /* El Primer hijo entra en estado de espera hasta que el 
         * Grand hijo envíe la sumaA a través del pipe_gh.
         */
        close(pipe_gh[1]);
        int sumaA = 0;
        read(pipe_gh[0], &sumaA, sizeof(int));
        close(pipe_gh[0]);


        /* Una vez recibida la sumaA, calcula el total sumando el segundo arreglo */
        int suma_total = sumaA + calcular_suma(arregloB, N2);
        printf("[Primer hijo  | PID %d] suma total = %d\n", getpid(), suma_total);

        write(pipe_ph[1], &suma_total, sizeof(int));
        close(pipe_ph[1]);
        exit(0);
    }



    /* PADRE: Receptor final de los resultados
     * El proceso padre cierra los extremos de escritura de todas las tuberías 
     * y utiliza read() para recolectar los cálculos.Esto garantiz 
     * que el Padre solo imprima los resultados cuando 
     * los hijos hayan terminado sus procesos.
     */
    close(pipe_gh[0]);
    close(pipe_gh[1]);
    close(pipe_sh[1]);
    close(pipe_ph[1]);

    int sumaB_recibida = 0;
    int suma_total_recibida = 0;


    /* Recolección de datos desde el Segundo hijo y el Primer hijo */
    read(pipe_sh[0], &sumaB_recibida, sizeof(int));
    close(pipe_sh[0]);

    read(pipe_ph[0], &suma_total_recibida, sizeof(int));
    close(pipe_ph[0]);



    /* Salida final por pantalla según*/
    printf("\n[Padre         | PID %d] RESULTADOS\n", getpid());
    printf("  sumaB  (fichero01)        = %d\n", sumaB_recibida);
    printf("  Suma total (fich00+fich01)= %d\n", suma_total_recibida);
}
