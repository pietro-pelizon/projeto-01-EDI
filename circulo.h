//
// Created by pietr on 20/09/2025.
//

#ifndef CIRCULO_H
#define CIRCULO_H

/// A definição da struct círculo foi movida para o arquivo.c
/// o header só precisa saber que o objeto 'circulo' existe.
typedef struct circulo circulo;

/// @brief: Constrói/define um círculo.
/// @param i: Identificador do círculo.
/// @param x: Coordenada x do centro do círculo.
/// @param y: Coordenada y do centro do círculo.
/// @param raio: Raio do círculo.
/// @param corb: Cor da borda do círculo.
/// @param corp: Cor de preenchimento do círculo.
/// @return: Retorna o círculo criado.
circulo criaCirculo(int i, double x, double y, double raio, char *corb, char *corp);

/* ------- MÉTODOS GET: CÍRCULO ------- */

/// @brief: Pega o identificador do círculo.
/// @return: Retorna o identificador do círculo.
int getIdentCirculo(circulo *c);

/// @brief: Pega a coordenada x do centro do círculo.
/// @return: Retorna a coordenada x do centro do círculo.
double getXCirculo(circulo *c);

/// @brief: Pega a coordenada y do círculo.
/// @return: Retorna a coordenada y do círculo.
double getYCirculo(circulo *c);

/// @brief: Pega a coordenada y do círculo.
/// @return: Retorna a coordenada y do círculo.
double getRaioCirculo(circulo *c);

/// @brief: Pega a cor de borda do círculo.
/// @return: Retorna a cor de borda do círculo.
char getCorbCirculo(circulo *c);

/// @brief: Pega a cor de preenchimento do círculo.
/// @return: Retorna a cor de preenchimento do círculo.
char getCorpCirculo(circulo *c);

/* ------- MÉTODOS SET: CÍRCULO ------- */

/// @brief: Define o novo identificador do círculo.
void setIdentCirculo(circulo *c, int i);

/// @brief: Define o novo valor da coordenada x do centro do círculo.
void setXCirculo(circulo *c, double x);

/// @brief: Define a nova coordenada y do centro do círculo.
void setYCirculo(circulo *c, double y);

/// @brief: Define o novo tamanho do raio do círculo.
void setRaioCirculo(circulo *c, double raio);

/// @brief: Define a nova cor de borda do círculo.
void setCorbCirculo(circulo *c, char *corb);

/// @brief: Define a nova cor de preenchimento do círculo.
void setCorpCirculo(circulo *c, char *corp);

/* ------- MÉTODOS ADICIONAIS: CÍRCULO ------- */

/// @brief: Calcula a área do círculo.
/// @return: Retorna o tamanho da área do círculo.
double calcAreaCirculo(circulo *c, double r);

#endif //CIRCULO_H
