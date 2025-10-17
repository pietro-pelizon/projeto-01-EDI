#ifndef PROCESSAQRY_H
#define PROCESSAQRY_H
#include "chao.h"
#include "disparador.h"
#include "carregadores.h"
#include "arena.h"

#define MAX_OBJETOS 100

typedef struct stRepositorio repositorio;
typedef struct stArena arena;
typedef struct stReportTxt report_txt;


/// @brief: Limpa uma forma específica de todos os disparadores de um repositório
/// @param repo: Ponteiro para o repositório contendo os disparadores.
/// @param forma: Forma a ser removida das posições de disparo
void limpaFormaDeTodosDisparadores(repositorio *repo, forma *forma);

/// @brief: Caso haja formas remanescentes na posição de disparo do disparador, as devolve para o chão.
/// @param repo: Ponteiro para o repositório contendo os disparadores.
/// @param c: Ponteiro para o chão, para onde as formas voltarão.
void devolveFormasDisparadoresParaChao(repositorio *repo, chao *c);

/// @brief: Caso haja formas remanescentes no carregador, as devolve para o chão.
/// @param repo: Ponteiro para o repositório contendo os carregadores.
/// @param c: Ponteiro para o chão, para onde as formas voltarão.
void devolveFormasCarregadoresParaChao(repositorio *repo, chao *c);

/// @brief: Inicializa o repositório que guardará todos os carregadores e disparadores.
/// @return: Um ponteiro para a estrutura do repositório.
repositorio* criarRepositorio();

/// @brief: Destrói o repositório e todos os carregadores e disparadores contidos lá dentro.
/// @param repo: Ponteiro para o repositório.
void destrutorRepositorio(repositorio *repo);

/// @brief: Processa totalmente o arquivo .qry e seus comandos.
/// @param repo: Ponteiro para o repositório de objetos.
/// @param nome_path_qry: Nome do caminho para o arquivo .qry
/// @param nome_txt: Nome do arquivo txt que será aberto para dar log das funções executadas.
/// @param arena: Ponteiro para a arena.
/// @param chao: Ponteiro para o chão.
/// @param pontuacao_total: Pontuação total do jogo.
/// @param filaSVG: Fila de formas que serão desenhadas no arquivo .svg
/// @param formas_clonadas: Número de formas clonadas para report no txt.
/// @param formas_esmagadas: Número de formas esmagadas para report no txt,
void processaQry(repositorio *repo, char *nome_path_qry, const char *nome_txt, arena *arena, chao *chao, double *pontuacao_total,
                 fila *filaSVG, int *formas_clonadas, int *formas_esmagadas);


#endif //PROCESSAQRY_H
