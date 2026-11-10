#include"raylib.h"
#include"jogo.h"
#include<stdlib.h>
#include<time.h>

#define TAM 42
#define TOPO 110
#define MARGEM 24

static int primeiraJogada=1, estado=0; // 0 jogando, 1 perdeu, 2 venceu
static double inicio=0, fim=0;

static void reiniciar(void) {
    inicializarJogo();
    primeiraJogada=1;
    estado=0;
    inicio=GetTime();
    fim=0;
}

int main(void) {
    srand((unsigned)time(NULL));
    InitWindow(MARGEM*2+9*TAM, TOPO+9*TAM+MARGEM, "Campo Minado");
    SetTargetFPS(60);
    reiniciar();
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) { linhas=9; colunas=9; numMinas=10; SetWindowSize(MARGEM*2+colunas*TAM,TOPO+linhas*TAM+MARGEM); reiniciar(); }
        if (IsKeyPressed(KEY_TWO)) { linhas=16; colunas=16; numMinas=40; SetWindowSize(MARGEM*2+colunas*TAM,TOPO+linhas*TAM+MARGEM); reiniciar(); }
        if (IsKeyPressed(KEY_R)) reiniciar();
        if (estado==0 && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))) {
            Vector2 m=GetMousePosition();
            int c=((int)m.x-MARGEM)/TAM, l=((int)m.y-TOPO)/TAM;
            if (m.x>=MARGEM && m.y>=TOPO && posicaoValida(l,c) &&
                m.x<MARGEM+colunas*TAM && m.y<TOPO+linhas*TAM) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !aberto[l][c]) {
                    bandeira[l][c]=!bandeira[l][c];
                } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !bandeira[l][c] && !aberto[l][c]) {
                    if (primeiraJogada) {
                        colocarMinas(l,c);
                        calcularNumeros();
                        primeiraJogada=0;
                        inicio=GetTime();
                    }
                    if (campo[l][c]==-1) { estado=1; fim=GetTime(); aberto[l][c]=1; }
                    else { abrirCasa(l,c); if (verificarVitoria()) {estado=2; fim=GetTime();} }
                }
            }
        }
        BeginDrawing();
        ClearBackground((Color){22,30,46,255});
        DrawText("CAMPO MINADO",MARGEM,14,24,RAYWHITE);
        int marcadas=0;
        for(int l=0;l<linhas;l++) for(int c=0;c<colunas;c++) marcadas+=bandeira[l][c];
        DrawText(TextFormat("Minas: %d",numMinas-marcadas),MARGEM,48,18,ORANGE);
        DrawText(TextFormat("Tempo: %ds",(int)((estado ? fim : GetTime())-inicio)),MARGEM+145,48,18,RAYWHITE);
        DrawText(estado==1?"BOOM! R reinicia":estado==2?"VITORIA! R reinicia":"1: Facil  2: Medio  R: Reiniciar",MARGEM,80,15,estado==1?RED:estado==2?GREEN:LIGHTGRAY);
        for(int l=0;l<linhas;l++) for(int c=0;c<colunas;c++) {
            int x=MARGEM+c*TAM,y=TOPO+l*TAM;
            int revelada=aberto[l][c] || (estado!=0 && campo[l][c]==-1);
            DrawRectangle(x,y,TAM-2,TAM-2,revelada?(Color){190,201,211,255}:(Color){75,105,143,255});
            if (revelada) {
                if(campo[l][c]==-1) DrawText("*",x+13,y+6,29,RED);
                else if(campo[l][c]>0) {
                    Color cores[]={BLUE,DARKGREEN,RED,PURPLE,MAROON,ORANGE,BLACK,DARKGRAY};
                    DrawText(TextFormat("%d",campo[l][c]),x+13,y+8,25,cores[campo[l][c]-1]);
                }
            } else if(bandeira[l][c]) DrawText("F",x+12,y+7,26,YELLOW);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
