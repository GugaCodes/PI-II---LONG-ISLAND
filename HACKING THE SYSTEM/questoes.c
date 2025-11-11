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

void nova_pergunta() {
    srand(time(NULL));
    pergunta_atual = banco[rand() % total_perguntas];
}
