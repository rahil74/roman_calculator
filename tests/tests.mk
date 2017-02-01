#
# tests.mk
#
# Makefile for the tests program, relies on check
#

# Test Program with Check
TESTS = $(BUILD_TESTS_DIR)/tests

# Libraries required for test program along with check
LIBS :=
LIBS += -lcheck
LIBS += -lcheck_pic
LIBS += -lrt
LIBS += -lm
LIBS += -lroman_calculator

# Extra Compilation flags needed for check
CFLAGS_EXTRA = -pthread

# Test program sources and objects
TESTS_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TESTS_OBJS = $(patsubst $(TESTS_DIR)/%.c, $(BUILD_TESTS_DIR)/%.o, $(TESTS_SRCS))

# Rule for building Test Program
$(TESTS) : $(TESTS_OBJS)
	@echo "Building $@ ..."
	@$(CC) -o $@ $^ $(CFLAGS_EXTRA) $(LIBS) $(CFLAGS) $(LDFLAGS) 

# Rule for building sources	
$(TESTS_OBJS): $(TESTS_SRCS)
	@echo "Compiling $^ ..."
	@$(CC) -c $^ $(CFLAGS_EXTRA) $(LIBS) $(CFLAGS) -o $@

.PHONY: clean check

# Targets
clean:
	@rm -f $(TESTS) $(TESTS_OBJS)

check:
	@$(TESTS)

