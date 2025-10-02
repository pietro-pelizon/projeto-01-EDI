#include "processaQry.h"
#include "carregadores.h"
#include "disparador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJETOS 100

typedef struct stRepositorio {
    carregador *c[MAX_OBJETOS];
    int num_carregadores;
    disparador *d[MAX_OBJETOS];
    int num_disparadores;

}repositorio;



repositorio* criarRepositorio() {
    repositorio *repo = malloc(sizeof(repositorio));
    if (repo == NULL) {
        printf("Erro ao alocar memoria para o repositorio de objetos!\n");
        return NULL;
    }

    repo -> num_carregadores = 0;
    repo -> num_disparadores = 0;
    repo -> c;
    repo -> d;

    return repo;

}

void destruirRepositorio(repositorio* repo) {
    if (repo == NULL) return;

    for (int i = 0; i < repo->num_carregadores; i++) {
        destrutorCarregador(repo-> c[i]);
    }
    for (int i = 0; i < repo->num_disparadores; i++) {
        destrutorDisparador(repo-> d[i]);
    }

    free(repo);
}

disparador *encontraOUCriarDisparador(repositorio *repo, int id) {
    for (int i = 0; i < repo -> num_disparadores; i++) {
        if (getIDdisparador(repo -> d[i]) == id) {
            return repo -> d[i];
        }
    }

    if (repo -> num_disparadores < MAX_OBJETOS) {
        disparador *novo_disparador = criaDisparador(id, 0, 0, NULL, NULL);
        repo -> d[repo -> num_disparadores++] = novo_disparador;
            return novo_disparador;
    }

    return NULL;
}

carregador* encontrarOuCriarCarregador(repositorio* repo, int id) {
    for (int i = 0; i < repo->num_carregadores; i++) {
        if (getIDCarregador(repo->c[i]) == id) {
            return repo->c[i];
        }
    }

    if (repo->num_carregadores < MAX_OBJETOS) {
        carregador* novo_c = criaCarregador(id);
        repo-> c[repo->num_carregadores++] = novo_c;
        return novo_c;
    }

    return NULL;
}

void processaQry(repositorio *repo, char *nome_path_qry, const char *nome_txt, arena *arena, chao *chao, double *pontuacao_total) {
    FILE *arquivo_qry = fopen(nome_path_qry, "r");
    if (!arquivo_qry) {
        printf("Erro ao abrir o arquivo qry!\n");
        return;
    }

    FILE *arquivo_txt = fopen(nome_txt, "w");
    if (!arquivo_txt) {
        printf("Erro ao abrir o arquivo txt!\n");
        return;
    }


    char linha_buffer[512];
    char comando[16];


    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo_qry) != NULL) {
        sscanf(linha_buffer, "%s", comando);
        fprintf(arquivo_txt, "[*] %s", linha_buffer);

        if (strcmp(comando, "pd") == 0) {
            int id; double x, y;
            sscanf(linha_buffer, "pd %i %lf %lf", &id, &x, &y);
            disparador *d = encontraOUCriarDisparador(repo, id);
            if (d) {
                posicionaDisparador(d, x, y);
            }
        }


    }


}