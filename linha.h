#ifndef LINHA_H
#define LINHA_H

typedef struct linha linha;

/* ------ FUNÇÃO CONSTRUTORA: LINHA ------- */

/// @brief: Constrói uma linha com os atributos dados pelos parâmetros.
/// @param i: Identificador da linha.
/// @param x1: Coordenada x do primeiro ponto.
/// @param y1: Coordenada y do primeiro ponto.
/// @param x2: Coordenada x do segundo ponto.
/// @param y2: Coordenada y do segundo ponto.
/// @param cor: Cor da linha.
/// @return: Retorna um ponteiro para a linha.
linha criaLinha(int i, double x1, double y1, double x2, double y2, char *cor);

/* ------- MÉTODOS GET: LINHA ------- */

/// @brief: Pega o identificador da linha.
/// @param l: Ponteiro para a linha;
/// @return: Retorna o identificador da linha.
int getIDLinha(linha *l);

/// @brief: Pega a coordenada x do primeiro ponto da linha.
/// @param l: Ponteiro para a linha;
/// @return: Retorna a coordenada x1 do primeiro ponto da linha.
double getX1Linha(linha *l);

/// @brief: Pega a coordenada y do primeiro ponto da linha.
/// @param l: Ponteiro para a linha;
/// @return: Retorna a coordenada y1 do primeiro ponto da linha.
double getY1Linha(linha *l);

/// @brief: Pega a coordenada x do segundo ponto da linha.
/// @param l: Ponteiro para a linha;
/// @return: Retorna a coordenada x2 do segundo ponto da linha.
double getX2Linha(linha *l);

/// @brief: Pega a coordenada y do segundo da linha.
/// @param l: Ponteiro para a linha.
/// @return: Retorna a coordenada y2 da linha.
double getY2Linha(linha *l);

/// @brief: Pega a cor da linha.
/// @param l: Ponteiro para a linha;
/// @return: Retorna a cor da linha.
char *getCorLinha(linha *l);

/* ------- MÉTODOS SET: LINHA ------- */

/// @brief: Define um novo identificador para a linha.
/// @param l: Ponteiro para a linha.
/// @param i: Novo identificador da linha.
void setIDLinha(linha *l, int i);

/// @brief: Define uma nova coordenada x do primeiro ponto para a linha.
/// @param l: Ponteiro para a linha.
/// @param x1: Nova coordenada x do primeiro ponto da linha.
void setX1Linha(linha *l, double x1);

/// @brief: Define uma nova coordenada y do primeiro ponto para a linha.
/// @param l: Ponteiro para a linha.
/// @param y1: Nova coordenada y do primeiro ponto da linha.
void setY1Linha(linha *l, double y1);

/// @brief: Define uma nova coordenada x do segundo ponto para a linha.
/// @param l: Ponteiro para a linha.
/// @param x2: Nova coordenada x do segundo ponto da linha.
void setX2Linha(linha *l, double x2);

/// @brief: Define uma nova coordenada y do segundo ponto para a linha.
/// @param l: Ponteiro para a linha.
/// @param y2: Nova coordenada x do segundo ponto da linha.
void setY2Linha(linha *l, double y2);

/// @brief: Define uma nova cor para a linha.
/// @param l: Ponteiro para a linha.
/// @param cor: Nova cor da linha.
void setCorLinha(linha *l, char *cor);

/* ------- MÉTODOS ADICIONAIS: LINHA ------- */

/// @brief: Calcula o comprimento da linha.
/// @param l: Ponteiro para a linha.
/// @return: Retorna o comprimento da linha.
double calcComprimentoLinha(linha *l);

/// @brief: Calcula a área da linha.
/// @param l: Ponteiro para a linha.
/// @return: Retorna a área calculada da linha
double calcAreaLinha(linha *l);

/// @brief: Libera a linha.
/// @param pl: Ponteiro duplo para a linha a ser liberada.
void destrutorLinha(linha **pl);

#endif //LINHA_H
