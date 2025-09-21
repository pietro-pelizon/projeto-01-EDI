//
// Created by pietr on 20/09/2025.
//

#include "fila.h"

typedef struct nodeF {
	void *item;
	nodeF *prox;
}nodeF;

typedef struct fila {
	nodeF *inicio;
	nodeF *fim;
	int tam;
}fila;
