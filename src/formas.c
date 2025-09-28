#include "formas.h"

#include <stdio.h>
#include <stdlib.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef enum stTipoForma {
	CIRCULO,
	RETANGULO,
	LINHA,
	TEXTO
}tipoForma;

typedef struct stForma {
	int id;
	tipoForma tipo;
	void *dados;
}forma;

forma *criaForma(int id, tipoForma tipo, void *dados) {
	forma *f = malloc (sizeof(forma));
	if (f == NULL) {
		printf("Erro ao criar a forma!\n");
		return NULL;
	}

	f -> id = id;
	f -> tipo = tipo;
	f -> dados = dados;

	return f;
}

int getIDForma(forma *f) {
	return f -> id;
}

tipoForma getTipoForma(forma *f) {
	return f -> tipo;
}

void *getFormaDados(forma *f) {
	return f -> dados;
}

double getAreaForma(forma *f) {
	if (f == NULL) {
		return 0.0;
	}

	switch (f -> tipo) {
		case CIRCULO: return calcAreaCirculo(f -> dados);
		case RETANGULO: return calcAreaRetangulo(f -> dados);
		case LINHA: return calcAreaLinha(f -> dados);
		case TEXTO: return calcAreaTexto(f -> dados);
	}

	return 0.0;
}

void destrutorForma(forma *f) {

	if (f == NULL) {
		return;
	}

	void* dados = f -> dados;

	switch (f -> tipo) {
		case CIRCULO: destrutorCirculo((circulo**) &dados); break;
		case RETANGULO: destrutorRetangulo((retangulo**) &dados); break;
		case LINHA: destrutorLinha((linha**) &dados); break;
		case TEXTO: destrutorTexto((texto **) &dados); break;
	}

	free(f);

}


void setPosicaoForma(forma *f, double x, double y) {
	if (f == NULL || f -> dados == NULL) {
		return;
	}


	switch (f -> tipo) {
		case CIRCULO: {
			circulo *c = (circulo*) f -> dados;
			setXCirculo(c, x);
			setYCirculo(c, x);
			break;
		}

		case RETANGULO: {
			retangulo *r = (retangulo*) f -> dados;
			setXretangulo(r, x);
			setYretangulo(r, y);
			break;
		}

		case LINHA: {
			linha *l = (linha*) f -> dados;

			double x1Antigo = getX1Linha(l);
			double x2Antigo = getX2Linha(l);
			double y1Antigo = getY1Linha(l);
			double y2Antigo = getY2Linha(l);

			double dX = x - x1Antigo;
			double dY = y - y1Antigo;

			setX1Linha(l, x);
			setY1Linha(l, y);
			setX2Linha(l, x2Antigo + dX);
			setY2Linha(l, y2Antigo + dY);
			break;
		}

		case TEXTO: {
			texto *t = (texto*)f-> dados;
			setXTexto(t, x);
			setYTexto(t, y);
			break;
		}

		default: {
			printf("Forma inexistente ou sem posicao!\n");
			break;
		}
	}
}
