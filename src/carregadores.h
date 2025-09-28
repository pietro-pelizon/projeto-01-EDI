#ifndef CARREGADORES_H
#define CARREGADORES_H

#include "pilha.h"
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

/// @brief: Coloca dados da fila, 'n' vezes no carregador desejado.
/// @param chao: Fila de onde os dados que serão adicionados ao carregador virão.
/// @param alvo: Carregador aonde serão colocados os dados.
/// @param n: Número de vezes que um dado será retirado do chao e inserido no carregador.
/// @return: Retorna a quantidade de formas acrescentadas ao carregador. Se 'n' for negativo, encerra a função.
int loadCarregador(fila *chao, carregador *alvo, int n);

/* ------- FUNÇÃO GET: CARREGADOR ------- */

/// @brief: Pega o ID do carregador desejado.
/// @param alvo: Carregador onde o ID será pego.
/// @return: Retorna o ID do carregador desejado.
int getIDCarregador(carregador *alvo);


#endif //CARREGADORES_H
