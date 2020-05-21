#include <stdio.h>
#include "QuadTree.c"

int main(){

  QuadTree Q = make();
  struct NODE *no = CreatePNode(2);
  struct NODE *p = CreatePNode(2);
  struct NODE *no2 = CreatePNode(2);
  struct NODE *no3 = CreatePNode(2);
  no->x = 10;
  no->y = 10;
  PRInsert(no, &Q.root, 8, 8, 16, 16);

  p->x = 2;
  p->y = 2;
  PRInsert(p, &Q.root, 8, 8, 16, 16);

  no2->x = 11;
  no2->y = 3;
  PRInsert(no2, &Q.root, 8, 8, 16, 16);


  no3->x = 15;
  no3->y = 2;
  PRInsert(no3, &Q.root, 8, 8, 16, 16);
  
  printf("\nroot: (%d,%d) %d\n", Q.root->x, Q.root->y, Q.root->colour);
  if(Q.root->Pos[3]->Pos[0] != NULL){
    printf("NW DIFERENT NULL\n");
  }

  if(Q.root->Pos[3]->Pos[1] != NULL){
    printf("NE DIFERENT NULL\n");
  }

  if(Q.root->Pos[3]->Pos[2] != NULL){
    printf("SW DIFERENT NULL\n");
  }

  if(Q.root->Pos[3]->Pos[3] != NULL){
    printf("SE DIFERENT NULL\n");
  }
  
  
  return 0;
}
