#include <stdio.h>
#include <stdlib.h>

float Sx[4] = {-0.25, 0.25, -0.25, 0.25};
float Sy[4] = {0.25, 0.25, -0.25, -0.25};

struct NODE{

  struct NODE * Pos[4];
  /*
  struct NODE * NW;
  struct NODE * NE;
  struct NODE * SW;
  struct NODE * SE;
  */
  int x, y;
  int colour;
  //Cell Value;
};


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
  /*
  new->NW = NULL;
  new->NE = NULL;
  new->SW = NULL;
  new->SE = NULL;
  */

  for(int i = 0; i < 4; i++) new->Pos[i] = NULL;
  new->colour = colour;

  return new;
}

/*
1 = GRAY (nonleaf node)
2 = BLACK (contais a data point)
3 = WHITE (is empty)
*/

//verifica se o nó é vazia e se não é folha
/*int node_isEmpty(NODE* node){
  return node->NW == NULL && node->NE == NULL && node->SW == NULL && node->SE == NULL && node->colour == 1;
}*/
/*
static struct NODE* get_node(struct NODE* no, int q){
  switch (q) {
      case 1:
       return no->NW;
       break;
      case 2:
       return no->NE;
       break;
      case 3:
       return no->SW;
       break;
      case 4:
       return no->SE;
       break;

      default:
        return NULL;
       break;
  }
}
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

struct NODE * CopyMemory(struct NODE *no){

  struct NODE * new = (struct NODE *)malloc(sizeof(struct NODE));
  /*
  new->NW = no->NW;
  new->NE = no->NE;
  new->SW = no->SW;
  new->SE = no->SE;
  */
  new->x  = no->x;
  
  for(int i = 0; i < 4; i++) new->Pos[i] = no->Pos[i];
  new->y = no->y;
  new->colour = no->colour;

  return new;
}

/*
 * NW = 0
 * NE = 1
 * SW = 2
 * SE = 3
 */
void PRInsert(struct NODE *no, struct NODE **root, int X, int Y, int Lx, int Ly){

  struct NODE *T;
  struct NODE *U;
  int q; //Quadrante
  int qu;

  if((*root) == NULL){ //Se não existir nenhum nó no root
    (*root) = CopyMemory(no);
    //printf("1(%d,%d)", (*root)->x, (*root)->y);
    return;
  }else if((*root)->colour != 1){ //Quando já temos um no 
    if((no->x == (*root)->x) && (no->y == (*root)->y)){ //Se o root for igual ao no terminamos a funcao
      return;
    }else{  //Se não for vemos em que quadrante é que o root vai ficar 
      U = CopyMemory((*root));
      (*root) = CreatePNode(1);
      q = PRCompare(U, X, Y);
      printf("2(%d,%d) %d", U->x, U->y, q);
      (*root)->Pos[q] = U;
    }
  }

  T = CopyMemory((*root));
  q = PRCompare(no, X, Y);

  while(T->Pos[q] != NULL && T->Pos[q]->colour == 1){ //AQUI O NOT NO PSEUDOCÓDIGO É PARA TODA A EXPRESSÃO OU SÓ PARA T null?
    T = T->Pos[q];
    X = X + Sx[q-1]*Lx;
    Lx = Lx/2;
    Y = Y + Sy[q-1]*Ly;
    Ly = Ly/2;
    q = PRCompare(no,X,Y);
    printf("\n\n\n\n%d\n\n\n", q);
  }

  
  if( T->Pos[q] == NULL) T->Pos[q] = CopyMemory(no);
  else if((no->x == T->Pos[q]->x) && (no->y == T->Pos[q]->y)) return; //ja foi inserido
  else{
    U = CopyMemory(T->Pos[q]);
    
    do{
      T->Pos[q] = CreatePNode(1);
      T = CopyMemory(T->Pos[q]);
      X = X + Sx[q-1]*Lx;
      Lx = Lx/2;
      Y = Y + Sy[q-1]*Ly;
      Ly = Ly/2;
      q = PRCompare(no,X,Y);
      qu = PRCompare(U,X,Y);
    }while(q == qu);

    T->Pos[q] = CopyMemory(no);
    T->Pos[qu] = CopyMemory(U);
  }
}
