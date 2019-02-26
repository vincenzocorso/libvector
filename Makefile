# Main Settings
BUILD_DIR		:=	lib
SRC_DIR			:=	src
INCLUDE_DIR		:=	include
TEST_DIR		:=	test

OUTPUT			:=	liblibvector.a

# Makefile setup
CFLAGS			:=	-Wall -std=c11
INC_PATH		:=	-I $(INCLUDE_DIR)
LIBS_PATH		:=	-L $(BUILD_DIR)
INSTALL_PATH_LIB	:=	/usr/local/lib
INSTALL_PATH_INC	:=	/usr/local/include
LIBS			:=	-l:$(OUTPUT) -lm -lcheck -pthread -lrt

# Files
SRCS			:=	$(wildcard $(SRC_DIR)/*.c)
OBJS			:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TESTS			:=	$(wildcard $(TEST_DIR)/*.c)
INCLUDES		:=	$(wildcard $(INCLUDE_DIR)/*.h)

# Library
$(BUILD_DIR)/$(OUTPUT):		$(OBJS)
				@echo "Compiling library..."
				@ar -rcs $@ $^

$(BUILD_DIR)/%.o:		$(SRC_DIR)/%.c
				@echo "Compiling "$<
				@$(CC) $(CFLAGS) $(INC_PATH) -c $< -o $@

# Other stuff
.PHONY:	setup test install clean leaks

setup:
	@echo "Starting setup..."
	@mkdir -p $(BUILD_DIR) $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) # Create folders if not exists

test:
	@echo "Testing..."
	@$(foreach file, $(TESTS), \
	$(CC) $(CFLAGS) $(INC_PATH) $(LIBS_PATH) $(file) $(LIBS) -o $(basename $(file)); \
	./$(basename $(file)) )

install:
	@echo "Installing..."
	@install -m 644 $(BUILD_DIR)/$(OUTPUT) $(INSTALL_PATH_LIB)
	@echo $(OUTPUT)" installed in "$(INSTALL_PATH_LIB)
	@install -m 644 $(INCLUDES) $(INSTALL_PATH_INC)
	@echo $(INCLUDES)" installed in "$(INSTALL_PATH_INC)
	@echo "Installation completed."

clean:
	@echo "Cleaning..."
	@rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(OUTPUT)

leaks:
	@echo "Checking memory leaks..."
	@$(foreach file, $(TESTS), \
	valgrind --leak-check=yes ./$(basename $(file)); )
