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

/// @brief: Pega o dado que se encontra no fim da fila.
/// @param f: Ponteiro para a fila.
/// @return: Um ponteiro para o objeto que se encontra no fim da fila. NULL caso a fila esteja vazia.
void *getFimFila(fila *f);

/// @brief: Remove um dado da fila, do seu início.
/// @param f: Um ponteiro para a fila em questão.
/// @return: Um ponteiro para o dado removido. NULL caso a remoção falhar (caso ela já esteja vazia).
void *dequeue(fila *f);

/// @brief: Libera todos os elementos da fila, e ao final, libera a fila em si.
/// @param f: Ponteiro para a fila em questão.
/// @param destrutor: Ponteiro para uma função que sabe como remover um determinado item,
/// recebe um ponteiro para o item como parâmetro.
void liberaFila(fila *f, void (*destrutor)(void *item));


/// @brief: Exibe todos os elementos da fila, independente de seu tipo.
/// @param f: Ponteiro para a fila em questão.
/// @param impressor: Ponteiro para a função que sabe como exibir determinado dado,
/// recebe um dado como parâmetro.
/// @return: Se a fila estiver vazia, encerra a função. Se o usuário passar NULL para função impressora
/// exibe o endereço de memória de todos os dados presentes na fila. Caso ele passe um dado diferente de NULL
/// exibe o objeto em questão.
void exibeFila(fila *f, void (*impressor)(void *item));

/// @brief: Faz a cópia de uma fila para outra fila.
/// @param principal: Fila que será copiada para a outra.
/// @param copia: Fila que será criada a partir da cópia da fila 'principal'.
void copiaFila(fila *principal, fila *copia);

#endif //FILA_H
