#include "disparador.h"
#include "carregadores.h"
#include "formas.h"
#include "arena.h"
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

	d -> formaEmDisparo = NULL;

}

forma* shiftDisparador(disparador *d, char botao, int n) {
    if (d == NULL || n < 0) {
        return NULL;
    }

    forma *forma_anterior = d->formaEmDisparo;

    for (int i = 0; i < n; i++) {
        switch (botao) {
            case 'd': {

                if (forma_anterior != NULL) {
                    adicionaFormaCarregador(d->dir, forma_anterior);
                    forma_anterior = NULL;
                }

                if (carregadorEstaVazio(d -> esq)) {
                    d->formaEmDisparo = NULL;
                    return NULL;
                }

                forma_anterior = removeDoCarregador(d -> esq);
                d->formaEmDisparo = forma_anterior;
                break;
            }

            case 'e': {

                if (forma_anterior != NULL) {
                    adicionaFormaCarregador(d->esq, forma_anterior);
                    forma_anterior = NULL;
                }

                if (carregadorEstaVazio(d -> dir)) {
                    d->formaEmDisparo = NULL;
                    return NULL;
                }

                forma_anterior = removeDoCarregador(d -> dir);
                d->formaEmDisparo = forma_anterior;
                break;
            }

            default: {
                return NULL;
            }
        }
    }


    return forma_anterior;
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

	forma *formaDisparada = d -> formaEmDisparo;
	d -> formaEmDisparo = NULL;

	double x_disparador = getXdisparador(d);
	double y_disparador = getYdisparador(d);

	double posicaoFinalX = dx + x_disparador;
	double posicaoFinalY = dy + y_disparador;

	setPosicaoForma(formaDisparada, posicaoFinalX, posicaoFinalY);


	return formaDisparada;

}

fila *rajadaDisparador(disparador *d, char botao, double dx, double dy, double ix, double iy, arena *a) {
	if (d == NULL || a == NULL) {
		return NULL;
	}

	double x_original = getXdisparador(d);
	double y_original = getYdisparador(d);

	fila *fila_disparos = criaFila();
	int formas_disparadas = 0;


	for (int i = 0; ; i++) {

		forma *formaAtual = shiftDisparador(d, botao, 1);
		if (formaAtual == NULL) {
			break;
		}

		double dx_atual = dx + (i * ix);
		double dy_atual = dy + (i * iy);

		forma *formaDisparada = disparaDisparador(d, dx_atual, dy_atual);

		if (formaDisparada != NULL) {

			adicionaFormaArena(a, formaDisparada);
			enqueue(fila_disparos, formaDisparada);
			formas_disparadas++;
		}
	}

	posicionaDisparador(d, x_original, y_original);

	return fila_disparos;
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

void limpaFormaDoDisparador(disparador *d, forma *f) {
	if (d == NULL || f == NULL) {
		return;
	}

	if (d -> formaEmDisparo == f) {
		d -> formaEmDisparo = NULL;
	}
}


void destrutorDisparador(disparador **ptr_disparador) {
	if (ptr_disparador == NULL || *ptr_disparador == NULL) return;

	disparador* d = *ptr_disparador;

	free(d);
	*ptr_disparador = NULL;
}
