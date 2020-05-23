#ifndef BARCOS_H
#define BARCOS_H

typedef struct{
  int type; //Indica o tipo de barco
  char **bitmap; //Bitmap
  int row, col, dim; 
  int rot; //Indica a rotacao
  int shot_count; //Indica o numero de vezes que foi atingida
}Ship;

//Aloca memoria para o bitmap do barco e define o bitmap, dim e shot_count
void create_ship(Ship *ship, int ind);
//Faz a rotação dos barcos
void rotate(Ship *ship); 

#endif
