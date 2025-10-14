#ifndef RETANGULO_H
#define RETANGULO_H


 /* ------- TAD RETANGULO -------
 * O Retângulo é um objeto, que contém os seguintes atributos:
 * Identificador: Permite diferenciar os retângulos uns dos outros pelo ID;
 * Âncora: Define a posição de referência do retângulo no cenário,
 * contendo as coordenadas (x, y);
 * Largura: Define a dimensão horizontal do retângulo (width);
 * Altura: Define a dimensão vertical do retângulo (height);
 * Cor de Borda: Define a cor da linha que contorna o retângulo;
 * Cor de Preenchimento: Define a cor que preenche o interior do retângulo.
 */

typedef struct stRetangulo retangulo;

/* ------- FUNÇÃO CONSTRUTORA: RETÂNGULO ------- */

/// @brief: Constrói/define um retângulo com os atributos dos parâmetros.
/// @param i: Identificador do retângulo.
/// @param x: Coordenada x da âncora do retângulo.
/// @param y: Coordenada y da âncora do retângulo.
/// @param w: Largura do retângulo (width).
/// @param h: Altura do retângulo (height).
/// @param corb: Cor da borda do retângulo.
/// @param corp: Cor de preenchimento do retângulo.
/// @return: Retorna um ponteiro para o retângulo criado.
retangulo *criaRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp);

/* ------- MÉTODOS GET: RETÂNGULO ------- */

/// @brief: Pega o identificador do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna o identificador do círculo.
int getIDretangulo(retangulo *r);

/// @brief: Pega a coordenada x da âncora do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna a coordenada x da âncora do retângulo.
double getXretangulo(retangulo *r);

/// @brief: Pega a coordenada y da âncora do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna a coordenada y da âncora do retângulo.
double getYretangulo(retangulo *r);

/// @brief: Pega a largura do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna a largura do retângulo.
double getLarguraRetangulo(retangulo *r);

/// @brief: Pega a altura do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna a altura do retângulo.
double getAlturaRetangulo(retangulo *r);

/// @brief: Pega a cor de borda do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna a cor de borda do retângulo.
char *getCorbRetangulo(retangulo *r);

/// @brief: Pega a cor de preenchimento do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna a cor de preenchimento do retângulo.
char *getCorpRetangulo(retangulo *r);

/* ------- MÉTODOS SET: RETÂNGULO ------- */

/// @brief: Define um novo identificador para o retângulo.
/// @param r: Ponteiro para o retângulo.
/// @param i: Novo identificador do retângulo.
void setIDretangulo(retangulo *r, int i);

/// @brief: Define uma nova coordenada x para a âncora do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @param x: Nova coordenada x da âncora do retângulo.
void setXretangulo(retangulo *r, double x);

/// @brief: Define uma nova coordenada y para a âncora do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @param y: Nova coordenada y da âncorda do retângulo.
void setYretangulo(retangulo *r, double y);

/// @brief: Define uma nova largura para o retângulo.
/// @param r: Ponteiro para o retângulo.
/// @param w: Nova largura para o retângulo.
void setLarguraRetangulo(retangulo *r, double w);

/// @brief: Define uma nova altura para o retângulo.
/// @param r: Ponteiro para o retângulo.
/// @param h: Nova altura para o retângulo.
void setAlturaRetangulo(retangulo *r, double h);

/// @brief: Define uma nova cor de borda para o retângulo.
/// @param r: Ponteiro para o retângulo.
/// @param corb: Nova cor de borda do retângulo.
void setCorbRetangulo(retangulo *r, char *corb);

/// @brief: Define uma nova cor de preenchimento para o retângulo.
/// @param r: Ponteiro para o retângulo.
/// @param corp: Nova cor de preenchimento para o retângulo.
void setCorpRetangulo(retangulo *r, char *corp);

/* ------- MÉTODOS ADICIONAIS: RETÂNGULO ------- */

/// @brief: Calcula a área do retângulo.
/// @param r: Ponteiro para o retângulo.
/// @return: Retorna a área calculada do retângulo.
double calcAreaRetangulo(retangulo *r);

/// @brief: Libera o retângulo da memória.
/// @param r: Ponteiro para o retângulo a ser liberado.
void destrutorRetangulo(retangulo *r);

#endif //RETANGULO_H
