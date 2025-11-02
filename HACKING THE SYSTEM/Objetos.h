// --- Arquivos Objetos --- 


enum {JOGADOR, PROJETIL, INIMIGOS};

struct Jogador
{
	int ID;
	int x;
	int y;
	int vidas;
	int velocidade;
	int borda_x;
	int borda_y;
	int pontos;
};