#include "circulo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265358

typedef struct stCirculo {
	int i;
	double x, y;
	double r;
	char *corb, *corp;
}circulo;

circulo *criaCirculo(int i, double x, double y, double r, char *corb, char *corp) {
	circulo *c = malloc (sizeof(circulo));
	if (c == NULL) {
		printf("Erro na alocacao do objeto circulo!");
		exit(1);
	}

	c -> i = i;
	c -> x = x;
	c -> y = y;
	c -> r = r;
	c -> corb = (char*) malloc (strlen(corb) + 1);
	if (c -> corb == NULL) {
		printf("Erro de alocacao de memoria para a cor da borda do circulo!\n");
		free(c);
		exit(1);
	}
	strcpy(c -> corb, corb);

	c -> corp = (char*) malloc (strlen(corp) + 1);
	if (c -> corp == NULL) {
		printf("Erro de alocacao de memoria para a cor do preenchimento do circulo!\n");
		free(c -> corb);
		free(c);
		exit(1);
	}
	strcpy (c -> corp, corp);

	return c;
}

int getIDCirculo( circulo *c) {
	return c -> i;
}

double getXCirculo(circulo *c) {
	return c -> x;
}

double getYCirculo(circulo *c) {
	return c -> y;
}

double getRaioCirculo(circulo *c) {
	return c -> r;
}

char *getCorbCirculo(circulo *c) {
	return c -> corb;
}

char *getCorpCirculo(circulo *c) {
	return c -> corp;
}

void setIDCirculo(circulo *c, int i) {
	c -> i = i;
}

void setXCirculo(circulo *c, double x) {
	c -> x = x;
}

void setYCirculo(circulo *c, double y) {
	c -> y = y;
}

void setRaioCirculo(circulo *c, double raio) {
	c -> r = raio;
}

void setCorbCirculo(circulo *c, char *corb) {
	if (corb == NULL) {
		return;
	}

	char* novaCorb = (char*) malloc (strlen(corb) + 1);
	if (novaCorb == NULL) {
		printf("Erro ao alocar memoria para a nova cor de preenchimento do retangulo!\n");
		return;
	}

	strcpy(novaCorb, corb);
	free(c -> corb);
	c -> corb = novaCorb;
}

void setCorpCirculo(circulo *c, char *corp) {
	if (corp == NULL) {
		return;
	}

	char* novaCorp = (char*) malloc (strlen(corp) + 1);
	if (novaCorp == NULL) {
		printf("Erro ao alocar memoria para a nova cor de preenchimento do retangulo!\n");
		return;
	}

	strcpy(novaCorp, corp);
	free(c -> corp);
	c -> corp = novaCorp;
}

double calcAreaCirculo(circulo *c) {
	return PI * ((c -> r) * (c -> r));
}

void destrutorCirculo(circulo **pc) {
	if (pc == NULL || *pc == NULL) {
		return;
	}

	circulo *c = *pc;

	free(c -> corb);
	free(c -> corp);
	free(c);

	*pc = NULL;
}

