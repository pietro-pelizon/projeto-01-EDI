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

forma *insereDoChaoParaCarregador(carregador *car, chao *c) {
	if (c == NULL || car == NULL) {
		printf("Erro na funcao 'insereDoChaoParaCarregador'!\n");
	}

	forma *f = retiraDoChao(c);
	if (f != NULL) {
		adicionaFormaCarregador(car, f);
	}

	return f;
}

fila *loadCarregadorN(chao *c, carregador *alvo, int n) {
	if (n < 0) return criaFila();
	if (c == NULL || alvo == NULL) return NULL;

	fila *fila_formas_inseridas = criaFila();

	for (int i = 0; i < n; i++) {
		if (chaoEstaVazio(c)) break;

		forma *forma_movida = retiraDoChao(c);
		adicionaFormaCarregador(alvo, forma_movida);
		enqueue(fila_formas_inseridas, forma_movida);
	}

	return fila_formas_inseridas;
}


bool carregadorEstaVazio(carregador *c) {
	if (c == NULL) {
		return true;
	}

	bool vazio = estaVaziaPilha(c -> p);
	return vazio;

}

forma *removeDoCarregador(carregador *c) {
	if (c == NULL) {
		return NULL;
	}
	forma *removido = pop(c -> p);


	return removido;
}

int getIDCarregador(carregador *c) {
	return c -> i;
}

void destrutorCarregador(carregador **c_ptr) {
	if (c_ptr == NULL || *c_ptr == NULL) {
		return;
	}

	carregador *c = *c_ptr;

	liberaPilha(c -> p, NULL);

	free(c);

	*c_ptr = NULL;
}
