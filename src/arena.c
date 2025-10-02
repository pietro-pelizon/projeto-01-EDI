#include "arena.h"
#include "fila.h"
#include "formas.h"
#include "sobreposicao.h"
#include "chao.h"

#include <stdio.h>
#include <stdlib.h>



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

double processaArena(arena *a, chao *c, double *pontuacao_total) {
    if (c == NULL || a == NULL) {
        printf("Erro na funcao processaArena!\n");
        return -1.0;
    }

    while (getTamArena(a) >= 2) {
        forma *forma_I = removeFormaArena(a);
        forma *forma_J = removeFormaArena(a);

        if (formasSobrepoem(forma_I, forma_J)) {
            double area_I = getAreaForma(forma_I);
            double area_J = getAreaForma(forma_J);

            if (area_I < area_J) {
                *pontuacao_total += area_I;
                destrutorForma(forma_I);
                adicionaNoChao(c, forma_J);
            }

            else if (area_I > area_J) {
                if (getTipoForma(forma_I) == LINHA) {
                    char *corLinha = getCorLinha(getFormaDados(forma_I));
                    char * cor_complementar_linha = getCorComplementar(corLinha);
                    setCorbFormas(forma_J, cor_complementar_linha);

                }

                else {
                    trocaCores(forma_I, forma_J);
                }

                forma *clone_I = clonarForma(forma_I);
                alternaCores(clone_I);

                adicionaNoChao(c, forma_I);
                adicionaNoChao(c, forma_J);
                adicionaNoChao(c, clone_I);

            }

            else {
                adicionaNoChao(c, forma_I);
                adicionaNoChao(c, forma_J);
            }
        }

        else {
            adicionaNoChao(c, forma_I);
            adicionaNoChao(c, forma_J);
        }

    }

    if (arenaEstaVazia(a) == true) {
        adicionaNoChao(c, removeFormaArena(a));
    }

    return *pontuacao_total;
}




