#ifdef MAT
  
#include <stdio.h>
#include <stdlib.h>
#include "barcos.h"
#include "tabuleiro.h"


/*
  Cria a tabela alocando a memoria necessaria para a matriz e para o array ships
  e inicializa , na struct cell, o shot a 0 e o ship a Null
*/
void create_table(Game *player){

   //Alocar dinamicamente a memoria para struct Ship **matrix[SIZE][SIZE];
  player->matrix = (Cell**) malloc(player->size * sizeof(Cell*)); //Linhas
   for(int i = 0; i < player->size; i++){
     player->matrix[i] = (Cell *) malloc (player->size * sizeof(Cell)); //Colunas
   }


   for(int i = 0; i < player->size; i++){
     for(int j = 0; j < player->size; j++){
            player->matrix[i][j].shot = 0;
            player->matrix[i][j].ship = NULL;
     }
   }


   player->ships = (Ship * ) malloc(sizeof(Ship) * player->num_ships);
}

//Para fazer print da matriz ao colocar os barcos
void print_table(Game player){
  printf("   ");
  for(int i = 1; i <= player.size; i++){
    printf("%3d", i);
  }

  printf("\n");

  for(int i = 0; i < player.size; i++){
    printf("%3d  ", i+1);
 
    for(int j = 0; j < player.size; j++){

      if(player.matrix[i][j].ship == NULL){
	printf("0  ");
      }else{
	switch(player.matrix[i][j].ship->type){
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

//Para fazer print das matrizes ao jogar
void print_game(Game player, Game opponent){
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
    for(int i = 0; i < player.size; i++){
      printf("%3d", i+1);
   
      for(int j = 0; j < player.size; j++){
	if(player.matrix[i][j].ship == NULL){
	  //Para printar os tiros na agua foi buscar os shots do adversário porque não temos o 3 no bitmap
	  if(opponent.matrix[i][j].shot > 0){  //Mostrar os tiros feitos pelo adversário caso tenha atingido a agua!
	    printf("%3d", 3);
	  }else{
	    printf("%3d", 0);
	  }
	  
	}else{
	  
	  int aux_row = 4 - (player.matrix[i][j].ship->row + 2 - i);
	  int aux_col = 4 - (player.matrix[i][j].ship->col + 2 - j);
	  
	  if(player.matrix[i][j].ship->bitmap[aux_row][aux_col] == '2'){
	    printf("%3c", 'X');
	  }else{
	    switch(player.matrix[i][j].ship->type){
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
      printf("%3d", i+1);

      for(int j = 0; j < player.size; j++) {
        printf("%3d", player.matrix[i][j].shot);
      }

      printf("\n");
    }
}

//Liberta toda a memoria alocada
void free_memory(Game *player1, Game *player2, int num){

  //liberta reservada para os bitmaps dos navios
  for(int i = 0; i < num; i++){
    for(int j = 0; j < 5; j++){
      free(player1->ships[i].bitmap[j]);
      free(player2->ships[i].bitmap[j]);
    }
    free(player1->ships[i].bitmap);
    free(player2->ships[i].bitmap);
  }
  
  //liberta espaço em memoria do array que guardava os navios
  free(player1->ships);
  free(player2->ships);

  //liberta tabuleiro
  for(int i = 0; i < player1->size; i++){
    free(player1->matrix[i]);
    free(player2->matrix[i]);
  }

  free(player1->matrix);
  free(player2->matrix);
}

#endif
