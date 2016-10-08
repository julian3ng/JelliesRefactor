CC=gcc-5
LD=gcc-5

MODULES=data_structures utils models views controllers
SRC_DIR=$(addprefix src/,$(MODULES)) src
BUILD_DIR=$(addprefix build/,$(MODULES)) build

SRC=$(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ=$(patsubst src/%.c,build/%.o,$(SRC))
INC=-Iinclude
LDFLAGS=-lncurses
CFLAGS=-std=c99 -Wall -Werror -g

vpath %.c $(SRC_DIR)

define make-goal
$1/%.o: %.c
	@echo "Compiling" $$@
	$(CC) $(INC) -c -g $$< -o $$@
	@echo ""
endef

.PHONY: all checkdirs clean

all: checkdirs build/main

build/main: $(OBJ)
	@echo "Linking..."
	$(LD) $(LDFLAGS) $^ -o $@
	@echo "Done! :)"

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

print-%: ; @echo $*=$($*)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
