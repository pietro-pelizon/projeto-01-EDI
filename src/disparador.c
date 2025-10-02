#include "disparador.h"
#include "carregadores.h"
#include "formas.h"
#include "arena.h"
#include "chao.h"
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct stDisparador {
	int i;
	double x, y;
	forma *formaEmDisparo;
	carregador *esq, *dir;
}disparador;

disparador *criaDisparador(int i, double x, double y, carregador *esq, carregador *dir) {
	disparador *d = malloc (sizeof(disparador));
	if (d == NULL) {
		printf("Erro ao criar o disparador!\n");
		return NULL;
	}

	d -> i = i;
	d -> x = x;
	d -> y = y;
	d -> esq = esq;
	d -> dir = dir;
	d -> formaEmDisparo = NULL;

	printf("Disparador %i criado com sucesso!\n", d -> i);

	return d;

}

int getIDdisparador(disparador *d) {
	return d -> i;
}

void posicionaDisparador(disparador *d, double x, double y) {
	if (d == NULL) {
		printf("Disparador nulo passado para a função de posicionamento!\n");
		return;
	}

	d -> x = x;
	d -> y = y;

}

void attachDisparador(disparador *d, carregador *esq, carregador *dir) {
	if (d == NULL) {
		printf("Disparador NULL foi passado para a função attachDisparador!\n");
		return;
	}

	if (esq == NULL || dir == NULL) {
		printf("Carregador NULL passado para a funcao attachDisparador!\n");
		return;
	}

	d -> esq = esq;
	d -> dir = dir;

}

forma *shiftDisparador(disparador *d, char botao, int n) {
	int i;
	forma *formaEmDisparo = NULL;

	if (n == 0) {
		return 0;
	}

	switch (botao) {
		case 'e': {
			for (i = 0; i < n; i++) {
				if (carregadorEstaVazio(d -> esq)) {
					printf("O carregador esquerdo esgotou!\n");
					return NULL;
				}

				formaEmDisparo = removeDoCarregador(d -> esq);
				adicionaFormaCarregador(d -> dir, formaEmDisparo);
			}
			break;
		}

		case 'd': {
			for (i = 0; i < n; i++) {
				if (carregadorEstaVazio(d -> dir)) {
					printf("O carregador direito esgotou!\n");
					return NULL;
				}

				formaEmDisparo = removeDoCarregador(d->dir);
				adicionaFormaCarregador(d -> esq, formaEmDisparo);
			}
			break;
		}

		default: {
			printf("Botao '%c' invalido!\n", botao);
			return NULL;
		}
	}

	d -> formaEmDisparo = formaEmDisparo;
	return formaEmDisparo;
}

forma *disparaDisparador(disparador *d, double dx, double dy) {
	if (d == NULL) {
		printf("Disparador inexistente passado para a função disparaDisparador!\n");
		return NULL;
	}

	if (d -> formaEmDisparo == NULL) {
		printf("Nenhuma forma está na posição de disparo!\n");
		return NULL;
	}

	forma *formaDisparada = getFormaEmDisparo(d);
	double x_disparador = getXdisparador(d);
	double y_disparador = getYdisparador(d);

	double posicaoFinalX = dx + x_disparador;
	double posicaoFinalY = dy + y_disparador;

	setPosicaoForma(formaDisparada, posicaoFinalX, posicaoFinalY);

	d -> formaEmDisparo = NULL;

	return formaDisparada;

}

void rajadaDisparador(disparador *d, char botao, double dx, double dy, double ix, double iy, arena *a) {
	if (d == NULL || a == NULL) {
		return;
	}


	int i = 0;

	for (i = 0; ; i++) {
		forma *formaAtual = shiftDisparador(d, botao, 1);

		if (formaAtual == NULL) {
			printf("Fim da rajada! Carregador '%c' esgotado!\n", botao);
			break;
		}

		double dx_atual = dx + (i * ix);
		double dy_atual = dy + (i * iy);

		forma *formaDisparada = disparaDisparador(d, dx_atual, dy_atual);

		///colocar setPosicaoForma
		if (formaDisparada != NULL) {
			adicionaFormaArena(a, formaDisparada);
		}
	}
}

forma *getFormaEmDisparo(disparador *d) {
	if (d == NULL || d -> formaEmDisparo == NULL) {
		return NULL;
	}

	return d -> formaEmDisparo;
}

double getXdisparador(disparador *d) {
	return d -> x;
}

double getYdisparador(disparador *d) {
	return d -> y;
}

void destrutorDisparador(disparador *d) {
	if (d == NULL) {
		return;
	}

	destrutorForma(d -> formaEmDisparo);
	destrutorCarregador(d -> esq);
	destrutorCarregador(d -> dir);

	free(d);


}
