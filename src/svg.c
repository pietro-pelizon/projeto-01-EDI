#include "svg.h"

#include <stdio.h>
#include <stdlib.h>



void printaCabecalhoSVG(FILE *svg, const char *nomeArquivo) {
	abreSvgEscrita(nomeArquivo);
	fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(svg,"<svg width=\"1000\" height=\"1000\" viewBox=\"0 0 1000 1000\" xmlns=\"http://www.w3.org/2000/svg\">\n");

}

FILE *abreSvgEscrita(const char *nomeArquivo) {
	FILE *svg = fopen (nomeArquivo, "w");
	if (svg == NULL) {
		printf("Erro ao abrir o arquivo SVG!\n");
		exit(EXIT_FAILURE);
	}

	return svg;

}

void insereCirculo(FILE *svg, circulo *c) {
	fprintf(svg, " <circle id=\"%i\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" \>\n",
	getIDCirculo(c), getXCirculo(c), getYCirculo(c), getRaioCirculo(c), getCorbCirculo(c), getCorpCirculo(c));
}

void insereRetangulo(FILE *svg, retangulo *r) {
	fprintf(svg, " <rect id=\"%i\" x=\"%lf\" y=\"%lf\" width=\"%lf\" stroke=\"%lf\" =\"%s\" fill=\"%s\" \>\n",
	getIDretangulo(r), getXretangulo(r), getYretangulo(r), getLarguraRetangulo(r), getAlturaRetangulo(r),
	getCorbRetangulo(r), getCorpRetangulo(r));
}

void insereLinha(FILE *svg, linha *l) {
fprintf(svg, " <line id=\"%i\" x1=\"%lf\ y1=\"%lf\ x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" \>\n",
	getIDLinha(l), getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l));
}

void insereTexto(FILE *svg, texto *t, estilo *e) {

	fprintf(svg, " <text id=\"%i\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\"
			  "font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" ", getIDTexto(t), getXTexto(t),
			  getYTexto(t), getCorbTexto(t), getCorpTexto(t), getfFamily(e), getfWeight(e), getfSize(e));

	char ancora = getATexto(t);
	switch (ancora) {
		case 'i':
		default:
			fprintf(svg, "text-anchor=\"start\"");
			break;

		case 'm':
			fprintf(svg, "text-anchor=\"middle\"");
			break;

		case 'f':
			fprintf(svg, "text-anchor=\"end\"");
			break;
	}

	fprintf(svg, ">\"%s\"<text\>\n", getTxtoTexto(t));

}

void fechaSVG(FILE *svg) {
	fprintf(svg, "\n</svg>");
	fclose(svg);
}
