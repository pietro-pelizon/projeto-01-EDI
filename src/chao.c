#include "chao.h"
#include "fila.h"
#include "formas.h"
#include <stdio.h>
#include <stdlib.h>

struct stChao {
    fila *filaChao;
};

chao *criaChao() {
    chao *c = (chao*) malloc(sizeof(chao));
    if (c == NULL) {
        printf("Erro ao criar o chao!\n");
        return NULL;
    }
    c->filaChao = criaFila();
    printf("Chão criado com sucesso!\n");
    return c;
}


void adicionaNoChao(chao *c, forma *f) {
    if (c == NULL || f == NULL) {
        return;
    }

    enqueue(c->filaChao, f);
    printf("DEBUG: Forma ID=%d ADICIONADA ao chão\n", getIDforma(f));
}

forma *retiraDoChao(chao *c) {
    if (c == NULL) return NULL;

    forma *removido = dequeue(c -> filaChao);

    return removido;
}

void destrutorChao(chao *chao) {
    if (chao == NULL) return;

    printf("DEBUG CHAO: Destruindo chão. Formas na fila: %d\n", getTamFila(chao -> filaChao));

    if (chao -> filaChao != NULL) {
        liberaFila(chao -> filaChao, (void (*)(void*)) destrutorForma);
        chao -> filaChao = NULL;
    }

    free(chao);
}


fila *getFilaDoChao(chao *c) {
    if (c == NULL) return NULL;
    return c -> filaChao;
}

bool chaoEstaVazio(chao *c) {
    if (c == NULL) return true;
    return estaVaziaFila(c -> filaChao);
}
