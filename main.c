#include<stdio.h>
#include "struct.h"

int main(){

  Game player1;
  Ship teste;


  player1.size = 10;

  create_table(&player1);
  print_table(player1);
  create_ship(&teste);
  printf("\n\n");
  char pos = 'u';
  rotate(&teste, 1);
  check_table(&teste, &player1, 4, 5, pos, 4 , 4);
  add_ship_table(&teste, &player1, 1, 0, pos);
  print_table(player1);

  if(check_table(&teste, &player1, 1, 1, pos, 4 , 4)== 1){
    printf("\ninvalid\n");
  }
  else {
    add_ship_table(&teste, &player1, 1, 1, pos);
      printf("\n\n");
    print_table(player1);

  }

  return 0;
}
