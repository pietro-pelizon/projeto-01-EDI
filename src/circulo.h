#ifndef CIRCULO_H
#define CIRCULO_H



/* ------- TAD CIRCULO -------
 * O círculo é um objeto, que contém os seguintes atributos:
 * Identificador: Permite diferenciar os círculos uns dos outros pelo ID;
 * Âncora: A âncora do círculo fica em seu centro, contém coordenadas (x, y)
 * e faz referência a posição do objeto;
 * raio: O raio do círculo;
 * cor de borda: define a cor de borda pertencente ao círculo;
 * Cor de preenchimento: define a cor de preenchimento pertencente ao círculo;
 */


/// A definição da struct círculo foi movida para o arquivo.c
typedef struct stCirculo circulo;

/* ------- FUNÇÃO CONSTRUTORA: CÍRCULO ------- */

/// @brief: Constrói/define um círculo.
/// @param i: Identificador do círculo.
/// @param x: Coordenada x do centro do círculo.
/// @param y: Coordenada y do centro do círculo.
/// @param r: Raio do círculo.
/// @param corb: Cor da borda do círculo.
/// @param corp: Cor de preenchimento do círculo.
/// @return: Retorna o círculo criado.
circulo *criaCirculo(int i, double x, double y, double r, char *corb, char *corp);

/* ------- MÉTODOS GET: CÍRCULO ------- */

/// @brief: Pega o identificador do círculo.
/// @param c: Ponteiro para o círculo.
/// @return: Retorna o identificador do círculo.
int getIDCirculo(circulo *c);

/// @brief: Pega a coordenada x do centro do círculo.
/// @param c: Ponteiro para o círculo.
/// @return: Retorna a coordenada x do centro do círculo.
double getXCirculo(circulo *c);

/// @brief: Pega a coordenada y do círculo.
/// @param c: Ponteiro para o círculo.
/// @return: Retorna a coordenada y do círculo.
double getYCirculo(circulo *c);

/// @brief: Pega a coordenada y do círculo.
/// @param c: Ponteiro para o círculo.
/// @return: Retorna a coordenada y do círculo.
double getRaioCirculo(circulo *c);

/// @brief: Pega a cor de borda do círculo.
/// @param c: Ponteiro para o círculo.
/// @return: Retorna a cor de borda do círculo.
char *getCorbCirculo(circulo *c);

/// @brief: Pega a cor de preenchimento do círculo.
/// @param c: Ponteiro para o círculo.
/// @return: Retorna a cor de preenchimento do círculo.
char *getCorpCirculo(circulo *c);

/* ------- MÉTODOS SET: CÍRCULO ------- */

/// @brief: Define o novo identificador do círculo.
/// @param c: Ponteiro para o círculo.
/// @param i: Novo identificador do círculo.
void setIDCirculo(circulo *c, int i);

/// @brief: Define o novo valor da coordenada x do centro do círculo.
/// @param c: Ponteiro para o círculo.
/// @param x: Nova coordenada x do centro do círculo.
void setXCirculo(circulo *c, double x);

/// @brief: Define a nova coordenada y do centro do círculo.
/// @param c: Ponteiro para o círculo.
/// @param y: Nova coordenada y do centro do círculo.
void setYCirculo(circulo *c, double y);

/// @brief: Define o novo tamanho do raio do círculo.
/// @param c: Ponteiro para o círculo.
/// @param r: Novo tamanho do raio do círculo.
void setRaioCirculo(circulo *c, double r);

/// @brief: Define a nova cor de borda do círculo.
/// @param c: Ponteiro para o círculo.
/// @param corb: Nova cor de borda do círculo.
void setCorbCirculo(circulo *c, char *corb);

/// @brief: Define a nova cor de preenchimento do círculo.
/// @param c: Ponteiro para o círculo.
/// @param corp: Nova cor de preenchimento do círculo.
void setCorpCirculo(circulo *c, char *corp);

/* ------- MÉTODOS ADICIONAIS: CÍRCULO ------- */

/// @brief: Calcula a área do círculo.
/// @param c: Ponteiro para o círculo.
/// @return: Retorna o tamanho da área do círculo.
double calcAreaCirculo(circulo *c);

/// @brief: Libera o objeto círculo.
/// @param pc: Ponteiro duplo para o círculo a ser liberado
void destrutorCirculo(circulo **pc);

#endif //CIRCULO_H
