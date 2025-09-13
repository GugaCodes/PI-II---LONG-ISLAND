#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>

int main() {

    // inciciando biblioteca
    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();


    ALLEGRO_DISPLAY* janela = al_create_display(1280, 720); /// criação da janela
    al_set_window_position(janela, 200, 200); // posição inicial da janela

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // definindo "FPS"

    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue(); // criação da fila de eventos
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_start_timer(timer);

    float pos_x = 150, pos_y = 450, pos_x1 = 450, pos_Y2 = 450;// posição da bolinha


    bool jogando = true;
    while (jogando) {
        ALLEGRO_EVENT evento; //criando(chamando) eventos
        al_wait_for_event(fila_eventos, &evento);
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        // andando com mouse 
        else if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) {// seta pra direita
            pos_x += 20;
        }
        else if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) { //seta para esquerda
            pos_x -= 20;
        }
        else if (evento.keyboard.keycode == ALLEGRO_KEY_UP) { // Seta para cima
            pos_y -= 20;
        }
        else if (evento.keyboard.keycode == ALLEGRO_KEY_DOWN) { // seta para baixo
            pos_y += 20;
        }

        al_clear_to_color(al_map_rgb(125, 125, 125));// colocando a cor da tela
        al_draw_filled_circle(pos_x, pos_y, 50, al_map_rgb(0, 0, 255));// desenhando bolinha 1
        al_draw_filled_circle(pos_x1, pos_Y2, 50, al_map_rgb(124, 200, 50));
        al_draw_text(font, al_map_rgb(0, 0, 0), 15, 20, 0, "Hackin the Sistem\n testando ideia de livro\n para que consiga passar a mensagem");//colocando texto na tela
        al_flip_display();


        //delimitando bolinha ao tamanho da tela
        if (pos_x >= 1280 - 25) {
            pos_x = pos_x - 40;
        }
        else if (pos_x <=0 + 25) {
            pos_x = pos_x + 40;
        }
        else if (pos_y >= 720 - 25) {
            pos_y = pos_y - 40;
        }
        else if (pos_y <= 0 + 25) {
			pos_y = pos_y + 40;

        }

        //criando a entrada de dados a partir de uma condição
        if (pos_x == pos_x1 && pos_y == pos_Y2) {
            int resultado = 2;   
            al_draw_text(font,al_map_rgb(3, 0, 0), 400, 360, 0, "Descubra para que valor de X obteremos a saída y=4 se 2X-2 = 4");
            al_flip_display();

        }
    }

    // destruindo eventos
    al_destroy_font(font);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}