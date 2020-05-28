#ifndef IO_H
#define IO_H

//Verifica se todos os tipos de barcos tem pelo menos 1 e retorna o total de barcos inseridos
int check(int num_type[]);
//Funcao para libertar buffer do scanf
void clean_buffer();

#ifdef MAT

//Verifica se as coordenadas dadas pertencem ao tabuleiro ou não
int inside_table(Game *player, int row, int col);
//Pede as coordenadas e a rotacao do barco ao jogador e insere caso seja possivel
void insert_ships(Game *player, int flag);
//Analisa os tiros
int aim_fire(Game *player, int row, int col);

#else

int inside_table(QuadTree *player, int row, int col);
void insert_ships(QuadTree *player, int X, int Y, int Lx, int Ly, int flag);
int aim_fire(QuadTree *player, int row, int col, int X, int Y, int Lx, int Ly);

#endif
#endif
