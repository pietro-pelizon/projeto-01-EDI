#ifndef STDQRY_H
#define STDQRY_H
#include <stdio.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"

FILE *abreSvgEscrita(const char *nomeArquivo);

void printaCabecalhoSvg(FILE *svg, const char *nomeArquivo);

void insereRetangulo(FILE *svg, retangulo *r);

void insereCirculo(FILE *svg, circulo *c)

void insereTexto(FILE *svg, texto *t)

void insereLinha(FILE *svg, linha *l)

void fechaSVG(FILE *svg);

#endif //STDQRY_H
