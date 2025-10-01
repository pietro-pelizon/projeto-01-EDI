#include "chao.h"
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct stChao {
    fila *filaChao;
}chao;

chao *criaChao() {
    chao *c = (chao*) malloc (sizeof(chao));
    if (c == NULL) {
        printf("Erro ao criar o chao!\n");
        return NULL;
    }
    c -> filaChao = criaFila();

    printf("Chão criado com sucesso!\n");

    return c;
}

bool chaoEstaVazio(chao *c) {
    if (estaVazia(c -> filaChao)) {
        return true;
    }

    return false;
}

void voltaProChao(chao *c, forma *f) {
    if (f == NULL || c == NULL) {
        return;
    }

    enqueue(c -> filaChao, f);
}

forma *retiraChao(chao *c) {
    if (c == NULL) {
        return NULL;
    }

    forma *removido = dequeue(c -> filaChao);
    return removido;
}

void destrutorChao(chao *c) {
    if (c == NULL) {
        return;
    }

    free(c -> filaChao);
    free(c);
}

