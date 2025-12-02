# define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "movimento.h"
#include "delimitacao.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <math.h>
#include "Objetos.h"
#include "respostas.h"
#include "questoes.h"
#include "colisao.h"
#include <time.h>
#include <string.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


struct botao {
    int btn_x1, btn_x2, btn_y1, btn_y2;
    int btn2_x1, btn2_x2, btn2_y1, btn2_y2;
    int btn3_x1, btn3_x2, btn3_y1, btn3_y2;
    int btn4_x1, btn4_x2, btn4_y1, btn4_y2;
};

struct espaco {
    int esp_x1, esp_x2, esp_y1, esp_y2;
    int erro_x1, erro_x2, erro_y1, erro_y2;
    int livro1_x1, livro1_x2, livro1_y1, livro1_y2;
    int livro2_x1, livro2_x2, livro2_y1, livro2_y2;
    int livro3_x1, livro3_x2, livro3_y1, livro3_y2;
    int comp_x1, comp_x2, comp_y1, comp_y2;
};

/*bool colidiu(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2) {
    return(x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2
        );
}*/
//________________________________________________________________________________________________________

 /*
    ========== INICIANDO OS SONS DO JOGO =====================
    */

ALLEGRO_SAMPLE* trilha_sonora = NULL;
ALLEGRO_SAMPLE* acerto = NULL;
ALLEGRO_SAMPLE* erro_tela = NULL;
ALLEGRO_SAMPLE* somfase2 = NULL;
ALLEGRO_SAMPLE* clique_tela = NULL;
ALLEGRO_SAMPLE* clique_tela2 = NULL;
ALLEGRO_SAMPLE* relogio = NULL;
ALLEGRO_SAMPLE* som_fase1 = NULL;
ALLEGRO_SAMPLE* missionPassed = NULL;
ALLEGRO_SAMPLE* concluido = NULL;

ALLEGRO_SAMPLE_INSTANCE* inst_trilha_sonora = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_acerto = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_erro_tela = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_somfase2 = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_clique_tela = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_clique_tela2;
ALLEGRO_SAMPLE_INSTANCE* inst_relogio = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_som_fase1 = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_missionPassed = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_concluido = NULL;


