#ifndef PILHA_H
#define PILHA_H

// A definição da struct foi movida para o arquivo.c
// para encapsular a implementação. O header só precisa
// saber que o tipo 'pilha' existe.
typedef struct pilha pilha;
typedef struct node node;


/// @brief: cria uma pilha de alocação dinâmica
/// @return: retorna um ponteiro para o início da pilha
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
/// @return: Retorna 1 se a pilha estiver vazia, 0 caso contrário.
int estaVazia(pilha *p);


/// @brief: Libera todos os dados dentro da estrutura.
/// @param p: ponteiro para a pilha a ser liberada.
void liberaPilha(pilha *p);

/// @brief: Mostra os elementos que estão dentro da devida da pilha.
/// @param p: Ponteiro para a pilha.
/// @param imprimeItem: Ponteiro para a função que sabe como imprimir os items.
/// @param item: parâmetro da função que sabe imprimir os itens.
void imprimePilha(pilha *p, (*imprimeItem)(void *item));



#endif //PILHA_H