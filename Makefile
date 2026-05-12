########################################################################
#
#               Pontificia Universidad Javeriana
#       Autor:
#       Fecha:
#       Archivo para Automatizacion de procesos de compilacion
########################################################################
GCC=gcc
PROGRAMAS=tallerFork
MODULO=ficheros.c procesos.c
flags=

all = ${PROGRAMAS}

tallerFork:
	$(GCC) main.c $(MODULO) $(flags) -o $(PROGRAMAS)

clean:
	$(RM)	$(PROGRAMAS)
