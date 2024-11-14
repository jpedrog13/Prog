CC=gcc
CFLAGS=-g -I/usr/include/SDL2 -D_REENTRANT -Wall -pedantic -std=c99 -lSDL2 -lSDL2_image -ansi -lm  -lSDL2_gfx

DEPS = proj_h
OBJ = graf.o func.o proj.o

%.o: %.c $(DEPS)
	    $(CC) -c -o $@ $< $(CFLAGS)

proj: $(OBJ)
	    $(CC) -o $@ $^ $(CFLAGS)
