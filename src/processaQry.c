#include "processaQry.h"

#include <stdio.h>

#include "carregadores.h"
#include "chao.h"
#include "arena.h"
#include "disparador.h"



void processaQry(const char *nome_path_qry, arena *arena, chao *chao, disparador *d, carregador *c, double *pontuacao_total) {
    FILE *arquivo_qry = fopen(nome_path_qry, "r");
    if (!arquivo_qry) {
        printf("Erro ao abrir o arquivo QRY!\n");
        return;
    }

    char comando[16];
    char linha_buffer[512];


}



