#ifndef FILA_H
#define FILA_H
#include "stdbool.h"


 /* ------- TAD FILA -------
 * A Fila é uma estrutura de dados genérica, que organiza elementos
 * e opera com os seguintes conceitos:
 * Padrão FIFO (First-In, First-Out): Garante que o primeiro elemento a ser
 * inserido na fila será também o primeiro a ser removido, seguindo a
 * lógica de uma fila de espera convencional;
 * Dados Genéricos (void*): Armazena ponteiros genéricos ('void*'), permitindo
 * que a mesma estrutura de fila seja usada para guardar qualquer tipo de
 * dado (formas, disparadores, etc.);
 * Início da Fila: É a extremidade da fila de onde os
 * elementos são removidos ('dequeue');
 * Fim da Fila: É a extremidade da fila onde novos elementos são
 * inseridos ('enqueue').
 */

// A definição das structs foram movidas para o arquivo.c
typedef struct fila fila;
typedef struct nodeF nodeF;

/// @brief: Cria uma fila.
/// @return: Retorna um ponteiro para fila. NULL caso a criação falhe.
fila *criaFila(void);

/// @brief: Pega e retorna a quantiade de dados dentro da fila.
/// @param f: Ponteiro para a fila.
/// @return: Quantidade de dados dentro da fila.
int getTamFila(fila *f);

/// @brief: Verifica se a fila está vazia.
/// @param f: Ponteiro para a fila a ser checada.
/// @return: Retorna TRUE para caso esteja vazia e FALSE para o contrário.
bool estaVaziaFila(fila *f);

/// @brief: Adiciona um dado à fila, ao seu fim.
/// @param f: Ponteiro para a fila.
/// @param item: Dado que será adicionado à fila.
void enqueue(fila *f, void *item);

/// @brief: Pega o elemento que está no início da fila sem o remover.
/// @param f: Ponteiro para a fila.
/// @return: Retorna o elemento que está no início da fila. NULL caso a fila esteja vazia.
nodeF *getInicioFila(fila *f);

/// @brief: Pega o dado que se encontra no fim da fila.
/// @param f: Ponteiro para a fila.
/// @return: Um ponteiro para o objeto que se encontra no fim da fila. NULL caso a fila esteja vazia.
nodeF *getFimFila(fila *f);

/// @brief: Remove um dado da fila, do seu início.
/// @param f: Um ponteiro para a fila em questão.
/// @return: Um ponteiro para o dado removido. NULL caso a remoção falhar (caso ela já esteja vazia).
void *dequeue(fila *f);

/// @brief: Libera todos os elementos da fila, e ao final, libera a fila em si.
/// @param f: Ponteiro para a fila em questão.
/// @param destrutor: Ponteiro para uma função que sabe como remover um determinado item,
/// recebe um ponteiro para o item como parâmetro.
void liberaFila(fila *f, void (*destrutor)(void *item));

/// @brief: Faz a cópia de uma fila para outra fila.
/// @param principal: Fila que será copiada para a outra.
/// @param copia: Fila que será criada a partir da cópia da fila 'principal'.
void copiaFila(fila *principal, fila *copia);

/// @brief: Dada uma fila, realiza uma ação determina pela função inserida no callback;
/// @param f: Ponteiro para a fila.
/// @param acao: Ponteiro para a função da ação, essa função recebe o item atual da fila.
/// @param aux_data: Dado auxiliar, caso a função precise.
void passthroughQueue(fila *f, void (*acao)(void *item, void *aux_data), void *aux_data);

/// @brief: Pega o proximo nó da fila.
/// @param n: Ponteiro para o nó.
/// @return: O nó que está na frente do nó passado como parâmetro.
nodeF *getProxNode(nodeF *n);

/// @brief: Pega o conteúdo de determinado nó da fila.
/// @param n: Ponteiro para o nó.
/// @return: O conteúdo do nó.
void *getItemNode(nodeF *n);

#endif //FILA_H
