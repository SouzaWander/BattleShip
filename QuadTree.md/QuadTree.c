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

  new->Value.shot = 0;
  return new;
}

/*
1 = GRAY (nonleaf node)
2 = White (contais a data point / leaf)
3 = Tiros recebidos
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
  }else if((no->x == T->Pos[q]->x) && (no->y == T->Pos[q]->y)) return; //ja foi inserido
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


//Percorre a arvore e retorna um nó que se encontra no quadrante das coordenadas x y
/*Usada no codigo para verificar se já existe um nó numa dada coordenada e para obter um nó de uma dada
util por exemplo quando estamos a inserir barcos no "tabuleiro" e para modificar alguns valores contidos nessa
estrutura quando um jogador acerta um tiro */
struct NODE* CheckQuadTree(struct NODE *root, int x, int y,  int X, int Y, int Lx, int Ly){
  if(root == NULL){
    return NULL;
  }

  struct NODE* no = CreatePNode(2);
  no->x = x;
  no->y = y;
  int q = PRCompare(no, X, Y);


  if(root->colour != 1){
    if((no->x == root->x) && (no->y == root->y)){
	free(no);
	return root;
    }
  }
  if(root->Pos[q] == NULL){
    free(no);
    return NULL;
  }
  //Percorre a arvore ate chegar a um nó folha
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
    return NULL;
  }

  if(root->Pos[q]->colour != 1){
    if((no->x == root->Pos[q]->x) && (no->y == root->Pos[q]->y)){
      free(no);
      return root->Pos[q];
    }
  }
  free(no);
  return NULL;
}

//Para fazer print durante a insercao dos barcos
void print_table(QuadTree player, int X, int Y, int Lx, int Ly){

  struct NODE *no;

  printf("   ");
  for(int i = 1; i <= player.size; i++){
    printf("%3d", i);
  }

  printf("\n");

  for(int i = 1; i <= player.size; i++){
    printf("%3d  ", i);

    for(int j = 1; j <= player.size; j++){

      no = CheckQuadTree(player.root, i, j, X, Y, Lx, Ly);
      if(no == NULL){
	printf("0  ");
      }else{
	switch(no->Value.ship->type){
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


//Para fazer print durante o jogo
void print_game(QuadTree player, int X, int Y, int Lx, int Ly){

  struct NODE* no;

  //Legenda
  printf("Meu tabuleiro:");
  for(int i = 0; i < ((player.size-4)*3-1); i++) printf(" ");
  printf("\t\t");
  printf("Tiros efetuados:\n\n   ");

  //Tabela do jogador atual
  for(int i = 1; i <= player.size; i++){ //Printar numero das colunas
    printf("%3d", i);
  }

  //Tabela dos shots adversarios
  printf("\t\t   ");
  for(int i = 1; i <= player.size; i++){ //Printar numero das colunas
    printf("%3d", i);
  }

  printf("\n");

  //Print das matrizes
  for(int i = 1; i <= player.size; i++){
    printf("%3d", i);

    for(int j = 1; j <= player.size; j++){

      no = CheckQuadTree(player.root, i, j, X, Y, Lx, Ly);

      if(no == NULL){
	printf("%3d", 0);
      }else if(no->colour == 3){
	printf("%3d", 3);
      }
      else if(no->colour == 4){
          printf("%3d", 0);
      }
      else{
	int aux_row = 4 - (no->Value.ship->row + 2 - i);
	int aux_col = 4 - (no->Value.ship->col + 2 - j);

	if(no->Value.ship->bitmap[aux_row][aux_col] == '2'){
	  printf("%3c", 'X');
	}else{
	  switch(no->Value.ship->type){
	  case(1):
	    printf("%3c", 'A');
	    break;
	  case(2):
	    printf("%3c", 'B');
	    break;
	  case(3):
	    printf("%3c", 'C');
	    break;
	  case(4):
	    printf("%3c", 'D');
	    break;
	  case(5):
	    printf("%3c", 'E');
	    break;
	  default:
	    break;
	  }
	}
      }
    }
    printf("\t\t");
    printf("%3d", i);

    for(int j = 1; j <= player.size; j++) {
      no = CheckQuadTree(player.root, i, j, X, Y, Lx, Ly);
      if(no== NULL){
        printf("%3d", 0);
      }
      else{
        printf("%3d", no->Value.shot);
      }
    }

    printf("\n");
  }
}

//função recurssiva para libertar a memoria reservada pela matriz
void free_tree(struct NODE* node){
  if(node == NULL){
    return;
  }
  // se for folha
  else if(node->colour > 1){
    free(node);
    return;
  }
  //aplicar a função para todos os ramos daquele no
  else{
    for(int i = 0; i < 4; i++){
      free_tree(node->Pos[i]);
    }
    free(node);
  }
}
#endif
