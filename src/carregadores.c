#include "carregadores.h"
#include "pilha.h"

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

void adicionaFormaCarregador(carregador *l, forma *f) {
	if (l == NULL || f == NULL) {
		return;
	}

	if (l->p == NULL) {
		printf("Erro: Tentativa de push em carregador com pilha nula!\n");
		return;
	}

	push(l -> p, f);
}

void adicionaChaoCarregador(carregador *l, chao *c) {
	if (l == NULL || c == NULL) {
		return;
	}

	forma *retirado = retiraChao(c);

	adicionaFormaCarregador(l, retirado);
}

int loadCarregador(chao *c, carregador *alvo, int n) {

	if (n < 0) {
		return -1;
	}
	if (c == NULL || alvo == NULL) {
		printf("Erro: chao ou carregador nulos passados para a loadCarregador!\n");
		return -1;
	}

	if (n == 0) {
		printf("Quantidade de formas nula, nada a colocar no carregador!\n");
		return 0;
	}

	int i;
	for (i = 0; i < n; i++) {
		if (chaoEstaVazio(c)) {
			printf("As formas que estavam no chão se esgotaram antes adicionar as %i formas ao carragador!\n", n);
			printf("Foram colocadas somente %i formas!\n", i);
			break;
		}

		adicionaChaoCarregador(alvo, c);
	}

	return i;
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
