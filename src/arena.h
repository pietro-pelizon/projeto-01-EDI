#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>

#include "chao.h"
#include "fila.h"
#include "formas.h"


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


/// A definição da struct fica no arquivo .c
typedef struct stArena arena;

/// @brief: Cria uma arena com largura e altura.
/// @param largura: Define o limite horizontal da arena.
/// @param altura: Define o limite vertical da arena.
/// @return: Retorna um ponteiro para a arena criada.
arena *criaArena(double largura, double altura);

/// @brief: Adiciona uma forma à arena.
/// @param a: Ponteiro para a arena.
/// @param f: Ponteiro para a forma que será adicionado à arena.
/// @return: Retorna um ponteiro para a forma adicionada.
forma *adicionaFormaArena(arena *a, forma *f);

/// @brief: Remove uma forma da arena.
/// @param a: Ponteiro para a arena.
/// @param f: Ponteiro para o objeto que será removido.
/// @return: Retorna um ponteiro para o objeto removido.
forma *removeFormaArena(arena *a, forma *f);

/// @brief: Libera a arena e todas as formas dentro dela.
/// @param a: Ponteiro para a arena.
void destrutorArena(arena **a);

/// @brief: Pega e retorna a largura atual da arena.
/// @param a: Ponteiro para a arena.
/// @return: Largura da arena.
double getLarguraArena(arena *a);

/// @brief: Pega e retorna a altura atual da arena.
/// @param a: Ponteiro para a arena.
/// @return: Altura da arena.
double getAlturaArena(arena *a);

/// @brief: Define uma nova largura para a arena.
/// @param a: Ponteiro para a arena.
void setLarguraArena(arena *a, double novaLargura);

/// @brief: Define uma nova altura para arena.
/// @param a: Ponteiro para a arena.
void setAlturaArena(arena *a, double novaAltura);

/// @brief: Conta e retorna a quantidade de formas que estão na arena.
/// @param a: Ponteiro para a arena.
/// @return: Quantidade de formas na arena.
int getArenaNumFormas(arena *a);

/// @brief: Faz o cálculos envolvendo a arena e as formas lançadas nelas.
/// @param a: Ponteiro para a arena.
/// @param c: Ponteiro para o chão.
/// @param pontuacao_total: Pontuação total do round (soma da área das formas esmagadas).
/// @param anotacoes_svg: Fila de anotações do SVG.
/// @param arquivo_txt: Ponteiro para o arquivo txt onde os reports acontecerão.
void processaArena(arena *a, chao *c, double *pontuacao_total, fila *anotacoes_svg, FILE *arquivo_txt, int *formas_clonadas, int *formas_esmagadas);

#endif //ARENA_H
