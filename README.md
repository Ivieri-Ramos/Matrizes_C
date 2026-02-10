# 🧮 Sistema de Análise Numérica e Álgebra Linear

Este projeto foi desenvolvido como parte da disciplina de Cálculo do curso **Ciência da Computação**. O objetivo principal foi implementar, **do zero e em Linguagem C**, uma biblioteca para manipulação de matrizes e utilizá-la para realizar ajustes de curvas pelo **Método dos Mínimos Quadrados**.

## 🚀 Funcionalidades Principais

O sistema é capaz de processar dados observados e compará-los com diferentes modelos matemáticos para determinar a melhor aproximação.

### 🛠️ Biblioteca de Matrizes Própria (`lib_matriz.c`)

Diferente de usar bibliotecas prontas, toda a lógica matricial foi implementada manualmente:

* **Gestão de Memória:** Alocação e liberação dinâmica de matrizes (`malloc`/`free`) para otimização de recursos.
* **Operações Fundamentais:** Soma, Multiplicação e Transposição de matrizes.
* **Algoritmos Complexos:**
* Cálculo da **Matriz Inversa** (utilizando escalonamento/Gauss-Jordan).
* Verificação de Matriz Identidade e Singularidade.


* **Tratamento de Erros:** Sistema robusto de validação (`matriz_resultado`) para prevenir falhas de segmentação ou dimensões incompatíveis.

### 📈 Análise Numérica (`funcoes_mat.c`)

Aplicação prática da biblioteca para resolver problemas reais:

* Implementação do **Método dos Mínimos Quadrados** para regressão linear e polinomial.
* Cálculo de erros **Absolutos** e **Relativos** para validação de modelos.
* Geração automática da Matriz de Vandermonde para polinômios de grau .

## 💻 Tecnologias Utilizadas

* **Linguagem C** (Padrão C99/C11)
* **Bibliotecas Padrão:** `stdlib.h` (Gerenciamento de memória), `math.h` (Cálculos matemáticos), `stdio.h` (I/O).
* **Ferramentas:** GCC (Compilador), Make (Opcional).

## 📂 Estrutura do Projeto

* `lib_matriz.c/h`: O "motor" do projeto. Contém todas as operações de baixo nível com matrizes.
* `funcoes_mat.c/h`: Camada de lógica matemática que utiliza a *lib_matriz* para aplicar os Mínimos Quadrados.
* `respostas_trabalho.c/h`: Contém os dados observados e a lógica específica para exibir os relatórios de erros.
* `menu_completo.c/h`: Interface via terminal para navegação entre os exercícios.
* `main.c`: Ponto de entrada da aplicação.
* `utils.c/h`: Funções auxiliares.

## ⚙️ Como Compilar e Rodar

Para compilar o projeto, você precisará de um compilador C (como o GCC). Abra o terminal na pasta do projeto e execute:

```bash
# Compilar todos os arquivos fonte e linkar a biblioteca matemática (-lm)
gcc main.c lib_matriz.c funcoes_mat.c menu_completo.c respostas_trabalho.c utils.c -o algebra_linear -lm

# Rodar o executável (Linux/Mac)
./algebra_linear

# Rodar o executável (Windows)
algebra_linear.exe

```

## 🧠 Exemplo de Código (Snippet)

Um trecho da lógica de alocação dinâmica implementada em `lib_matriz.c`:

```c
matriz_resultado criar_matriz(matriz *matriz, const size_t linhas, const size_t colunas) {
    if (linhas == 0 || colunas == 0) return MAT_ERRO_PARAMETRO_INVALIDO;
    
    // Alocação do vetor de ponteiros
    matriz -> dados = (double **) malloc(sizeof(double *) * linhas);
    
    // Alocação de um bloco contíguo para melhorar a performance de cache
    double *dados_ligados = (double *) malloc(sizeof(double) * linhas * colunas);
    
    // Ligação dos ponteiros
    for (size_t i = 0; i < linhas; i++) {
        matriz -> dados[i] = dados_ligados + (i * colunas);
    }
    
    matriz -> mat_colunas = colunas;
    matriz -> mat_linhas = linhas;
    return MAT_SUCESSO;
}

```

## 👨‍💻 Autor

**Ivieri Julião Ramos**

* Estudante de Ciência da Computação - UFAPE
* [Email](mailto:ivieriramos@gmail.com)
