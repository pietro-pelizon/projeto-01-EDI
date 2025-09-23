#ifndef TEXTO_H
#define TEXTO_H

typedef struct stEstilo estilo;
typedef struct stTexto texto;

/* ------- FUNÇÃO CONSTRUTORA: ESTILO ------- */

/// @brief: Cria o estilo do texto.
/// @param fFamily Família da fonte.
/// @param fWeight Espessura do texto.
/// @param fSize: Tamanho da fonte.
/// @return: Retorna o estilo criado do texto.
estilo *criaEstilo(char *fFamily, char *fWeight, char *fSize);

/* ------- MÉTODOS GET: ESTILO ------- */

/// @brief: Pega a família da fonte do texto.
/// @param e: Ponteiro para o estilo da fonte.
/// @return: Retorna a família da fonte do texto
char *getfFamily(estilo *e);

/// @brief: Pega a espessura do estilo do texto.
/// @param e: Ponteiro para o estilo da fonte.
/// @return: Retorna a espessura do estilo do texto.
char *getfWeight(estilo *e);

/// @brief: Pega o tamanho do estilo do texto.
/// @param e: Ponteiro para o estilo da fonte.
/// @return: Retorna o tamanho do estilo do texto.
char *getfSize(estilo *e);

/* ------- MÉTODOS SET: ESTILO ------- */

/// @brief: Define uma nova família para a fonte do texto.
/// @param e: Ponteiro para o estilo da fonte.
/// @param newfFamily: Nova família da fonte do texto.
void setfFamily(estilo *e, char *newfFamily);

/// @brief: Define uma nova espessura para o estilo do texto.
/// @param e: Ponteiro para o estilo da fonte.
/// @param newfWeight: Nova espessura do estilo do texto.
void setfWeight(estilo *e, char *newfWeight);

/// @brief: Define um novo tamanho para o estilo do texto.
/// @param e: Ponteiro para o estilo da fonte.
/// @param newfSize: Novo tamanho do estilo do texto.
void setfSize(estilo *e, char *newfSize);

/* ------- FUNÇÃO CONSTRUTORA: TEXTO ------- */

/// @brief: Constrói uma forma texto.
/// @param i: Identificador do texto.
/// @param x: Coordenada x da âncora do texto.
/// @param y: Coordenada y da âncora do texto.
/// @param corb: Cor de borda do texto.
/// @param corp: Cor de preenchimento do texto.
/// @param a: Posição da âncora (começo, meio ou fim).
/// @param txto: O texto em si.
/// @param e: Ponteiro para estilo.
/// @return: Retorna o texto já criado.
texto *criaTexto(int i, double x, double y, char *corb, char *corp, char a, char *txto, estilo *e);

/* ------- MÉTODOS GET: TEXTO ------- */

/// @brief: Pega o identificador do texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna o identificador do texto.
int getIDTexto(texto *t);

/// @brief: Pega a coordenada x da âncora do texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna a coordenada x da âncora do texto.
double getXTexto(texto *t);

/// @brief: Pega a coordenada y da âncora do texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna a coordenada y da âncora do texto.
double getYTexto(texto *t);

/// @brief: Pega a cor de borda do texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna a cor de borda do texto.
char *getCorbTexto(texto *t);

/// @brief: Pega a cor de preenchimento do texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna a cor de preenchimento do texto.
char *getCorpTexto(texto *t);

/// @brief: Pega a posição da âncora do texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna a posição da âncora do texto.
char getATexto(texto *t);

/// @brief: Pega o texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna o texto.
char *getTxtoTexto(texto *t);

/// @brief: Pega o estilo do texto.
/// @param t: Ponteiro para o texto.
/// @return: Retorna o estilo do texto.
estilo *getEstiloTexto(texto *t);

/* ------- MÉTODOS SET: TEXTO ------- */

/// @brief: Define um novo identificador para o texto.
/// @param t: Ponteiro para o texto.
/// @param i: Novo identificador do texto.
void setIDTexto(texto *t, int i);

/// @brief: Define uma nova coordenada x para a âncora do texto.
/// @param t: Ponteiro para o texto.
/// @param x: Nova coordenada x da âncora do texto.
void setXTexto(texto *t, double x);

/// @brief: Define uma nova coordenada y para a âncora do texto.
/// @param t: Ponteiro para o texto.
/// @param y: Nova coordenada y da âncora do texto.
void setYTexto(texto *t, double y);

/// @brief: Define uma nova cor de borda ao texto.
/// @param t: Ponteiro para o texto.
/// @param corb: Nova cor de borda do texto.
void setCorbTexto(texto *t, char *corb);

/// @brief: Define uma nova cor de preenchimento ao texto.
/// @param t: Ponteiro para o texto.
/// @param corp: Nova cor de preenchimento do texto.
void setCorpTexto(texto *t, char *corp);

/// @brief: Define uma nova posição de âncora para o texto.
/// @param t: Ponteiro para o texto.
/// @param a: Novo posição da âncora do texto.
void setATexto(texto *t, char a);

/// @brief: Define um novo estilo ao texto.
/// @param t: Ponteiro para o texto.
/// @param novoEstilo: Novo estilo do texto.
void setEstiloTexto(texto *t, estilo *novoEstilo);

/* ------- MÉTODOS ADICIONAIS ------- */

/// @brief: Calcula a área atribuída ao círculo.
/// @param t: Ponteiro para o texto.
/// @return: Retorna a área calculada do círculo.
double calcAreaTexto(texto *t);

void destrutorTexto(texto *t)

#endif //TEXTO_H
