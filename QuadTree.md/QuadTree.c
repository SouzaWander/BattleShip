#ifdef QUAD

#include <stdio.h>
#include <stdlib.h>
#include "barcos.h"
#include "QuadTree.h"

float Sx[4] = {-0.25, 0.25, -0.25, 0.25};
float Sy[4] = {0.25, 0.25, -0.25, -0.25};

void create_table(QuadTree * player){
  player->root = (struct NODE *)malloc(sizeof(struct NODE));
  player->root = NULL;
  player->ships = (Ship * ) malloc(sizeof(Ship) * player->num_ships);
}

struct NODE * CreatePNode(int colour){
  struct NODE* new = (struct NODE *)malloc(sizeof(struct NODE));

  for(int i = 0; i < 4; i++) new->Pos[i] = NULL;
  new->colour = colour;

  if(colour == 1){    //Para indicar quando e no intermedio
    new->x = -1;
    new->y = -1;
  }
  
  return new;
}

/*
1 = GRAY (nonleaf node)
2 = White (contais a data point / leaf)
*/

/*
 * NW = 0
 * NE = 1
 * SW = 2
 * SE = 3
 */
static int PRCompare(struct NODE *P, int X, int Y){

  if(P->x < X){
    if(P->y < Y){
      return 2;
    }else{
      return 0;
    }
  }else if(P->y < Y){
    return 3;
  }
  
  return 1;
}

void PRInsert(struct NODE *no, struct NODE **root, int X, int Y, int Lx, int Ly){

  struct NODE *T;
  struct NODE *U;
  int q;
  int qu;

  if((*root) == NULL){ //Se não existir nenhum nó no root
    (*root) = no;
    return;
  }else if((*root)->colour != 1){ //Quando já temos um no 
    if((no->x == (*root)->x) && (no->y == (*root)->y)){ //Se o root for igual ao no terminamos a funcao
      return;
    }else{  //Se não for vemos em que quadrante é que o root vai ficar 
      U = (*root);
      (*root) = CreatePNode(1);
      q = PRCompare(U, X, Y);
      (*root)->Pos[q] = U;
    }
  }

  T = (*root);
  q = PRCompare(no, X, Y);

  while(T->Pos[q] != NULL && T->Pos[q]->colour == 1){
    T = T->Pos[q];
    X = X + Sx[q]*Lx;
    Lx = Lx/2;
    Y = Y + Sy[q]*Ly;
    Ly = Ly/2;
    q = PRCompare(no,X,Y);
  }

  if( T->Pos[q] == NULL){
    T->Pos[q] = no;
  }
  else if((no->x == T->Pos[q]->x) && (no->y == T->Pos[q]->y)) return; //ja foi inserido
  else{
    U = T->Pos[q];
    do{
      T->Pos[q] = CreatePNode(1);
      T = T->Pos[q];
      X = X + Sx[q]*Lx;
      Lx = Lx/2;
      Y = Y + Sy[q]*Ly;
      Ly = Ly/2;
      q = PRCompare(no,X,Y);
      qu = PRCompare(U,X,Y);
    }while(q == qu);

    T->Pos[q] = no;
    T->Pos[qu] = U;
  }
}


void PrintQuadTree(struct NODE *no){

  if(no == NULL){
    printf("Null ");
    return;
  }

  printf("(%d,%d) ", no->x, no->y);
  
  PrintQuadTree(no->Pos[0]);
  PrintQuadTree(no->Pos[1]);
  PrintQuadTree(no->Pos[2]);
  PrintQuadTree(no->Pos[3]);
}

int CheckQuadTree(struct NODE *root, int x, int y,  int X, int Y, int Lx, int Ly){

    struct NODE* no = CreatePNode(2);
    no->x = x;
    no->y = y;
    int q = PRCompare(no, X, Y);

    if(root == NULL){
      free(no);
      return 0;
    }else if(root->colour != 1){
      if((no->x == root->x) && (no->y == root->y)){
	free(no);
	return root->Value.ship->type;
      }
    }
    if(root->Pos[q] == NULL){
      free(no);
      return 0;
    }

    while(root->Pos[q] != NULL && root->Pos[q]->colour == 1){
      root = root->Pos[q];
      X = X + Sx[q]*Lx;
      Lx = Lx/2;
      Y = Y + Sy[q]*Ly;
      Ly = Ly/2;
      q = PRCompare(no,X,Y);
    }

    if(root->Pos[q] == NULL){
      free(no);
      return 0;
    }

    if(root->Pos[q]->colour != 1){
      if((no->x == root->Pos[q]->x) && (no->y == root->Pos[q]->y)){
	free(no);
        return root->Pos[q]->Value.ship->type;
      }
    }

    free(no);
    return 0;
}


void print_table(QuadTree player, int X, int Y, int Lx, int Ly){

  int type;
  
  printf("   ");
  for(int i = 1; i <= player.size; i++){
    printf("%3d", i);
  }
  
  printf("\n");
  
  for(int i = 1; i <= player.size; i++){
    printf("%3d  ", i);
 
    for(int j = 1; j <= player.size; j++){

      if((type = CheckQuadTree(player.root, i, j, X, Y, Lx, Ly)) == 0){
	printf("0  ");
      }else{
	switch(type){
	case(1):
	  printf("%c  ", 'A');
	  break;
	case(2):
	  printf("%c  ", 'B');
	  break;
	case(3):
	  printf("%c  ", 'C');
	  break;
	case(4):
	  printf("%c  ", 'D');
	  break;
	case(5):
	  printf("%c  ", 'E');
	  break;
	default:
	  break;
	}
      }
    }
    printf("\n");
  }
}


#endif
