CC	=	gcc
SHELL   =	/bin/sh
CFLAGS  =	-g -Og $(PKGFLAGS)

PKGFLAGS        =	`pkg-config fuse --cflags --libs`

studentfs.o : FSProj.c
	gcc -Wall -g -Og $(PKGFLAGS) FSProj.c -o studentfs
