#include "circulo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct circulo {
	int i;
	double x, y;
	double raio;
	char *corb, *corp;
}circulo;

circulo *criaCirculo(int i, double x, double y, double raio, char *corb, char *corp) {
	circulo *c = malloc (sizeof(circulo));
	if (c == NULL) {
		printf("Erro na alocacao do objeto circulo!");
		exit(1);
	}

	c -> i = i;
	c -> x = x;
	c -> y = y;
	c -> raio = raio;
	c -> corb = (char*) malloc (strlen(corb) + 1);
	if (c -> corb == NULL) {
		printf("Erro de alocacao de memoria para a cor da borda do circulo!\n");
		exit(1);
	}
	strcpy(c -> corb, corb);

	c -> corp = (char*) malloc (strlen(corp) + 1);
	if (c -> corp == NULL) {
		printf("Erro de alocacao de memoria para a cor do preenchimento do circulo!\n");
		exit(1);
	}
	strcpy (c -> corp, corp);

	return c;
}

int getIDCirculo(circulo *c) {
	return c -> i;
}

double getXCirculo(circulo *c) {
	return c -> x;
}

double getYCirculo(circulo *c) {
	return c -> y;
}

double getRaioCirculo(circulo *c) {
	return c -> raio;
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
	c -> raio = raio;
}

void setCorbCirculo(circulo *c, char *corb) {
	c -> corb = corb;
}

void setCorpCirculo(circulo *c, char *corp) {
	c -> corp = corp;
}

