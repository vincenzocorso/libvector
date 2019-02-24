# Main Settings
BUILD_DIR		:=	lib
SRC_DIR			:=	src
INCLUDE_DIR		:=	include
TEST_DIR		:=	test

OUTPUT			:=	libvector.a

# Makefile setup
CFLAGS			:=	-Wall -std=c11
INC_PATH		:=	-I $(INCLUDE_DIR)
LIBS_PATH		:=	-L $(BUILD_DIR)
LIBS			:=	-l:$(OUTPUT) -lm -lcheck -pthread -lrt
SRCS			:=	$(wildcard $(SRC_DIR)/*.c)
OBJS			:=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TESTS			:=	$(wildcard $(TEST_DIR)/*.c)

# Library
$(BUILD_DIR)/$(OUTPUT):		$(OBJS)
				@echo "Compiling library..."
				@ar -rcs $@ $^

$(BUILD_DIR)/%.o:		$(SRC_DIR)/%.c
				@echo "Compiling "$<
				@$(CC) $(CFLAGS) $(INC_PATH) -c $< -o $@

# Other stuff
.PHONY:	setup test clean leaks

setup:
	@echo "Starting setup..."
	@mkdir -p $(BUILD_DIR) $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) # Create folders if not exists

test:
	@echo "Testing..."
	@$(foreach file, $(TESTS), \
	$(CC) $(CFLAGS) $(INC_PATH) $(LIBS_PATH) $(file) $(LIBS) -o $(basename $(file)); \
	./$(basename $(file)) )

clean:
	@echo "Cleaning..."
	@rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(OUTPUT)

leaks:
	@echo "Checking memory leaks..."
	@$(foreach file, $(TESTS), \
	valgrind --leak-check=yes ./$(basename $(file)); )
