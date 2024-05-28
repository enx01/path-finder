CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses
BIN_DIR = bin
SRC_DIR = src
CURR_DIR = $(shell pwd)

# Defintion du nom de l'executable
BINARY_TARGET = $(BIN_DIR)/path_finder


# Cible par defaut
all: $(BINARY_TARGET)

compile : $(BINARY_TARGET)

SRCS :=  $(shell find $(SRC_DIR) -name '*.c')

$(BINARY_TARGET) :
	mkdir -p $(BIN_DIR)
	$(CC) -o $(BINARY_TARGET) $(SRCS) $(LDFLAGS)

# Nettoyage des artefacts de compilation.
clean :
	rm -rf $(BIN_DIR)

run :
	xterm -bg black -fg white -e $(CURR_DIR)/$(BIN_DIR)/path_finder &

test : clean compile run

# Phony targets (not associated with files)
.PHONY: all clean


