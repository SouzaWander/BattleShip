#include <stdio.h>
#include <stdlib.h>

float Sx[4] = {-0.25, 0.25, -0.25, 0.25};
float Sy[4] = {0.25, 0.25, -0.25, -0.25};

struct NODE{
  struct NODE * Pos[4];
  int x, y;
  int colour;
  //Cell Value;
};


/*
typedef struct{
  int x;
  int y;
}Point;
*/

typedef struct{
  struct NODE *root;
}QuadTree;

QuadTree make(){
  QuadTree new;
  new.root = (struct NODE *)malloc(sizeof(struct NODE));
  new.root = NULL;
  return new;
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
int PRCompare(struct NODE *P, int X, int Y){

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
