#  Autor: Pietro Fernando Pelizon

PROJ_NAME := ted
CC        := gcc
CFLAGS    := -W -Wall -Wextra -ggdb -std=c99 -fstack-protector-all
LIBS      := -lm

SOURCES   := $(wildcard *.c)
OBJETOS   := $(SOURCES:.c=.o)


# Regras de compilação:

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJETOS)
	@echo "Linkando $(PROJ_NAME)..."
	@$(CC) -o $@ $^ $(LIBS)
	@echo "✓ Build completo!"

%.o: %.c
	@echo "Compilando $<..."
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "Limpando arquivos..."
	@rm -f *.o $(PROJ_NAME)
	@echo "✓ Limpeza concluída!"

.PHONY: all clean