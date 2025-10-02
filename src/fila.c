#include "fila.h"
#include "formas.h"
#include <stdlib.h>
#include <stdio.h>

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

bool estaVazia(fila *f) {
	if (f -> tam == 0) {
		return true;
	}

	return false;
}

void enqueue(fila *f, void *item) {
	nodeF *novo = malloc (sizeof(nodeF));
	if (!novo) {
		free(novo);
		return;
	}

	novo -> item = item;
	novo -> prox = NULL;

	if (estaVazia(f)) {
		f -> inicio = novo;
		f -> fim = novo;
	}

	else {
		f -> fim -> prox = novo;
		f -> fim = novo;

	}

	f -> tam++;
}

void *getInicioFila(fila *f) {
	if (estaVazia(f)) {
		return NULL;
	}

	return f -> inicio -> item;
}

void *getFimFila(fila *f) {
	if (estaVazia(f)) {
		return NULL;
	}

	return f -> fim -> item;
}

void *dequeue(fila *f) {
	if (estaVazia(f)) {
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
	if (estaVazia(f)) {
		return;
	}

	nodeF *atual = f -> inicio;
	while (atual != NULL) {
		nodeF *aux = atual;

		if (destrutor != NULL) {
			destrutor(atual -> item);
		}

		free(aux);
		atual = atual -> prox;
	}

	free(f);
}

void copiaFila(fila *principal, fila *copia) {
	if (estaVazia(principal)) {
		return;
	}

	nodeF *aux = principal -> inicio;
	while (aux != NULL) {
		enqueue(copia, aux -> item);
		aux = aux -> prox;
	}
}

void passingQueue(fila *f, void *(acao)(void *item)) {
	if (f == NULL) {
		return;
	}

	nodeF *atual = f -> fim;

	while (atual != NULL) {
		if (acao != NULL) {
			acao(atual -> item);
		}
		atual = atual -> prox;
	}

}

