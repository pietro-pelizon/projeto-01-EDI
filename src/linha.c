#include "linha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct stLinha {
	int i;
	double x1, y1, x2, y2;
	char *cor;
	bool eh_pontilhada;
} linha;

linha *criaLinha(int i, double x1, double y1, double x2, double y2, char *cor, bool eh_pontilhada) {
	linha *l = malloc (sizeof(linha));
	if (l == NULL) {
		printf("Erro na alocacao de memoria para o objeto linha!\n");
		exit(1);
	}

	l -> i = i;
	l -> x1 = x1;
	l -> y1 = y1;
	l -> x2 = x2;
	l -> y2 = y2;
	l -> eh_pontilhada = eh_pontilhada;

	l -> cor = (char*) malloc (strlen(cor) + 1);
	if (l -> cor == NULL) {
		printf("Erro na alocaco de memoria para a cor do objeto linha!\n");
		free(l);
		exit(1);
	}
	strcpy(l -> cor, cor);

	return l;
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

bool getEh_pontilhada(linha *l) {
	return l -> eh_pontilhada;
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

void setEh_pontilhada(linha *l, bool opcao) {
	l -> eh_pontilhada = opcao;
}

double calcComprimentoLinha(linha *l) {
	double dx = l -> x2 - l -> x1;
	double dy = l -> y2 - l -> y1;
	double comprimento = sqrt((dx*dx) + (dy*dy));
	return comprimento;
}

double calcAreaLinha(linha *l) {
	double area = 2 * (calcComprimentoLinha(l));
	return area;
}

void destrutorLinha(linha *l) {
	if (l == NULL) {
		return;
	}

	free(l->cor);

	free(l);

}

