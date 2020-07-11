CC ?= gcc
PROGRAM = app_porta.exe
CFILES := $(shell find -name '*.c')
OBJS = $(CFILES:.c=.o)
DEPDIR = .deps
CFLAGS = `pkg-config --cflags gtk+-3.0` -std=c11 -O0 -g -Wall
LIBS = `pkg-config --libs gtk+-3.0 gmodule-2.0` -lsqlite3

all: $(PROGRAM)

-include $(OBJS:%.o=$(DEPDIR)/%.Po)

%.o: %.c
	@mkdir -p $(DEPDIR)
	$(CC) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $(CFLAGS) $<
	@mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f $(PROGRAM)
