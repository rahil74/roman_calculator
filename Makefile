#
# Master Makefile
# 
# Usage: make all
# Usage: make check to run the unit tests
#

# Compiler
CC = gcc

# Directories
MAKE_DIR = $(PWD)
LIB_DIR = $(MAKE_DIR)/srcs
TESTS_DIR = $(MAKE_DIR)/tests

BUILD_DIR = $(MAKE_DIR)/build
BUILD_LIB_DIR = $(BUILD_DIR)/lib
BUILD_TESTS_DIR = $(BUILD_DIR)/tests

# Include paths
INCLUDE_PATH :=
INCLUDE_PATH += -I $(MAKE_DIR)
INCLUDE_PATH += -I $(LIB_DIR)
INCLUDE_PATH += -I $(TESTS_DIR)

# Library paths
LIB_PATH :=
LIB_PATH += -L $(BUILD_LIB_DIR)
LIB_PATH += -L /usr/local/lib

# Compilation Switches
CFLAGS :=
CFLAGS += -fPIC 
CFLAGS += -Wall 
CFLAGS += $(INCLUDE_PATH)

# Linker Switches
LDFLAGS :=
LDFLAGS += $(LIB_PATH)
LDFLAGS += -Wl,-R$(BUILD_LIB_DIR)

# Export variables for use in other makefiles
export CC MAKE_DIR LIB_DIR TESTS_DIR BUILD_DIR BUILD_LIB_DIR BUILD_TESTS_DIR INCLUDE_PATH LIB_PATH CFLAGS LDFLAGS

# Targets
all:
	@mkdir -p $(BUILD_LIB_DIR)
	@mkdir -p $(BUILD_TESTS_DIR)
	@$(MAKE) -C srcs -f roman_calculator.mk
	@$(MAKE) -C tests -f tests.mk

clean:
	@$(MAKE) -C srcs -f roman_calculator.mk clean
	@$(MAKE) -C tests -f tests.mk clean

check:
	@$(MAKE) -C tests -f tests.mk check