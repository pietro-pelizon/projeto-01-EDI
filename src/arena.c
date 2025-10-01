#include "arena.h"
#include "fila.h"
#include "formas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sobreposicao.h"

typedef struct stArena {
    double altura, largura;
    fila *filaArena;
}arena;

arena *criaArena(double largura, double altura) {
    arena *a = (arena*) malloc (sizeof(arena));
    if (a == NULL) {
        printf("Erro ao criar a arena!\n");
        return NULL;
    }

    a -> largura = largura;
    a-> altura = altura;
    a -> filaArena = criaFila();

    printf("Arena criada com sucesso!\n");

    return a;
}

forma *adicionaFormaArena(arena *a, forma *f) {
    if (f == NULL) {
        return NULL;
    }

    if (a == NULL) {
        printf("Arena inexistente passada para a função 'adicionaFormaArena'\n");
        return NULL;
    }

    enqueue(a -> filaArena, f);

    return f;

}

forma *removeFormaArena(arena *a) {
    if (a == NULL ) return NULL;

    forma *removido = dequeue(a -> filaArena);

    return removido;
}

bool arenaEstaVazia(arena *a) {
    if (a == NULL) return true;

    return estaVazia(a -> filaArena);
}

void destrutorArena(arena **a_ptr) {
    if (a_ptr == NULL || *a_ptr == NULL) {
        return;
    }
    arena* a = *a_ptr;

    liberaFila(a -> filaArena, destrutorForma);

    free(a);
    *a_ptr = NULL;
}

double getLarguraArena(arena *a) {
    return a -> largura;
}

double getAlturaArena(arena *a) {
    return a -> altura;
}

void setLarguraArena(arena *a, double novaLargura) {
    a -> largura = novaLargura;
}

void setAlturaArena(arena *a, double novaAltura) {
    a -> altura = novaAltura;
}
int getArenaNumFormas(arena *a) {
    return getTamFila(a -> filaArena);
}

void calcArena(arena *a, forma *f) {

}




