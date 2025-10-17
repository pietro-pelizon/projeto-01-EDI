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

	printf("DEBUG ATCH: Disparador %d attached: esq=%d, dir=%d\n",
		  d->i, getIDCarregador(esq), getIDCarregador(dir));


	d -> esq = esq;
	d -> dir = dir;

	d -> formaEmDisparo = NULL;

}

forma* shiftDisparador(disparador *d, char botao, int n) {
    if (d == NULL || n < 0) {
        return NULL;
    }

    forma *forma_anterior = d->formaEmDisparo;

	printf("DEBUG SHFT: Ordem de disparo - Botão: %c\n", botao);
    for (int i = 0; i < n; i++) {
        switch (botao) {
            case 'd': {
                printf("DEBUG SHFT: Botão esquerdo pressionado. Forma atual em disparo: %p\n",
                       (void*)forma_anterior);

                if (forma_anterior != NULL) {
                    printf("DEBUG SHFT: Movendo forma ID=%d do disparo para carregador direito\n",
                           getIDforma(forma_anterior));
                    adicionaFormaCarregador(d->dir, forma_anterior);
                    forma_anterior = NULL;
                }

                if (carregadorEstaVazio(d -> esq)) {
                    printf("DEBUG SHFT: Carregador esquerdo vazio. Nenhuma forma movida para disparo.\n");
                    d->formaEmDisparo = NULL;
                    return NULL;
                }

                forma_anterior = removeDoCarregador(d -> esq);
                d->formaEmDisparo = forma_anterior;
                printf("DEBUG SHFT: Forma ID=%d colocada em posição de disparo do carregador esquerdo\n",
                       getIDforma(forma_anterior));
                break;
            }

            case 'e': {
                printf("DEBUG SHFT: Botão direito pressionado. Forma atual em disparo: %p\n",
                       (void*)forma_anterior);

                if (forma_anterior != NULL) {
                    printf("DEBUG SHFT: Movendo forma ID=%d do disparo para carregador esquerdo\n",
                           getIDforma(forma_anterior));
                    adicionaFormaCarregador(d->esq, forma_anterior);
                    forma_anterior = NULL;
                }

                if (carregadorEstaVazio(d -> dir)) {
                    printf("DEBUG SHFT: Carregador direito vazio. Nenhuma forma movida para disparo.\n");
                    d->formaEmDisparo = NULL;
                    return NULL;
                }

                forma_anterior = removeDoCarregador(d -> dir);
                d->formaEmDisparo = forma_anterior;
                printf("DEBUG SHFT: Forma ID=%d colocada em posição de disparo do carregador direito\n",
                       getIDforma(forma_anterior));
                break;
            }

            default: {
                printf("DEBUG SHFT: Botão inválido: %c\n", botao);
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

	printf("DEBUG DSP: Tentando disparar. formaEmDisparo=%p\n", (void*)d -> formaEmDisparo);
	if (d->formaEmDisparo != NULL) {
		printf("DEBUG DSP: Forma ID=%d está em posição de disparo\n", getIDforma(d -> formaEmDisparo));
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
		printf("DEBUG RJD: Parâmetros nulos\n");
		return NULL;
	}

	double x_original = getXdisparador(d);
	double y_original = getYdisparador(d);

	fila *fila_disparos = criaFila();
	int formas_disparadas = 0;

	printf("DEBUG RJD: Iniciando rajada. Posição original: (%.2f, %.2f)\n", x_original, y_original);
	printf("DEBUG RJD: dx=%.2f, dy=%.2f, ix=%.2f, iy=%.2f\n", dx, dy, ix, iy);

	for (int i = 0; ; i++) {
		printf("DEBUG RJD: Iteração %d\n", i);

		forma *formaAtual = shiftDisparador(d, botao, 1);
		if (formaAtual == NULL) {
			printf("DEBUG RJD: Fim da rajada - carregador vazio\n");
			break;
		}

		double dx_atual = dx + (i * ix);
		double dy_atual = dy + (i * iy);

		printf("DEBUG RJD: Deslocamento para forma %d: (%.2f, %.2f)\n",
			   getIDforma(formaAtual), dx_atual, dy_atual);

		forma *formaDisparada = disparaDisparador(d, dx_atual, dy_atual);

		if (formaDisparada != NULL) {
			printf("DEBUG RJD: Forma %d disparada para (%.2f, %.2f)\n",
				   getIDforma(formaDisparada),
				   getXForma(formaDisparada),
				   getYForma(formaDisparada));

			adicionaFormaArena(a, formaDisparada);
			enqueue(fila_disparos, formaDisparada);
			formas_disparadas++;
		}
	}

	posicionaDisparador(d, x_original, y_original);

	printf("DEBUG RJD: Rajada completa. %d formas disparadas\n", formas_disparadas);
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
		printf("DEBUG LIMPA: Removendo forma ID=%d da posição de disparo do disparador ID=%d\n",
			   getIDforma(f), d -> i);
		d -> formaEmDisparo = NULL;
	}
}


void destrutorDisparador(disparador **ptr_disparador) {
	if (ptr_disparador == NULL || *ptr_disparador == NULL) return;

	disparador* d = *ptr_disparador;

	if (d->formaEmDisparo != NULL) {
		printf("AVISO: Disparador %d tinha forma ID=%d em posição de disparo não utilizada\n",
			   d -> i, getIDforma(d -> formaEmDisparo));
	}

	free(d);
	*ptr_disparador = NULL;
}
