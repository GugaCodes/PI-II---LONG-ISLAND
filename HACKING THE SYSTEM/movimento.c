#include "movimento.h"

void mover_personagem(ALLEGRO_EVENT evento, float* pos_x, float* pos_y, float* frame, float velocidade_personagem, int* current_frame_y) {
    if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
        *frame += 0.3f;
        *current_frame_y = 77 * 2;
        *pos_x += velocidade_personagem;
    }
    if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) {
        *frame += 0.3f;
        *current_frame_y = 75;
        *pos_x -= velocidade_personagem;
    }
    if (evento.keyboard.keycode == ALLEGRO_KEY_UP) {
        *frame += 0.3f;
        *current_frame_y = 78 * 4;
        *pos_y -= velocidade_personagem;
    }
    if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) {
        *frame += 0.3f;
        *current_frame_y = 0;
        *pos_y += velocidade_personagem;
    }
}

void mover_personagem2(ALLEGRO_EVENT evento, float* pos_x, float* pos_y, float* frame, float velocidade_personagem, int* current_frame_y) {
    if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
        *frame += 0.3f;
        *current_frame_y = 77 * 2;
        *pos_x += velocidade_personagem;
    }
    if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) {
        *frame += 0.3f;
        *current_frame_y = 75;
        *pos_x -= velocidade_personagem;
    }
    
}

