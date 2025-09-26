#include "carregadores.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct stCarregador {
	int i;
	pilha *p;
}carregador;


carregador *criaCarregador(int i) {
	carregador *c = malloc(sizeof(carregador));
	if (c == NULL) {
		printf("Erro ao criar o carregador!\n");
		return NULL;
	}

	c -> i = i;
	c -> p = criaPilha();
	if (c -> p == NULL) {
		printf("Erro ao criar a pilha do carregador!\n");
		free(c);
		exit(EXIT_FAILURE);
	}


	printf("Carregador %d criado com sucesso!\n", c -> i);
	return c;

}

int loadCarregador(fila *chao, carregador *alvo, int n) {

	if (n < 0) {
		return -1;
	}
	if (chao == NULL || alvo == NULL) {
		printf("Erro: Fila ou carregador nulos passados para a loadCarregador!\n");
		return -1;
	}

	if (alvo -> p == NULL) {
		printf("O carregador nao possui uma pilha inicializada!\n");
		return -1;
	}

	if (n == 0) {
		printf("Quantidade de formas nula, nada a colocar no carregador!\n");
		return -1;
	}

	int i;
	for (i = 0; i < n; i++) {
		if (estaVazia(chao)) {
			printf("A fila esta vazia!\n");
			break;
		}

		void *itemTransferido = dequeue(chao);

		push(alvo -> p, itemTransferido);
	}

	return i;

}

int getIDCarregador(carregador *alvo) {
	return alvo -> i;
}
