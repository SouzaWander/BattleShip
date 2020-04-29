#ifndef BARCOS_H
#define BARCOS_H

typedef struct{
  int type;
  char **bitmap;
  int row, col, dim;
  int rot;
  int shot_count;
}Ship;

//Aloca memoria para o bitmap do barco e define o bitmap, dim e shot_count
void create_ship(Ship *ship, int ind);
//Faz a rotação dos barcos
void rotate(Ship *ship); 

#endif
