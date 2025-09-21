#ifndef FILA_H
#define FILA_H
#include "stdbool.h"

// A definição da struct foi movida para o arquivo.c
// para encapsular a implementação. O header só precisa
// saber que o tipo 'fila' existe.
typedef struct fila fila;
typedef struct nodeF nodeF;

/// @brief: Cria uma fila.
/// @return: Retorna um ponteiro para fila. NULL caso a criação falhe.
fila *criaFila(void);

/// @brief: Verifica se a fila está vazia.
/// @param f: Ponteiro para a fila a ser checada.
/// @return: Retorna TRUE para caso esteja vazia e FALSE para o contrário.
bool estaVazia(fila *f);

/// @brief: Adiciona um dado à fila, ao seu fim.
/// @param f: Ponteiro para a fila.
/// @param item: Dado que será adicionado à fila.
void enqueue(fila *f, void *item);

/// @brief: Pega o elemento que está no início da fila sem o remover.
/// @param f: Ponteiro para a fila.
/// @return: Retorna o elemento que está no início da fila. NULL caso a fila esteja vazia.
void *getInicioFila(fila *f);

/// @brief:
void *getFimFila(fila *f);

void *dequeue(fila *f);

void liberaFila(fila *f, void (*destrutor)(void *item));

void exibeFila(fila *f, void (*impressor)(void *item));











#endif //FILA_H
