#include "disparador.h"

#include <stdio.h>
#include <stdlib.h>

#include "carregadores.h"
#include "formas.h"

typedef struct stDisparador {
	int i;
	double x, y;
	carregador *esq, *dir;
}disparador;

disparador *criaDisparador(int i, int Iesq, int Idir double x, double y, carregador *esq, carregador *dir) {
	disparador *d = malloc (sizeof(disparador));
	if (d == NULL) {
		printf("Erro ao criar o disparador!\n");
		return NULL;
	}

	x = 0.0;
	y = 0.0;
	d -> i = i;
	d -> x = x;
	d -> y = y;
	d -> esq = criaCarregador(Iesq);
	d -> dir = criaCarregador(Idir);

	return d;

}

int getIDDisparador(disparador *d) {
	return d -> i;
}

void posicionaDisparador(disparador *d, int i, double x, double y) {
	int id = getIDDisparador(d);

	if (id == i) {
		d -> x = x;
		d -> y = y;
	}

	else {
		printf("disparador com ID %i inexistente!\n", i);
	}

}

void atachDisparador(disparador *d, carregador *c, char posicao);

void shitfDisparador(disparador *d, char botao);

forma *disparaDisparador(disparador *d, double dx, double dy);

fila *rajadaDisparador(disparador *d, char botao, double dx, double dy, double ix, double iy);

forma *disparadorGetFormaEmDisparo(disparador *d);

void disparadorGetPosicao(disparador *d, double *x, double *y);

#endif //DISPARADOR_H
