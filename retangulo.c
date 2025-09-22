#include "retangulo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct retangulo {
	int i;
	double x, y, w, h;
	char *corb, *corp;
}retangulo;

retangulo *criaRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp) {
	retangulo *d = malloc (sizeof(retangulo));
	if (d == NULL) {
		printf("Erro na alocacao do objeto retangulo!\n");
		exit(1);
	}

	d -> i = i;
	d -> x = x;
	d -> y = y;
	d -> w = w;
	d -> h = h;
	d -> corb = malloc (strlen(corb) + 1);
	if (d -> corb == NULL) {
		printf("Erro na alocacao de memoria para a cor de borda do retangulo!\n");
		exit(1);
	}
}

int getIDretangulo(retangulo *d);

double getXretangulo(retangulo *d);

double getYretangulo(retangulo *d);

double getWretangulo(retangulo *d);

double getHretangulo(retangulo *d);

char *getCorbRetangulo(retangulo *d);

char *getCorpRetangulo(retangulo *d);

void setIDretangulo(retangulo *d, int i);

void setXretangulo(retangulo *d, double x);

void setYretangulo(retangulo *d, double y);

void setWretangulo(retangulo *d, double w);

void setHretangulo(retangulo *d, double h);

void setCorbRetangulo(retangulo *d, char *corb);

void setCorpRetangulo(retangulo *d, char *corp);