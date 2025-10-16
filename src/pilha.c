#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct stNodeP {
    void *item;
    node *prox;
}node;

typedef struct stPilha {
    node *topo;
    int tam;
}pilha;


pilha *criaPilha(void) {
    pilha *p = malloc (sizeof(pilha));
    if (!p) {
        printf("falha na alocacao de memoria da pilha!\n");
        return NULL;
    }

    p -> topo = NULL;
    p -> tam = 0;

    return p;
}

void push(pilha *p, void *item) {
    if (p == NULL) return;

    node *novo = (node*) malloc(sizeof(node));
    if (!novo) {
        printf("erro ao alocar memoria para o noh da pilha\n");
        return;
    }

    novo -> item = item;
    novo -> prox = p -> topo;
    p -> topo = novo;

    p -> tam++;
}

void *pop(pilha *p) {
    if (estaVaziaPilha(p)) {
        return NULL;
    }

    node *memory = p -> topo;

    void *itemDesempilhado = memory -> item;
    p -> topo = memory -> prox;
    free(memory);

    p -> tam--;

    return itemDesempilhado;
}

void *topo(pilha *p) {
    if (estaVaziaPilha(p)) {
        printf("a pilha esta vazia\n");
        return NULL;
    }

    return p -> topo -> item;
}

bool estaVaziaPilha(pilha *p) {
    if (p -> tam == 0) {
        return true;
    }

    return false;
}

void liberaPilha(pilha *p, void (*destrutor)(void *item)) {
    if (p == NULL) {
        return;
    }

    node *atual = p -> topo;

    while (atual != NULL) {
        node *proximo = atual -> prox;

        if (destrutor != NULL && atual -> item != NULL) {
            destrutor(atual -> item);
        }

        free(atual);

        atual = proximo;
    }

    free(p);
}


void copiaPilha(pilha *principal, pilha *copia) {
    if (estaVaziaPilha(principal)) {
        return;
    }

    pilha *auxiliar = criaPilha();
    node *atual = principal -> topo;
    while (atual != NULL) {
        push(auxiliar, atual -> item);
        atual = atual -> prox;
    }

    atual = auxiliar -> topo;
    while (atual != NULL) {
        push(copia, atual -> item);
        atual = atual -> prox;
    }

    liberaPilha(auxiliar, NULL);
}