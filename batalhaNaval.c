#include <stdio.h>
#include <stdlib.h>


// Tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10

// Tamanho das matrizes de habilidade (deve ser ímpar para centralização)
#define TAMANHO_HABILIDADE 5

// Valores para representar elementos no tabuleiro
#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5

// Estrutura para representar as coordenadas de um ponto
typedef struct {
    int linha;
    int coluna;
} Coordenadas;

// Função para inicializar o tabuleiro com água e navios
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Inicializa com água
        }
    }

    // Posiciona alguns navios (exemplo)
    tabuleiro[2][2] = NAVIO;
    tabuleiro[7][7] = NAVIO;
    tabuleiro[4][1] = NAVIO;
}

// Função para criar a matriz de habilidade em cone
void criarHabilidadeCone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i >= j && i >= TAMANHO_HABILIDADE - 1 - j) {
                cone[i][j] = 1; // Define a área do cone com 1
            } else {
                cone[i][j] = 0; // Define o restante como 0
            }
        }
    }
}

// Função para criar a matriz de habilidade em cruz
void criarHabilidadeCruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                cruz[i][j] = 1; // Define a área da cruz com 1
            } else {
                cruz[i][j] = 0; // Define o restante como 0
            }
        }
    }
}

// Função para criar a matriz de habilidade em octaedro (losango)
void criarHabilidadeOctaedro(int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2) {
                octaedro[i][j] = 1; // Define a área do octaedro com 1
            } else {
                octaedro[i][j] = 0; // Define o restante como 0
            }
        }
    }
}

// Função para sobrepor a habilidade no tabuleiro
void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                        Coordenadas origem) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int tabuleiroLinha = origem.linha - TAMANHO_HABILIDADE / 2 + i;
                int tabuleiroColuna = origem.coluna - TAMANHO_HABILIDADE / 2 + j;

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (tabuleiroLinha >= 0 && tabuleiroLinha < TAMANHO_TABULEIRO &&
                    tabuleiroColuna >= 0 && tabuleiroColuna < TAMANHO_TABULEIRO) {
                    tabuleiro[tabuleiroLinha][tabuleiroColuna] = AREA_HABILIDADE; // Marca a área da habilidade
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf("0 "); // Água
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("3 "); // Navio
            } else if (tabuleiro[i][j] == AREA_HABILIDADE) {
                printf("5 "); // Área da habilidade
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    Coordenadas origemCone = {3, 3};
    Coordenadas origemCruz = {6, 6};
    Coordenadas origemOctaedro = {1, 8};

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Cria as matrizes de habilidade
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // Sobrepõe as habilidades no tabuleiro
    sobreporHabilidade(tabuleiro, cone, origemCone);
    sobreporHabilidade(tabuleiro, cruz, origemCruz);
    sobreporHabilidade(tabuleiro, octaedro, origemOctaedro);

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
