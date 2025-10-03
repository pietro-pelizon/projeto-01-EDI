#include <stdio.h>
#include <stdlib.h>

#include "formas.h"

#include <string.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "svg.h"
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
	void *dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO: {
			return getCorbCirculo(dados);
		}

		case RETANGULO: {
			return getCorbRetangulo(dados);
		}

		case LINHA: {
			return getCorLinha(dados);
		}

		case TEXTO: {
			return getCorbTexto(dados);
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
	void *dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO: {
			return getCorpCirculo(dados);
		}

		case RETANGULO: {
			return getCorpRetangulo(dados);
		}

		case LINHA: {
			return getCorLinha(dados);
		}

		case TEXTO: {
			return getCorpTexto(dados);
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
	void *dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO: {
			setCorpCirculo(dados, novaCor); break;
		}

		case RETANGULO: {
			setCorpRetangulo(dados, novaCor); break;
		}

		case LINHA: {
			setCorLinha(dados, novaCor); break;
		}

		case TEXTO: {
			setCorpTexto(dados, novaCor); break;
		}

		default:
			break;
	}
}

void setCorbFormas(forma *f, char *novaCor) {
	if (f == NULL || novaCor == NULL) {
		return;
	}

	tipoForma tipo = getTipoForma(f);
	void *dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO: {
			setCorbCirculo(dados, novaCor); break;
		}

		case RETANGULO: {
			setCorbRetangulo(dados, novaCor); break;
		}

		case LINHA: {
			setCorLinha(dados, novaCor); break;
		}

		case TEXTO: {
			setCorbTexto(dados, novaCor); break;
		}
		default:
			break;
	}
}

forma *clonarForma(forma *f_original) {
    if (f_original == NULL) return NULL;

    static int max_id = 10000;
    int novo_id = ++max_id;

    tipoForma tipo = getTipoForma(f_original);
    void *dados_orig = getFormaDados(f_original);
    void *novos_dados = NULL;
    forma *forma_clonada = NULL;

    switch (tipo) {
        case CIRCULO: {
            circulo *c = (circulo*)dados_orig;
            novos_dados = criaCirculo(novo_id,
                getXCirculo(c),
                getYCirculo(c),
                getRaioCirculo(c),
                getCorbCirculo(c),
                getCorpCirculo(c));
            break;
        }

        case RETANGULO: {
            retangulo *r = (retangulo*)dados_orig;
            novos_dados = criaRetangulo(novo_id,
                getXretangulo(r),
                getYretangulo(r),
                getLarguraRetangulo(r),
                getAlturaRetangulo(r),
                getCorbRetangulo(r),
                getCorpRetangulo(r));
            break;
        }

        case LINHA: {
            linha *l = (linha*)dados_orig;
            novos_dados = criaLinha(novo_id,
                getX1Linha(l),
                getY1Linha(l),
                getX2Linha(l),
                getY2Linha(l),
                getCorLinha(l));
            break;
        }

        case TEXTO: {
            texto *t = (texto*)dados_orig;
            estilo *e_orig = getEstiloTexto(t);
            estilo *e_novo = NULL;

            if (e_orig != NULL) {
                e_novo = criaEstilo(
                    getfFamily(e_orig),
                    getfWeight(e_orig),
                    getfSize(e_orig)
                );
            }

            novos_dados = criaTexto(novo_id,
                getXTexto(t),
                getYTexto(t),
                getCorbTexto(t),
                getCorpTexto(t),
                getATexto(t),
                getTxtoTexto(t),
                e_novo);
        	if (e_novo != NULL) {
        		destroiEstilo(e_novo);

        	}
            break;
        }
        default:
            return NULL;
    }

    if (novos_dados != NULL) {
        forma_clonada = criaForma(novo_id, tipo, novos_dados);
    }

    return forma_clonada;
}

char *getCorComplementar(char *cor_hexa_original) {
    if (cor_hexa_original == NULL) {
        char* branco_padrao = (char*) malloc(8 * sizeof(char));
        if (branco_padrao) {
            strcpy(branco_padrao, "#FFFFFF");
            return branco_padrao;
        }
        return NULL;
    }

    int tem_hash = (cor_hexa_original[0] == '#');
    const char *cor_str = tem_hash ? cor_hexa_original + 1 : cor_hexa_original;
    int len = strlen(cor_str);

    int r, g, b;

    if (len == 6) {
        if (sscanf(cor_str, "%02x%02x%02x", &r, &g, &b) != 3) {
            printf("Formato inválido de cor hexadecimal: %s\n", cor_hexa_original);
            r = g = b = 0;
        }
    }
    else if (len == 3) {
        int r_short, g_short, b_short;
        if (sscanf(cor_str, "%1x%1x%1x", &r_short, &g_short, &b_short) != 3) {
            printf("Formato inválido de cor hexadecimal: %s\n", cor_hexa_original);
            r = g = b = 0;
        } else {
            r = r_short * 17;
            g = g_short * 17;
            b = b_short * 17;
        }
    }
    else {
        printf("Comprimento inválido de cor hexadecimal: %s (comprimento: %d)\n", cor_hexa_original, len);
        char* branco_padrao = (char*) malloc(8 * sizeof(char));
        if (branco_padrao) {
            strcpy(branco_padrao, "#FFFFFF");
            return branco_padrao;
        }
        return NULL;
    }

    int comp_r = 255 - r;
    int comp_g = 255 - g;
    int comp_b = 255 - b;

    comp_r = (comp_r < 0) ? 0 : (comp_r > 255) ? 255 : comp_r;
    comp_g = (comp_g < 0) ? 0 : (comp_g > 255) ? 255 : comp_g;
    comp_b = (comp_b < 0) ? 0 : (comp_b > 255) ? 255 : comp_b;

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
	char *cor_preenchimento_forma_I = getCorpForma(f1);

	setCorbFormas(f2, cor_preenchimento_forma_I);
	setCorpFormas(f1, cor_borda_forma_J);
}

