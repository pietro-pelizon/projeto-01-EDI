#ifndef PILHA_H
#define PILHA_H
#include <stdbool.h>

/// @brief: A definição da struct foi movida para o arquivo.c
/// para encapsular a implementação. O header só precisa
/// saber que os tipos 'pilha' e 'nodeP' existem.
typedef struct pilha pilha;
typedef struct nodeP nodeP;

/// @brief: Cria uma pilha de alocação dinâmica
/// @return: Retorna um ponteiro para o início da pilha. Retorna NULL caso a alocação da pilha falhe.
pilha *criaPilha();

/// @brief: Insere um elemento no topo da pilha.
/// @param p: Ponteiro para a struct pilha.
/// @param item: Ponteiro para o dado que será inserido na pilha.
void push(pilha *p, void *item);

/// @brief: Remove e retorna o elemento do topo da pilha.
/// @param p: Ponteiro para a struct pilha.
/// @return: Retorna o elemento desempilhado. Retorna NULL se a pilha estiver vazia.
void *pop(pilha *p);

/// @brief: Retorna o elemento no topo da pilha sem o remover.
/// @param p: Ponteiro para a struct pilha.
/// @return: Retorna o elemento que está no topo. Retorna NULL se a pilha estiver vazia.
void *topo(pilha *p);

/// @brief: Verifica se a pilha está vazia.
/// @param p: Ponteiro para a struct pilha.
/// @return: Retorna TRUE se a pilha estiver vazia, FALSE caso contrário.
bool estaVazia(pilha *p);

/// @brief: Libera todos os dados dentro da estrutura.
/// @param p: Ponteiro para a pilha a ser liberada.
/// @param destrutor: Ponteiro para uma função que sabe como liberar um item.
/// @param item: Dado que será liberado da pilha.
void liberaPilha(pilha *p, void (*destrutor)(void *item));

/// @brief: Mostra os elementos que estão dentro da devida da pilha.
/// @param p: Ponteiro para a pilha.
/// @param impressor: Ponteiro para a função que sabe como imprimir os itens.
/// @param item: Dado que será exibido da pilha.
void printaPilha(pilha *p, void (*impressor)(void *item));



#endif //PILHA_H