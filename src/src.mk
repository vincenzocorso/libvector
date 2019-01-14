CFLAGS	=	-Wall -std=c11
BUILD	=	$(HOME)/lib
INC	=	-I$(HOME)/include

LIB	=	libvector.a
OBJS	=	$(patsubst %.c,$(BUILD)/%.o,$(wildcard *.c))

$(BUILD)/$(LIB):	$(OBJS)
	@echo "Compiling library..."
	@ar -rcs $(BUILD)/$(LIB) $^

$(BUILD)/%.o:	%.c
	@echo "Compiling" $(@F)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $(BUILD)/$(@F)
