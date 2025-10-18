#include "processaGeo.h"
#include "chao.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

chao *processaGeo(const char *nome_path_geo) {
    FILE *arquivo_geo = fopen(nome_path_geo, "r");
    if (arquivo_geo == NULL) {
        perror("Erro ao abrir o arquivo .geo");
        return NULL;
    }

    chao *meuChao = criaChao();
    if (meuChao == NULL) {
        fclose(arquivo_geo);
        return NULL;
    }

    char linha_buffer[512];
    char comando[16];

    char estilo_familia[64] = "sans";
    char estilo_peso[16] = "n";
    char estilo_tamanho[16] = "12";

    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo_geo) != NULL) {
        if (linha_buffer[0] == '\n' || linha_buffer[0] == '#') {
            continue;
        }

        comando[0] = '\0';
        sscanf(linha_buffer, "%s", comando);

        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; char corb[64] = "", corp[64] = "";
            int num_lidos = sscanf(linha_buffer, "c %i %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);

            if (num_lidos < 4) continue;

            circulo *c = criaCirculo(id, x, y, r, corb, corp);
            forma *f = criaForma(id, CIRCULO, c);
            adicionaNoChao(meuChao, f);
        }

        else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; char corb[64] = "", corp[64] = "";
            int num_lidos = sscanf(linha_buffer, "r %i %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);

            if (num_lidos < 5) continue;

            retangulo *r = criaRetangulo(id, x, y, w, h, corb, corp);
            forma *f = criaForma(id, RETANGULO, r);

            adicionaNoChao(meuChao, f);
        }

        else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[64] = "";
            int num_lidos = sscanf(linha_buffer, "l %i %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);

            if (num_lidos < 5) continue;

            linha *l = criaLinha(id, x1, y1, x2, y2, cor, false);
            forma *f = criaForma(id, LINHA, l);

            adicionaNoChao(meuChao, f);
        }

        else if (strcmp(comando, "t") == 0) {
            int id; double x, y; char corp[64] = "", corb[64] = "";
            char ancora = 'i';
            char conteudo_texto[256] = "";
            int offset = 0;

            sscanf(linha_buffer, "t %i %lf %lf %s %s %c %n", &id, &x, &y, corb, corp, &ancora, &offset);

            if (offset > 0) {
                const char *inicio_texto = linha_buffer + offset;
                while (*inicio_texto && (*inicio_texto == ' ' || *inicio_texto == '\t')) {
                    inicio_texto++;
                }
                strncpy(conteudo_texto, inicio_texto, sizeof(conteudo_texto) - 1);
                conteudo_texto[sizeof(conteudo_texto) - 1] = '\0';
                conteudo_texto[strcspn(conteudo_texto, "\r\n")] = 0;
            }


            estilo *e_temp = criaEstilo(estilo_familia, estilo_peso, estilo_tamanho);
            texto *t = criaTexto(id, x, y, corb, corp, ancora, conteudo_texto, e_temp);
            destroiEstilo(e_temp);

            forma *f = criaForma(id, TEXTO, t);


            if (f) {
                adicionaNoChao(meuChao, f);
            }
        }

        else if (strcmp(comando, "ts") == 0) {
            char familia[64], peso[16], tamanho[16];
            int num_lidos = sscanf(linha_buffer, "ts %s %s %s", familia, peso, tamanho);

            if (num_lidos == 3) {
                strcpy(estilo_familia, familia);
                strcpy(estilo_peso, peso);
                strcpy(estilo_tamanho, tamanho);
            }
        }
    }
        fclose(arquivo_geo);
        return meuChao;
}
