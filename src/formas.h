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
forma *criaForma(int id, tipoForma tipo, void *dados);

/// @brief: Pega e retorna o ID da forma.
/// @param f: Ponteiro para a forma.
/// @return: ID da forma.
int getIDforma(forma *f);

/// @brief: Pega o tipo da forma e o retorna.
/// @param f: Ponteiro para a forma.
/// @return: Tipo da forma.
tipoForma getTipoForma(forma *f);

/// @brief: Pega e retorna os dados da forma.
/// @param f: Ponteiro para a forma.
/// @return: Ponteiro para os dados da forma.
void *getFormaDados(forma *f);

/// @brief: Define um novo identificador para a forma.
/// @param f: Ponteiro para a forma.
/// @param novoID: Novo identificador.
void setIDforma(forma *f, int novoID);

/// @brief: Pega e retorna a cor de borda de uma forma genérica.
/// @param f: Ponteiro para a forma.
/// @return: Cor de borda da forma genérica.
char *getCorbForma(forma *f);

/// @brief: Pega e retorna a cor de preenchimento de uma forma genérica.
/// @param f: Ponteiro para a forma.
/// @return: Cor de preenchimento de uma forma genérica.
char *getCorpForma(forma *f);

/// @brief: Define uma nova cor de preenchimento para uma forma genérica.
/// @param f: Ponteiro para a forma.
/// @param novaCor: Nova cor de preenchimento para a forma genérica.
void setCorpFormas(forma *f, char *novaCor);

/// @brief: Define uma nova cor de borda para uma forma genérica.
/// @param f: Ponteiro para a forma.
/// @param novaCor: Nova cor de borda da forma genérica.
void setCorbFormas(forma *f, char *novaCor);

/// @brief: Clona uma forma, acrescentando 1 ao seu ID.
/// @param f_original: Forma que será clonada;
/// @return: Ponteiro para a forma clonada.
forma *clonarForma(forma *f_original);

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

/// @brief: Faz o cálculo para obter a cor complementar de uma cor em hexadecimal.
/// @param cor_hexa_original: A cor que terá sua cor complementar calculada.
/// @return: Retorna um ponteiro para a cor complementar em hexadecimal.\n Caso seja um formato inválido, retorna o complementar da cor preta.
char *getCorComplementar(char *cor_hexa_original);

/// @brief: Troca a cor de preenchimento de f1 com a cor de borda de f2.
/// @param f1: Ponteiro para a forma 1.
/// @param f2: Ponteiro para a forma 2;
void trocaCores(forma *f1, forma *f2);

/// @brief: Troca a cor de preenchimento da forma com sua cor de borda e vice-versa.
/// @param f: Ponteiro para a forma.
void alternaCores(forma *f);

/// @brief: Dado o tipo da forma, pega seus dados e a desenha em um arquivo svg.
/// @param f: Ponteiro para a forma.
/// @param svg: Ponteiro para o arquivo svg.
void desenhaFormaSvg(forma *f, FILE *svg);

/// @brief: Dado o tipo da forma, pega seus dados e gera um relatório no arquivo txt.
/// @param f: Ponteiro para a forma.
/// @param txt: Arquivo .txt aonde as informações serão escritas.
/// @param reportDaFuncaoQRY: Começo padrão que será adicionado conforme a função do .qry.
void escreveDadosFormaTxt(forma *f, FILE *txt, char *reportDaFuncaoQRY);


#endif //FORMAS_H
