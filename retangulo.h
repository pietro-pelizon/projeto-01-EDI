#ifndef RETANGULO_H
#define RETANGULO_H

typedef struct retangulo retangulo;

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
/// @param d: Ponteiro para o retângulo.
/// @return: Retorna o identificador do círculo.
int getIDretangulo(retangulo *d);

/// @brief: Pega a coordenada x da âncora do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @return: Retorna a coordenada x da âncora do retângulo.
double getXretangulo(retangulo *d);

/// @brief: Pega a coordenada y da âncora do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @return: Retorna a coordenada y da âncora do retângulo.
double getYretangulo(retangulo *d);

/// @brief: Pega a largura do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @return: Retorna a largura do retângulo.
double getWretangulo(retangulo *d);

/// @brief: Pega a altura do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @return: Retorna a altura do retângulo.
double getHretangulo(retangulo *d);

/// @brief: Pega a cor de borda do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @return: Retorna a cor de borda do retângulo.
char *getCorbRetangulo(retangulo *d);

/// @brief: Pega a cor de preenchimento do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @return: Retorna a cor de preenchimento do retângulo.
char *getCorpRetangulo(retangulo *d);

/* ------- MÉTODOS SET: RETÂNGULO ------- */

/// @brief: Define um novo identificador para o retângulo.
/// @param d: Ponteiro para o retângulo.
/// @param i: Novo identificador do retângulo.
void setIDretangulo(retangulo *d, int i);

/// @brief: Define uma nova coordenada x para a âncora do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @param x: Nova coordenada x da âncora do retângulo.
void setXretangulo(retangulo *d, double x);

/// @brief: Define uma nova coordenada y para a âncora do retângulo.
/// @param d: Ponteiro para o retângulo.
/// @param y: Nova coordenada y da âncorda do retângulo.
void setYretangulo(retangulo *d, double y);

/// @brief: Define uma nova largura para o retângulo.
/// @param d: Ponteiro para o retângulo.
/// @param w: Nova largura para o retângulo.
void setWretangulo(retangulo *d, double w);

/// @brief: Define uma nova altura para o retângulo.
/// @param d: Ponteiro para o retângulo.
/// @param h: Nova altura para o retângulo.
void setHretangulo(retangulo *d, double h);

/// @brief: Define uma nova cor de borda para o retângulo.
/// @param d: Ponteiro para o retângulo.
/// @param corb: Nova cor de borda do retângulo.
void setCorbRetangulo(retangulo *d, char *corb);

/// @brief: Define uma nova cor de preenchimento para o retângulo.
/// @param d: Ponteiro para o retângulo.
/// @param corp: Nova cor de preenchimento para o retângulo.
void setCorpRetangulo(retangulo *d, char *corp);


#endif //RETANGULO_H
