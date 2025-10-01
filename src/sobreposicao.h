#ifndef SOBREPOSICAO_H
#define SOBREPOSICAO_H

#include <stdbool.h>

#include "formas.h"
#include "linha.h"
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"

/* ------- TAD SOBREPOSIÇÃO -------
 * Basicamente, o TAD apresentado contém funções
 * que verificam se existe sobreposição entre
 * variados tipos de formas (Círculo, retângulo,
 * texto, linha).
 *
 * Contém uma função mestre que obtém os tipos
 * das formas apresentadas nos parâmetros e
 * decide qual função especialista irá delegar
 * para tal verificação.
 *
 * Como essas verificações são feitas, é trivial.
 */


/* ------- FUNÇÃO MESTRE ------- */

/// @brief: Checa se duas formas genéricas se sobrepõem num plano. Função mestre que chama as outras funções especialistas.
/// @param f1: Ponteiro para a primeira forma genérica.
/// @param f2: Ponteiro para a segunda forma genérica.
/// @return: true se há sobreposição, false caso contrário.
bool formasSobrepoem(forma *f1, forma *f2);


/* ------- FUNÇÕES ESPECIALISTAS ------- */

/// @brief: Checa se dois círculos se sobrepõem.
/// @param c1: Ponteiro void para o primeiro objeto círculo.
/// @param c2: Ponteiro void para o segundo objeto círculo.
/// @return: true se há sobreposição, false caso contrário.
bool sobrepoe_circulo_circulo(circulo *c1, circulo *c2);

/// @brief: Checa se um círculo e um retângulo se sobrepõem.
/// @param c1: Ponteiro para o objeto círculo.
/// @param r: Ponteiro para o objeto retângulo.
/// @return: true se há sobreposição, false caso contrário.
bool sobrepoe_circulo_retangulo(circulo *c1, retangulo *r);

/// @brief: Checa se um círculo e um segmento de reta se sobrepõem. Usado para linha e texto.
/// @param c: Ponteiro para o objeto círculo.
/// @param l: Ponteiro para o objeto linha (pode ser uma linha real ou uma temporária convertida de um texto).
/// @return: true se há sobreposição, false caso contrário.
bool sobrepoe_circulo_linhaOUtexto(circulo *c, linha *l);

/// @brief: Checa se dois retângulos alinhados aos eixos se sobrepõem.
/// @param r1: Ponteiro para o primeiro objeto retângulo.
/// @param r2: Ponteiro para o segundo objeto retângulo.
/// @return: true se há sobreposição, false caso contrário.
bool sobrepoe_retangulo_retangulo(retangulo *r1, retangulo *r2);

/// @brief: Checa se dois segmentos de reta se sobrepõem (interceptam).
/// @param l1: Ponteiro para o primeiro objeto linha.
/// @param l2: Ponteiro para o segundo objeto linha.
/// @return: true se há sobreposição, false caso contrário.
bool sobrepoe_linha_linha(linha *l1, linha *l2);

/// @brief: Checa a sobreposição entre uma linha e um texto, convertendo o texto para uma linha temporária.
/// @param l: Ponteiro para o objeto linha.
/// @param t: Ponteiro para o objeto texto.
/// @return: true se há sobreposição, false caso contrário.
bool sobrepoe_linha_texto(linha *l, texto *t);

/// @brief: Checa a sobreposição entre um retângulo e um segmento de reta.
/// @param r: Ponteiro para o objeto retângulo.
/// @param l: Ponteiro para o objeto linha.
/// @return: true se há sobreposição, false caso contrário.
bool sobrepoe_retangulo_linha(retangulo *r, linha *l);


/* ------- FUNÇÕES ADICIONAIS PARA A VERIFICAÇÃO DE SOBREPOSIÇÃO --------*/

/// @brief: Converte um objeto texto em um segmento de reta, preenchendo um objeto linha existente.
/// @param t: Ponteiro para o objeto texto de origem.
/// @param l_out: Ponteiro para o objeto linha de destino que será preenchido com as coordenadas.
void converter_texto_para_linha(texto *t, linha *l_out);

/// @brief: Calcula o quadrado da distância euclidiana entre dois pontos (x1, y1) e (x2, y2).
/// @param x1: Coordenada X do primeiro ponto.
/// @param y1: Coordenada Y do primeiro ponto.
/// @param x2: Coordenada X do segundo ponto.
/// @param y2: Coordenada Y do segundo ponto.
/// @return: O valor da distância ao quadrado.
double distancia_quadrada(double x1, double y1, double x2, double y2);

/// @brief: Verifica se um ponto (px, py) está contido dentro dos limites de um retângulo.
/// @param r: Ponteiro para o objeto retângulo.
/// @param px: Coordenada X do ponto a ser verificado.
/// @param py: Coordenada Y do ponto a ser verificado.
/// @return: true se o ponto está dentro, false caso contrário.
bool ponto_dentro_retangulo(retangulo *r, double px, double py);

/// @brief: Determina a orientação de um trio ordenado de pontos (p, q, r).
/// @param px: Coordenada X do primeiro ponto.
/// @param py: Coordenada Y do primeiro ponto.
/// @param qx: Coordenada X do segundo ponto.
/// @param qy: Coordenada Y do segundo ponto.
/// @param rx: Coordenada X do terceiro ponto.
/// @param ry: Coordenada Y do terceiro ponto.
/// @return: 0 para colinear, 1 para horário, 2 para anti-horário.
int orientacao(double px, double py, double qx, double qy, double rx, double ry);

/// @brief: Verifica se um ponto q está no segmento de reta pr, assumindo que os três são colineares.
/// @param px: Coordenada X do ponto p (extremidade do segmento).
/// @param py: Coordenada Y do ponto p.
/// @param qx: Coordenada X do ponto q (ponto a ser verificado).
/// @param qy: Coordenada Y do ponto q.
/// @param rx: Coordenada X do ponto r (outra extremidade do segmento).
/// @param ry: Coordenada y do ponto r.
/// @return: true se o ponto q está no segmento pr, false caso contrário.
bool pontoEstaNoSegmento(double px, double py, double qx, double qy, double rx, double ry);

#endif // SOBREPOSICAO_H

