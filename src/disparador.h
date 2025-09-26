#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "carregadores.h"
#include "formas.h"

typedef struct stDisparador disparador;


disparador *criaDisparador();

int getIDDisparador(disparador *d);

/// @brief: Posiciona o disparador 'i' na coordenada '(x,y)'
/// @param i: Identificador do disparador a ser posicionado.
/// @param x: Coordenada x de onde o disparador deve ser posicionado.
/// @param y: Coordenada y de onde o disparador deve ser posicionado.
void posicionaDisparador(int i, double x, double y);

/// @brief: Encaixa no disparador um carregador.
/// @param d: Disparador ao qual o carregador será encaixado.
/// @param c: Carregador que será encaixado (esquerdo ou direito).
/// @param posicao: Define em qual lado o carregador será conectado
/// ao disparador, esquerda ou direita.
void atachDisparador(disparador *d, carregador *c, char posicao);

/// @brief: Coloca a carga que estava no carregador em posição de disparo.
/// Caso já houver uma carga no disparador, a transfere para o topo da carga
/// do outro lado.
/// @param d: Disparador onde a carga será colocada.
/// @param botao: Define o lado de ambos carregador e disparador.
void shitfDisparador(disparador *d, char botao);

/// @brief: Dispara a forma que estava no disparador.
/// @param d: Posição do disparador.
/// @param dx: Distância em coordenada x em que a forma será disparada na arena.
/// @param dy: Distância em coordenada y em que a forma será disparada na arena.
/// @return: Retorna um ponteiro para a forma disparada.
forma *disparaDisparador(disparador *d, double dx, double dy);


/// @brief: Dispara uma rajada de formas na arena, nas posições dx, dy, na forma
/// ((dx + i) * ix) e ((dy + i) * iy).
/// @param d: Disparador que será utilizado.
/// @param botao: Define qual lado do disparador será utilizado.
/// @param dx: Distância em coordenada x em que a forma será disparada.
/// @param dy: Distância em coordenada y em que a forma será disparada.
/// @param ix: Valor a ser acrescentado ao deslocamento dx.
/// @param iy: Valor a ser acrescentado ao deslocamento dy.
/// @return: Retorna um ponteiro para a fila de objetos disparados.
fila *rajadaDisparador(disparador *d, char botao, double dx, double dy, double ix, double iy);

/// @brief: Pega a forma que está em posição de disparo.
/// @param d: Ponteiro para o disparador que contém a forma.
/// @return: Retorna um ponteiro para a forma que está na posição de disparo.
forma *disparadorGetFormaEmDisparo(disparador *d);

/// @brief: Pega a posição do disparador.
/// @param d: Ponteiro para o disparador.
/// @param x: Coordenada x do disparador.
/// @param y: Coordenada y do disparador.
void disparadorGetPosicao(disparador *d, double *x, double *y);

#endif //DISPARADOR_H
