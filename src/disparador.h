#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "carregadores.h"
#include "formas.h"
#include "arena.h"


 /* ------- TAD DISPARADOR -------
 * O disparador é um objeto, que contém os seguintes atributos:
 * Identificador: Permite diferenciar os disparadores uns dos outros pelo ID;
 * Âncora: Define a posição do disparador no cenário, contendo as
 * coordenadas (x, y) de onde os disparos se originam;
 * Carregadores: Contém dois ponteiros para carregadores (esquerdo e direito),
 * que funcionam como fontes de munição (formas) para o disparador;
 * Posição de Disparo: Um espaço que armazena a única forma que está
 * atualmente pronta para ser disparada. Esta posição é preenchida pela
 * função 'shiftDisparador' e esvaziada pela 'disparaDisparador'.
 */

typedef struct stDisparador disparador;

/// @brief: Cria um disparador com os atributos dados pelos parâmetros,
/// e uma posição de disparo.
/// @param i: Identificador do disparador.
/// @param x: Coordenada X inicial do disparador.
/// @param y: Coordenada Y inicial do disparador.
/// @param esq: Carregador esquerdo do disparador.
/// @param dir: Carregador direito do disparador.
/// @return: Retorna um ponteiro para o disparador criado.
/// @return: Retorna NULL caso a criação falhe.
disparador *criaDisparador(int i, double x, double y, carregador *esq, carregador *dir);

/// @brief: Pega o identificador do disparador e o retorna;
/// @param d: Ponteiro para o disparador.
/// @return: Identificador do disparador.
int getIDdisparador(disparador *d);

/// @brief: Posiciona o disparador 'd' na coordenada '(x,y)'
/// @param d: Ponteiro para o disparador.
/// @param x: Coordenada x de onde o disparador deve ser posicionado.
/// @param y: Coordenada y de onde o disparador deve ser posicionado.
void posicionaDisparador(disparador *d, double x, double y);

/// @brief: Encaixa no disparador ambos os carregadores, esquerdo e direito.
/// @param d: Disparador ao qual o carregador será encaixado.
/// @param esq: Carregador esquerdo.
/// @param dir: Carregador direito.
void attachDisparador(disparador *d, carregador *esq, carregador *dir);

/// @brief: Coloca a carga que estava no carregador em posição de disparo.
/// Caso já houver uma carga no disparador, a transfere para o topo da carga
/// do outro lado.
/// @param d: Disparador onde a carga será colocada.
/// @param botao: Define qual lado do disparador será apertado.
/// @param n: Número de vezes em que o botão será apertado.
/// @return: Retorna um ponteiro para a forma que ficou no ponto de disparo.
/// Caso o usuário tenha apertado o botão a ponto de acabar com todas as formas
/// que estão no carregador selecionado, retorna NULL;
forma *shiftDisparador(disparador *d, char botao, int n);

/// @brief: Dispara a forma que estava no disparador.
/// @param d: Posição do disparador.
/// @param dx: Distância em coordenada x em que a forma será disparada na arena.
/// @param dy: Distância em coordenada y em que a forma será disparada na arena.
/// @return: Retorna um ponteiro para a forma disparada.
forma *disparaDisparador(disparador *d, double dx, double dy);

/// @brief: Dispara uma rajada de formas na arena, nas posições dx, dy, na forma
/// ((dx + (i * ix))) e ((dy + (i * iy))).
/// @param d: Disparador que será utilizado.
/// @param botao: Define qual lado do disparador será utilizado.
/// @param dx: Distância em coordenada x em que a forma será disparada.
/// @param dy: Distância em coordenada y em que a forma será disparada.
/// @param ix: Valor a ser multiplicado com o iterador e acrescentado ao deslocamento dx.
/// @param iy: Valor a ser multiplicado com o iterador e acrescentado ao deslocamento dy.
/// @param a: Arena aonde as formas serão disparadas.
void rajadaDisparador(disparador *d, char botao, double dx, double dy, double ix, double iy, arena *a);

/// @brief: Pega a forma que está em posição de disparo.
/// @param d: Ponteiro para o disparador que contém a forma.
/// @return: Retorna um ponteiro para a forma que está na posição de disparo.
forma *getFormaEmDisparo(disparador *d);

/// @brief: Pega a coordenada x da posição do disparador.
/// @param d: Ponteiro para o disparador.
/// @return: Retorna a coordenada x da posição do disparador.
double getXdisparador(disparador *d);

/// @brief: Pega a coordenada y da posição do disparador.
/// @param d: Ponteiro para o disparador.
/// @return: Retorna a coordenada y da posição do disparador.
double getYdisparador(disparador *d);

#endif //DISPARADOR_H
