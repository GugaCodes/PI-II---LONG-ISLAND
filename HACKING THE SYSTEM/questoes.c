#include "questoes.h"
#include <stdlib.h>
#include <time.h>

// Banco de perguntas fixas
Questao banco[] = {

    // === EQUAÇÕES SIMPLES === 
    {"2(5x - 2) = 76",  8},
    {"2x + 10 = -10", -10},
    {"2x + 10 = 42", 16},
    {"4(5x - 4) = 456", 25},
    {"4x - 12 = 32", 11},
    {"2x + 6 = 26", 10},
    {"6x - 18 = 60", 13},
    {"5(2x + 3) = 155", 14},  
    {"5(2x + 4) = -30",  -5},
    {"3x - 9 = 21", 10},      
    {"2x + 5 = 27", 11},
    {"2x + 8 = 34", 13},
    {"3x + 6 = 42", 12},
    {"6(3x - 2) = -120", -6},
    {"5x - 10 = 50", 12},
    {"5x - 20 = 55", 15},
    {"2x + 4 = 32", 14},
    {"3x + 12 = 57", 15},
    {"4x - 16 = 40", 14},

    //{"2x + 10 = 42", 16},
    {"6x - 12 = 84", 16},

    {"3x + 3 = 54", 17},
    {"7x - 21 = 98", 17},

    {"2x + 14 = 50", 18},
    {"4x - 8 = 64", 18},

    {"2x + 16 = 58", 21},
    {"7x - 28 = 119", 21},

    // === NEGATIVAS ===
    //{"2x + 10 = -10", -10},
    {"3x - 15 = -45", -10}, 

    {"2x + 8 = -14", -11},
    {"4x - 20 = -64", -11},

    {"3x + 12 = -24", -12},
    {"5x - 15 = -75", -12},

    {"2x + 6 = -20", -13},
    {"6x - 18 = -96", -13},

    {"3x + 9 = -33", -14},
    {"7x - 28 = -126", -14},

    {"2x + 10 = -20", -15},
    {"4x - 16 = -76", -15},

    // === EQUAÇÕES COM MULTIPLICAÇÃO ===
    {"3(2x - 5) = 45", 10},    

    {"4(3x + 1) = 148", 12},   


    //{"2(5x - 2) = 76",  8},    
    {"3(4x - 6) = 102", 10},   
    {"7(3x + 2) = 329", 15},   
    {"8(2x - 1) = 200", 13},  
    {"9(2x + 5) = 378", 17},   
    {"5(4x - 3) = 385", 20},

    //{"4(5x - 4) = 456", 25},
    {"6(3x + 5) = 540", 25},   

    {"7(4x - 3) = 721", 26},
    {"8(3x + 1) = 648", 27},
    {"9(3x - 2) = 621", 23},

    // === MULTIPLICAÇÃO NEGATIVAS ===
    {"4(3x - 1) = -100", -8},
    {"8(2x + 3) = -80",  -8},  

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

