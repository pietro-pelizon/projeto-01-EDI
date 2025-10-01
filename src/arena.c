#include "arena.h"
#include "fila.h"
#include "formas.h"
#include "sobreposicao.h"
#include "chao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int getTamArena(arena *a) {
    if (a == NULL) {
        return -1;
    }

    return getTamFila(a -> filaArena);
}


double processaArena(arena *a, double, chao *c, double pontuacao_total) {
    forma *forma_I = removeFormaArena(a);
    forma *forma_J = removeFormaArena(a);

    while (getTamArena(a) >= 2) {
        if (formasSobrepoem(forma_I, forma_J) == true) {
            double area_I = getAreaForma(forma_I);
            double area_J = getAreaForma(forma_J);

            if (area_I < area_J) {
                destrutorForma(forma_I);
                voltaProChao(c, forma_J);
                pontuacao_total += area_I;
            }

            else if (area_I > area_J) {
                trocaCores(forma_I, forma_J);
                forma *clone_I = clonarForma(forma_I);
                alternaCores(clone_I);

                voltaProChao(c, clone_I);
                voltaProChao(c, forma_J);
            }

            else {
                voltaProChao(c, forma_I);
                voltaProChao(c, forma_J);
            }
        }

        else {
            voltaProChao(c, forma_I);
            voltaProChao(c, forma_J);
        }

    }
    if (arenaEstaVazia(a) != true) {
        voltaProChao(c, forma_I);
    }

    return pontuacao_total;
}




