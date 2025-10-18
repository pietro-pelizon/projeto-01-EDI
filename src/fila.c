#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

#include "formas.h"

typedef struct nodeF {
	void *item;
	nodeF *prox;
}nodeF;

typedef struct fila {
	nodeF *inicio;
	nodeF *fim;
	int tam;
}fila;


fila *criaFila(void) {
	fila *f = malloc (sizeof(fila));
	if (!f) {
		printf("Erro ao criar a fila!\n");
		return NULL;
	}

	f -> inicio = NULL;
	f -> fim = NULL;
	f -> tam = 0;

	return f;

}

int getTamFila(fila *f) {
	return f -> tam;
}

bool estaVaziaFila(fila *f) {
	if (f -> tam == 0) {
		return true;
	}

	return false;
}

void enqueue(fila *f, void *item) {
	nodeF *novo = malloc(sizeof(nodeF));
	if (!novo) {
		perror("malloc nodeF");
		exit(1);
	}


	novo -> item = item;
	novo -> prox = NULL;

	if (estaVaziaFila(f)) {
		f -> inicio = novo;
		f -> fim = novo;
	}

	else {
		f -> fim -> prox = novo;
		f -> fim = novo;

	}

	f -> tam++;
}

nodeF *getInicioFila(fila *f) {
	if (estaVaziaFila(f)) {
		return NULL;
	}

	return f -> inicio;
}

nodeF *getFimFila(fila *f) {
	if (estaVaziaFila(f)) {
		return NULL;
	}

	return f -> fim;
}

void *dequeue(fila *f) {
	if (estaVaziaFila(f)) {
		return NULL;
	}

	nodeF *remover = f -> inicio;
	void *retorno = f -> inicio -> item;
	f -> inicio = f -> inicio -> prox;

	if (f -> inicio == NULL) {
		f -> fim = NULL;
	}

	f -> tam--;

	free(remover);
	return retorno;

}

void liberaFila(fila *f, void (*destrutor)(void *item)) {
	if (f == NULL) return;

	nodeF *atual = f -> inicio;
	int contador = 0;
	while (atual != NULL) {
		nodeF *proximo = atual->prox;

		if (destrutor != NULL && atual -> item != NULL) {
			destrutor(atual->item);
			contador++;
		}

		free(atual);

		atual = proximo;
	}

	free(f);
}

void copiaFila(fila *principal, fila *copia) {
	if (estaVaziaFila(principal)) {
		return;
	}

	nodeF *aux = principal -> inicio;
	while (aux != NULL) {
		enqueue(copia, aux -> item);
		aux = aux -> prox;
	}
}

void passthroughQueue(fila *f, void (*acao)(void *item, void *aux_data), void *aux_data) {
	if (f == NULL || acao == NULL || estaVaziaFila(f)) {
		return;
	}

	nodeF *atual = f->inicio;

	while (atual != NULL) {
		acao(atual->item, aux_data);

		atual = atual->prox;
	}
}

nodeF* getProxNode(nodeF *n) {
	if (n == NULL) {
		return NULL;
	}
	return n -> prox;
}

void *getItemNode(nodeF *n) {
	if (n == NULL) {
		return NULL;
	}
	return n->item;
}

