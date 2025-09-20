#ifndef PILHA_H
#define PILHA_H

// A definição da struct foi movida para o arquivo .c
// para encapsular a implementação. O header só precisa
// saber que o tipo 'pilha' existe.
typedef struct pilha pilha;
typedef struct node node;

/// @brief: Inicializa uma pilha, deixando-a pronta para uso.
/// @param p: Um ponteiro para a struct pilha.
void inicializa(pilha *p);

/// @brief Insere um elemento no topo da pilha.
/// @param p Ponteiro para a struct pilha.
/// @param item Ponteiro para o dado que será inserido na pilha.
void push(pilha *p, void *item);

/// @brief: Remove e retorna o elemento do topo da pilha.
/// @param p: Ponteiro para a struct pilha.
/// @return: Retorna o elemento que foi desempilhado. Retorna NULL se a pilha estiver vazia.
void *pop(pilha *p);

/// @brief: Retorna o elemento no topo da pilha sem removê-lo.
/// @param p: Ponteiro para a struct pilha.
/// @return: Retorna o elemento que está no topo. Retorna NULL se a pilha estiver vazia.
void *topo(pilha *p);

/// @brief: Verifica se a pilha está vazia.
/// @param p: Ponteiro para a struct pilha.
/// @return: Retorna 1 se a pilha estiver vazia, 0 caso contrário.
int estaVazia(pilha *p);

#endif //PILHA_H