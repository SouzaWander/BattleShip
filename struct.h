#include<stdlib.h>
#include<stdio.h>

typedef struct {
  int num_ships;
  int **bitmap;
  int row, col; //Posicao centro do barco
  int rot
}Ship;

typedef struct{
  Ship *ship;
  int shot;
}Cell;

typedef struct{
    int size;
    Cell **matrix;
}Game;

/*
 * 0 - Empty
 * 1 - Piece without being hitted
 * 2 - piece hitted
 * 3 - missed shot
*/


//submarinos, contratorpedeiros, naviostanque, portaavioes, t;
void create_ship(Ship *ship, int ind){
  ship->bitmap = (int**) malloc(5 * sizeof(int*)); //Linhas
  for(int i = 0; i < 5; i++){
      ship->bitmap[i] = (int*) malloc (sizeof(int) * 5); //Colunas
  }

  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
           ship->bitmap[i][j] = 0;
        }
    }

    switch (ind) {
    case(1):
      ship->bitmap[2][2] = 1;
      break;

    case(2):
      ship->bitmap[2][2] = 1;
      ship->bitmap[3][2] = 1;
      break;

    case(3):
      ship->bitmap[2][2] = 1;
      ship->bitmap[3][2] = 1;
      ship->bitmap[4][2] = 1;
      break;

    case(4):
      ship->bitmap[2][4] = 1;
      ship->bitmap[2][2] = 1;
      ship->bitmap[2][3] = 1;
      ship->bitmap[3][3] = 1;
      break;

    case(5):
      ship->bitmap[2][2] = 1;
      ship->bitmap[3][2] = 1;
      ship->bitmap[4][2] = 1;
      ship->bitmap[2][3] = 1;
      ship->bitmap[2][4] = 1;
      break;
    }
}
//Cria a tabela
void create_table(Game *player){

   //Alocar dinamicamente a memoria para struct Ship **matrix[SIZE][SIZE];
   player->matrix = (Cell**) malloc(player->size * sizeof(Cell*)); //Linhas
   for(int i = 0; i < player->size; i++){
       player->matrix[i] = (Cell *) malloc (sizeof(Cell) * player->size); //Colunas
   }

   for(int i = 0; i < player->size; i++){
     for(int j = 0; j < player->size; j++){
            player->matrix[i][j].ship = NULL;
         }
     }
}


//Faz print do tabueleiro
void print_table(Game player){
  for(int i = 0; i < player.size; i++){
    for(int j = 0; j < player.size; j++){
            if(player.matrix[i][j].ship == NULL){
                printf("0");
            }else{
                printf("1");
            }
        }
        printf("\n");
    }
}


// return -1: Tipo de barco sem ser inserido
int check(Ship ships[]){
  int count = 0;

  for(int i = 1; i < 7; i++){
    if(ships[i].num_ships <= 0){
      return -1;
    }

    count += ships[i].num_ships;
  }

  return count;
}

int inside_table(Game *player, int row, int col){
  //Se coordeadas introduzidas não pertcerem as dimensoes do map
  if(row > player->size || col > player->size || row < 0 || col < 0){
      printf("Erro: posicao fora dos limites");
      return 1;
  }
  return 0;
}


int check_table(Ship *ship, Game *player, int row,int col){
  for(int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++) {
       if(ship->bitmap[i][j] != 0){
        if(inside_table(player,row-2+i,col-2+j) == 1 || player->matrix[row-2+i][col-2+j].ship != NULL){
          return 1;
        }
      }
    }
  }
  return 0;
}


void add_ship_table(Ship *ship, Game *player, int row,int col, char pos){
  /*row = row-2;
  col = col-2;*/
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if(ship->bitmap[i][j] != 0){
          player->matrix[row-2+i][col-2+j].ship = ship;
      }
    }

  }
}

void rotate(Ship *ship){
  int aux[5][5];
  printf("\nrotate\n");
  //vamos tirar isto quando ja tivermos criado a situação para construir os barcos
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
           aux[i][j] = 0;
        }
    }


  switch (ship->rot) {

    case 90:
      for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          if(ship->bitmap[i][j] != 0){
            aux[4-j][i] = ship->bitmap[i][j];
          }
        }
      }
      break;


      case 180:
        for(int i = 0; i < 5; i++){
          for(int j = 0; j < 5; j++){
            if(ship->bitmap[i][j] != 0){
              aux[j][4-i] = ship->bitmap[i][j];
            }
          }
        }
        break;

      case 270:
        for(int i = 0; i < 5; i++){
          for(int j = 0; j < 5; j++){
            if(ship->bitmap[i][j] != 0){
              aux[4-i][4-j] = ship->bitmap[i][j];
            }
          }
        }
        break;

      default:
        break;
  }

  //copia conteudo da matriz aux para o bitmap
  if(ship->rot > 0){
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < 5; j++){
        if(aux[i][j] == 0){
         ship->bitmap[i][j] = 0;
        }
        else{
          ship->bitmap[i][j] = 1;
        }
      }
    }
  }

}
