#ifndef JOGO_H
#define JOGO_H
#define MAX_LINHAS 20
#define MAX_COLUNAS 20
extern int linhas, colunas, numMinas;
extern int campo[MAX_LINHAS][MAX_COLUNAS], aberto[MAX_LINHAS][MAX_COLUNAS], bandeira[MAX_LINHAS][MAX_COLUNAS];
void inicializarJogo(void);
void colocarMinas(int linhaSegura, int colunaSegura);
int posicaoValida(int linha, int coluna);
int contarMinasAoRedor(int linha, int coluna);
void calcularNumeros(void);
void abrirCasa(int linha, int coluna);
int verificarVitoria(void);
#endif
