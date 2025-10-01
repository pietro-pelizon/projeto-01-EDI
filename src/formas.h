#ifndef FORMAS_H
#define FORMAS_H

/*
 * ------- TAD FORMAS -------
 * O TAD Formas provê uma interface genérica para manipular diferentes
 * tipos de objetos geométricos (círculos, retângulos, etc.) de forma
 * uniforme. A 'forma' genérica funciona como um container com os
 * seguintes conceitos:
 *
 * Forma Genérica: Um 'invólucro' (wrapper) que representa qualquer objeto
 * geométrico do programa. Não armazena dados de geometria diretamente, mas
 * aponta para eles;
 *
 * Identificador de Tipo (enum): Uma 'etiqueta' (tag) que identifica qual o
 * tipo real da forma armazenada, permitindo que
 * operações específicas sejam aplicadas corretamente;
 *
 * Ponteiro de Dados (void*): Um ponteiro genérico que aponta para a estrutura
 * de dados real e específica da forma, onde os atributos são de fato
 * armazenados.
 */

/// Identificador de tipo para as formas.
typedef enum EnumtipoForma {
    CIRCULO,
    RETANGULO,
    LINHA,
    TEXTO
} tipoForma;

/// A definição da struct está no arquivo.c
typedef struct stForma forma;

/// @brief: Cria uma fórmula genérica.
/// @param tipo: Tipo da forma.
/// @param dados: Ponteiro para os dados da forma.
/// @return: Retorna um ponteiro para a forma criada.
forma *criaForma(tipoForma tipo, void *dados);

/// @brief: Pega o tipo da forma e o retorna.
/// @param f: Ponteiro para a forma.
/// @return: Tipo da forma.
tipoForma getTipoForma(forma *f);

/// @brief: Pega e retorna os dados da forma.
/// @param f: Ponteiro para a forma.
/// @return: Ponteiro para os dados da forma.
void *getFormaDados(forma *f);

/// @brief: Calcula a área da forma.
/// @param f: Ponteiro a forma.
/// @return: Retorna a área já calculada da área.
double getAreaForma(forma *f);

/// @brief: Libera toda a forma e a destrói.
/// @param f: Ponteiro para a forma.
void destrutorForma(forma *f);

/// @brief: Define a posição de uma forma genérica.
/// @param f: Ponteiro para a forma genérica.
/// @param x: Nova coordenada X.
/// @param y: Nova coordenada Y.
void setPosicaoForma(forma *f, double x, double y);



#endif //FORMAS_H