int main() {

    /*
    =========== VARIAVEIS GLOBAIS ===============
    */
    //criando uma váriavel de controle de telas

    int tela = 0;
    int height = 720, width = 1280;

    bool missaoConcluida = false;
    bool missaoConcluida2 = false;
    bool errofase1 = false;
    bool errofase2 = false;
    bool errofase3 = false;

    //DELIMMITANDO POSIÇÃO INICIAL DO PERSONAGEM

    float pos_x = 150, pos_y = 450, pos_x1 = 450, pos_Y2 = 450;

    float frame = 0.f;
    int current_frame_y = 0;

    // VARIAVEIS DO MOUSE
    float mouseX = 0.f, mouseY = 0.f;

    //================= COLISÃO DO PERSONAGEM NA FASE 2 ===============================

    float largura_personagem = 64;
    float altura_personagem = 64;

    float largura_resposta = 80;
    float altura_resposta = 40;

    //============== SISTEMA DE PONTUAÇÃO ==============
    //int pontos = 0;



    //texto caindo
    float velocidade_queda = 50;


    //__________________________________________________________________________________________________



    //CRIANDO AS STRICT DO BOTÃO PRNCIPAL

    struct botao menu;

    //BOTÃO JOGAR
    menu.btn_x1 = 550;
    menu.btn_x2 = 980;
    menu.btn_y1 = 450;
    menu.btn_y2 = 525;

    //BOTÃO SAIR

    menu.btn2_x1 = 550;
    menu.btn2_x2 = 980;
    menu.btn2_y1 = 610;
    menu.btn2_y2 = 680;

    //BOTÃO VOLTAR AO MENU PRINCIPAL TELA ERRO

    menu.btn3_x1 = 250;
    menu.btn3_x2 = 1031;
    menu.btn3_y1 = 510;
    menu.btn3_y2 = 580;

    menu.btn4_x1 = 250;
    menu.btn4_x2 = 1031;
    menu.btn4_y1 = 415;
    menu.btn4_y2 = 485;


    //CRIANDO A STRUCT DOS BOTÕES NA TELA DE FASES

    struct botao tela_fase;

    //BOTÃO VOLTAR

    tela_fase.btn_x1 = 100;
    tela_fase.btn_x2 = 420;
    tela_fase.btn_y1 = 630;
    tela_fase.btn_y2 = 705;

    //ir para fase 1

    tela_fase.btn2_x1 = 65;
    tela_fase.btn2_x2 = 460;
    tela_fase.btn2_y1 = 180;
    tela_fase.btn2_y2 = 625;


    //---------------------COLISÕES FASE 1--------------------------//

    struct botao mesa;
    mesa.btn_x1 = 438;
    mesa.btn_x2 = 510;
    mesa.btn_y1 = 240;
    mesa.btn_y2 = 300;

    struct botao mesa2;
    mesa2.btn_x1 = 728;
    mesa2.btn_x2 = 790;
    mesa2.btn_y1 = 243;
    mesa2.btn_y2 = 300;

    struct botao bau;
    bau.btn_x1 = 585;
    bau.btn_x2 = 650;
    bau.btn_y1 = 322;
    bau.btn_y2 = 350;

    struct botao quadro;
    quadro.btn_x1 = 1065;
    quadro.btn_x2 = 1120;
    quadro.btn_y1 = 322;
    quadro.btn_y2 = 350;

    struct botao pistas;
    pistas.btn_x1 = 140;
    pistas.btn_x2 = 180;
    pistas.btn_y1 = 245;
    pistas.btn_y2 = 265;

    struct botao mesapc;
    mesapc.btn_x1 = 150;
    mesapc.btn_x2 = 280;
    mesapc.btn_y1 = 390;
    mesapc.btn_y2 = 420;

    struct botao estantes;
    estantes.btn_x1 = 115;
    estantes.btn_x2 = 325;
    estantes.btn_y1 = 518;
    estantes.btn_y2 = 560;

    struct botao pc;
    pc.btn_x1 = 1020;
    pc.btn_x2 = 1110;
    pc.btn_y1 = 220;
    pc.btn_y2 = 240;

    struct botao placa;
    placa.btn_x1 = 1115;
    placa.btn_x2 = 1130;
    placa.btn_y1 = 428;
    placa.btn_y2 = 480;

    struct botao estanteE;
    estanteE.btn_x1 = 10;
    estanteE.btn_x2 = 90;
    estanteE.btn_y1 = 520;
    estanteE.btn_y2 = 590;

    struct botao mesa3;
    mesa3.btn_x1 = 358;
    mesa3.btn_x2 = 510;
    mesa3.btn_y1 = 530;
    mesa3.btn_y2 = 600;

    struct botao estantes2;
    estantes2.btn_x1 = 850;
    estantes2.btn_x2 = 1130;
    estantes2.btn_y1 = 520;
    estantes2.btn_y2 = 580;

    struct botao pcfora;
    pcfora.btn_x1 = 750;
    pcfora.btn_x2 = 812;
    pcfora.btn_y1 = 562;
    pcfora.btn_y2 = 630;

    struct botao sofa;
    sofa.btn_x1 = 1200;
    sofa.btn_x2 = 1270;
    sofa.btn_y1 = 500;
    sofa.btn_y2 = 630;


    struct botao pc2;
    pc2.btn_x1 = 176;
    pc2.btn_x2 = 200;
    pc2.btn_y1 = 363;
    pc2.btn_y2 = 390;


    //CRIANDO STRUCT PARA IR PARA FASE 2

    struct botao tela_fase2;

    //BOTÃO PARA IR PARA FASE 2

    tela_fase2.btn_x1 = 460;
    tela_fase2.btn_x2 = 820;
    tela_fase2.btn_y1 = 180;
    tela_fase2.btn_y2 = 625;

    //CRIANDO STRUCT PARA FUNCIONALIDADES DA FASE 3
    // 
    //-----------------------------------------------------------------//

    struct botao tela_fase3;

    tela_fase3.btn_x1 = 820;
    tela_fase3.btn_x2 = 1180;
    tela_fase3.btn_y1 = 180;
    tela_fase3.btn_y2 = 625;

    struct botao play;

    play.btn_x1 = 1100;
    play.btn_x2 = 1235;
    play.btn_y1 = 668;
    play.btn_y2 = 710;

    struct botao peixe;
    peixe.btn_x1 = 1140;
    peixe.btn_x2 = 1245;
    peixe.btn_y1 = 40;
    peixe.btn_y2 = 105;

    struct botao phishing;
    phishing.btn_x1 = 245;
    phishing.btn_x2 = 465;
    phishing.btn_y1 = 600;
    phishing.btn_y2 = 653;

    struct botao legitimo;
    legitimo.btn_x1 = 840;
    legitimo.btn_x2 = 1055;
    legitimo.btn_y1 = 600;
    legitimo.btn_y2 = 653;

    struct botao exit;
    exit.btn_x1 = 650;
    exit.btn_x2 = 950;
    exit.btn_y1 = 410;
    exit.btn_y2 = 510;

    struct botao try;
    try.btn_x1 = 345;
    try.btn_x2 = 635;
    try.btn_y1 = 410;
    try.btn_y2 = 510;
    //-----------------------------------------------------------------//

    //STRUCT PARA TELA DE PROXIMA FASE

    struct botao prox_fase;

    //BOTÃO PARA IR PARA PROX FASE

    prox_fase.btn_x1 = 385;
    prox_fase.btn_x2 = 880;
    prox_fase.btn_y1 = 640;
    prox_fase.btn_y2 = 705;

    //BOTÃO PARA IR PARA O MENU PRINCIPAL

    prox_fase.btn2_x1 = 385;
    prox_fase.btn2_x2 = 880;
    prox_fase.btn2_y1 = 550;
    prox_fase.btn2_y2 = 625;




    //CRIANDO STRUCT PARA SAIR PELA PORTA

    struct espaco fase1;

    fase1.esp_x1 = 500;
    fase1.esp_x2 = 690;
    fase1.esp_y1 = 610;
    fase1.esp_y2 = 720;


    // ESTANTE COM LIVRO 1
    fase1.livro1_x1 = 230;
    fase1.livro1_x2 = 325;
    fase1.livro1_y1 = 520;
    fase1.livro1_y2 = 695;

    // ESTANTE COM LIVRO 2

    fase1.livro2_x1 = 230;
    fase1.livro2_x2 = 330;
    fase1.livro2_y1 = 150;
    fase1.livro2_y2 = 270;

    // MESA COM LIVRO 3

    fase1.livro3_x1 = 430;
    fase1.livro3_x2 = 550;
    fase1.livro3_y1 = 240;
    fase1.livro3_y2 = 400;

    //MESA COM COMPUTADOR

    fase1.comp_x1 = 1000;
    fase1.comp_x2 = 1120;
    fase1.comp_y1 = 210;
    fase1.comp_y2 = 350;



    //ATALHO PARA TELA DE ERRO
    fase1.erro_x1 = 120;
    fase1.erro_x2 = 210;
    fase1.erro_y1 = 250;
    fase1.erro_y2 = 370;




    // -------------- INICIAALIZAÇÃO DE OBJETOS -------





     // inciciando biblioteca
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(10);

    srand(time(NULL)); // pra gerar números aleatórios
    init_answers(); // inicializa as respostas
    nova_pergunta(); // escolhe a primeira pergunta aleatória

    float spawn_timer = 0;
    float spawn_interval = 2.0; // a cada 2 segundos cria uma resposta


    ALLEGRO_DISPLAY* janela = al_create_display(width, height); /// criação da janela
    al_set_window_position(janela, 200, 200); // posição inicial da janela

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_FONT* fonte_fase2 = al_load_font("./fonte.ttf", 20, 0); // FONTE DA FASE 2
    ALLEGRO_FONT* fonte = al_load_font("./fonte.ttf", 30, 0); // pergunta da fase 2
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 10.0); // definindo "FPS"
    ALLEGRO_TIMER* timer_fase2 = al_create_timer(1.0 / 60.0); // 60fps
    ALLEGRO_BITMAP* tela_inicial = al_load_bitmap("./TELA_INICIAL.png");
    ALLEGRO_BITMAP* tela_fases = al_load_bitmap("TELA_FASES.png");
    ALLEGRO_BITMAP* fase_1 = al_load_bitmap("FASE1-PT.png");
    ALLEGRO_BITMAP* fase_2 = al_load_bitmap("TELA_FASE2.png");
    ALLEGRO_BITMAP* fase_3 = al_load_bitmap("TELA_FASE_3.png");
    ALLEGRO_BITMAP* tela_final = al_load_bitmap("TELA_FINAL.png");
    ALLEGRO_BITMAP* tela_fases_2 = al_load_bitmap("TELA-FASES-2.png");
    ALLEGRO_BITMAP* tela_fases_3 = al_load_bitmap("TELA-FASES-3.png");
    ALLEGRO_BITMAP* fase_concluida = al_load_bitmap("CONGRATULATIONS.png");
    ALLEGRO_BITMAP* mensagem_erro = al_load_bitmap("MENS_ERRO.png");
    ALLEGRO_BITMAP* livro1 = al_load_bitmap("LIVRO1.png");
    ALLEGRO_BITMAP* livro2 = al_load_bitmap("LIVRO2.png");
    ALLEGRO_BITMAP* livro3 = al_load_bitmap("LIVRO3.png");
    ALLEGRO_BITMAP* guanabara_fase1 = al_load_bitmap("GAFANHOTO1.png");
    ALLEGRO_BITMAP* tela_senha = al_load_bitmap("TELA_SENHA.png");
    ALLEGRO_BITMAP* guanabara_fase2 = al_load_bitmap("GAFANHOTO2.png");
    ALLEGRO_BITMAP* guanabara_fase3 = al_load_bitmap("GAFANHOTO3.png");
    ALLEGRO_BITMAP* sprite = al_load_bitmap("PERSONAGEM.png");
    ALLEGRO_BITMAP* tela_phishing1 = al_load_bitmap("LEGITIMO(disciplinas).png");
    ALLEGRO_BITMAP* tela_phishing2 = al_load_bitmap("PHISHING(presente).png");
    ALLEGRO_BITMAP* tela_phishing3 = al_load_bitmap("PHISHING(fatura).png");
    ALLEGRO_BITMAP* tela_phishing4 = al_load_bitmap("LEGITIMO(reuniao).png");
    ALLEGRO_BITMAP* tela_phishing5 = al_load_bitmap("LEGITIMO(loja).png");
    ALLEGRO_BITMAP* tela_phishing6 = al_load_bitmap("PHISHING(redes).png");
    ALLEGRO_BITMAP* phishing_consulta = al_load_bitmap("PHISHING_CONSULTA.png");
    ALLEGRO_BITMAP* erro_fase3 = al_load_bitmap("ERRO_FASE3.png");


    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // criação da fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer_fase2));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_start_timer(timer);
    al_start_timer(timer_fase2);
    colisao_init();
    colisao_clear();
    colisao_add(mesa.btn_x1, mesa.btn_y1, mesa.btn_x2, mesa.btn_y2);
    colisao_add(mesa2.btn_x1, mesa2.btn_y1, mesa2.btn_x2, mesa2.btn_y2);
    colisao_add(bau.btn_x1, bau.btn_y1, bau.btn_x2, bau.btn_y2);
    colisao_add(quadro.btn_x1, quadro.btn_y1, quadro.btn_x2, quadro.btn_y2);
    colisao_add(pistas.btn_x1, pistas.btn_y1, pistas.btn_x2, pistas.btn_y2);
    colisao_add(mesapc.btn_x1, mesapc.btn_y1, mesapc.btn_x2, mesapc.btn_y2);
    colisao_add(estantes.btn_x1, estantes.btn_y1, estantes.btn_x2, estantes.btn_y2);
    colisao_add(pc.btn_x1, pc.btn_y1, pc.btn_x2, pc.btn_y2);
    colisao_add(placa.btn_x1, placa.btn_y1, placa.btn_x2, placa.btn_y2);
    colisao_add(estanteE.btn_x1, estanteE.btn_y1, estanteE.btn_x2, estanteE.btn_y2);
    colisao_add(mesa3.btn_x1, mesa3.btn_y1, mesa3.btn_x2, mesa3.btn_y2);
    colisao_add(estantes2.btn_x1, estantes2.btn_y1, estantes2.btn_x2, estantes2.btn_y2);
    colisao_add(pcfora.btn_x1, pcfora.btn_y1, pcfora.btn_x2, pcfora.btn_y2);
    colisao_add(sofa.btn_x1, sofa.btn_y1, sofa.btn_x2, sofa.btn_y2);
    colisao_add(pc2.btn_x1, pc2.btn_y1, pc2.btn_x2, pc2.btn_y2);





    //-------------------------------------------------------------------------
    //=================CRIAÇÃO DE DISPOSITIVOS=====================
    trilha_sonora = al_load_sample("som_menu_principal.mp3");
    clique_tela = al_load_sample("som_clique.mp3");
    clique_tela2 = al_load_sample("som_clique2.mp3");
    relogio = al_load_sample("theclock.mp3");
    som_fase1 = al_load_sample("fase1song.mp3");
    somfase2 = al_load_sample("somfase2.mp3");
    missionPassed = al_load_sample("missionpassed.mp3");
    erro_tela = al_load_sample("error.mp3");
    concluido = al_load_sample("endgame.mp3");


    inst_trilha_sonora = al_create_sample_instance(trilha_sonora);
    inst_clique_tela = al_create_sample_instance(clique_tela);
    inst_clique_tela2 = al_create_sample_instance(clique_tela2);
    inst_relogio = al_create_sample_instance(relogio);
    inst_som_fase1 = al_create_sample_instance(som_fase1);
    inst_somfase2 = al_create_sample_instance(somfase2);
    inst_missionPassed = al_create_sample_instance(missionPassed);
    inst_erro_tela = al_create_sample_instance(erro_tela);
    inst_concluido = al_create_sample_instance(concluido);


    al_attach_sample_instance_to_mixer(inst_clique_tela, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_clique_tela2, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_trilha_sonora, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_relogio, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_som_fase1, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_missionPassed, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_erro_tela, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_concluido, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_somfase2, al_get_default_mixer());

    al_set_sample_instance_playmode(inst_trilha_sonora, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(inst_somfase2, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(inst_concluido, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(inst_relogio, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(inst_som_fase1, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(inst_missionPassed, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(inst_erro_tela, ALLEGRO_PLAYMODE_ONCE);

    al_set_sample_instance_gain(inst_trilha_sonora, 0.2);
    al_set_sample_instance_gain(inst_somfase2, 0.2);
    al_set_sample_instance_gain(inst_concluido, 0.2);
    al_set_sample_instance_gain(inst_relogio, 0.4);
    al_set_sample_instance_gain(inst_som_fase1, 0.1);





    //--------------------------------------------------------------------------

    //VARIAVEIS PARA JOGAR A FASE 1
    char resposta[50] = "";
    int pos = 0;
    int erro = 0;

    int tempo_restante = 10 * 60;
    int minutos = 1;
    int segundos = 1;

    // CRIANDO UMA VÁRIAVEL DE VELOCIDADE PARA O PERSONGEM
    int velocidade_personagem = 10;

    // VARIÁVEL DE RESPOSTAS DA FASE 3
    int respostas_fase3 = 0;

    bool jogando = true;
    while (jogando) {
        ALLEGRO_EVENT evento; //criando(chamando) eventos
        al_wait_for_event(fila_eventos, &evento);
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        frame += 0.0f;
        if (frame > 4) {
            frame -= 4;
        }
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) { //Saber a posição do meu mouse
            mouseX = evento.mouse.x; // verifico a posição X
            mouseY = evento.mouse.y; // Verifico a posição Y
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            //if (evento.mouse.button & 1) {
               // tela++;
           // }
            //if (evento.mouse.button & 2) {
                //tela--;
            //}
        }

        // tela inicial do jogo
        if (tela == 0) {
            al_stop_sample_instance(inst_concluido);
            al_stop_sample_instance(inst_erro_tela);
            al_stop_sample_instance(inst_missionPassed);
            al_draw_bitmap(tela_inicial, 0, 0, 0);
            al_play_sample_instance(inst_trilha_sonora);
            //al_draw_filled_rectangle(menu.btn_x1, menu.btn_y1, menu.btn_x2, menu.btn_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= menu.btn_x1 && mouseX <= menu.btn_x2 && mouseY >= menu.btn_y1 && mouseY <= menu.btn_y2) {
                    tela++;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= menu.btn2_x1 && mouseX <= menu.btn2_x2 && mouseY >= menu.btn2_y1 && mouseY <= menu.btn2_y2) {
                    break;
                    al_play_sample_instance(inst_clique_tela);
                }

            }
        }


        // TELA DO MENU DE FASES
        if (tela == 1) {
            al_clear_to_color(al_map_rgb(0, 125, 125));// colocando a cor da tela
            al_draw_bitmap(tela_fases, 0, 0, 0);

            //al_draw_filled_rectangle(tela_fase.btn2_x1, tela_fase.btn2_y1, tela_fase.btn2_x2, tela_fase.btn2_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= tela_fase.btn_x1 && mouseX <= tela_fase.btn_x2 && mouseY >= tela_fase.btn_y1 && mouseY <= tela_fase.btn_y2) {
                    tela--;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= tela_fase.btn2_x1 && mouseX <= tela_fase.btn2_x2 && mouseY >= tela_fase.btn2_y1 && mouseY <= tela_fase.btn2_y2) {
                    tela = 10;
                    al_play_sample_instance(inst_clique_tela);
                }
            }
        }


        // TELA DA FASE 1
        if (tela == 2) {
            al_stop_sample_instance(inst_trilha_sonora);
            al_play_sample_instance(inst_relogio);
            al_play_sample_instance(inst_som_fase1);
            al_draw_bitmap(fase_1, 0, 0, 0);
            //al_draw_filled_rectangle(fase1.livro1_x1, fase1.livro1_y1, fase1.livro1_x2, fase1.livro1_y2, al_map_rgb(248, 320, 124));
            al_draw_bitmap_region(sprite, 75 * (int)frame, current_frame_y, 75, 77, pos_x, pos_y, 0);


            float prev_x = pos_x;
            float prev_y = pos_y;

            // aplica movimento (leva pos_x/pos_y para a nova posição)
            mover_personagem(evento, &pos_x, &pos_y, &frame, velocidade_personagem, &current_frame_y);

            // limita posição à tela
            delimitar(evento, &pos_x, &pos_y);

            // testa colisão com obstáculos registrados
            // se colidir, revertendo para posição anterior
            if (colisao_test(pos_x, pos_y, (int)largura_personagem, (int)altura_personagem)) {
                pos_x = prev_x;
                pos_y = prev_y;
                // opcional: printf("DEBUG: colisão, rollback para %.1f, %.1f\n", pos_x, pos_y);
            }

            /*
            ============ SISTEMA DE TEMPO ================
            */


            if (evento.type == ALLEGRO_EVENT_TIMER && evento.timer.source == timer) {
                tempo_restante--; // diminui o tempo em 1 segundo
                if (tempo_restante <= 0) {
                    tela = 6; // mensagem de erro
                }
                minutos = tempo_restante / 60;
                segundos = tempo_restante % 60;
            }
            al_draw_textf(fonte_fase2, al_map_rgb(255, 255, 0), 50, 50, ALLEGRO_ALIGN_CENTRE, "%02d:%02d", minutos, segundos);

            //SE CHEGAR NA ESTANTE 1 E ABRIR O LIVRO
            //al_draw_filled_rectangle(fase1.livro1_x1, fase1.livro1_y1, fase1.livro1_x2, fase1.livro1_y2, al_map_rgb(248, 320, 124));
            if (pos_x >= fase1.livro1_x1 && pos_x <= fase1.livro1_x2 && pos_y >= fase1.livro1_y1 && pos_y <= fase1.livro1_y2 && evento.keyboard.keycode == ALLEGRO_KEY_E) {
                tela = 7;
            }

            //SE CHAGAR NA ESTANTE 2 E ABRIR O LIVRO
            //al_draw_filled_rectangle(fase1.livro2_x1, fase1.livro2_y1, fase1.livro2_x2, fase1.livro2_y2, al_map_rgb(248, 320, 124));
            if (pos_x >= fase1.livro2_x1 && pos_x <= fase1.livro2_x2 && pos_y >= fase1.livro2_y1 && pos_y <= fase1.livro2_y2 && evento.keyboard.keycode == ALLEGRO_KEY_E) {
                tela = 8;
            }

            //SE CHEGAR NA ESTANTE ABRE O LIVRO 3
            //al_draw_filled_rectangle(fase1.livro3_x1, fase1.livro3_y1, fase1.livro3_x2, fase1.livro3_y2, al_map_rgb(248, 320, 124));
            if (pos_x >= fase1.livro3_x1 && pos_x <= fase1.livro3_x2 && pos_y >= fase1.livro3_y1 && pos_y <= fase1.livro3_y2 && evento.keyboard.keycode == ALLEGRO_KEY_E) {
                tela = 9;
            }

            //SE CHEGAR NO COMPUTADOR, APARECE TELA DE SENHA
            //al_draw_filled_rectangle(fase1.comp_x1, fase1.comp_y1, fase1.comp_x2, fase1.comp_y2, al_map_rgb(248, 320, 124));
            if (pos_x >= fase1.comp_x1 && pos_x <= fase1.comp_x2 && pos_y >= fase1.comp_y1 && pos_y <= fase1.comp_y2 && evento.keyboard.keycode == ALLEGRO_KEY_E) {
                memset(resposta, "", sizeof(resposta));
                pos = 0;
                tela = 11;

            }

            /*
               ---- Delimitação das Colisões dos Objetos da Fase 1 ----
            al_draw_filled_rectangle(mesa.btn_x1, mesa.btn_y1, mesa.btn_x2, mesa.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(mesa2.btn_x1, mesa2.btn_y1, mesa2.btn_x2, mesa2.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(bau.btn_x1, bau.btn_y1, bau.btn_x2, bau.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(quadro.btn_x1, quadro.btn_y1, quadro.btn_x2, quadro.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(pistas.btn_x1, pistas.btn_y1, pistas.btn_x2, pistas.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(mesapc.btn_x1, mesapc.btn_y1, mesapc.btn_x2, mesapc.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(estantes.btn_x1, estantes.btn_y1, estantes.btn_x2, estantes.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(pc.btn_x1, pc.btn_y1, pc.btn_x2, pc.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(placa.btn_x1, placa.btn_y1, placa.btn_x2, placa.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(estanteE.btn_x1, estanteE.btn_y1, estanteE.btn_x2, estanteE.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(mesa3.btn_x1, mesa3.btn_y1, mesa3.btn_x2, mesa3.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(estantes2.btn_x1, estantes2.btn_y1, estantes2.btn_x2, estantes2.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(pcfora.btn_x1, pcfora.btn_y1, pcfora.btn_x2, pcfora.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(sofa.btn_x1, sofa.btn_y1, sofa.btn_x2, sofa.btn_y2, al_map_rgb(248, 320, 124));
            al_draw_filled_rectangle(pc2.btn_x1, pc2.btn_y1, pc2.btn_x2, pc2.btn_y2, al_map_rgb(248, 320, 124));
            */


            // SE CHEGAR NO ESPAÇO DELIMITADO AO TECLAR E, APARECE TELA DE ERRO
            //al_draw_filled_rectangle(fase1.erro_x1, fase1.erro_y1, fase1.erro_x2, fase1.erro_y2, al_map_rgb(100, 320, 124));
            if (pos_x >= fase1.erro_x1 && pos_x <= fase1.erro_x2 && pos_y >= fase1.erro_y1 && pos_y <= fase1.erro_y2 && evento.keyboard.keycode == ALLEGRO_KEY_E) { tela = 6; }



        }





        // TELA DE PARABÉNS COM BOTOÕES PARA IR PRA PROXIMA FASE

        if (tela == 3) {
            if (!missaoConcluida) {
                al_stop_sample_instance(inst_relogio);
                al_stop_sample_instance(inst_som_fase1);
                al_play_sample_instance(inst_missionPassed);
                missaoConcluida = true;
            }





            al_clear_to_color(al_map_rgb(0, 125, 125));
            al_draw_bitmap(fase_concluida, 0, 0, 0);
            //al_draw_filled_rectangle(prox_fase.btn2_x1, prox_fase.btn2_y1, prox_fase.btn2_x2, prox_fase.btn2_y2, al_map_rgb(100, 20, 48));
            if (evento.mouse.button & 1) {
                if (mouseX >= prox_fase.btn_x1 && mouseX <= prox_fase.btn_x2 && mouseY >= prox_fase.btn_y1 && mouseY <= prox_fase.btn_y2) {
                    tela = 4;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= prox_fase.btn2_x1 && mouseX <= prox_fase.btn2_x2 && mouseY >= prox_fase.btn2_y1 && mouseY <= prox_fase.btn2_y2) {
                    tela = 0;
                    al_play_sample_instance(inst_clique_tela);
                }
            }
        }
        else {
            missaoConcluida = false;
        }

        // TELA DE FASES COM A SEGUNDA FASE DESBLOQUEADA
        if (tela == 4) {
            al_stop_sample_instance(inst_missionPassed);
            al_clear_to_color(al_map_rgb(0, 125, 125));
            al_draw_bitmap(tela_fases_2, 0, 0, 0);
            //al_draw_filled_rectangle(tela_fase2.btn_x1, tela_fase2.btn_y1, tela_fase2.btn_x2, tela_fase2.btn_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= tela_fase2.btn_x1 && mouseX <= tela_fase2.btn_x2 && mouseY >= tela_fase2.btn_y1 && mouseY <= tela_fase2.btn_y2) {
                    tela = 12;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= tela_fase.btn_x1 && mouseX <= tela_fase.btn_x2 && mouseY >= tela_fase.btn_y1 && mouseY <= tela_fase.btn_y2) {
                    tela = 0;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= tela_fase.btn2_x1 && mouseX <= tela_fase.btn2_x2 && mouseY >= tela_fase.btn2_y1 && mouseY <= tela_fase.btn2_y2) {
                    tela = 2;
                    al_play_sample_instance(inst_clique_tela);
                }

            }
        }

        // TELA COM A FASE 2
        if (tela == 5) {
            al_play_sample_instance(inst_somfase2);

            if (evento.keyboard.keycode == ALLEGRO_KEY_X) {
                tela = 13;
            }


            // andando com personagem
            mover_personagem2(evento, &pos_x, &pos_y, &frame, velocidade_personagem, &current_frame_y);
            //velocidade_personagem = 50;

            //DELIMITANDO O PERSONGAME NA TELA
            delimitar(evento, &pos_x, &pos_y);



            if (evento.type == ALLEGRO_EVENT_TIMER) {
                spawn_timer += 1.0 / 60;

                if (spawn_timer >= spawn_interval) {
                    spawn_answer(pergunta_atual.resposta);
                    spawn_timer = 0;
                }

                update_answers();

                //==================VERIFICANDO A COLISÃO =======================
                verificar_colisoes(pos_x, pos_y, 64, 64, 80, 40);



                // ===================  DESENHO ============================
                //CRIANDO A TELA DA FASE
                al_draw_bitmap(fase_2, 0, 0, 0);

                //DEFININDO A POSIÇÃO DA SPRITE NA TELA
                pos_y = 587;
                //DESENHANDO A SPRITE
                al_draw_bitmap_region(sprite, 75 * (int)frame, current_frame_y, 75, 77, pos_x, pos_y, 0);

                // Pergunta no topo
                al_draw_text(fonte, al_map_rgb(255, 255, 255), 640, 50, ALLEGRO_ALIGN_CENTER, pergunta_atual.texto);

                // TEXTO COM A PONTUAÇÃO
                char texto_pontos[32];
                sprintf(texto_pontos, "pontos: %d", pontos);
                al_draw_text(font, al_map_rgb(255, 255, 0), 50, 50, 0, texto_pontos);
                // Respostas caindo
                draw_answers(fonte_fase2);

                if (pontos == 50) {
                    tela = 13;
                    pontos = 0;
                }

                al_flip_display();
            }













        }
        ///TELA DE MENSAGEM DE ERRO
        if (tela == 6) {
            al_stop_sample_instance(inst_relogio);
            al_stop_sample_instance(inst_som_fase1);
            if (!errofase1) {
                al_play_sample_instance(inst_erro_tela);
                errofase1 = true;
            }


            al_draw_bitmap(mensagem_erro, 0, 0, 0);
            //al_draw_filled_rectangle(menu.btn3_x1, menu.btn3_y1, menu.btn3_x2, menu.btn3_y2, al_map_rgb(255, 154, 32));
            //al_draw_filled_rectangle(menu.btn4_x1, menu.btn4_y1, menu.btn4_x2, menu.btn4_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= menu.btn4_x1 && mouseX <= menu.btn4_x2 && mouseY >= menu.btn4_y1 && mouseY <= menu.btn4_y2) {
                    tela = 1;
                    al_play_sample_instance(inst_clique_tela);
                    al_stop_sample_instance(inst_erro_tela);

                }
                if (mouseX >= menu.btn3_x1 && mouseX <= menu.btn3_x2 && mouseY >= menu.btn3_y1 && mouseY <= menu.btn3_y2) {
                    tela = 0;
                    al_play_sample_instance(inst_clique_tela);
                    al_stop_sample_instance(inst_erro_tela);
                }
            }
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { tela = 2; }


        }
        else {
            errofase1 = false;
        }

        //DESENHANDO TELA DO LIVRO COM ENIGMA 1
        if (tela == 7) {
            al_draw_bitmap(livro1, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { tela = 2; }
        }

        //DESENHANDO TELA DO LIVRO COM ENIGMA 2;
        if (tela == 8) {
            al_draw_bitmap(livro2, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { tela = 2; }
        }

        //DESENHANDO TELA DO LIVRO COM ENIGMA 3

        if (tela == 9) {
            al_draw_bitmap(livro3, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { tela = 2; }
        }

        // TELA COM GUANABARA NA FASE 1
        if (tela == 10) {
            al_draw_bitmap(guanabara_fase1, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                tela = 2;
                al_play_sample_instance(inst_clique_tela);
            }
        }

        /*
        ============== DESENHANDO A TELA DO COMUPTADOR COM A MECANICA ====================
        */

        if (tela == 11) {
            /*
            ======= DESENHANDO A TELA ==========
            */
            al_draw_bitmap(tela_senha, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                tela = 2;
            }


            /*
            ======= CRIAÇÃO DA MECÂNICA DE RESPOSTAS =============
            */
            if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    printf("Resposta final: %s\n", resposta);
                    if (strcmp(resposta, "primeiro") == 0 || strcmp(resposta, "primeiro mes") == 0 || strcmp(resposta, "01") == 0) {
                        tela = 3;
                        pos = 0;
                        resposta[0] = '\0';
                        erro = 0;
                    }
                    else {
                        pos = 0;
                        resposta[0] = '\0';
                        erro++;
                    }
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && pos > 0) {
                    pos--;
                    resposta[pos] = '\0';
                    erro = 0;
                }
                else if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {
                    resposta[pos++] = (char)evento.keyboard.unichar;
                    resposta[pos] = '\0';
                    erro = 0;


                }
            }

            //PRINTANDO MENSAGEM DE ERRO
            if (erro != 0) {
                al_draw_textf(font, al_map_rgb(255, 0, 0), 851, 507, ALLEGRO_ALIGN_CENTRE, "RESPOSTA INCORRETA");
            }
            //PRINTANDO O TEXTO DIGITADO NA TELA
            al_draw_textf(font, al_map_rgb(255, 255, 255), 851, 507, ALLEGRO_ALIGN_CENTRE, "%s", resposta);
        }


        // TELA DE FASE COM GUANABARA 2

        if (tela == 12) {
            al_draw_bitmap(guanabara_fase2, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                tela = 5;
                al_play_sample_instance(inst_clique_tela);
            }
        }


        // TELA DE PARABÉNS COM BOTOÕES PARA IR PRA PROXIMA FASE - 2

        if (tela == 13) {
            al_stop_sample_instance(inst_somfase2);
            if (!missaoConcluida2) {
                al_play_sample_instance(inst_missionPassed);
                missaoConcluida2 = true;
            }
            al_clear_to_color(al_map_rgb(0, 125, 125));
            al_draw_bitmap(fase_concluida, 0, 0, 0);
            //al_draw_filled_rectangle(prox_fase.btn2_x1, prox_fase.btn2_y1, prox_fase.btn2_x2, prox_fase.btn2_y2, al_map_rgb(100, 20, 48));
            if (evento.mouse.button & 1) {
                if (mouseX >= prox_fase.btn_x1 && mouseX <= prox_fase.btn_x2 && mouseY >= prox_fase.btn_y1 && mouseY <= prox_fase.btn_y2) {
                    tela = 14;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= prox_fase.btn2_x1 && mouseX <= prox_fase.btn2_x2 && mouseY >= prox_fase.btn2_y1 && mouseY <= prox_fase.btn2_y2) {
                    tela = 0;
                    al_play_sample_instance(inst_clique_tela);
                }
            }
        }
        else {
            missaoConcluida2 = false;
        }


        //--------------------------FASE-3-----------------------------//
        // 

        //TELA COM A FASE 3 DESBLOQUEADA
        if (tela == 14) {

            al_stop_sample_instance(inst_missionPassed);
            al_clear_to_color(al_map_rgb(0, 0, 144));
            al_draw_bitmap(tela_fases_3, 0, 0, 0);
            //al_draw_filled_rectangle(tela_fase3.btn_x1, tela_fase3.btn_y1, tela_fase3.btn_x2, tela_fase3.btn_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= tela_fase2.btn_x1 && mouseX <= tela_fase2.btn_x2 && mouseY >= tela_fase2.btn_y1 && mouseY <= tela_fase2.btn_y2) {
                    tela = 12;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= tela_fase.btn_x1 && mouseX <= tela_fase.btn_x2 && mouseY >= tela_fase.btn_y1 && mouseY <= tela_fase.btn_y2) {
                    tela = 0;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= tela_fase.btn2_x1 && mouseX <= tela_fase.btn2_x2 && mouseY >= tela_fase.btn2_y1 && mouseY <= tela_fase.btn2_y2) {
                    tela = 2;
                    al_play_sample_instance(inst_clique_tela);
                }
                if (mouseX >= tela_fase3.btn_x1 && mouseX <= tela_fase3.btn_x2 && mouseY >= tela_fase3.btn_y1 && mouseY <= tela_fase3.btn_y2) {
                    tela = 15;
                    al_play_sample_instance(inst_clique_tela);
                }

            }


        }

        //TELA DE FASE COM O GUANABARA 3
        if (tela == 15) {
            al_stop_sample_instance(inst_erro_tela);
            al_draw_bitmap(guanabara_fase3, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                tela = 16;
                al_play_sample_instance(inst_clique_tela);
            }
        }

        //TELA COM A FASE 3
        if (tela == 16) {
            respostas_fase3 = 0;
            al_clear_to_color(al_map_rgb(148, 0, 144));
            al_draw_bitmap(fase_3, 0, 0, 0);
            //al_draw_filled_rectangle(play.btn_x1, play.btn_y1, play.btn_x2, play.btn_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= play.btn_x1 && mouseX <= play.btn_x2 && mouseY >= play.btn_y1 && mouseY <= play.btn_y2) { tela = 17; }
                al_play_sample_instance(inst_clique_tela2);
            }
        }

        //TELA MENSAGENS


        if (tela == 17) {
            al_draw_bitmap(tela_phishing1, 0, 0, 0);

            //sprintf(respostas_fase3, "pontos: %d", respostas_fase3);
            al_draw_text(font, al_map_rgb(255, 255, 0), 50, 50, 0, respostas_fase3);

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && (evento.mouse.button & 1)) {
                if (mouseX >= peixe.btn_x1 && mouseX <= peixe.btn_x2 && mouseY >= peixe.btn_y1 && mouseY <= peixe.btn_y2) {
                    tela = 19;
                    al_play_sample_instance(inst_clique_tela2);
                    continue;
                }
                if (mouseX >= phishing.btn_x1 && mouseX <= phishing.btn_x2 && mouseY >= phishing.btn_y1 && mouseY <= phishing.btn_y2) {
                    tela = 18;
                    al_play_sample_instance(inst_clique_tela2);
                    continue;
                }
                if (mouseX >= legitimo.btn_x1 && mouseX <= legitimo.btn_x2 && mouseY >= legitimo.btn_y1 && mouseY <= legitimo.btn_y2) {
                    respostas_fase3 += 10;
                    al_play_sample_instance(inst_clique_tela2);
                    tela = 18;
                    continue;
                }
            }
        }

        if (tela == 18) {
            al_draw_bitmap(tela_phishing2, 0, 0, 0);

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && (evento.mouse.button & 1)) {
                if (mouseX >= peixe.btn_x1 && mouseX <= peixe.btn_x2 && mouseY >= peixe.btn_y1 && mouseY <= peixe.btn_y2) {
                    tela = 20;
                    al_play_sample_instance(inst_clique_tela2);
                    continue;
                }

                if (mouseX >= phishing.btn_x1 && mouseX <= phishing.btn_x2 && mouseY >= phishing.btn_y1 && mouseY <= phishing.btn_y2) {
                    respostas_fase3 += 10;
                    al_play_sample_instance(inst_clique_tela2);
                    tela = 31;
                    continue;
                }

                if (mouseX >= legitimo.btn_x1 && mouseX <= legitimo.btn_x2 && mouseY >= legitimo.btn_y1 && mouseY <= legitimo.btn_y2) {
                    tela = 31;
                    al_play_sample_instance(inst_clique_tela2);
                    continue;
                }
            }
        }

        if (tela == 31) {
            al_draw_bitmap(tela_phishing3, 0, 0, 0);

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && (evento.mouse.button & 1)) {
                if (mouseX >= peixe.btn_x1 && mouseX <= peixe.btn_x2 && mouseY >= peixe.btn_y1 && mouseY <= peixe.btn_y2) {
                    //tela = 21;
                    //continue;
                    al_play_sample_instance(inst_clique_tela2);
                }

                if (mouseX >= phishing.btn_x1 && mouseX <= phishing.btn_x2 && mouseY >= phishing.btn_y1 && mouseY <= phishing.btn_y2) {
                    respostas_fase3 += 10;
                    al_play_sample_instance(inst_clique_tela2);
                    tela = 32;
                    continue;
                }

                if (mouseX >= legitimo.btn_x1 && mouseX <= legitimo.btn_x2 && mouseY >= legitimo.btn_y1 && mouseY <= legitimo.btn_y2) {
                    tela = 32;
                    al_play_sample_instance(inst_clique_tela2);
                    continue;
                }
            }
        }

        if (tela == 32) {
            al_draw_bitmap(tela_phishing4, 0, 0, 0);

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && (evento.mouse.button & 1)) {
                if (mouseX >= peixe.btn_x1 && mouseX <= peixe.btn_x2 && mouseY >= peixe.btn_y1 && mouseY <= peixe.btn_y2) {
                    //tela = 22;
                    //continue;
                    al_play_sample_instance(inst_clique_tela2);
                }

                if (mouseX >= phishing.btn_x1 && mouseX <= phishing.btn_x2 && mouseY >= phishing.btn_y1 && mouseY <= phishing.btn_y2) {
                    tela = 33;
                    al_play_sample_instance(inst_clique_tela2);
                    continue;
                }

                if (mouseX >= legitimo.btn_x1 && mouseX <= legitimo.btn_x2 && mouseY >= legitimo.btn_y1 && mouseY <= legitimo.btn_y2) {
                    respostas_fase3 += 10;
                    al_play_sample_instance(inst_clique_tela2);
                    tela = 33;
                    continue;
                }
            }

        }

        if (tela == 33) {
            al_draw_bitmap(tela_phishing5, 0, 0, 0);

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && (evento.mouse.button & 1)) {
                if (mouseX >= peixe.btn_x1 && mouseX <= peixe.btn_x2 && mouseY >= peixe.btn_y1 && mouseY <= peixe.btn_y2) {
                    //tela = 23;
                    // al_play_sample_instance(inst_clique_tela2);
                    //continue;
                }

                if (mouseX >= phishing.btn_x1 && mouseX <= phishing.btn_x2 && mouseY >= phishing.btn_y1 && mouseY <= phishing.btn_y2) {
                    tela = 34;
                    al_play_sample_instance(inst_clique_tela2);
                    continue;
                }

                if (mouseX >= legitimo.btn_x1 && mouseX <= legitimo.btn_x2 && mouseY >= legitimo.btn_y1 && mouseY <= legitimo.btn_y2) {
                    respostas_fase3 += 10;
                    al_play_sample_instance(inst_clique_tela2);
                    tela = 34;
                    continue;


                }
            }
        }

        if (tela == 34) {
            al_draw_bitmap(tela_phishing6, 0, 0, 0);

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && (evento.mouse.button & 1)) {
                if (mouseX >= peixe.btn_x1 && mouseX <= peixe.btn_x2 && mouseY >= peixe.btn_y1 && mouseY <= peixe.btn_y2) {
                    //tela = 24;
                    // al_play_sample_instance(inst_clique_tela2);
                    //continue;
                }

                if (mouseX >= phishing.btn_x1 && mouseX <= phishing.btn_x2 && mouseY >= phishing.btn_y1 && mouseY <= phishing.btn_y2) {
                    respostas_fase3 += 10;
                    al_play_sample_instance(inst_clique_tela2);
                    if (respostas_fase3 >= 50) {
                        tela = 25; //TELA FINAL DO JOGO
                    }
                    else {
                        tela = 40; // TELA DE ERRO FASE 3
                    }
                    continue;

                }

                if (mouseX >= legitimo.btn_x1 && mouseX <= legitimo.btn_x2 && mouseY >= legitimo.btn_y1 && mouseY <= legitimo.btn_y2) {
                    if (respostas_fase3 >= 50) {
                        tela = 25; //TELA FINAL DO JOGO
                        al_play_sample_instance(inst_clique_tela2);
                    }
                    else {
                        tela = 40; // TELA DE ERRO FASE 3
                        al_play_sample_instance(inst_clique_tela2);
                    }
                    continue;

                }
            }
        }

        if (tela == 19) {
            al_draw_bitmap(phishing_consulta, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                tela = 17;
                al_play_sample_instance(inst_clique_tela2);
            }
        }

        if (tela == 20) {
            al_draw_bitmap(phishing_consulta, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                tela = 18;
                al_play_sample_instance(inst_clique_tela2);
            }
        }
        if (tela == 21) {
            al_draw_bitmap(phishing_consulta, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                tela = 31;
                al_play_sample_instance(inst_clique_tela2);
            }
        }

        if (tela == 22) {
            al_draw_bitmap(phishing_consulta, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                tela = 32;
                al_play_sample_instance(inst_clique_tela2);
            }
        }

        if (tela == 23) {
            al_draw_bitmap(phishing_consulta, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                tela = 33;
                al_play_sample_instance(inst_clique_tela2);
            }
        }

        if (tela == 24) {
            al_draw_bitmap(phishing_consulta, 0, 0, 0);
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                tela = 34;
                al_play_sample_instance(inst_clique_tela2);
            }
        }

        if (tela == 40) {
            al_draw_bitmap(erro_fase3, 0, 0, 0);
            if (!errofase3) {
                al_play_sample_instance(inst_erro_tela);
                errofase3 = true;
            }

            //al_draw_filled_rectangle(exit.btn_x1, exit.btn_y1, exit.btn_x2, exit.btn_y2, al_map_rgb(255, 154, 32));
            //al_draw_filled_rectangle(try.btn_x1, try.btn_y1, try.btn_x2, try.btn_y2, al_map_rgb(255, 0, 0));

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && (evento.mouse.button & 1)) {
                if (mouseX >= exit.btn_x1 && mouseX <= exit.btn_x2 && mouseY >= exit.btn_y1 && mouseY <= exit.btn_y2) {
                    tela = 0;
                    al_play_sample_instance(inst_clique_tela);

                }
                else if (mouseX >= try.btn_x1 && mouseX <= try.btn_x2 && mouseY >= try.btn_y1 && mouseY <= try.btn_y2) {
                    tela = 15;
                    al_play_sample_instance(inst_clique_tela);
                }
            }

        }
        else {
            errofase3 = false;
        }



        //--------------TELA FINAL-------------------//


        if (tela == 25) {
            al_draw_bitmap(tela_final, 0, 0, 0);
            al_play_sample_instance(inst_concluido);

        }





        al_flip_display();

    }

    // destruindo eventos
    al_destroy_font(font);
    al_destroy_font(fonte_fase2);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(tela_inicial);
    al_destroy_bitmap(tela_fases);
    al_destroy_bitmap(tela_final);
    al_destroy_bitmap(fase_1);
    al_destroy_bitmap(tela_fases_2);
    al_destroy_bitmap(tela_fases_3);
    al_destroy_bitmap(fase_concluida);
    al_destroy_bitmap(mensagem_erro);
    al_destroy_bitmap(sprite);
    al_destroy_bitmap(livro1);
    al_destroy_bitmap(livro2);
    al_destroy_bitmap(livro3);
    al_destroy_bitmap(guanabara_fase1);
    al_destroy_bitmap(tela_senha);
    al_destroy_bitmap(guanabara_fase2);
    al_destroy_bitmap(guanabara_fase3);
    al_destroy_bitmap(fase_2);
    al_destroy_bitmap(fase_3);
    al_destroy_bitmap(tela_phishing1);
    al_destroy_bitmap(erro_fase3);

    al_destroy_sample(acerto);
    al_destroy_sample(erro_tela);
    al_destroy_sample(somfase2);
    al_destroy_sample(clique_tela);
    al_destroy_sample(clique_tela2);
    al_destroy_sample(relogio);
    al_destroy_sample(som_fase1);
    al_destroy_sample(missionPassed);
    al_destroy_sample(concluido);


    al_destroy_sample_instance(inst_trilha_sonora);
    al_destroy_sample_instance(inst_erro_tela);
    al_destroy_sample_instance(inst_acerto);
    al_destroy_sample_instance(inst_somfase2);
    al_destroy_sample_instance(inst_clique_tela);
    al_destroy_sample_instance(inst_clique_tela2);
    al_destroy_sample_instance(inst_relogio);
    al_destroy_sample_instance(inst_som_fase1);
    al_destroy_sample_instance(inst_missionPassed);
    al_destroy_sample_instance(inst_concluido);
    return 0;
}