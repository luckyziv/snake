CC = gcc

#reversed
C11 = -lcurses

SRC = src/main.c src/ui/ui.c
INC = src/ui/ui.h src/typedef.h

OBJ = out/snake

$(OBJ) : $(SRC) $(INC)
	$(CC) $(C11) -o $(OBJ) $(SRC) $(INC)

clean:
	cd out/
	rm -rf *.o $(OBJ)
