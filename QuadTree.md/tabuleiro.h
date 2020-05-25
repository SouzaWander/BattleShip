#ifndef  TABULEIRO_H
#define  TABULEIRO_H

#ifdef MAT

typedef struct{
  Ship *ship;
  int shot; 
}Cell;

typedef struct{
  int num_ships; //Numero total de barcos
  int size;  //Size do tabuleiro
  Cell **matrix; //matriz do jogo
  Ship *ships; //O array com os barcos na matriz
}Game;

//Cria a tabela e aloca a memoria necessaria
void create_table(Game *player);
//Para fazer print da matriz ao colocar os barcos
void print_table(Game player);
//Para fazer print das matrizes ao jogar
void print_game(Game player, Game opponent);
//Liberta toda a memoria alocada
void free_memory(Game *player1, Game *player2, int num);

#endif
#endif
