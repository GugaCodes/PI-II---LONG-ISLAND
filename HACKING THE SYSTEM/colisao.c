#include "colisao.h"
#include "questoes.h"
#include <stdio.h>

extern Answer answers[MAX_ANSWERS]; // usa o vetor global das respostas

int pontos = 0;

bool colidiu(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2) {
    return (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2);
}

void verificar_colisoes(float pos_x, float pos_y, float largura_personagem, float altura_personagem,
    float largura_resposta, float altura_resposta) {

    for (int i = 0; i < MAX_ANSWERS; i++) {
        if (answers[i].active) {
            if (colidiu(pos_x, pos_y, largura_personagem, altura_personagem,
                answers[i].x, answers[i].y, largura_resposta, altura_resposta)) {

                if (answers[i].is_correct) {
                    printf("✅ Acertou!\n");
                    pontos += 10;
                    nova_pergunta(); // troca a conta
                }
                else {
                    printf("❌ Errou!\n");
                    pontos -= 10;
                }


                answers[i].active = false;
            }
        }
    }
}
