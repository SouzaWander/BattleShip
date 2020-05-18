#include <stdio.h>
#include <stdlib.h>

float Sx[4] = {-0.25, 0.25, -0.25, 0.25};
float Sy[4] = {0.25, 0.25, -0.25, -0.25};

struct NODE{
  struct NODE * NW;
  struct NODE * NE;
  struct NODE * SW;
  struct NODE * SE;
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

  new->NW = NULL;
  new->NE = NULL;
  new->SW = NULL;
  new->SE = NULL;
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

static struct NODE* get_node(struct NODE* root, int q){
  switch (q) {
      case 1:
       return root->NW;
       break;
      case 2:
       return root->NE;
       break;
      case 3:
       return root->SW;
       break;
      case 4:
       return root->SE;
       break;

      default:
        return NULL;
       break;
  }
}

int PRCompare(struct NODE *P, int X, int Y){

  if(P->x < X){
    if(P->y < Y){
      return 3;
    }else{
      return 1;
    }
  }else if(P->y < Y){
    return 4;
  }

  return 2;
}

struct NODE * CopyMemory(struct NODE *no){

  struct NODE * new = (struct NODE *)malloc(sizeof(struct NODE));

  new->NW = no->NW;
  new->NE = no->NE;
  new->SW = no->SW;
  new->SE = no->SE;
  new->x  = no->x;
  new->y = no->y;
  new->colour = no->colour;

  return new;
}

/*
 * NW = 1
 * NE = 2
 * SW = 3
 * SE = 4
 */
void PRInsert(struct NODE *no, struct NODE **root, int X, int Y, int Lx, int Ly){

  struct NODE *T;
  struct NODE *U;
  int q; //Quadrante

  if((*root) == NULL){
    (*root) = CopyMemory(no);
    printf("1(%d,%d)", (*root)->x, (*root)->y);
    return;
  }else if((*root)->colour != 1){
    if((no->x == (*root)->x) && (no->y == (*root)->y)){
      return;
    }else{
      U = CopyMemory((*root));
      (*root) = CreatePNode(1);
      q = PRCompare(U, X, Y);
      printf("2(%d,%d)", U->x, U->y);
      switch(q){
        case 1:
	       (*root)->NW = U;
	       break;
        case 2:
	       (*root)->NE = U;
	       break;
        case 3:
	       (*root)->SW = U;
	       break;
        case 4:
	       (*root)->SE = U;
	       break;

        default:
	       break;
      }
    }
  }

  
  T = CopyMemory((*root));
  q = PRCompare(no, X, Y);
  
  while( T != NULL && T->colour != 1){
    T = get_node(T, q);
    X = X + Sx[q-1]*Lx;
    Lx = Lx/2;
    Y = Y + Sy[q-1]*Ly;
    Ly = Ly/2;
    q = PRCompare(no,X,Y);
  }
  
  if( T == NULL) T = no;
  else if((no->x == T->x) && (no->y == T->y)) return; //ja foi inserido
  else{
    
    U = CopyMemory(T);
    int qu;
    struct NODE *aux;
    
    do{
      T = CreatePNode(1);
      T = get_node(T,q);
      X = X + Sx[q-1]*Lx;
      Lx = Lx/2;
      Y = Y + Sy[q-1]*Ly;
      Ly = Ly/2;
      q = PRCompare(no,X,Y);
      qu = PRCompare(U,X,Y);
    }while(q == qu);

    //aux = get_node(T,q); //Erro de segmentation fault aqui
    //aux = CopyMemory(no);
    //aux = get_node(T,qu); //Erro de segmentation fault aqui
    //aux = CopyMemory(U);
    
  }
  
}
