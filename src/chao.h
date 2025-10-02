#ifndef CHAO_H
#define CHAO_H

#include "formas.h"
#include <stdbool.h>


 /* ------- TAD CHAO -------
 * O TAD Chão funciona como um repositório ou "inventário" para as
 * formas criadas, mas ainda não estão em jogo (ou seja,
 * ainda não foram colocadas em um carregador ou disparadas na arena).
 * Seus principais conceitos são:
 *
 * Armazenamento Primário: Serve como o local inicial de armazenamento
 * para todas as formas lidas do arquivo de entrada, antes de serem
 * distribuídas para os carregadores;
 *
 * Fonte de Munição: Atua como a fonte de onde as formas são retiradas
 * ('retiraChao') para serem inseridas nos carregadores dos
 * disparadores;
 *
 * Gerenciamento de Memória: É responsável pelo ciclo de vida das formas
 * que ainda não entraram no jogo. Ao ser destruído, todas as formas
 * restantes no chão também são liberadas da memória.
 */

/// A definição da struct está no arquivo .c
typedef struct stChao chao;

/// @brief: Cria o chão (onde as formas ficam antes
/// de serem carregadas e disparadas na arena)
/// @return: Retorna um ponteiro para o chão criado.
chao *criaChao();

/// @brief: Verifica se o chão está vazio.
/// @param c: Ponteiro para o chão.
/// @return: TRUE se estiver vazio.
/// @return: FALSE se não estiver vazio.
bool chaoEstaVazio(chao *c);

/// @brief: Coloca uma forma no chão.
/// @param c: Ponteiro para o chão.
/// @param f: Ponteiro para a forma que será colocada no chão.
void adicionaNoChao(chao *c, forma *f);

/// @brief: Retira uma forma do chão.
/// @param c: Ponteiro para o chão.
/// @return: Retorna um ponteiro para a forma retirada.
forma *retiraChao(chao *c);

/// @brief: Libera toda a memória do chão.
/// @param c: Ponteiro para o chão a ser liberado.
void destrutorChao(chao *c);

#endif //CHAO_H
