CFLAGS		=	-Wall
LIB_PATH	=	-L$(CURDIR)/lib
INC_PATH	=	-I$(CURDIR)/include
LIBS		=	-l:libvector.a -lm -lcheck

all:
	@mkdir -p lib # Create lib folder if not exist
	@$(MAKE) -C src -f src.mk HOME="$(CURDIR)"

.PHONY: clean test leaks
clean:
	@echo "Cleaning..."
	rm -f lib/*.o

test:
	@echo "Testing..."
	@$(foreach file, $(wildcard *.c) $(wildcard test/*.c), \
	$(CC) $(LIB_PATH) $(INC_PATH) $(CFLAGS) $(CURDIR)/$(file) $(LIBS) -o $(CURDIR)/$(basename $(file)); \
	./$(basename $(file)); )

leaks:
	@echo "Check memory leaks"
	@$(foreach file, $(wildcard *.c) $(wildcard test/*.c), \
	valgrind --leak-check=yes ./$(basename $(file)); )
