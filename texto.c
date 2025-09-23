#include "texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stEstilo {
	char *fFamily;
	char *fWeight;
	char *fSize;
}estilo;

typedef struct stTexto {
	int i;
	double x, y;
	char *corb, *corp, a;
	char *txto;
	estilo *e;
}texto;

estilo *criaEstilo(char *fFamily, char *fWeight, char *fSize) {
	estilo *e = malloc (sizeof(estilo));
	if (e == NULL) {
		printf("Erro ao alocar memoria para o estilo do texto!\n");
		exit(1);
	}

	e -> fFamily = (char*) malloc (strlen(fFamily) + 1);
	if (e -> fFamily == NULL) {
		printf("Erro ao alocar memoria para a familia do estilo!\n");
		free(e);
		exit(1);
	}
	strcpy(e -> fFamily, fFamily);

	e -> fWeight = (char*) malloc (strlen(fWeight) + 1);
	if (e -> fWeight == NULL) {
		printf("Erro ao alocar memoria para a espessura do estilo!\n");
		free(e);
		exit(1);
	}
	strcpy(e -> fWeight, fWeight);

	e -> fSize = (char*) malloc (strlen(fSize) + 1);
	if (e -> fSize == NULL) {
		printf("Erro ao alocar memoria para o tamanho do estilo!\n");
		free(e);
		exit(1);
	}
	strcpy(e -> fSize, fSize);

	return e;
}

char *getfFamily(estilo *e) {
	return e -> fFamily;
}

char *getfWeight(estilo *e) {
	return e -> fWeight;
}

char *getfSize(estilo *e) {
	return e -> fSize;
}

void setfFamily(estilo *e, char *newfFamily) {
	if (newfFamily == NULL) {
		return;
	}

	free(e -> fFamily);

	e -> fFamily = (char*) malloc (strlen(newfFamily) + 1);
	if (e -> fFamily == NULL) {
		printf("Erro ao trocar a familia do estilo do texto!\n");
		free(e);
		exit(1);
	}
	strcpy(e -> fFamily, newfFamily);
}

void setfWeight(estilo *e, char *newfWeight) {
	if (newfWeight == NULL) {
		return;
	}

	free(e -> fWeight);

	e -> fWeight = (char*) malloc (strlen(newfWeight) + 1);
	if (e -> fWeight == NULL) {
		printf("Erro ao trocar a espessura do estilo do texto!\n");
		free(e);
		exit(1);
	}
	strcpy(e -> fWeight, newfWeight);
}

void setfSize(estilo *e, char *newfSize) {
	if (newfSize == NULL) {
		return;
	}

	free(e -> fSize);
	e -> fSize = (char*) malloc (strlen(newfSize) + 1);
	if (e -> fSize == NULL) {
		printf("Erro ao trocar o tamanho do estilo do texto!\n");
		free(e);
		exit(1);
	}
	strcpy(e -> fSize, newfSize);
}

texto *criaTexto(int i, double x, double y, char *corb, char *corp, char a, char *txto, estilo *e) {
	texto *t = malloc (sizeof(texto));
	if (t == NULL) {
		printf("Erro ao alocar memoria para a stTexto!\n");
		exit(1);
	}

	t -> i = i;
	t -> x = x;
	t -> y = y;
	t -> corb = (char*) malloc (strlen(corb) + 1);
	if (t -> corb == NULL) {
		printf("Erro na alocacao da cor de borda do texto!\n");
		free(t);
		exit(1);
	}
	strcpy(t -> corb, corb);

	t -> corp = (char*) malloc (strlen(corp) + 1);
	if (t -> corp == NULL) {
		printf("Erro na alocacao da cor de preenchimento do texto!\n");
		free(t);
		exit(1);
	}
	strcpy(t -> corp, corp);

	t -> a = a;

	t -> txto = (char*) malloc (strlen(txto) + 1);
	if (t -> txto == NULL) {
		printf("Erro ao alocar memoria para o texto!\n");
		free(t);
		exit(1);
	}
	strcpy(t -> txto, txto);

	t -> e = e;

	return t;

}

int getIDTexto(texto *t) {
	return t -> i;
}

double getXTexto(texto *t) {
	return t -> x;
}

double getYTexto(texto *t) {
	return t -> y;
}

char *getCorbTexto(texto *t) {
	return t -> corb;
}

char *getCorpTexto(texto *t) {
	return t -> corp;
}

char getATexto(texto *t) {
	return t -> a;
}

char *getTxtoTexto(texto *t) {
	return t -> txto;
}

estilo *getEstiloTexto(texto *t) {
	return t -> e;
}

void setIDTexto(texto *t, int i) {
	t -> i = i;
}

void setXTexto(texto *t, double x) {
	t -> x = x;
}

void setYTexto(texto *t, double y) {
	t -> y = y;
}

void setCorbTexto(texto *t, char *corb) {
	free(t -> corb);

	t -> corb = (char*) malloc (strlen(corb) + 1);
	if (t -> corb == NULL) {
		printf("Erro ao trocar a cor da borda o texto!\n");
		free(t);
		exit(1);
	}
	strcpy(t -> corb, corb);
}

void setCorpTexto(texto *t, char *corp) {
	free(t -> corp);

	t -> corp = (char*) malloc (strlen(corp) + 1);
	if (t -> corp == NULL) {
		printf("Erro ao trocar a cor da borda o texto!\n");
		free(t);
		exit(1);
	}
	strcpy(t -> corp, corp);
}

void setATexto(texto *t, char a) {
	t -> a = a;
}

void setEstiloTexto(texto *t, estilo *novoEstilo) {
	t -> e = novoEstilo;
}

double calcAreaTexto(texto *t) {
	double area = 20.0 * strlen(t -> txto);
	return area;
}

