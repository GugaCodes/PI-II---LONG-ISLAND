#ifndef QUESTOES_H
#define QUESTOES_H

typedef struct {
    char texto[32];   // texto da pergunta
    float resposta;   // valor correto de x
} Questao;

extern Questao banco[];       // banco de perguntas
extern int total_perguntas;   // número total de perguntas
extern Questao pergunta_atual;

void nova_pergunta();          // função para pegar uma pergunta aleatória

#endif
