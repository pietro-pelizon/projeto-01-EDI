#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    void *item;
    node *prox;
}node;

typedef struct pilha {
    pilha *topo;
    int tam;
}pilha;

void inicializa(pilha *p) {
    p -> topo = NULL;
}

void push(pilha *p, void *item) {
    pilha *novo = malloc(sizeof(item));
}