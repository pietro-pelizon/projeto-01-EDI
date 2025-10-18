#include "arena.h"
#include "fila.h"
#include "formas.h"
#include "sobreposicao.h"
#include "chao.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct stArena {
    fila *filaArena;
}arena;

arena *criaArena() {
    arena *a = (arena*) malloc (sizeof(arena));
    if (a == NULL) {
        printf("Erro ao criar a arena!\n");
        return NULL;
    }

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

    return estaVaziaFila(a -> filaArena);
}

void destrutorArena(arena **a_ptr) {
    if (a_ptr == NULL || *a_ptr == NULL) {
        return;
    }
    arena* a = *a_ptr;

    liberaFila(a -> filaArena, NULL);

    free(a);
    *a_ptr = NULL;
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

void processaArena(arena *a, chao *c, double *pontuacao_total, fila *anotacoes_svg,
                   FILE *arquivo_txt, int *formas_clonadas, int *formas_esmagadas, repositorio *repo) {
    if (c == NULL || a == NULL || arquivo_txt == NULL) {
        printf("Erro: Parâmetros nulos passados para processaArena!\n");
        return;
    }

    *pontuacao_total = 0.0;
    double area_esmagada_round = 0.0;

    if (formas_clonadas != NULL) *formas_clonadas = 0;
    if (formas_esmagadas != NULL) *formas_esmagadas = 0;

        printf("\n=== INICIANDO PROCESSAMENTO DA ARENA ===\n");
    while (getTamArena(a) >= 2) {
        forma *forma_I = removeFormaArena(a);
        forma *forma_J = removeFormaArena(a);

        if (formasSobrepoem(forma_I, forma_J)) {

            printf("\nSobreposição detectada!\n");

            double area_I = getAreaForma(forma_I);
            double area_J = getAreaForma(forma_J);

            fprintf(arquivo_txt, "Forma %d (I) vs Forma %d (J). HOUVE SOBREPOSIÇÃO.\n",
                    getIDforma(forma_I), getIDforma(forma_J));

            if (area_I < area_J) {
                printf("=== I < J ===\n ID = %d (I) (área %.2f) foi esmagada por ID = %d (J) (área %.2f).\n",
                        getIDforma(forma_I), area_I, getIDforma(forma_J), area_J);
                fprintf(arquivo_txt, "<<<-- I < J -->>> forma %d (I) (área %.2f) foi esmagada por forma %d (J) (área %.2f).\n",
                        getIDforma(forma_I), area_I, getIDforma(forma_J), area_J);

                if (repo != NULL) {
                    limpaFormaDeTodosDisparadores(repo, forma_I);
                }

                double x_esmagada = getXForma(forma_I);
                double y_esmagada = getYForma(forma_I);

                estilo *estilo_asterisco = criaEstilo("sans-serif", "bold", "30px");
                texto* asterisco = criaTexto(-1, x_esmagada, y_esmagada, "red", "black", 'm', "*", estilo_asterisco);
                destroiEstilo(estilo_asterisco);
                enqueue(anotacoes_svg, criaForma(-1, TEXTO, asterisco));

                *pontuacao_total += area_I;
                area_esmagada_round += area_I;
                if (formas_esmagadas != NULL) (*formas_esmagadas)++;

                destrutorForma(forma_I);
                adicionaNoChao(c, forma_J);
            }
            else if (area_I >= area_J) {
                printf("=== I >= J ===\n ID = %d (I) (área %.2f) modificou a ID = %d (J) (área %.2f).\n\n",
                    getIDforma(forma_I), area_I, getIDforma(forma_J), area_J);
                fprintf(arquivo_txt, "<<<-- I >= J -->>>\n forma %d (I) (área %.2f) modificou a forma %d (J) (área %.2f).\n\n",
                        getIDforma(forma_I), area_I, getIDforma(forma_J), area_J);

                forma *clone_I = NULL;

                if (getTipoForma(forma_I) == LINHA) {
                    char *corLinha = getCorLinha(getFormaDados(forma_I));
                    char *cor_complementar_linha = getCorComplementar(corLinha);

                    setCorbFormas(forma_J, cor_complementar_linha);

                    clone_I = clonarForma(forma_I);

                    void *dados_clone = getFormaDados(clone_I);
                    if (dados_clone != NULL) {
                        setCorLinha((linha*)dados_clone, cor_complementar_linha);
                    }

                    free(corLinha);
                    free(cor_complementar_linha);
                } else {
                    setCorbFormas(forma_J, getCorpForma(forma_I));
                    clone_I = clonarForma(forma_I);
                    alterna_cores_forma(clone_I);
                }

                if (formas_clonadas != NULL) (*formas_clonadas)++;

                adicionaNoChao(c, forma_I);
                adicionaNoChao(c, forma_J);
                if (clone_I != NULL) {
                    adicionaNoChao(c, clone_I);
                }
            }
        }
        else {
            fprintf(arquivo_txt, "Forma %d (I) vs Forma %d (J). NÃO HOUVE SOBREPOSIÇÃO.\n",
                    getIDforma(forma_I), getIDforma(forma_J));
            adicionaNoChao(c, forma_I);
            adicionaNoChao(c, forma_J);
        }
    }

    if (!arenaEstaVazia(a)) {
        adicionaNoChao(c, removeFormaArena(a));
    }

    fprintf(arquivo_txt, "Área total esmagada no round: %.2f\n", area_esmagada_round);
}

