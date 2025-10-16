#ifndef CARREGADORES_H
#define CARREGADORES_H

#include "formas.h"
#include "chao.h"
#include <stdbool.h>

#include "fila.h"


/* ------- CARREGADOR -------
 * Um carregador pode receber como carga qualquer tipo de variável.
 * Primeiro, deve ser criado com a função 'criaCarregador', após isso
 * a função 'loadCarregador' pode ser chamada para carregá-lo com o tipo
 * desejado, 'n' vezes. Funciona sob o sistema LIFO (Last In, First Out).
 */

typedef struct stCarregador carregador;

/* ------- FUNÇÃO CONSTRUTORA ------- */
/// @brief: Função construtora do carregador.
/// @param i: Identificador do carregador
/// @return: Retorna um ponteiro para o carregador.
///
carregador *criaCarregador(int i);

/* ------- FUNÇÕES ADICIONAIS -------*/

/// @brief: Adiciona uma forma ao carregador
/// @param l: Ponteiro para o carregador.
/// @param f: Ponteiro para a forma que será adicionada.
/// @return: A forma que foi inserida no carregador.
forma *adicionaFormaCarregador(carregador *l, forma *f);

/// @brief: Adiciona um dado proveniente do chão ao carregador.
/// @param c: Ponteiro para o carregador.
/// @param c: Dado que será adicionada ao carregador.
/// @return: Forma que foi retirada do chão e inserida ao carregador.
forma *insereDoChaoParaCarregador(carregador *l, chao *c);

/// @brief: Coloca dados da fila, 'n' vezes no carregador desejado.
/// @param c: Ponteiro para o chão de onde as formas serão adicionadas ao carregador.
/// @param alvo: Carregador aonde serão colocados os dados.
/// @param n: Número de vezes que um dado será retirado do chao e inserido no carregador.
/// @return: Uma fila com as formas inseridas no carregador.
fila *loadCarregadorN(chao *c, carregador *alvo, int n);

/// @brief: Checa se o carregador está vazio.
/// @param c: Ponteiro para o carregador.
/// @return: TRUE se estiver vazio.
/// @return: FALSE se não estiver vazio.
bool carregadorEstaVazio(carregador *c);


/// @brief: Remove uma forma do carregador
/// @param c: Ponteiro para o carregador.
/// @return: Forma que foi removida do carregador.
forma *removeDoCarregador(carregador *c);

/// @brief: Destrói o carregador.
/// @param c: Ponteiro para o carregador a ser destruído.
void destrutorCarregador(carregador **c);

/* ------- FUNÇÃO GET: CARREGADOR ------- */

/// @brief: Pega o ID do carregador desejado.
/// @param c: Carregador onde o ID será pego.
/// @return: Retorna o ID do carregador desejado.
int getIDCarregador(carregador *c);

#endif //CARREGADORES_H
