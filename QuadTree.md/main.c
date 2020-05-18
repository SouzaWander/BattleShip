#include <stdio.h>
#include "QuadTree.c"

int main(){

  QuadTree Q = make();
  struct NODE *no;
  no->x = 2;
  no->y = 2;
  PRInsert(no, &Q.root, 8, 8, 16, 16);

  
  no->x = 10;
  no->y = 10;
  PRInsert(no, &Q.root, 8, 8, 16, 16);

  if(Q.root->NW != NULL){
    printf("NW DIFERENT NULL");
  }

  if(Q.root->NE != NULL){
    printf("NE DIFERENT NULL");
  }

  if(Q.root->SW != NULL){
    printf("SW DIFERENT NULL");
  }

  if(Q.root->SE != NULL){
    printf("SE DIFERENT NULL");
  }
  return 0;
}
