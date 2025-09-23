#include "linha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct stLinha {
	int i;
	double x1, y1, x2, y2;
	char *cor;
}linha;

linha *criaLinha(int i, double x1, double y1, double x2, double y2, char *cor) {
	linha *c = malloc (sizeof(linha));
	if (c == NULL) {
		printf("Erro na alocacao de memoria para o objeto linha!\n");
		exit(1);
	}

	c -> i = i;
	c -> x1 = x1;
	c -> y1 = y1;
	c -> x2 = x2;
	c -> y2 = y2;

	c -> cor = (char*) malloc (strlen(cor) + 1);
	if (c -> cor == NULL) {
		printf("Erro na alocaco de memoria para a cor do objeto linha!\n");
		free(c);
		exit(1);
	}

	return c;
}

int getIDLinha(linha *l) {
	return l -> i;
}

double getX1Linha(linha *l) {
	return l -> x1;
}

double getY1Linha(linha *l) {
	return l -> y1;
}

double getX2Linha(linha *l) {
	return l -> x2;
}

double getY2Linha(linha *l) {
	return l -> y2;
}

char *getCorLinha(linha *l) {
	return l -> cor;
}

void setIDLinha(linha *l, int i) {
	l -> i = i;
}

void setX1Linha(linha *l, double x1) {
	l -> x1 = x1;
}

void setY1Linha(linha *l, double y1) {
	l -> y1 = y1;
}

void setX2Linha(linha *l, double x2) {
	l -> x2 = x2;
}

void setY2Linha(linha *l, double y2) {
	l -> y2 = y2;
}

void setCorLinha(linha *l, char *cor) {
	if (cor == NULL) {
		return;
	}

	char *novaCor = (char*) malloc (strlen(cor) + 1);
	if (novaCor == NULL) {
		printf("Erro de alocacao de memoria para a nova cor da linha!\n");
		return;
	}

	strcpy(novaCor, cor);

	free(l -> cor);

	l -> cor = novaCor;


}

double calcComprimentoLinha(linha *l) {
	double dx = l->x2 - l->x1;
	double dy = l->y2 - l->y1;
	double comprimento = sqrt((dx*dx) + (dy*dy));
	return comprimento;
}

double calcAreaLinha(linha *l) {
	double area = 2 * (calcComprimentoLinha(l));
	return area;
}

void destrutorLinha(linha **pl) {
	if (pl == NULL || *pl == NULL) {
		return;
	}

	linha *l = *pl;

	free(l->cor);

	free(l);

	*pl = NULL;
}