void alternaCores(forma *f) {
	if (f == NULL) {
		return;
	}

	char *borda = getCorbForma(f);
	char *preenchimento = getCorpForma(f);

	setCorpFormas(f, borda);
	setCorbFormas(f, preenchimento);

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
			setYCirculo(c, y);
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

void desenhaFormaSvg(forma *f, FILE *svg) {
	tipoForma tipo = getTipoForma(f);
	void *dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO: {
			insereCirculo(svg, (circulo*)dados); break;
		}

		case RETANGULO: {
			insereRetangulo(svg, (retangulo*)dados); break;
		}

		case LINHA: {
			insereLinha(svg, (linha*)dados); break;
		}

		case TEXTO: {
			insereTexto(svg, (texto*)dados); break;
		}

		default: break;
	}
}

void escreveDadosFormaTxt(forma *f, FILE *txt, char *reportDaFuncaoQRY) {
	tipoForma tipo = getTipoForma(f);
	void* dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO: {
			fprintf(txt, "%s\n Círculo\n ID: %i\n Âncora em: (%.2lf, %.2lf)\n Raio: %lf\n Cor de borda: %s\n Cor de preenchimento: %s\n",
				reportDaFuncaoQRY,
				getIDforma(f),
				getXCirculo(dados),
				getYCirculo(dados),
				getRaioCirculo(dados),
				getCorbForma(f),
				getCorpForma(f)); break;
		}

		case RETANGULO: {
			fprintf(txt, "%s\n Retângulo\n ID: %i\n Âncora em: (%.2lf, %.2lf)\n Largura: %lf\n Altura %lf\n Cor de borda: %s\n Cor de preenchimento: %s\n",
				reportDaFuncaoQRY,
				getIDforma(f),
				getXretangulo(dados),
				getYretangulo(dados),
				getLarguraRetangulo(dados),
				getAlturaRetangulo(dados),
				getCorbForma(f),
				getCorpForma(f)); break;
		}

		case LINHA: {
			fprintf(txt, "%s\n Linha\n ID: %i\n Âncora de início em: (%.2lf, %.2lf)\n Âncora de fim em: (%.2lf, %.2lf)\n Cor: %s\n",
				reportDaFuncaoQRY,
				getIDforma(f),
				getX1Linha(dados),
				getY1Linha(dados),
				getX2Linha(dados),
				getY2Linha(dados),
				getCorbForma(f)); break;
		}
		case TEXTO: {
			texto* t = (texto*)dados;
			estilo* e = getEstiloTexto(t);

			fprintf(txt, " Texto\n ID: %d\n Âncora em: (%.2f, %.2f)\n Posição da Âncora: %c\n Conteúdo: \"%s\"\n Cor de borda: %s\n Cor de preenchimento: %s\n",
				getIDforma(f),
				getXTexto(t),
				getYTexto(t),
				getATexto(t),
				getTxtoTexto(t),
				getCorbForma(f),
				getCorpForma(f));

			if (e != NULL) {
				fprintf(txt, " Família da fonte: %s\n Peso da fonte: %s\n Tamanho da fonte: %s\n\n",
					getfFamily(e),
					getfWeight(e),
					getfSize(e));
			} else {
				fprintf(txt, "\n");
			} break;


			default:
			fprintf(txt, "Tipo de forma desconhecida!\n");
			break;
		}
	}
}

double getXForma(forma *f) {
	if (f == NULL) {
		return 0.0;
	}

	tipoForma tipo = getTipoForma(f);
	void* dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO:
			return getXCirculo(dados);
		case RETANGULO:
			return getXretangulo(dados);
		case TEXTO:
			return getXTexto(dados);
		case LINHA:
			return getX1Linha(dados);
		default:
			return 0.0;
	}
}

double getYForma(forma *f) {
	if (f == NULL) {
		return 0.0;
	}

	tipoForma tipo = getTipoForma(f);
	void* dados = getFormaDados(f);

	switch (tipo) {
		case CIRCULO:
			return getYCirculo(dados);
		case RETANGULO:
			return getYretangulo(dados);
		case TEXTO:
			return getYTexto(dados);
		case LINHA:
			return getY1Linha(dados);
		default:
			return 0.0;
	}
}


