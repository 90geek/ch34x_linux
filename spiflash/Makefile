# Makefile for WCH CH34x chips

CC := gcc
OBJ := DEMO
CFLAGS := -Wall -g
OBJ_C := spiflash.o ch34x_lib.o file_utils.c

$(OBJ):$(OBJ_C)
	$(CC) -o $@ $^ $(CFLAGS)
	$(CC) -c ch34x_lib.c $(CFLAGS)
%.o:%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf *.o $(OBJ) 

