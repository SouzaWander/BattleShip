#ifdef QUAD

#ifndef  QUADTREE_H
#define  QUADTREE_H

typedef struct{
  Ship *ship;
  int shot;
}Cell;

struct NODE{
  struct NODE * Pos[4];
  int x, y;
  int colour;
  Cell Value;
};

typedef struct{
  struct NODE *root;
  int size;
  int num_ships;
  Ship *ships;
  int X, Y, Lx, Ly;
}QuadTree;


//Cria a tabela e aloca a memoria necessaria
void create_table(QuadTree *player);
//Cria um novo no
struct NODE * CreatePNode(int colour);
//Insere um novo no na arvore
void PRInsert(struct NODE *no, struct NODE **root, int X, int Y, int Lx, int Ly);
//Para fazer print da matriz ao colocar os barcos
void print_table(QuadTree player, int X, int Y, int Lx, int Ly);
//Para fazer print das matrizes ao jogar
//void print_game(QuadTree player, QuadTree opponent);
//Liberta toda a memoria alocada
//void free_memory(Game *player1, Game *player2, int num);

int CheckQuadTree(struct NODE *root, int x, int y,  int X, int Y, int Lx, int Ly);
Ship* get_ship(struct NODE *root, int x, int y,  int X, int Y, int Lx, int Ly);

#endif
#endif
