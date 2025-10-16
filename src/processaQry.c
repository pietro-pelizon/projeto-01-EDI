#include "processaQry.h"
#include "carregadores.h"
#include "disparador.h"
#include "arena.h"
#include "formas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"

#define MAX_OBJETOS 100

typedef struct stRepositorio {
    carregador *c[MAX_OBJETOS];
    int num_carregadores;
    disparador *d[MAX_OBJETOS];
    int num_disparadores;
}repositorio;

typedef struct stReportTxt {
    FILE* arquivo_txt;
    char* mensagem_relatorio;
} report_txt;

static void acao_escrever_dados_forma(void* item, void* aux_data) {
    forma* f = (forma*)item;
    report_txt *info = (report_txt*)aux_data;

    escreveDadosFormaTxt(f, info -> arquivo_txt, info -> mensagem_relatorio);
}

repositorio* criarRepositorio() {
    repositorio *repo = malloc(sizeof(repositorio));
    if (repo == NULL) {
        printf("Erro ao alocar memoria para o repositorio de objetos!\n");
        return NULL;
    }

    repo -> num_carregadores = 0;
    repo -> num_disparadores = 0;

    return repo;

}

void destrutorRepositorio(repositorio* repo) {
    if (repo == NULL) return;

    for (int i = 0; i < repo->num_carregadores; i++) {
        destrutorCarregador(&repo -> c[i]);
    }
    for (int i = 0; i < repo->num_disparadores; i++) {
        destrutorDisparador(&repo -> d[i]);
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

static void acao_reportar_forma(void* item, void* aux_data) {
    forma* f = (forma*)item;
    FILE* arquivo_txt = (FILE*)aux_data;

    escreveDadosFormaTxt(f, arquivo_txt, NULL);
}


void devolveFormasCarregadoresParaChao(repositorio *repo, chao *c) {
    printf("DEBUG: Devolvendo formas de %d carregadores\n", repo->num_carregadores);

    for (int i = 0; i < repo->num_carregadores; i++) {
        carregador *car = repo->c[i];
        printf("DEBUG: Processando carregador %d\n", getIDCarregador(car));

        while (!carregadorEstaVazio(car)) {
            forma *f = removeDoCarregador(car);
            if (f != NULL) {
                printf("DEBUG: Devolvendo forma ID=%d do carregador %d ao chão\n",
                       getIDforma(f), getIDCarregador(car));
                adicionaNoChao(c, f);
            }
        }
    }
}

void devolveFormasDisparadoresParaChao(repositorio *repo, chao *c) {
    for (int i = 0; i < repo->num_disparadores; i++) {
        disparador *d = repo->d[i];
        forma *f = getFormaEmDisparo(d);

        if (f != NULL) {
            printf("DEBUG: Devolvendo forma ID=%d do disparador %d (em posição de disparo) ao chão\n",
                   getIDforma(f), getIDdisparador(d));
            adicionaNoChao(c, f);
            limpaFormaDoDisparador(d, f);
        }
    }
}

void limpaFormaDeTodosDisparadores(repositorio *repo, forma *f) {
    if (repo == NULL || f == NULL) {
        return;
    }

    printf("DEBUG LIMPA: Limpando forma ID=%d de todos os disparadores\n", getIDforma(f));

    for (int i = 0; i < repo -> num_disparadores; i++) {
        limpaFormaDoDisparador(repo -> d[i], f);
    }
}


void processaQry(repositorio *repo, char *nome_path_qry, const char *nome_txt, arena *arena, chao *chao, double *pontuacao_total,
    fila *filaSVG, int *formas_clonadas, int *formas_esmagadas) {
    FILE *arquivo_qry = fopen(nome_path_qry, "r");
    if (!arquivo_qry) {
        printf("Erro ao abrir o arquivo qry!\n");
        return;
    }

    FILE *arquivo_txt = fopen(nome_txt, "w");
    if (!arquivo_txt) {
        printf("Erro ao abrir o arquivo txt!\n");
        fclose(arquivo_qry);
        return;
    }

    int instrucoes_realizadas = 0;
    int total_disparos = 0;
    *formas_esmagadas = 0;
    *formas_clonadas = 0;
    *pontuacao_total = 0.0;

    char linha_buffer[512];
    char comando[16];
    comando[0] = '\0';

    int linha_numero = 0;
    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo_qry) != NULL) {
        linha_numero++;
        sscanf(linha_buffer, "%s", comando);
        fprintf(arquivo_txt, "[*] %s", linha_buffer);

        if (strcmp(comando, "pd") == 0) {
            int id; double x, y;
            sscanf(linha_buffer, "pd %i %lf %lf", &id, &x, &y);
            disparador *d = encontraOUCriarDisparador(repo, id);
            if (d) {
                posicionaDisparador(d, x, y);
                instrucoes_realizadas++;
            }
        }

        else if (strcmp(comando, "lc") == 0) {
            int id, n;
            sscanf(linha_buffer, "lc %i %i", &id, &n);
            carregador *c = encontrarOuCriarCarregador(repo, id);
            if (c) {
                instrucoes_realizadas++;
                fila *formas_carregadas = loadCarregadorN(chao, c, n);

                if (formas_carregadas != NULL) {
                    report_txt info_report;
                    info_report.arquivo_txt = arquivo_txt;
                    info_report.mensagem_relatorio = "";
                    passthroughQueue(formas_carregadas, acao_escrever_dados_forma, &info_report);
                    liberaFila(formas_carregadas, NULL);
                }
            }
        }
        else if (strcmp(comando, "atch") == 0) {
            int id1, id2, id3;
            sscanf(linha_buffer, "atch %i %i %i", &id1, &id2, &id3);
            disparador *d = encontraOUCriarDisparador(repo, id1);
            carregador *c1 = encontrarOuCriarCarregador(repo, id2);
            carregador *c2 = encontrarOuCriarCarregador(repo, id3);

            if (d && c1 && c2) {
                attachDisparador(d, c1, c2);
                instrucoes_realizadas++;
            }
        }
        else if (strcmp(comando, "shft") == 0) {
            int id, n; char botao;
            sscanf(linha_buffer, "shft %i %c %i", &id, &botao, &n);
            disparador *d = encontraOUCriarDisparador(repo, id);
            if (d) {
                instrucoes_realizadas++;
                shiftDisparador(d, botao, n);
                forma *forma_final = getFormaEmDisparo(d);

                if (forma_final) {
                    escreveDadosFormaTxt(forma_final, arquivo_txt, NULL);
                } else {
                    fprintf(arquivo_txt, "Nenhuma forma na posição de disparo!\n");
                }
            }
        }

        else if (strcmp(comando, "dsp") == 0) {
            int id; double dx, dy;
            char flag_visual[4] = "";

            int campos_lidos = sscanf(linha_buffer, "dsp %d %lf %lf %3s", &id, &dx, &dy, flag_visual);

            printf("DEBUG DSP: Comando dsp - campos_lidos=%d, flag_visual='%s'\n", campos_lidos, flag_visual);

            disparador* d = encontraOUCriarDisparador(repo, id);

            if (d) {
                instrucoes_realizadas++;
                double x_inicial_disparador = getXdisparador(d);
                double y_inicial_disparador = getYdisparador(d);
                forma* forma_disparada = disparaDisparador(d, dx, dy);

                if (forma_disparada) {
                    total_disparos++;
                    adicionaFormaArena(arena, forma_disparada);

                    double x_final = getXForma(forma_disparada);
                    double y_final = getYForma(forma_disparada);

                    escreveDadosFormaTxt(forma_disparada, arquivo_txt, NULL);

                    if (campos_lidos == 4 && strcmp(flag_visual, "v") == 0) {
                        printf("DEBUG DSP: Criando anotações visuais para disparo\n");

                        double tam_caixa = 20.0;
                        retangulo* caixa_id = criaRetangulo(-1,
                            x_inicial_disparador - (tam_caixa / 2.0),
                            y_inicial_disparador + (tam_caixa / 2.0),
                            tam_caixa, tam_caixa, "red", "none");
                        enqueue(filaSVG, criaForma(-1, RETANGULO, caixa_id));

                        char id_str[16];
                        sprintf(id_str, "%d", id);
                        estilo *estilo_marcador = criaEstilo("sans-serif", "bold", "12px");
                        texto* texto_id = criaTexto(-1, x_inicial_disparador, y_inicial_disparador,
                            "red", "red", 'm', id_str, estilo_marcador);
                        destroiEstilo(estilo_marcador);
                        enqueue(filaSVG, criaForma(-1, TEXTO, texto_id));

                        linha* proj_y = criaLinha(-1, x_final, y_inicial_disparador,
                            x_final, y_final, "#FF0000", true);
                        enqueue(filaSVG, criaForma(-1, LINHA, proj_y));

                        linha* proj_x = criaLinha(-1, x_inicial_disparador, y_final,
                            x_final, y_final, "#FF0000", true);
                        enqueue(filaSVG, criaForma(-1, LINHA, proj_x));

                        printf("DEBUG DSP: Anotações visuais criadas com sucesso\n");
                    }
                } else {
                    fprintf(arquivo_txt, "-> Falha no disparo: Nenhuma forma na posição de disparo.\n");
                }
            }
        }


        else if (strcmp(comando, "rjd") == 0) {
            int id; char botao; double dx, dy, ix, iy;
            sscanf(linha_buffer, "rjd %i %c %lf %lf %lf %lf", &id, &botao, &dx, &dy, &ix, &iy);
            disparador *d = encontraOUCriarDisparador(repo, id);

            if (d) {
                instrucoes_realizadas++;
                fila *formas_disparadas = rajadaDisparador(d, botao, dx, dy, ix, iy, arena);

                if (formas_disparadas != NULL) {
                    int tamFilaDisparos = getTamFila(formas_disparadas);
                    total_disparos += tamFilaDisparos;
                    passthroughQueue(formas_disparadas, acao_reportar_forma, arquivo_txt);
                    liberaFila(formas_disparadas, NULL);
                }
            }
        }
        else if (strcmp(comando, "calc") == 0) {
            instrucoes_realizadas++;

            printf("\n--- DEBUG PRÉ-CALC ---\n");
            printf("Pontuação antes do calc: %lf\n", *pontuacao_total);
            printf("Formas na arena ANTES de processar: %d\n", getArenaNumFormas(arena));
            printf("----------------------\n\n");

            processaArena(arena, chao, pontuacao_total, filaSVG, arquivo_txt, formas_clonadas, formas_esmagadas, repo);
        }
    }

    printf("=== RELATÓRIO FINAL ===\n");
    printf("Pontuação total: %lf\n", *pontuacao_total);
    printf("Instruções realizadas: %i\n", instrucoes_realizadas);
    printf("Total de disparos: %i\n", total_disparos);
    printf("Formas esmagadas: %i\n", *formas_esmagadas);
    printf("Formas clonadas: %i\n", *formas_clonadas);

    fprintf(arquivo_txt, "\n ----- RELATÓRIO FINAL ----- \n");
    fprintf(arquivo_txt, "Pontuação total: %lf\n", *pontuacao_total);
    fprintf(arquivo_txt, "Número de instruções realizadas: %i\n", instrucoes_realizadas);
    fprintf(arquivo_txt, "Número total de disparos: %i\n", total_disparos);
    fprintf(arquivo_txt, "Número de formas esmagadas: %i\n", *formas_esmagadas);
    fprintf(arquivo_txt, "Número de formas clonadas: %i\n", *formas_clonadas);

    fclose(arquivo_qry);
    fclose(arquivo_txt);
}


