#ifndef PROCESSAGEO_H
#define PROCESSAGEO_H
#include <stdio.h>

#include "chao.h"

/// @brief: Abre o arquivo .geo no modo de leitura,
/// e processa os dados das formas que estão contidos
/// nele. A cada criação de forma, adiciona a forma ao chão.
/// @param nome_path_geo: Nome do arquivo .geo.
/// @return: O chão com as formas já criadas e adicionadas a ele.
chao *processaGeo(const char *nome_path_geo);

#endif //PROCESSAGEO_H