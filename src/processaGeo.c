#include "processaGeo.h"
#include "chao.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512
#define COMANDO_SIZE 16
#define COR_SIZE 64
#define TEXTO_SIZE 256
#define ESTILO_FAMILIA_SIZE 64
#define ESTILO_PESO_SIZE 16
#define ESTILO_TAMANHO_SIZE 16

typedef struct stEstiloTexto {
    char familia[ESTILO_FAMILIA_SIZE];
    char peso[ESTILO_PESO_SIZE];
    char tamanho[ESTILO_TAMANHO_SIZE];
} estilo_texto;

static void converter_familia_svg(const char* familia_trabalho, char* familia_svg) {
    if (strcmp(familia_trabalho, "sans") == 0) {
        strcpy(familia_svg, "sans-serif");
    } else if (strcmp(familia_trabalho, "serif") == 0) {
        strcpy(familia_svg, "serif");
    } else if (strcmp(familia_trabalho, "cursive") == 0) {
        strcpy(familia_svg, "cursive");
    } else {
        strcpy(familia_svg, "sans-serif"); // padrão
    }
}

static void converter_peso_svg(const char* peso_trabalho, char* peso_svg) {
    if (strcmp(peso_trabalho, "n") == 0) {
        strcpy(peso_svg, "normal");
    } else if (strcmp(peso_trabalho, "b") == 0) {
        strcpy(peso_svg, "bold");
    } else if (strcmp(peso_trabalho, "b+") == 0) {
        strcpy(peso_svg, "bolder");
    } else if (strcmp(peso_trabalho, "l") == 0) {
        strcpy(peso_svg, "lighter");
    } else {
        strcpy(peso_svg, "normal");
    }
}

static void inicializar_estilo_padrao(estilo_texto* estilo) {
    strcpy(estilo -> familia, "sans");
    strcpy(estilo -> peso, "n");
    strcpy(estilo -> tamanho, "12");
}

static void extrair_texto_com_espacos(const char* linha_buffer, int offset, char* conteudo_texto, size_t tamanho_max) {
    if (offset <= 0) {
        conteudo_texto[0] = '\0';
        return;
    }

    const char *inicio_texto = linha_buffer + offset;
    while (*inicio_texto && (*inicio_texto == ' ' || *inicio_texto == '\t')) {
        inicio_texto++;
    }

    strncpy(conteudo_texto, inicio_texto, tamanho_max - 1);
    conteudo_texto[tamanho_max - 1] = '\0';
    conteudo_texto[strcspn(conteudo_texto, "\r\n")] = '\0';
}

static void processar_circulo(const char* linha, chao* meuChao) {
    int id;
    double x, y, r;
    char corb[COR_SIZE] = "", corp[COR_SIZE] = "";

    int num_lidos = sscanf(linha, "c %i %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
    if (num_lidos < 4) return;

    circulo *c = criaCirculo(id, x, y, r, corb, corp);
    forma *f = criaForma(id, CIRCULO, c);
    adicionaNoChao(meuChao, f);
}

static void processar_retangulo(const char* linha, chao* meuChao) {
    int id;
    double x, y, w, h;
    char corb[COR_SIZE] = "", corp[COR_SIZE] = "";

    int num_lidos = sscanf(linha, "r %i %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
    if (num_lidos < 5) return;

    retangulo *r = criaRetangulo(id, x, y, w, h, corb, corp);
    forma *f = criaForma(id, RETANGULO, r);
    adicionaNoChao(meuChao, f);
}

static void processar_linha(const char* linha_buffer, chao* meuChao) {
    int id;
    double x1, y1, x2, y2;
    char cor[COR_SIZE] = "";

    int num_lidos = sscanf(linha_buffer, "l %i %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
    if (num_lidos < 5) return;

    linha *l = criaLinha(id, x1, y1, x2, y2, cor, false);
    forma *f = criaForma(id, LINHA, l);
    adicionaNoChao(meuChao, f);
}

static void processar_texto(const char* linha_buffer, chao* meuChao, estilo_texto* estilo_atual) {
    int id;
    double x, y;
    char corp[COR_SIZE] = "", corb[COR_SIZE] = "";
    char ancora = 'i';
    char conteudo_texto[TEXTO_SIZE] = "";
    int offset = 0;

    sscanf(linha_buffer, "t %i %lf %lf %s %s %c %n", &id, &x, &y, corb, corp, &ancora, &offset);

    extrair_texto_com_espacos(linha_buffer, offset, conteudo_texto, sizeof(conteudo_texto));

    char familia_svg[ESTILO_FAMILIA_SIZE];
    char peso_svg[ESTILO_PESO_SIZE];

    converter_familia_svg(estilo_atual->familia, familia_svg);
    converter_peso_svg(estilo_atual->peso, peso_svg);

    estilo *e_temp = criaEstilo(familia_svg, peso_svg, estilo_atual->tamanho);
    texto *t = criaTexto(id, x, y, corb, corp, ancora, conteudo_texto, e_temp);
    destroiEstilo(e_temp);

    forma *f = criaForma(id, TEXTO, t);
    if (f) {
        adicionaNoChao(meuChao, f);
    }
}

static void processar_estilo_texto(const char* linha, estilo_texto* estilo_atual) {
    char familia[ESTILO_FAMILIA_SIZE];
    char peso[ESTILO_PESO_SIZE];
    char tamanho[ESTILO_TAMANHO_SIZE];

    int num_lidos = sscanf(linha, "ts %s %s %s", familia, peso, tamanho);
    if (num_lidos == 3) {
        strcpy(estilo_atual->familia, familia);
        strcpy(estilo_atual->peso, peso);
        strcpy(estilo_atual->tamanho, tamanho);
    }
}

static void processar_comando(const char* linha_buffer, const char* comando,
                             chao* meuChao, estilo_texto* estilo_atual) {
    if (strcmp(comando, "c") == 0) {
        processar_circulo(linha_buffer, meuChao);
    }
    else if (strcmp(comando, "r") == 0) {
        processar_retangulo(linha_buffer, meuChao);
    }
    else if (strcmp(comando, "l") == 0) {
        processar_linha(linha_buffer, meuChao);
    }
    else if (strcmp(comando, "t") == 0) {
        processar_texto(linha_buffer, meuChao, estilo_atual);
    }
    else if (strcmp(comando, "ts") == 0) {
        processar_estilo_texto(linha_buffer, estilo_atual);
    }
}

chao* processaGeo(const char *nome_path_geo) {
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

    estilo_texto estilo_atual;
    inicializar_estilo_padrao(&estilo_atual);

    char linha_buffer[BUFFER_SIZE];
    char comando[COMANDO_SIZE];

    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo_geo) != NULL) {

        comando[0] = '\0';
        sscanf(linha_buffer, "%s", comando);

        processar_comando(linha_buffer, comando, meuChao, &estilo_atual);
    }

    fclose(arquivo_geo);
    return meuChao;
}