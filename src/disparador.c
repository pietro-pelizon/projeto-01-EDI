#include "disparador.h"
#include "carregadores.h"
#include "formas.h"
#include "arena.h"

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

	return d;

}

int getIDDisparador(disparador *d) {
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

	switch (botao) {
		case 'e': {
			for (i = 0; i < n; i++) {
				if (estaVazia((pilha*)d->esq)) {
					printf("O carregador esquerdo esgotou!\n");
					return NULL;
				}

				formaEmDisparo = (forma*)pop((pilha*)d->esq);
				push((pilha*)d->dir, formaEmDisparo);
			}
			break;
		}

		case 'd': {
			for (i = 0; i < n; i++) {
				if (estaVazia((pilha*)d->dir)) {
					printf("O carregador direito esgotou!\n");
					return NULL;
				}

				formaEmDisparo = (forma*)pop((pilha*)d->dir);
				push((pilha*)d->esq, formaEmDisparo);
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

fila *rajadaDisparador(disparador *d, char botao, double dx, double dy, double ix, double iy) {
	if (d == NULL) {
		return NULL;
	}

	fila *filaDeDisparos = criaFila();

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

		if (formaDisparada != NULL) {
			enqueue(filaDeDisparos, formaDisparada);
		}
	}

	return filaDeDisparos;

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

