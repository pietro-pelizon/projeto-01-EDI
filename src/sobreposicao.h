#ifndef SOBREPOSICAO_H
#define SOBREPOSICAO_H
#include <stdbool.h>
#include "formas.h"


/**
 * @brief Verifica se duas formas geométricas genéricas se sobrepõem.
 * * Esta é a única função que outros módulos precisam chamar para detecção de colisão.
 * Ela delega o trabalho para funções especialistas internas baseadas nos tipos das formas.
 * * @param f1 Ponteiro para a primeira forma.
 * @param f2 Ponteiro para a segunda forma.
 * @return true se as formas tiverem qualquer tipo de interseção, false caso contrário.
 */
bool formasSobrepoem(forma *f1, forma *f2);

#endif // SOBREPOSICAO_H

