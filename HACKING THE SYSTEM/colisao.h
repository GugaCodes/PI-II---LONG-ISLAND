#ifndef COLISAO_H
#define COLISAO_H

#include <stdbool.h>
#include "respostas.h"

bool colidiu(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2);

void verificar_colisoes(float pos_x, float pos_y, float largura_personagem, float altura_personagem,
    float largura_resposta, float altura_resposta);

void colisao_init(void);
void colisao_clear(void);
int colisao_add(int x1, int y1, int x2, int y2); // retorna id ou -1
bool colisao_test(float x, float y, int w, int h); // true se colidir

#endif // COLISAO_H

