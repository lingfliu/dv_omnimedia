CC = g++
CFLAGS = -o0 -g
LIBS = 

OBJ = vimtrx.o 

vimtrx: $(OBJ)
	$(CC) $(OBJ) -o vimtrx $(LIBS)
vimtrx.o: vimtrx.c vimtrx.h config.h
	$(CC) $(CFLAGS) -c vimtrx.c -o vimtrx.o
