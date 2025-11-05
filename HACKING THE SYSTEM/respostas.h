#ifndef RESPOSTAS_H
#define RESPOSTAS_H

#include <stdbool.h>
#include <stdio.h>
#include<allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#define MAX_ANSWERS 10

typedef struct {
	float x, y; // posção	
	float speed; // velocidade da queda
	bool active; // se aparece em tela
	bool is_correct; // se é a resposta certa
	char text[16]; // texto mostrado em tela
}Answer;

void init_answers();
void spawn_answer(float corret_value);
void update_answers();
void draw_answers(ALLEGRO_FONT* fonte_fase2);

#endif // !RESPOSTAS_H
