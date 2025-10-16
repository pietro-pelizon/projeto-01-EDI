# Versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto e linguagem (C)
project(ted C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -ggdb -fstack-protector-all)

# O CLion usará esta lista para entender seu projeto.
add_executable(ted # (Você ainda vai criar este)
        src/arena.c
        src/carregadores.c
        src/chao.c
        src/circulo.c
        src/disparador.c
        src/fila.c
        src/formas.c
        src/linha.c
        src/pilha.c
        src/processaGeo.c
        src/processaQry.c
        src/retangulo.c
        src/sobreposicao.c
        src/svg.c
        src/texto.c
        src/main.c
)

# Linka a biblioteca de matemática (-lm), necessária para funções como sqrt, fabs, etc.
target_link_libraries(ted PRIVATE m)