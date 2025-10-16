#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>

#include "chao.h"
#include "fila.h"
#include "formas.h"
#include "processaQry.h"



 /* ------- TAD ARENA -------
 * O TAD Arena representa o "mundo" ou "cenário" principal do programa,
 * funcionando como um container para todas as formas ativas. Seus
 * principais conceitos são:
 *
 * Limites Definidos: A arena é criada com uma largura e altura
 * específicas, que definem a área visível do cenário.
 *
 * Armazenamento FIFO (Fila): As formas são armazenadas em uma estrutura
 * de Fila (Primeiro que Entra, Primeiro que Sai). Isso garante que, ao
 * desenhar, as formas mais antigas sejam renderizadas por baixo das mais
 * novas, criando um efeito de profundidade correto;
 *
 * Gerenciamento de Memória: A arena é responsável pelo ciclo de vida das
 * formas que armazena. Ao ser destruída, todas as formas contidas nela
 * também são liberadas da memória.
 */


typedef struct stArena arena;
typedef struct stRepositorio repositorio;

/// @brief: Cria uma arena.
/// @return: Retorna um ponteiro para a arena criada.
arena *criaArena();

/// @brief: Adiciona uma forma à arena.
/// @param a: Ponteiro para a arena.
/// @param f: Ponteiro para a forma que será adicionado à arena.
/// @return: Retorna um ponteiro para a forma adicionada.
forma *adicionaFormaArena(arena *a, forma *f);

/// @brief: Remove uma forma da arena.
/// @param a: Ponteiro para a arena.
/// @return: Retorna um ponteiro para o objeto removido.
forma *removeFormaArena(arena *a);

/// @brief: Destrói a arena.
/// @param a: Ponteiro para a arena.
void destrutorArena(arena **a);

/// @brief: Conta e retorna a quantidade de formas que estão na arena.
/// @param a: Ponteiro para a arena.
/// @return: Quantidade de formas na arena.
int getArenaNumFormas(arena *a);

/// @brief: Processa a considerando as 2 primeiras formas arremessadas e assim sucessivamente.
/// @param a: Ponteiro para a arena.
/// @param c: Ponteiro para o chão.
/// @param pontuacao_total: Área das formas esmagadas.
/// @param anotacoes_svg: Fila de anotações do .svg (para depois printar as formas no arquivo .svg).
/// @param arquivo_txt: Ponteiro para o arquivo .txt para reportar se houve ou não sobreposição.
/// @param formas_clonadas: Número de formas clonadas no processo.
/// @param formas_destruidas: Número de formas destruídas no processo.
/// @param repo: Ponteiro para o repositório de carregadores e disparadores.
void processaArena(arena *a, chao *c, double *pontuacao_total, fila *anotacoes_svg, FILE *arquivo_txt, int *formas_clonadas, int *formas_destruidas, repositorio *repo);

#endif //ARENA_H
