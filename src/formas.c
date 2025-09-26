#include "formas.h"

#include <stdio.h>
#include <stdlib.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef struct stForma {
	int id;
	tipoForma tipo;
	void *dados;
}forma;

forma *criaForma(int id, tipoForma tipo, void *dados) {
	forma *f = malloc (sizeof(forma));
	if (f == NULL) {
		printf("Erro ao cria a forma!\n");
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
