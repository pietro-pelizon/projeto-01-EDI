#include "svg.h"

#include <stdio.h>

FILE* inicializaSvg(const char* caminhoArquivo, double largura, double altura) {
	FILE* svg = fopen(caminhoArquivo, "w");
	if (svg == NULL) {
		perror("ERRO ao abrir o arquivo SVG");
		return NULL;
	}

	fprintf(svg, "<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 %.0f %.0f\" xmlns=\"http://www.w3.org/2000/svg\">\n", largura, altura);

	fprintf(svg, "\t<rect width=\"1000%%\" height=\"1000%%\" fill=\"#f0f0f0\" />\n");

	return svg;
}

void insereCirculo(FILE *svg, circulo *c) {
	fprintf(svg, " <circle id=\"%i\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" />\n",
	getIDCirculo(c),
	getXCirculo(c),
	getYCirculo(c),
	getRaioCirculo(c),
	getCorbCirculo(c),
	getCorpCirculo(c));
}

void insereRetangulo(FILE *svg, retangulo *r) {
	fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" />\n",
		getIDretangulo(r),
		getXretangulo(r),
		getYretangulo(r),
		getLarguraRetangulo(r),
		getAlturaRetangulo(r),
		getCorbRetangulo(r),
		getCorpRetangulo(r));
}

void insereLinha(FILE *svg, linha *l) {
	fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" />\n",
		getIDLinha(l),
		getX1Linha(l),
		getY1Linha(l),
		getX2Linha(l),
		getY2Linha(l),
		getCorLinha(l));
}

void insereTexto(FILE *svg, texto *t) {
	if (t == NULL) return;

	estilo* e = getEstiloTexto(t);
	if (e == NULL) return;

	fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" ",
		getIDTexto(t),
		getXTexto(t),
		getYTexto(t),
		getCorbTexto(t),
		getCorpTexto(t),
		getfFamily(e),
		getfWeight(e),
		getfSize(e));

	char ancora = getATexto(t);
	switch (ancora) {
		case 'm':
			fprintf(svg, "text-anchor=\"middle\"");
			break;
		case 'f':
			fprintf(svg, "text-anchor=\"end\"");
			break;
		case 'i':
		default:
			fprintf(svg, "text-anchor=\"start\"");
			break;
	}

	fprintf(svg, ">%s</text>\n", getTxtoTexto(t));
}

void fechaSVG(FILE *svg) {
	fprintf(svg, "\n</svg>");
	fclose(svg);
}
