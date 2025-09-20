#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    void *item;
    struct node *prox;
}node;

typedef struct pilha {
    node *topo;
    int tam;
}pilha;



pilha criaPilha(pilha *p) {
    p -> topo = NULL;
    p -> tam = 0;

    return *p;
}

void push(pilha *p, void *item) {
    if (p == NULL) return;

    node *novo = (node*) malloc(sizeof(node));
    if (!novo) {
        printf("erro ao alocar memoria para o noh da pilha\n");
        exit(1);
    }

    novo -> item = item;
    novo -> prox = p -> topo;
    p -> topo = novo;

    p -> tam++;
}

void *pop(pilha *p) {
    if (p == NULL || p -> topo == NULL) {
        return NULL;
    }

    node *destroi = p -> topo;

    void *itemDesempilhado = destroi -> item;
    p -> topo = destroi -> prox;
    free(destroi);

    p -> tam--;

    return itemDesempilhado;
}

void *topo(pilha const *p) {
    if (p == NULL || p -> topo == NULL) {
        printf("a pilha esta vazia\n");
        return NULL;
    }

    return p -> topo -> item;
}

int estaVazia(pilha const *p) {
    if (p -> topo == NULL) {
        return 1;
    }

    return 0;
}

void liberaPilha(pilha *p) {
    if (p == NULL) {
        return;
    }

    node *atual = p -> topo;

    while (atual != NULL) {
        node *proximo = atual -> prox;
        free(atual);
        atual = proximo;

        p -> tam--;
    }

    free(p);
}


int main() {
    pilha p;
    criaPilha(&p);
    int *numero = malloc (sizeof(int));
    if (!numero) {
        printf("erro ao alocar memoria para o valor inteiro\n");
        return 1;
    }

    *numero = 10;



    push(&p, numero);


    int *numeroNoTopo = topo(&p);
    int *dadoRemovido = pop(&p);

    printf("dado removido: %d", *dadoRemovido);
    free(dadoRemovido);



    free(numero);

}