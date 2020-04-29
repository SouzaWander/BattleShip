#include "barcos.h"
#include <stdlib.h>

//Aloca memoria para o bitmap do barco e define o bitmap, dim e shot_count
void create_ship(Ship *ship, int ind){
  ship->bitmap = (char**) calloc(5, sizeof(char*)); //Linhas
  for(int i = 0; i < 5; i++){
    ship->bitmap[i] = (char*) calloc (5, sizeof(char)); //Colunas
  }

  switch (ind) {
    case(1):
      ship->bitmap[2][2] = '1';
      ship->dim = 1;
      ship->shot_count = 0;
      break;

    case(2):
      ship->bitmap[2][2] = '1';
      ship->bitmap[3][2] = '1';
      ship->dim = 2;
      ship->shot_count = 0;
      break;

    case(3):
      ship->bitmap[2][2] = '1';
      ship->bitmap[3][2] = '1';
      ship->bitmap[4][2] = '1';
      ship->dim = 3;
      ship->shot_count = 0;
      break;

    case(4):
      ship->bitmap[2][4] = '1';
      ship->bitmap[2][2] = '1';
      ship->bitmap[2][3] = '1';
      ship->bitmap[3][3] = '1';
      ship->dim = 4;
      ship->shot_count = 0;
      break;

    case(5):
      ship->bitmap[2][2] = '1';
      ship->bitmap[3][2] = '1';
      ship->bitmap[4][2] = '1';
      ship->bitmap[2][3] = '1';
      ship->bitmap[2][4] = '1';
      ship->dim = 5;
      ship->shot_count = 0;
      break;
    }
}

//Faz a rotação dos barcos
void rotate(Ship *ship){
  int aux[5][5];
  if(ship->rot == 0 || ship->rot == 90 || ship->rot == 180 ||  ship->rot == 270 || ship->rot == 360){
    //poe todos os valores da matriz aux para zero
    for(int k = 0 ; k < ship->rot/90; k++){
      for(int i = 0; i < 5; i++){
	for(int j = 0; j < 5; j++){
	  aux[i][j] = 0;
	}
      }
      //rotação 90
      for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          if(ship->bitmap[i][j] != 0){
            aux[4-j][i] = ship->bitmap[i][j];
          }
        }
      }
      //copia a matriz aux para o bitmap
      if(ship->rot > 0){
        for(int i = 0; i < 5; i++){
          for(int j = 0; j < 5; j++){
            if(aux[i][j] == 0){
	      ship->bitmap[i][j] = 0;
            }else{
              ship->bitmap[i][j] = 1;
            }
          }
        }
      }
    }
  }
}
