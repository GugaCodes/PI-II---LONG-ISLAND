#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

struct botão {
    int btn_x1, btn_x2, btn_y1, btn_y2;
    int btn2_x1, btn2_x2, btn2_y1, btn2_y2;
};

struct espaço {
    int esp_x1, esp_x2, esp_y1, esp_y2;
    int livro1_x1, livro1_x2, livro1_y1, livro1_y2;
};

int main() {

    //criando uma váriavel de controle de telas

    int tela = 0;
    int height = 720, width = 1280;

    //DELIMMITANDO POSIÇÃO INICIAL DO PERSONAGEM

    float pos_x = 150, pos_y = 450, pos_x1 = 450, pos_Y2 = 450;




    // VARIAVEIS DO MOUSE
    float mouseX, mouseY;

    //CRIANDO AS STRICT DO BOTÃO PRNCIPAL

    struct botão menu;

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

    //CRIANDO A STRUCT DOS BOTÕES NA TELA DE FASES

    struct botão tela_fase;

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

    //CRIANDO STRUCT PARA IR PARA FASE 2

    struct botão tela_fase2;

    //BOTÃO PARA IR PARA FASE 2

    tela_fase2.btn_x1 = 460;
    tela_fase2.btn_x2 = 820;
    tela_fase2.btn_y1 = 180;
    tela_fase2.btn_y2 = 625;

    //STRUCT PARA TELA DE PROXIMA FASE

    struct botão prox_fase;

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

    struct espaço fase1;

    fase1.esp_x1 = 500;
    fase1.esp_x2 = 690;
    fase1.esp_y1 = 660;
    fase1.esp_y2 = 720;

    fase1.livro1_x1 = 230;
    fase1.livro1_x2 = 325;
    fase1.livro1_y1 = 615;
    fase1.livro1_y2 = 695;

    



    // inciciando biblioteca
    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();


    ALLEGRO_DISPLAY* janela = al_create_display(width, height); /// criação da janela
    al_set_window_position(janela, 200, 200); // posição inicial da janela

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); // definindo "FPS"
    ALLEGRO_BITMAP* tela_inicial = al_load_bitmap("./TELA_INICIAL.png");
    ALLEGRO_BITMAP* tela_fases = al_load_bitmap("TELA_FASES.png");
    ALLEGRO_BITMAP* fase_1 = al_load_bitmap("FASE1-PT.png");
    ALLEGRO_BITMAP* tela_fases_2 = al_load_bitmap("TELA-FASES-2.png");
    ALLEGRO_BITMAP* fase_concluida = al_load_bitmap("CONGRATULATIONS.png");
    ALLEGRO_BITMAP* livro1 = al_load_bitmap("LIVRO1.png");

    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // criação da fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_start_timer(timer);



    bool jogando = true;
    while (jogando) {
        ALLEGRO_EVENT evento; //criando(chamando) eventos
        al_wait_for_event(fila_eventos, &evento);
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }




        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) { //Saber a posição do meu mouse
            mouseX = evento.mouse.x; // verifico a posição X
            mouseY = evento.mouse.y; // Verifico a posição Y
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            //if (evento.mouse.button & 1) {
               // tela++;
           // }
            if (evento.mouse.button & 2) {
                tela--;
            }
        }


        if (evento.keyboard.keycode == ALLEGRO_KEY_T) {
            tela = 1;
        }
        else if (evento.keyboard.keycode == ALLEGRO_KEY_R) {
            tela = 0;
        }
        else if (evento.keyboard.keycode == ALLEGRO_KEY_Y) {
            tela = 3;
        }

        // tela inicial do jogo
        if (tela == 0) {
            al_draw_bitmap(tela_inicial, 0, 0, 0);
            //al_draw_filled_rectangle(menu.btn_x1, menu.btn_y1, menu.btn_x2, menu.btn_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= menu.btn_x1 && mouseX <= menu.btn_x2 && mouseY >= menu.btn_y1 && mouseY <= menu.btn_y2) { tela++; }
                if (mouseX >= menu.btn2_x1 && mouseX <= menu.btn2_x2 && mouseY >= menu.btn2_y1 && mouseY <= menu.btn2_y2) { break; }
                
            }
        }


        // TELA DO MENU DE FASES
        if (tela == 1) {
            al_clear_to_color(al_map_rgb(0, 125, 125));// colocando a cor da tela
            al_draw_bitmap(tela_fases, 0, 0, 0);
            //al_draw_filled_rectangle(tela_fase.btn2_x1, tela_fase.btn2_y1, tela_fase.btn2_x2, tela_fase.btn2_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= tela_fase.btn_x1 && mouseX <= tela_fase.btn_x2 && mouseY >= tela_fase.btn_y1 && mouseY <= tela_fase.btn_y2) { tela--; }
                if (mouseX >= tela_fase.btn2_x1 && mouseX <= tela_fase.btn2_x2 && mouseY >= tela_fase.btn2_y1 && mouseY <= tela_fase.btn2_y2) { tela++; }
            }
        }


        // TELA DA FASE 1
        if (tela == 2) {
            al_draw_bitmap(fase_1, 0, 0, 0);
            al_draw_filled_circle(pos_x, pos_y, 10, al_map_rgb(0, 0, 255));
            //al_draw_filled_rectangle(fase1.livro1_x1, fase1.livro1_y1, fase1.livro1_x2, fase1.livro1_y2, al_map_rgb(248, 320, 124));

            // andando com mouse
            if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) { pos_x += 5; }// seta pra direita
            if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) { pos_x -= 5; }//seta para esquerda
            if (evento.keyboard.keycode == ALLEGRO_KEY_UP) { pos_y -= 5; }// Seta para cima
            if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) { pos_y += 5; }// seta para baixo

            //delimitando bolinha ao tamanho da tela
            if (pos_x >= 1280 - 25) { pos_x = pos_x - 40; }
            if (pos_x <= 0 + 25) { pos_x = pos_x + 40; }
            if (pos_y >= 720 - 25) { pos_y = pos_y - 40; }
            if (pos_y <= 0 + 25) { pos_y = pos_y + 40; }

            //SE CHEGAR NA ESTANTE 1 E ABRIR O LIVRO
            if (pos_x >= fase1.livro1_x1 && pos_x <= fase1.livro1_x2 && pos_y >= fase1.livro1_y1 && pos_y <= fase1.livro1_y2 && evento.keyboard.keycode == ALLEGRO_KEY_F) { 
                tela = 3;
            }
               
            //SE CHEGAR NA PORTA PASSA DE TELA
            //al_draw_filled_rectangle(fase1.esp_x1, fase1.esp_y1, fase1.esp_x2, fase1.esp_y2, al_map_rgb(248, 320, 124));
            if (pos_x >= fase1.esp_x1 && pos_x <= fase1.esp_x2 && pos_y >= fase1.esp_y1 && pos_y <= fase1.esp_y2 && evento.keyboard.keycode == ALLEGRO_KEY_F) { tela = 4; }
            if (pos_x >= fase1.livro1_x1 && pos_x <= fase1.livro1_x2 && pos_y >= fase1.livro1_y1 && pos_y <= fase1.livro1_y2 && evento.keyboard.keycode == ALLEGRO_KEY_F) { tela = 3; }
        }

        //DESENHANDO TELA DO LIVRO COM ENIGMA 1
        if (tela == 3) {
            al_draw_bitmap(livro1, 0, 0, 0);
        }
        
        // TELA DE PARABÉNS COM BOTOÕES PARA IR PRA PROXIMA FASE

        if (tela == 4) {
            al_clear_to_color(al_map_rgb(0, 125, 125));
            al_draw_bitmap(fase_concluida, 0, 0, 0);
            //al_draw_filled_rectangle(prox_fase.btn2_x1, prox_fase.btn2_y1, prox_fase.btn2_x2, prox_fase.btn2_y2, al_map_rgb(100, 20, 48));
            if (evento.mouse.button & 1) {
                if (mouseX >= prox_fase.btn_x1 && mouseX <= prox_fase.btn_x2 && mouseY >= prox_fase.btn_y1 && mouseY <= prox_fase.btn_y2) { tela++; }
                if (mouseX >= prox_fase.btn2_x1 && mouseX <= prox_fase.btn2_x2 && mouseY >= prox_fase.btn2_y1 && mouseY <= prox_fase.btn2_y2) { tela = 0; }
            }
        }

        // TELA DE FASES COM A SEGUNDA FASE DESBLOQUEADA
        if (tela == 5) {
            al_clear_to_color(al_map_rgb(0, 125, 125));
            al_draw_bitmap(tela_fases_2, 0, 0, 0);
            //al_draw_filled_rectangle(tela_fase2.btn_x1, tela_fase2.btn_y1, tela_fase2.btn_x2, tela_fase2.btn_y2, al_map_rgb(255, 154, 32));
            if (evento.mouse.button & 1) {
                if (mouseX >= tela_fase2.btn_x1 && mouseX <= tela_fase2.btn_x2 && mouseY >= tela_fase2.btn_y1 && mouseY <= tela_fase2.btn_y2) { tela++; }
                if (mouseX >= tela_fase.btn_x1 && mouseX <= tela_fase.btn_x2 && mouseY >= tela_fase.btn_y1 && mouseY <= tela_fase.btn_y2) { tela = 0; }

            }
        }
        if (tela == 6) {
            al_clear_to_color(al_map_rgb(0, 125, 125));
            
        }
        



        al_flip_display();

    }

    // destruindo eventos
    al_destroy_font(font);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(tela_inicial);
    al_destroy_bitmap(tela_fases);
    al_destroy_bitmap(fase_1);
    al_destroy_bitmap(tela_fases_2);
    al_destroy_bitmap(fase_concluida);
    al_destroy_bitmap(livro1);


    return 0;
}