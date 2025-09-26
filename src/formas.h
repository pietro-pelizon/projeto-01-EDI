#ifndef FORMAS_H
#define FORMAS_H

typedef enum {
	CIRCULO,
	RETANGULO,
	LINHA,
	TEXTO
}tipoForma;

typedef struct stForma forma;

forma *criaForma(int id, tipoForma tipo, void *dados);

void destroiForma(forma *f);

int getIDForma(forma *f);

tipoForma getTipoForma(forma *f);

void *getFormaDados(forma *f);

double getAreaForma(forma *f);

void destroiForma(forma *f);
#endif //FORMAS_H
