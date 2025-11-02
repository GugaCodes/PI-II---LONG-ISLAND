#include "delimitacao.h"

void delimitar(ALLEGRO_EVENT evento, float *pos_x, float *pos_y) {
    if (*pos_x >= 1280 - 55) { *pos_x = *pos_x - 10; }
    if (*pos_x <= 0 - 8) { *pos_x = *pos_x + 10; }
    if (*pos_y >= 720 - 75) { *pos_y = *pos_y - 10; }
    if (*pos_y <= 0 + 150) { *pos_y = *pos_y + 10; }
}
