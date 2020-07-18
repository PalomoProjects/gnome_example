#CC = arm-angstrom-linux-gnueabi-gcc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard --sysroot=/usr/local/oecore-x86_64/sysroots/armv7at2hf-neon-angstrom-linux-gnueabi
#CC ?= arm-angstrom-linux-gnueabi-gcc
CC ?= gcc
SRC=src
BIN=bin
INC=include
OUTPUT=output
PROGRAM = gnome
CFLAGS = -I$(INC) -std=c11 -O0 -g -Wall `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0 gmodule-2.0`

# link objects
$(BIN)/$(PROGRAM): $(OUTPUT)/widget_gtk.o $(OUTPUT)/main.o
	$(CC) $(OUTPUT)/widget_gtk.o $(OUTPUT)/main.o -o $(BIN)/$(PROGRAM) $(LIBS)

# generate main object
$(OUTPUT)/main.o: $(SRC)/main.c $(INC)/widget_gtk.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $(OUTPUT)/main.o

# generate widget_gtk object
$(OUTPUT)/widget_gtk.o: $(SRC)/widget_gtk.c $(INC)/widget_gtk.h
	$(CC) $(CFLAGS) -c $(SRC)/widget_gtk.c -o $(OUTPUT)/widget_gtk.o
