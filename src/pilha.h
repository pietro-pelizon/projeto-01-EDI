#ifndef PILHA_H
#define PILHA_H
#include <stdbool.h>


 /* ------- TAD PILHA -------
 * A Pilha é uma estrutura de dados genérica, que organiza elementos
 * e opera com os seguintes conceitos:
 *
 * Padrão LIFO (Last-In, First-Out): Garante que o último elemento a ser
 * inserido na pilha será também o primeiro a ser removido, seguindo a
 * lógica de uma pilha de pratos;
 *
 * Dados Genéricos (void*): Armazena ponteiros genéricos ('void*'), permitindo
 * que a mesma estrutura de pilha seja usada para guardar qualquer tipo de
 * dado (formas, carregadores, etc.);
 *
 * Topo da Pilha: É o único ponto de acesso da estrutura. Novos elementos são
 * adicionados no topo ('push'), e os elementos também são lidos ('topo') e
 * removidos ('pop) do topo.
 */

typedef struct stPilha pilha;
typedef struct stNodeP node;

/// @brief: Cria uma pilha de alocação dinâmica
/// @return: Retorna um ponteiro para o início da pilha. Retorna NULL caso a alocação da pilha falhe.
pilha *criaPilha(void);

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
bool estaVaziaPilha(pilha *p);

/// @brief: Libera todos os dados dentro da estrutura.
/// @param p: Ponteiro para a pilha a ser liberada.
/// @param destrutor: Ponteiro para uma função que sabe como liberar um item.
/// Esta função de callback recebe um único parâmetro: um ponteiro
/// (void *) para o dado a ser destruído.
void liberaPilha(pilha *p, void (*destrutor)(void *item));

/// @brief: Faz a cópia de uma pilha em outra.
/// @param principal: Pilha que será copiada.
/// @param copia: Pilha criada a partir da cópia da principal.
void copiaPilha(pilha *principal, pilha *copia);

#endif //PILHA_H