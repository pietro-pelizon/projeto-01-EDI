# Nome do executável final
TARGET = ted

NOME_ALUNO = Pietro Fernando Pelizon

# Compilador a ser usado
CC=gcc

# Flags de compilação: warnings, debug, padrão C99, proteção de stack
CFLAGS=-W -Wall -Wextra -ggdb -std=c99 -fstack-protector-all

# Bibliotecas a serem linkadas (lm para a biblioteca de matemática)
LIBS=-lm

# Lista de todos os seus arquivos fonte .c
# O make automaticamente encontrará todos os arquivos .c no diretório atual
SOURCES=$(wildcard *.c)

# Cria a lista de arquivos objeto .o a partir da lista de fontes
OBJETOS=$(SOURCES:.c=.o)

# --- REGRAS DE COMPILAÇÃO ---

# A regra 'all' é a padrão, que compila o projeto
all: $(TARGET)

# Regra para linkar todos os arquivos objeto e criar o executável final
$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(TARGET) $(OBJETOS) $(LIBS)

# Regra genérica para compilar um arquivo .c em um arquivo .o
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Regra para limpar os arquivos gerados (executáveis e objetos)
clean:
	rm -f *.o $(TARGET)

# Define que 'all' e 'clean' não são nomes de arquivos
.PHONY: all clean