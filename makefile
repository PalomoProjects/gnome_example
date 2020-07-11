include make_gtk.mk

all: $(BIN)/$(PROGRAM)


clean:
	rm -f $(BIN)/$(PROGRAM)
	rm -f $(OUTPUT)/*.o
