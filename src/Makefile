# Autor: Pietro Fernando Pelizon
# Adaptado para rodar DENTRO da pasta src/

PROJ_NAME := ted
CC        := gcc

CFLAGS    := -W -Wall -Wextra -ggdb -std=c99 -fstack-protector-all -I../include -I../unity -DUNITY_INCLUDE_DOUBLE
LIBS      := -lm

OBJ_DIR   := ../build

SRC       := $(wildcard *.c)
OBJETOS   := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CORE_OBJS := $(filter-out $(OBJ_DIR)/main.o, $(OBJETOS))

# Regras de compilação:

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJETOS)
	@echo "Linkando $(PROJ_NAME)..."
	@$(CC) -o $@ $^ $(LIBS)
	@echo "Build completo! Executável gerado na pasta src/"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilando $<..."
	@$(CC) -c $(CFLAGS) $< -o $@

# ==========================================================
# TARGETS DE LIMPEZA
# ==========================================================

clean:
	@echo "Limpando build..."
	@rm -rf $(OBJ_DIR)
	@rm -f $(PROJ_NAME)
	@echo "Limpo!"

.PHONY: all clean ted