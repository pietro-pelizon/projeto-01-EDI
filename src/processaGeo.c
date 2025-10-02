#include "processaGeo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chao.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"


chao *processaGeo(const char *nome_path_geo) {
    FILE *arquivo_geo = fopen(nome_path_geo, "r");
    if (arquivo_geo == NULL) {
        printf("Erro ao abrir o arquivo .geo!\n");
        return NULL;
    }

    chao *meuChao = criaChao();
    char linha_buffer[512];
    char comando[16];

    char estilo_familia[64] = "sans";
    char estilo_peso[16] = "n";
    char estilo_tamanho[16] = "12";

    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo_geo) != NULL) {
        if (linha_buffer[0] == '\n' || linha_buffer[0] == '#') continue;

        sscanf(linha_buffer, "%s", comando);

        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; char corb[64], corp[64];
            sscanf(linha_buffer, "c %i %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);

            circulo *c = criaCirculo(id, x, y, r, corb, corp);
            forma *f = criaForma(id, CIRCULO, c);
            adicionaNoChao(meuChao, f);
        }

        else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; char corb[64], corp[64];
            sscanf(linha_buffer, "r %i %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);

            retangulo *r = criaRetangulo(id, x, y, w, h, corb, corp);
            forma *f = criaForma(id, RETANGULO, r);
            adicionaNoChao(meuChao, f);
        }

        else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[64];
            sscanf(linha_buffer, "l %i %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);

            linha *l = criaLinha(id, x1, y1, x2, y2, cor);
            forma *f = criaForma(id, LINHA, l);
            adicionaNoChao(meuChao, f);
        }

        else if (strcmp(comando, "t") == 0) {
            int id; double x, y; char corp[64], corb[64], ancora;
            char conteudo_texto[256];

            char *inicio_texto = strstr(linha_buffer, "txto");
            if (inicio_texto != NULL) {
                inicio_texto += 5;
                inicio_texto[strcspn(inicio_texto, "\r\n")] = 0;
                strcpy(conteudo_texto, inicio_texto);
            }

            else {
                strcpy(conteudo_texto, "");
            }

            sscanf(linha_buffer, "t %i %lf %lf %s %s %c", &id, &x, &y, corp, corb, &ancora);

            estilo *e = criaEstilo(estilo_familia, estilo_peso, estilo_tamanho);
            texto *t = criaTexto(id, x, y, corb, corp, ancora, conteudo_texto, e);
            forma *f = criaForma(id, TEXTO, t);
            adicionaNoChao(meuChao, f);
            destroiEstilo(e);
        }

        else if (strcmp(comando, "ts") == 0) {
            sscanf(linha_buffer, "ts %s %s %s", &estilo_familia, &estilo_peso, &estilo_tamanho);
        }
    }

    fclose(arquivo_geo);
    return meuChao;
}
