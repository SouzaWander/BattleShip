#include <stdio.h>
#define SIZE 9

/*
o - água
x - barco atingido
* - posicao dos barcos
*/

//Functions
void create_table(char matrix[SIZE][SIZE]){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      matrix[i][j] = 'O';
    }
  }
}

void print_table(char matrix[SIZE][SIZE]){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      printf("%c\t", matrix[i][j]);
    }
    printf("\n");
  }
}

void add_ship_table(){

}

///////////////////////////////////////////////////

struct Ship{
  //Atributes
  int dim, x, y;
  int shot; //posicao atingida
  //int alive = 1;
  /* Se a posicao (x,y) corresponder a um barco e ainda nao tiver sido
  atingida aumentamos a var shot e mudamos o simbolo no Table. Se shot == dim
  mudamos o atributo alive para 0
  */
};

/*Cada barco vai ter um numero que o identifica, usamos uma funçao
para escolher um numero aleatorio e procurar espaço onde o barco caiba*/

/*criar uma class barco que vai ter um array de barcos e cada instancia de barco
se está vivo ou não. Isso ara saber se o jogo ja acabou ou não*/

int main(){

  /*struct Table tabuleiro;
  make(tabuleiro.matrix);
  print(tabuleiro.matrix);*/

  char player1_map[SIZE][SIZE];
  create_table(player1_map);
  print_table(player1_map);

  return 0;
}
