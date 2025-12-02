#define _CRT_SECURE_NO_WARNINGS

#include "respostas.h"
#include <stdio.h>
#include <stdlib.h>

Answer answers[MAX_ANSWERS]; // vetor global das respostas

void init_answers() {
    for (int i = 0; i < MAX_ANSWERS; i++) {
        answers[i].active = false;
    }
}

// Cria uma nova resposta caindo do topo
void spawn_answer(float correct_value) {
    for (int i = 0; i < MAX_ANSWERS; i++) {
        if (!answers[i].active) {   // acha uma vaga
            answers[i].x = rand() % (1280 - 100);
            answers[i].y = 0;
            answers[i].speed = 3;   // velocidade constante
            answers[i].active = true;

            // 1 em 5 chance de ser a resposta correta
            answers[i].is_correct = (rand() % 5 == 0);

            if (answers[i].is_correct)
                sprintf(answers[i].text, "x = %.0f", correct_value);
            else {
                int offset = (rand() % 50) - 25; // números maiores
                if (offset == 0) offset = 1;
                float wrong_value = correct_value + offset;
                sprintf(answers[i].text, "x = %.0f", wrong_value);
            }

            break; // spawnou uma resposta, sai do loop
        }
    }
}


void update_answers() {
    for (int i = 0; i < MAX_ANSWERS; i++) {
        if (answers[i].active) {
            answers[i].y += answers[i].speed; // cai

            if (answers[i].y > 720) // se passou do fim da tela
                answers[i].active = false;
        }
    }
}

void draw_answers(ALLEGRO_FONT* fonte_fase2) {
    for (int i = 0; i < MAX_ANSWERS; i++) {
        if (answers[i].active) {
            al_draw_text(fonte_fase2, al_map_rgb(255, 255, 0), answers[i].x, answers[i].y, 0, answers[i].text);
        }
    }
}
