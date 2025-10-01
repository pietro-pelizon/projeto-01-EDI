#include <stdio.h>
#include <stdlib.h>

#include "formas.h"

#include <string.h>

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
		printf("Erro ao criar a forma!\n");
		return NULL;
	}

	f -> id = id;
	f -> tipo = tipo;
	f -> dados = dados;

	return f;
}

int getIDforma(forma *f) {
	return f -> id;
}


tipoForma getTipoForma(forma *f) {
	return f -> tipo;
}

void *getFormaDados(forma *f) {
	return f -> dados;
}

void setIDforma(forma *f, int novoID) {
	f -> id = novoID;
}

char *getCorbForma(forma *f) {
	tipoForma tipo = getTipoForma(f);

	switch (tipo) {
		case CIRCULO: {
			return getCorbCirculo(getFormaDados(f)); break;
		}

		case RETANGULO: {
			return getCorbRetangulo(getFormaDados(f)); break;
		}

		case LINHA: {
			return getCorLinha(getFormaDados(f)); break;
		}

		case TEXTO: {
			return getCorbTexto(getFormaDados(f)); break;
		}
		default: {
			return NULL;
		}
	}
}

char *getCorpForma(forma *f) {
	if (f == NULL) {
		return NULL;
	}

	tipoForma tipo = getTipoForma(f);

	switch (tipo) {
		case CIRCULO: {
			return getCorpCirculo(getFormaDados(f)); break;
		}

		case RETANGULO: {
			return getCorpRetangulo(getFormaDados(f)); break;
		}

		case LINHA: {
			return getCorLinha(getFormaDados(f)); break;
		}

		case TEXTO: {
			return getCorpTexto(getFormaDados(f)); break;
		}
		default: {
			return NULL;
		}
	}
}

void setCorpFormas(forma *f, char *novaCor) {
	if (f == NULL || novaCor == NULL) {
		return;
	}

	tipoForma tipo = getTipoForma(f);

	switch (tipo) {
		case CIRCULO: {
			setCorpCirculo(getFormaDados(f), novaCor);
		}

		case RETANGULO: {
			setCorpRetangulo(getFormaDados(f), novaCor);
		}

		case LINHA: {
			setCorLinha(getFormaDados(f), novaCor);
		}

		case TEXTO: {
			setCorpTexto(getFormaDados(f), novaCor);
		}
	}
}

void setCorbFormas(forma *f, char *novaCor) {
	if (f == NULL || novaCor == NULL) {
		return;
	}

	tipoForma tipo = getTipoForma(f);

	switch (tipo) {
		case CIRCULO: {
			setCorbCirculo(getFormaDados(f), novaCor);
		}

		case RETANGULO: {
			setCorbRetangulo(getFormaDados(f), novaCor);
		}

		case LINHA: {
			setCorLinha(getFormaDados(f), novaCor);
		}

		case TEXTO: {
			setCorbTexto(getFormaDados(f), novaCor);
		}
	}
}

forma *clonarForma(forma *f_original) {
	int ID_original = getIDforma(f_original);
	tipoForma tipo_forma_original = getTipoForma(f_original);
	void *dados_original = getFormaDados(f_original);

	forma *forma_clone = criaForma(ID_original + 1, tipo_forma_original, dados_original);

	return forma_clone;
}


char *getCorComplementar(char *cor_hexa_original) {
	if (cor_hexa_original == NULL || cor_hexa_original[0] != '#') {
		char* branco_padrao = (char*) malloc(8 *  sizeof(char));
		if (branco_padrao) {
			strcpy(branco_padrao, "#FFFFFF");
			return branco_padrao;
		}
	}

	int r, g, b;

	if (strlen(cor_hexa_original) == 7) {
		sscanf(cor_hexa_original, "#%02x%02x%02x", &r, &g, &b);
	}

	else if (strlen(cor_hexa_original) == 4) {
		int r_short, g_short, b_short;

		sscanf(cor_hexa_original, "%1x%1x%1x", &r_short, &g_short, &b_short);

		r = r_short * 17;
		g = g_short * 17;
		b = b_short * 17;
	}

	else {
		printf("Formato invalido de cor hexadecimal!\n");
		r = 0, g = 0, b = 0;
	}

	int comp_r = 255 - r, comp_g = 255 - g, comp_b = 255 - b;

	char *cor_complementar_hexa = malloc(8 * sizeof(char));
	if (cor_complementar_hexa == NULL) {
		printf("Erro ao alocar memoria na funcao getCorComplementar!\n");
		return NULL;
	}

	sprintf(cor_complementar_hexa, "#%02x%02x%02x", comp_r, comp_g, comp_b);

	return cor_complementar_hexa;
}

void trocaCores(forma *f1, forma *f2) {
	if (f1 == NULL) {
		return;
	}

	char *cor_borda_forma_J = getCorbForma(f2);

	setCorpFormas(f1, cor_borda_forma_J);
}

void alternaCores(forma *f) {
	if (f == NULL) {
		return;
	}

	setCorpFormas(f, getCorbForma(f));
	setCorbFormas(f, getCorpForma(f));
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