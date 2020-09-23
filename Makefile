CC = gcc
CLAGS = -Wall -g
SOURCEDIR = src
BUILDDIR = build
DEBUGGER = gdb -q

.PHONY: all clean test

all: clean neo_gps.o uart.o main

main:
	$(CC) -g -o ${BUILDDIR}/main ${SOURCEDIR}/neo_gps.h ${SOURCEDIR}/uart.h ${BUILDDIR}/neo_gps.o ${BUILDDIR}/uart.o ${SOURCEDIR}/main.c

neo_gps.o:
	$(CC) -o ${BUILDDIR}/neo_gps.o -c ${SOURCEDIR}/neo_gps.c

uart.o:
	$(CC) -o ${BUILDDIR}/uart.o -c ${SOURCEDIR}/uart.c

clean:
	rm -f ${BUILDDIR}/*.o ${BUILDDIR}/main

test:
	sudo ${BUILDDIR}/main

debug:
	$(CC) -g -Wall -o ${BUILDDIR}/main ${SOURCEDIR}/neo_gps.c ${SOURCEDIR}/uart.c ${SOURCEDIR}/main.c
	sudo ${DEBUGGER} ${BUILDDIR}/main

