#include "jogo.h"
#include <stdlib.h>
int linhas=9, colunas=9, numMinas=10;
int campo[MAX_LINHAS][MAX_COLUNAS], aberto[MAX_LINHAS][MAX_COLUNAS], bandeira[MAX_LINHAS][MAX_COLUNAS];
void inicializarJogo() { // Inicializa o jogo; cria o campo
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            campo[i][j] = 0;
            aberto[i][j] = 0;
            bandeira[i][j] = 0;
        }
    }
}

void colocarMinas(int linhaSegura, int colunaSegura) { // Função que ira gerar as minas
    int minasColocadas = 0;

    while (minasColocadas < numMinas)
    {
        int linha = rand() % linhas; // Geração de posicao aleatoria
         int coluna = rand() % colunas; // Geração de posicao aleatoria

        // Nao permite colocar mina na primeira casa escolhida
        if (linha == linhaSegura && coluna == colunaSegura)
        {
            continue;
        }

        // Evita colocar duas minas na mesma posicao
        if (campo[linha][coluna] != -1)
        {
            campo[linha][coluna] = -1;
            minasColocadas++;
        }
    }
}

int posicaoValida(int linha, int coluna) { // Verifica se uma posição está dentro do campo
    return linha >= 0 &&
           linha < linhas &&
           coluna >= 0 &&
           coluna < colunas;
}

int contarMinasAoRedor(int linha, int coluna) { // Conta quantas minas existem ao redor
    int quantidade = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++) 
        {
            int novaLinha = linha + i;
            int novaColuna = coluna + j;

            if (posicaoValida(novaLinha, novaColuna)) // Verifica se a posicao vizinha esta dentro do campo
            {
                if (campo[novaLinha][novaColuna] == -1)
                {
                    quantidade++;
                }
            }
        }
    }

    return quantidade;
}

void calcularNumeros() { // Calcula os números do campo
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (campo[i][j] != -1)
            {
                campo[i][j] = contarMinasAoRedor(i, j);
            }
        }
    }
}



void abrirCasa(int linha, int coluna) { // Funcao recursiva
    if (!posicaoValida(linha, coluna)) // Verifica se a posição escolhida é valida
    {                                // Caso seja válida, empilha a posição desejada
        return;
    }

    if (aberto[linha][coluna] == 1 || bandeira[linha][coluna] == 1)// Verifica se a posicao ja foi escolhida(Se ja está na pilha).
    {
        return;
    }

    aberto[linha][coluna] = 1; // Mostra que a posicao ja está selecionada 

    if (campo[linha][coluna] != 0)
    {
        return;
    }

    for (int i = -1; i <= 1; i++) // Caso contrario, está disponivel para escolher 
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i != 0 || j != 0)
            {
                abrirCasa(linha + i, coluna + j);
            }
        }
    }
}

int verificarVitoria() { // Verifica vitória
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        { // Verifica se existe alguma casa sem mina que ainda nao foi aberta
            if (campo[i][j] != -1 && aberto[i][j] == 0) 
            {
                return 0;
            }
        }
    }

    return 1;
}

