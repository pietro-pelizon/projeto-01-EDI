#include "carregadores.h"
#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"


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

forma *adicionaFormaCarregador(carregador *l, forma *f) {
	if (l == NULL || f == NULL) {
		return NULL;
	}

	if (l->p == NULL) {
		printf("Erro: Tentativa de push em carregador com pilha nula!\n");
		return NULL;
	}

	push(l -> p, f);

	return f;
}

forma *insereDoChaoParaCarregador(carregador *l, chao *c) {
	if (l == NULL || c == NULL) {
		return NULL;
	}

	forma *retirado = retiraDoChao(c);

	return adicionaFormaCarregador(l, retirado);
}

fila *loadCarregadorN(chao *c, carregador *alvo, int n) {


	if (n < 0) {
		return criaFila();
	}
	if (c == NULL || alvo == NULL) {
		printf("Erro: chao ou carregador nulos passados para a loadCarregador!\n");
		return NULL;
	}

	if (n == 0) {
		printf("Quantidade de formas nula, nada a colocar no carregador!\n");
		return 0;
	}


	fila *fila_formas_inseridas = criaFila();
	for (int i = 0; i < n; i++) {
		if (chaoEstaVazio(c)) {
			printf("As formas do chão se esgotaram. Foram carregadas %d de %d formas.\n", i, n);
			break;
		}
		forma *forma_movida	=	insereDoChaoParaCarregador(alvo, c);

		if (forma_movida != NULL) {
			enqueue(fila_formas_inseridas, forma_movida);
		}
	}

	return fila_formas_inseridas;
}


bool carregadorEstaVazio(carregador *c) {
	if (c == NULL) return true;

	return estaVazia(c -> p);
}

forma *removeDoCarregador(carregador *c) {
	if (c == NULL) return NULL;

	forma *removido = pop(c -> p);

	return removido;
}

int getIDCarregador(carregador *c) {
	return c -> i;
}

void destrutorCarregador(carregador *c) {
	if (c == NULL) {
		return;
	}

	liberaPilha(c -> p, destrutorForma);

	free(c);
}
