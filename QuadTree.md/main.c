#include <stdio.h>
#include "QuadTree.c"

int main(){

  QuadTree Q = make();
  struct NODE *no;
  no->x = 10;
  no->y = 10;
  no->colour = 2;
  PRInsert(no, &Q.root, 8, 8, 16, 16);

  
  no->x = 2;
  no->y = 2;
  no->colour = 2;
  PRInsert(no, &Q.root, 8, 8, 16, 16);

  printf("\nroot: (%d,%d) %d\n", Q.root->x, Q.root->y, Q.root->colour);
  if(Q.root->Pos[0] != NULL){
    printf("NW DIFERENT NULL\n");
  }

  if(Q.root->Pos[1] != NULL){
    printf("NE DIFERENT NULL\n");
  }

  if(Q.root->Pos[2] != NULL){
    printf("SW DIFERENT NULL\n");
  }

  if(Q.root->Pos[3] != NULL){
    printf("SE DIFERENT NULL\n");
  }
  return 0;
}
