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


#define MAX_OBS 128

typedef struct {
    int x1, y1, x2, y2;
} Ob;

static Ob obstacles[MAX_OBS];
static int obstacles_count = 0;

void colisao_init(void) {
    obstacles_count = 0;
}

void colisao_clear(void) {
    obstacles_count = 0;
}

int colisao_add(int x1, int y1, int x2, int y2) {
    if (obstacles_count >= MAX_OBS) return -1;
    obstacles[obstacles_count].x1 = x1;
    obstacles[obstacles_count].y1 = y1;
    obstacles[obstacles_count].x2 = x2;
    obstacles[obstacles_count].y2 = y2;
    return obstacles_count++;
}

static int aabb_intersect(float ax1, float ay1, float ax2, float ay2,
    float bx1, float by1, float bx2, float by2) {
    return (ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1);
}

bool colisao_test(float x, float y, int w, int h) {
    float ax1 = x;
    float ay1 = y;
    float ax2 = x + (float)w;
    float ay2 = y + (float)h;
    for (int i = 0; i < obstacles_count; ++i) {
        Ob* o = &obstacles[i];
        if (aabb_intersect(ax1, ay1, ax2, ay2,
            (float)o->x1, (float)o->y1, (float)o->x2, (float)o->y2)) {
            return true;
        }
    }
    return false;
}
