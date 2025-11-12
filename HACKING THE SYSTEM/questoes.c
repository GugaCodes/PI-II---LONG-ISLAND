#include "questoes.h"
#include <stdlib.h>
#include <time.h>

// Banco de perguntas fixas
Questao banco[] = {
    {"2x + 4 = 10", 3},
    {"3x - 5 = 10", 5},
    {"4x + 8 = 20", 3},
    {"5x - 10 = 15", 5},
    {"6x + 12 = 30", 3}
};
int total_perguntas = sizeof(banco) / sizeof(banco[0]);
Questao pergunta_atual;

void embaralhar_perguntas() {
    for (int i = total_perguntas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Questao temp = banco[i];
        banco[i] = banco[j];
        banco[j] = temp;
    }
}


static int indice_atual = 0;

void nova_pergunta() {
    if (indice_atual >= total_perguntas)
        indice_atual = 0; // recomeça ou passa pra próxima fase

    pergunta_atual = banco[indice_atual];
    indice_atual++;
}

