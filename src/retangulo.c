#include "retangulo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stRetangulo {
	int i;
	double x, y, w, h;
	char *corb, *corp;
}retangulo;

retangulo *criaRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp) {
	retangulo *r = malloc (sizeof(retangulo));
	if (r == NULL) {
		printf("Erro na alocacao do objeto retangulo!\n");
		exit(1);
	}

	r -> i = i;
	r -> x = x;
	r -> y = y;
	r -> w = w;
	r -> h = h;
	r -> corb = (char*) malloc (strlen(corb) + 1);
	if (r -> corb == NULL) {
		printf("Erro na alocacao de memoria para a cor de borda do retangulo!\n");
		free(r);
		exit(1);
	}
	strcpy(r -> corb, corb);

	r -> corp = (char*) malloc (strlen(corp) + 1);
	if (r -> corp == NULL) {
		printf("Erro na alocacao de memoria para a cor de preenchimento do retangulo!\n");
		free(r);
		exit(1);
	}
	strcpy(r -> corp, corp);

	return r;

}

int getIDretangulo(retangulo *r) {
	return r -> i;
}

double getXretangulo(retangulo *r) {
	return r -> x;
}

double getYretangulo(retangulo *r) {
	return r -> y;
}

double getLarguraRetangulo(retangulo *r) {
	return r -> w;
}

double getAlturaRetangulo(retangulo *r) {
	return r -> h;
}

char *getCorbRetangulo(retangulo *r) {
	return r -> corb;
}

char *getCorpRetangulo(retangulo *r) {
	return r -> corp;
}

void setIDretangulo(retangulo *r, int i) {
	r -> i = i;
}

void setXretangulo(retangulo *r, double x) {
	r -> x = x;
}

void setYretangulo(retangulo *r, double y) {
	r -> y = y;
}

void setLarguraRetangulo(retangulo *r, double w) {
	r -> w = w;
}

void setAlturaRetangulo(retangulo *r, double h) {
	r -> h = h;
}

void setCorbRetangulo(retangulo *r, char *corb) {
	if (corb == NULL) {
		return;
	}

	char *novaCorb = (char*) malloc (strlen(corb) + 1);
	if (novaCorb == NULL) {
		printf("Erro ao alocar memoria para a nova cor de borda do retangulo!\n");
		return;
	}

	strcpy(novaCorb, corb);
	free(r -> corb);
	r -> corb = novaCorb;
}

void setCorpRetangulo(retangulo *r, char *corp) {
	if (corp == NULL) {
		return;
	}

	char* novaCorp = (char*) malloc (strlen(corp) + 1);
	if (novaCorp == NULL) {
		printf("Erro ao alocar memoria para a nova cor de preenchimento do retangulo!\n");
		return;
	}

	strcpy(novaCorp, corp);
	free(r -> corp);
	r -> corp = novaCorp;
}

double calcAreaRetangulo(retangulo *r) {
	return ((r -> w) * (r -> h));
}

void destrutorRetangulo(retangulo **pr) {
	if (pr == NULL || *pr == NULL) {
		return;
	}

	retangulo *r = *pr;

	free(r -> corb);
	free(r -> corp);
	free(r);

	*pr = NULL;

}



