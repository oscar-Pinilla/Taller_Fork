# Taller_Fork
# Taller 02 – Fork y Pipes en C

> Sistemas Operativos · Pontificia Universidad Javeriana  
> Semestre 2026-1

---

## ¿De qué trata esto?

Este es el segundo taller del curso. La idea era implementar una jerarquía de 4 procesos en C que se comunican entre sí usando `fork()` y `pipe()` para calcular la suma de dos arreglos de enteros leídos desde archivos.

Básicamente: el padre crea hijos, los hijos hacen cuentas y se mandan los resultados por tuberías hasta que el padre los imprime. Suena simple pero hacer que los pipes no se bloqueen y cerrar los descriptores correctamente tomó bastante depuración 😅

---

## Integrantes

| Nombre | Usuario GitHub |
|---|---|
| Oscar Pinilla | `@opini` |
| Johan Barreto | `@jbarreto` |
| David Pedraza | `@dpedraza` |

---

## Cómo funciona

La jerarquía de procesos queda así:

```
Padre
├── Segundo Hijo  ──→ calcula sumaB  ──────────────────→ pipe_sh ──→ Padre
└── Primer Hijo
    ├── Grand Hijo  ──→ calcula sumaA ──→ pipe_gh ──→ Primer Hijo
    └── (suma sumaA + sumaB) ──────────────────────────→ pipe_ph ──→ Padre
```

Cada proceso tiene su rol claro:

| Proceso | Qué hace | Por dónde manda el resultado |
|---|---|---|
| Grand Hijo | Suma `arregloA` | `pipe_gh` → Primer Hijo |
| Segundo Hijo | Suma `arregloB` | `pipe_sh` → Padre |
| Primer Hijo | Recibe `sumaA`, calcula total | `pipe_ph` → Padre |
| Padre | Recibe todo e imprime | — |

Lo más importante fue cerrar bien los extremos de cada pipe en cada proceso, porque si no se quedan esperando para siempre.

---

## Archivos del proyecto

```
TallerFork/
├── main.c          # valida argumentos, carga los archivos y llama a crear_procesos()
├── procesos.c      # toda la lógica de fork() y pipes
├── procesos.h
├── ficheros.c      # leer_arreglo() y calcular_suma()
├── ficheros.h
├── Makefile
├── archivo00.txt   # datos de prueba para arregloA
└── archivo01.txt   # datos de prueba para arregloB
```

---

## Cómo correrlo

**Compilar:**
```bash
make
```

**Ejecutar:**
```bash
./tallerFork N1 archivo00.txt N2 archivo01.txt
```

- `N1` = cuántos enteros leer del primer archivo
- `N2` = cuántos enteros leer del segundo archivo

**Ejemplo con los archivos de prueba incluidos** (`archivo00.txt`: `10 20 30 40 50` y `archivo01.txt`: `5 15 25 35 45`):

```bash
./tallerFork 5 archivo00.txt 5 archivo01.txt
```

Salida (los PIDs cambian cada vez):
```
Arreglo A: 5 elementos desde 'archivo00.txt'
Arreglo B: 5 elementos desde 'archivo01.txt'

[Grand hijo   | PID 12346] sumaA = 150
[Segundo hijo | PID 12345] sumaB = 125
[Primer hijo  | PID 12347] suma total = 275

[Padre        | PID 12344] RESULTADOS
  sumaB  (fichero01)        = 125
  Suma total (fich00+fich01)= 275
```

> ⚠️ El orden en que aparecen los mensajes de los hijos puede variar entre ejecuciones porque los procesos corren en paralelo. Lo que siempre es correcto son los números al final.

**Limpiar binarios:**
```bash
make clean
```

---

## Formato de los archivos de entrada

Enteros separados por espacios en una sola línea:
```
10 20 30 40 50
```

---

## Lo que aprendimos / dificultades

- Cerrar **todos** los extremos de pipe que cada proceso no usa es crítico. Olvidar uno solo causa bloqueos indefinidos.
- El orden de impresión de los hijos es no determinístico, lo cual fue confuso al principio hasta entender que es normal.
- `exit(1)` en los hijos (en vez de `return`) es necesario para que no sigan ejecutando código del padre.

---

## Entorno de desarrollo

- Ubuntu 22.04 / 24.04
- GCC 11+
- `make`

---

*Trabajo académico – Sistemas Operativos, Pontificia Universidad Javeriana, 2026.*
