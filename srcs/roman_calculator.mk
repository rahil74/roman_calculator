#
# roman_calculator.mk
#
# Makefile for building Roman Calculator library
#

# Library Roman Calculator
LIB = $(BUILD_LIB_DIR)/libroman_calculator.so

# Library sources and objects
LIB_SRCS = $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS = $(patsubst $(LIB_DIR)/%.c, $(BUILD_LIB_DIR)/%.o, $(LIB_SRCS))

# Rule for building Roman Calculator library
$(LIB) : $(LIB_OBJS)
	@echo "Building $@. ..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -shared -o $@ $^

# Rule for building sources	
$(LIB_OBJS): $(LIB_SRCS)
	@echo "Compiling $^ ...."
	@$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

# Targets
clean:
	@rm -f $(LIB) $(LIB_OBJS)

