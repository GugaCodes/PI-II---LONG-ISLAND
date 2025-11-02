#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#include <allegro5/allegro.h>

void mover_personagem(ALLEGRO_EVENT evento, float* pos_x, float* pos_y, float* frame, float velocidade_personagem, int* current_frame_y);
void mover_personagem2(ALLEGRO_EVENT evento, float* pos_x, float* pos_y, float* frame, float velocidade_personagem, int* current_frame_y);

#endif
