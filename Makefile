CC = gcc
SRC=src
BIN=bin
INC=include
OUTPUT=output
PROGRAM = gnome
CFLAGS = -I$(INC) -std=c11 -O0 -g -Wall `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0 gmodule-2.0`

all: $(BIN)/$(PROGRAM)

$(BIN)/$(PROGRAM): $(OUTPUT)/home_gtk.o $(OUTPUT)/main.o
	$(CC) $(OUTPUT)/home_gtk.o $(OUTPUT)/main.o -o $(BIN)/$(PROGRAM) $(LDFLAGS) $(ELFFLAG)

$(OUTPUT)/main.o: $(SRC)/main.c $(INC)/home_gtk.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $(OUTPUT)/main.o

$(OUTPUT)/home_gtk.o: $(SRC)/home_gtk.c $(INC)/home_gtk.h
	$(CC) $(CFLAGS) -c $(SRC)/home_gtk.c -o $(OUTPUT)/home_gtk.o


clean:
	rm -f $(OUTPUT)/$(PROGRAM)
	rm -f $(BIN)/*.o
