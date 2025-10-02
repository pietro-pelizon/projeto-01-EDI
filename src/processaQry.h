#ifndef PROCESSAQRY_H
#define PROCESSAQRY_H

#include "arena.h"
#include "chao.h"
#include "disparador.h"
#include "carregadores.h"


void processaQry(const char *nome_path_qry, arena *arena, chao *chao, disparador *d, carregador *c, double *pontuacao_total);



#endif //PROCESSAQRY_H