CC = gcc
SRC=src
BIN=bin
INC=include
OUTPUT=output
PROGRAM = gnome
CFLAGS = -I$(INC) -std=c11 -O0 -g -Wall `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0 gmodule-2.0`

# link objects
$(BIN)/$(PROGRAM): $(OUTPUT)/home_gtk.o $(OUTPUT)/main.o
	$(CC) $(OUTPUT)/home_gtk.o $(OUTPUT)/main.o -o $(BIN)/$(PROGRAM) $(LIBS)

# generate main object
$(OUTPUT)/main.o: $(SRC)/main.c $(INC)/home_gtk.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $(OUTPUT)/main.o

# generate home_gtk object
$(OUTPUT)/home_gtk.o: $(SRC)/home_gtk.c $(INC)/home_gtk.h
	$(CC) $(CFLAGS) -c $(SRC)/home_gtk.c -o $(OUTPUT)/home_gtk.o
