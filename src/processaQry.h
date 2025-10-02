#ifndef PROCESSAQRY_H
#define PROCESSAQRY_H
#include "chao.h"
#include "disparador.h"
#include "carregadores.h"
#include "arena.h"

typedef struct stRepositorio repositorio;

// Estruturas de gerenciamento que serão definidas no .c
typedef struct stRepositorioObjetos RepositorioObjetos;

/// @brief: Inicializa o repositório que guardará todos os carregadores e disparadores.
/// @return: Um ponteiro para a estrutura do repositório.
repositorio* criarRepositorio();


/// @brief: Libera a memória do repositório e de todos os objetos que ele contém.
/// @param repo: O repositório a ser destruído.
void destruirRepositorio(RepositorioObjetos* repo);



void processaQry(const char *nome_path_qry, const char *nome_txt, arena *arena, chao *chao, disparador *d, carregador *c, double *pontuacao_total);

#endif //PROCESSAQRY_H