#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct stNodeP {
    void *item;
    nodeP *prox;
}nodeP;

typedef struct stPilha {
    nodeP *topo;
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

    nodeP *novo = (nodeP*) malloc(sizeof(nodeP));
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
    if (estaVazia(p)) {
        return NULL;
    }

    nodeP *memory = p -> topo;

    void *itemDesempilhado = memory -> item;
    p -> topo = memory -> prox;
    free(memory);

    p -> tam--;

    return itemDesempilhado;
}

void *topo(pilha *p) {
    if (estaVazia(p)) {
        printf("a pilha esta vazia\n");
        return NULL;
    }

    return p -> topo -> item;
}

bool estaVazia(pilha *p) {
    if (p -> tam == 0) {
        return true;
    }

    return false;
}

void liberaPilha(pilha *p, void (*destrutor)(void *item)) {
    if (estaVazia(p)) {
        return;
    }

    nodeP *atual = p -> topo;

    while (atual != NULL) {
        nodeP *proximo = atual -> prox;

        if (destrutor != NULL) {
            destrutor(atual -> item);
        }

        free(atual);
        atual = proximo;
    }

    free(p);
}


void copiaPilha(pilha *principal, pilha *copia) {
    if (estaVazia(principal)) {
        return;
    }

    pilha *auxiliar = criaPilha();
    nodeP *atual = principal -> topo;
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