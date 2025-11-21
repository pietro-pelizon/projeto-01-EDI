# Projeto 01 - Estrutura de Dados (EDI)

**Autor:** Pietro Fernando Pelizon
**Linguagem:** C (C99)

## 📋 Sobre o Projeto

Este projeto, denominado **TED** (no executável), é um simulador de combate geométrico que implementa e manipula estruturas de dados fundamentais (Filas e Pilhas) para gerir formas geométricas num cenário (Arena).

O sistema lê ficheiros de entrada (`.geo` e `.qry`) para configurar o ambiente e executar comandos, gerando como saída ficheiros gráficos vetoriais (`.svg`) e relatórios de texto (`.txt`) detalhando as interações e colisões entre os objetos.

### Principais Funcionalidades

  * **Manipulação de Formas Geométricas:** Suporte para Círculos, Retângulos, Linhas e Texto, com gestão de atributos como coordenadas, dimensões, cores e estilos de fonte.
  * **TADs Genéricos:** Implementação de estruturas de dados genéricas (`void*`):
      * **Fila (Queue):** Utilizada para o "Chão" (armazenamento inicial) e para a "Arena" (objetos ativos).
      * **Pilha (Stack):** Utilizada nos "Carregadores" para gerir munição (LIFO).
  * **Sistema de Disparo:** Mecânica de carregadores e disparadores que movem formas do chão para a arena.
  * **Deteção de Colisões:** Algoritmos matemáticos para verificar sobreposição entre todas as formas suportadas (ex: Círculo vs Retângulo, Linha vs Texto, etc.).
  * **Regras de Combate:**
      * Se a forma A colide com B e Área(A) \< Área(B): A é "esmagada" (destruída) e gera pontuação.
      * Se a forma A colide com B e Área(A) ≥ Área(B): A modifica as cores de B e pode ser clonada.
  * **Saída Gráfica:** Geração de ficheiros SVG que representam visualmente o estado inicial e final da simulação.

## 🛠️ Compilação

O projeto inclui um `makefile` para facilitar a compilação. Certifique-se de ter o `gcc` e o `make` instalados.

Para compilar o projeto, navegue até à pasta `src` e execute:

```bash
make
```

Isto irá gerar o executável chamado **`ted`**.

Para limpar os ficheiros objeto (`.o`) e o executável:

```bash
make clean
```

## 🚀 Como Executar

A execução do programa requer parâmetros de linha de comando para indicar os diretórios e ficheiros de entrada/saída.

**Sintaxe:**

```bash
./ted -e [dir_entrada] -f [arquivo.geo] -o [dir_saida] -q [arquivo.qry]
```

**Parâmetros:**

  * `-e`: (Opcional) Caminho base para o diretório de entrada.
  * `-f`: (Obrigatório) Nome do ficheiro de geometria (`.geo`).
  * `-o`: (Obrigatório) Caminho para o diretório onde os ficheiros de saída (`.svg`, `.txt`) serão gravados.
  * `-q`: (Opcional) Nome do ficheiro de consultas/comandos (`.qry`).

**Exemplo de uso:**

```bash
./ted -e entrada -f exp1.geo -o saida -q exp1.qry
```

## 📂 Estrutura dos Ficheiros de Entrada

### Ficheiro .geo

Define as formas iniciais que são colocadas no "Chão".

  * `c id x y r corb corp`: Cria um Círculo.
  * `r id x y w h corb corp`: Cria um Retângulo.
  * `l id x1 y1 x2 y2 cor`: Cria uma Linha.
  * `t id x y corb corp ancora texto`: Cria um Texto.
  * `ts familia peso tamanho`: Define o estilo do texto subsequente.

### Ficheiro .qry

Define os comandos da simulação.

  * `pd id x y`: Posiciona um Disparador.
  * `lc id n`: Carrega um Carregador com `n` formas do chão.
  * `atch id_disp id_carr_dir id_carr_esq`: Acopla carregadores a um disparador.
  * `shft id_disp lado n`: Move munição dos carregadores para a posição de disparo.
  * `dsp id_disp dx dy`: Dispara uma forma.
  * `rjd ...`: Dispara uma rajada de formas.
  * `calc`: Processa a Arena (verifica colisões, pontua e gera relatório).

## 📦 Estrutura do Código (Módulos)

  * **`main.c`**: Ponto de entrada, orquestra a leitura de argumentos e o fluxo principal.
  * **`arena.c/h`**: Gere a fila de formas ativas e lógica de interação/colisão.
  * **`chao.c/h`**: Gere a fila de formas passivas (inventário).
  * **`carregadores.c/h`**: Implementa a lógica de carregamento usando pilhas.
  * **`disparador.c/h`**: Gere a mecânica de disparo e acoplamento de carregadores.
  * **`processaGeo.c/h` & `processaQry.c/h`**: Interpretadores dos ficheiros de entrada.
  * **`sobreposicao.c/h`**: Biblioteca matemática para verificar interseções entre formas.
  * **`svg.c/h`**: Responsável por desenhar as formas no formato SVG.
  * **`formas.c/h`**: Wrapper genérico para lidar com diferentes tipos de formas (polimorfismo).
