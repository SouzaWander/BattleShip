#include <stdio.h>
#include <stdlib.h>
#include "barcos.h"
#include "tabuleiro.h"

//Limpa buffer do scanf
void clean_buffer(){
  char c;
  while((c= getchar()) != '\n' && c != EOF);
}

/*
  Verifica se todos os tipos de barcos tem pelo menos 1
  e retorna o total de barcos inseridos

  return -1: Algum tipo de barco sem ser inserido
  return count: Se todos os tipos de barcos estão inseridos
*/
int check(int num_type[]){
  int count = 0;

  for(int i = 0; i < 5; i++){
    if(num_type[i] == 0){
      return -1;
    }
    count += num_type[i];
  }

  return count;
}


//Verifica se as coordenadas dadas pertencem ao tabuleiro ou não
int inside_table(Game *player, int row, int col){
  //Se coordeadas introduzidas não pertcerem as dimensoes do map
  if(row >= player->size || col >= player->size || row < 0 || col < 0){
      return -1;
  }
  return 0;
}

/*
 Verifica se a posicao está dentro dos limites
 e se nao ha outro barco naquela posicao
 Flag 0 -> Introducao Manual
 Flag 1 -> Introducao Automatica
*/
static int check_table(Ship *ship, Game *player, int flag){
  for(int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++) {
      if(ship->bitmap[i][j] != '0'){
        if(inside_table(player,ship->row-2+i,ship->col-2+j) == -1){
	  if(flag == 0) printf("Erro: posicao fora dos limites\n");
	  return -1;
        }

        if(player->matrix[ship->row-2+i][ship->col-2+j].ship != NULL){
	  if(flag == 0) printf("Posicao ja ocupada por outro barco!\n");
	  return -1;
        }
      }
    }
  }
  return 0;
}


/*
  Caso o barco não possa ser inserido, teste com a funcao check_table
  volta a colocar o bitmap com a posicao original usando a funcao rotate.
  Caso ele possa ser inserido vai a matriz e aponta a celula para o ship.
  Flag 0 -> Introducao Manual
  Flag 1 -> Introducao Automatica
*/
static int add_ship_table(Ship *ship, Game *player, int flag){

  if(check_table(ship, player, flag) == -1){
    ship->rot = 360 - ship->rot;
    rotate(ship);
    return -1;
  }

  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if(ship->bitmap[i][j] != '0'){
          player->matrix[ship->row-2+i][ship->col-2+j].ship = ship;
      }
    }

  }
  return 0;
}


/*
  Pede as coordenadas e a rotacao do barco ao jogador.
  Realiza a rotacao do barco e vai para a funcao add_ship_table verificar
se pode ser inserido e caso seja, o barco é inserido.
  Flag 0 -> Introducao Manual
  Flag 1 -> Introducao Automatica
*/
void insert_ships(Game *player, int flag){

  int test;


  if(flag == 0){
    printf("Vamos agora comecar a inserir os barcos no tabuleiro segundo a ordem escolhida.\n\n");
    for(int i = 0; i < player->num_ships; i++){
      do{
        print_table(*player);
        printf("\nCoordenadas do barco %d do tipo %d e a sua rotacao (0, 90, 180, 270, 360): ", i+1, player->ships[i].type);
        test = scanf("%d %d %d", &player->ships[i].row , &player->ships[i].col , &player->ships[i].rot);
	clean_buffer();
	while((test < 3) || ((player->ships[i].rot != 0) && (player->ships[i].rot != 90) && (player->ships[i].rot != 180) && (player->ships[i].rot != 270) && (player->ships[i].rot != 360))){
	  printf("\nCoordenadas invalidas! Coordenadas do barco %d do tipo %d e a sua rotacao (0, 90, 180, 270, 360): ", i+1, player->ships[i].type);
	  test = scanf("%d %d %d", &player->ships[i].row , &player->ships[i].col , &player->ships[i].rot);
	  clean_buffer();
	}

	player->ships[i].row--;
        player->ships[i].col--;
        rotate(&player->ships[i]);
      }while(add_ship_table(&player->ships[i], player, flag) == -1);

      printf("\n");
    }
    print_table(*player);

  }else{

    for(int i = 0; i < player->num_ships; i++){
      do{
        player->ships[i].row = (rand() % (player->size-1));
        player->ships[i].col = (rand() % (player->size-1));

        int aux = (rand() % 4);
        switch (aux) {
            case 0:
                 player->ships[i].rot = 0;
                 break;
            case 1:
                player->ships[i].rot = 90;
                break;
            case 2:
                player->ships[i].rot = 180;
                break;
            case 3:
                player->ships[i].rot = 270;
                break;
            case 4:
                player->ships[i].rot = 360;
                break;

            default:
                break;
        }

        rotate(&player->ships[i]);
      }while(add_ship_table(&player->ships[i], player, flag) == -1);
    }
  }
}


/*
  Analisa os tiros, se acertou na agua, num barco ou se a posicao já tinha
sido atingida. Alterando os valores necessarios
*/
int aim_fire(Game *player, int row, int col){

  if(player->matrix[row][col].ship == NULL){

    printf("\nTiro na agua!\n");
    return -1;

  }else{

    //calcula o valor correspondente a posicao no bit map
    int aux_row = 4 - (player->matrix[row][col].ship->row + 2 - row);
    int aux_col = 4 - (player->matrix[row][col].ship->col + 2 - col);

    if(player->matrix[row][col].ship->bitmap[aux_row][aux_col] == '2'){

      printf("Posicao ja tinha sido atingida!");

    }else{

      player->matrix[row][col].ship->bitmap[aux_row][aux_col] = '2';
      player->matrix[row][col].ship->shot_count++;
      printf("\nAtingiu o barco adversario!\n");

      if(player->matrix[row][col].ship->shot_count == player->matrix[row][col].ship->dim) {
        printf("Afundou barco adversario!\n");
	player->num_ships = player->num_ships - 1;
      }

    }

  }
  return 0;
}
