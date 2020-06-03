#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "barcos.h"
#include "QuadTree.h"
#include "tabuleiro.h"
#include "io.h"


int main(){

#ifdef QUAD

  QuadTree player1;
  QuadTree player2;

  int X, Y;
  int Lx = 32;
  int Ly = 32;

#else

  Game player1; //Jogador 1
  Game player2; //Jogador 2

#endif

  int num; //Pedir num_ships
  int num_type[5]; //Guarda o numero total de barcos de cada tipo
  int option;  //Serve para escolher no menu
  int ships_matrix; //Numero de barcos possíveis na matrix
  int aux = 0; //Variavel aux para criar varios barcos do mesmo tipo usado no ciclo for;
  int test = 0; //Para testar os scanfs

  //Menu
  printf("\n****   *****  *     *\t\t*       *  *  *      *  ****   *****  **\n*   *  *      * * * *\t\t *     *   *  * *    *  *   *  *   *  **\n****   *****  *  *  *\t\t  *   *    *  *  *   *  *   *  *   *  **\n*   *  *      *     *\t\t   * *     *  *   *  *  *   *  *   *    \n****   *****  *     *\t\t    *      *  *    * *  ****   *****  **\n");

  printf("\nPressione:\n1- Colocacao manual\n2- Colocacao automatica\nOutra tecla- Exit\n");

  test = scanf("%d", &option); //Escolha da opcao no menu
  clean_buffer();

  while(test != 1){
    printf("Insira uma opcao valida:");
    test = scanf("%d", &option);
    clean_buffer();
  }

  if(option == 1){  //Caso seja acionada a colocacao manual

    printf("\nInsira o tamanho do tabuleiro entre 20 e 40: ");

    test = scanf("%d", &player1.size); //Tamanho da matriz
    clean_buffer();

    while(player1.size < 20 || player1.size > 40 || test != 1){
      printf("Por favor insira um numero entre 20 e 40: ");
      test = scanf("%d", &player1.size); //Tamanho da matriz
      clean_buffer();
    }

    #ifdef QUAD
    while(Lx < player1.size){
      Lx = Lx * 2;
      Ly = Ly * 2;
    }

    X = Lx/2;
    Y = Lx/2;
    #endif

    ships_matrix = (player1.size*player1.size) / 25; //Calculo do numero maximo de navios
    player2.size = player1.size;

    printf("\nTipos de Barcos:  1\t 2\t 3\t  4\t  5   \n                  *\t *\t *\t ***\t  ***\n                 \t *\t *\t  *  \t  *  \n                 \t  \t *\t     \t  *  \n");

    printf("\nAlgumas regras de escolha:\n1- No minimo tem de escolher 1 barco de cada tipo.\n2- O numero total de barcos nao pode exceder %d.\nInsira o numero de barcos a colocar no tabuleiro: ", ships_matrix);

    test = scanf("%d", &num); //Numero de barcos a inserir
    clean_buffer();

    while(num < 5 || num > ships_matrix || test != 1){
      printf("\nNumero insuficiente para incluir todos os tipos de barco ou o numero excede o limite permitido!!\nQuantos barcos vao querer no tabuleiro: ");
      test = scanf("%d", &num); //Numero de barcos a inserir
      clean_buffer();
    }

    player1.num_ships = num;
    player2.num_ships = player1.num_ships;

    //Cria o tabuleiro de jogo alocando a memoria necessária
    create_table(&player1);
    create_table(&player2);

    //Pede todos os tipos de barco e faz uma verificacao no final
    do{
      for(int i = 0; i < 5; i++) num_type[i] = 0;

      for(int i = 0; i < 5; i++){
	printf("Numero de barcos do tipo %d: ", i+1);
	test = scanf("%d", &num_type[i]);
	clean_buffer();

	while(test != 1){
	  printf("Numero de barcos do tipo %d: ", i+1);
	  test = scanf("%d", &num_type[i]);
	  clean_buffer();
	}
      }
      printf("\n");
    }while(check(num_type) != player1.num_ships); //A funcao check vai verificar se todos os tipos estao com barcos e se a soma = num_ships

    //Atribuir os tipos aos barcos
    aux = 0;
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < num_type[j]; j++){
	player1.ships[aux].type = i+1;
	player2.ships[aux].type = i+1;
	aux++;
      }
    }

    /* Depois de termos os tipos de barcos definidos vamos criar o navio
     * alocando a memoria necessaria e inicializando as variaveis associadas
     * aos barcos
     */
    for(int i = 0; i < player1.num_ships; i++){
      create_ship(&player1.ships[i], player1.ships[i].type);
      create_ship(&player2.ships[i], player2.ships[i].type);
    }

    /* Para inserir os navios na matriz vamos a uma funcao onde sera
     * pedido os valores necessarios ao utilizador para inserir o navio
     */
    printf("\n\nPlayer 1:\n");
#ifdef MAT
    insert_ships(&player1, 0);
#else
    insert_ships(&player1, X, Y, Lx, Ly, 0);
#endif

    printf("\n\nPlayer 2:\n");
#ifdef MAT
    insert_ships(&player2, 0);
#else
    insert_ships(&player2, X, Y, Lx, Ly, 0);
#endif

  }else if(option == 2){ //Caso seja acionada a opcao automatica

    srand(time(0));

    //Damos valores random as variaveis
    player1.size = (rand() % (40-20+1)) + 20;
    player2.size = player1.size;

    ships_matrix = (player1.size*player1.size) / 25;

    player1.num_ships = (rand() % (ships_matrix-5+1)) + 5;
    player2.num_ships = player1.num_ships;

    #ifdef QUAD
    while(Lx < player1.size){
      Lx = Lx * 2;
      Ly = Ly * 2;
    }

    X = Lx/2;
    Y = Lx/2;
    #endif

    //Cria a matriz alocando a memoria necessária
    create_table(&player1);
    create_table(&player2);

    //Dar valores random ao num de cada tipo de barco
    int sobras = player1.num_ships-5;

    int i;
    for(i = 0; i < 4 && sobras != 0; i++){
      num_type[i] = (rand() % sobras) +1;
      sobras -= (num_type[i]-1);
    }

    if(sobras != 0){
      num_type[4] = sobras+1;
    }else{
      for(; i < 5; i++){
	num_type[i] = 1;
      }
    }

    for(int i = 0; i < 5; i++){
      for(int j = 0; j < num_type[i]; j++){
	player1.ships[aux].type = i+1;
	player2.ships[aux].type = i+1;
	aux++;
      }
    }

    //Criamos os barcos e inserimo-os na matriz
    for(int i = 0; i < player1.num_ships; i++){
      create_ship(&player1.ships[i], player1.ships[i].type);
      create_ship(&player2.ships[i], player2.ships[i].type);
    }

    #ifdef MAT
    insert_ships(&player1, 1);
    #else
    insert_ships(&player1, X, Y, Lx, Ly, 1);
    #endif

    #ifdef MAT
    insert_ships(&player2, 1);
    #else
    insert_ships(&player2, X, Y, Lx, Ly, 1);
    #endif

  }else{ //Caso seja acionada a opcao de sair do jogo
    printf("Ficamos a sua espera ;)\n");
    return 0;
  }

  /////////////////// JOGO //////////////////////////////////

  printf("\n*       *   *      *     *  ****  ****        ****  ****  *****      *      ****  * *\n *     *   * *     * * * *  *  *  *              *  *  *  *         * *     *  *  * *\n  *   *   *****    *  *  *  *  *  ****           *  *  *  * ***    *****    ****  * *\n   * *   *     *   *     *  *  *     *        *  *  *  *  *   *   *     *   **       \n    *   *       *  *     *  ****  ****        ****  ****  *****  *       *  * *   * *\n");

  int x;
  int y;
  int turn = 1;
  int res = 0;

  printf("\nVez do Player%d\n", turn);

#ifdef MAT
  print_game(player1, player2);
#else
  struct NODE* temp;
  struct NODE* new;
  print_game(player1, X, Y, Lx, Ly);

#endif


  while (player1.num_ships > 0 && player2.num_ships > 0 ){

    do{ //Pedir as coordenadas de tiro ao utilizador
      printf("\nEscolha as coordeadas do tiro (row, col): ");
      test = scanf("%d %d", &y, &x);
      clean_buffer();

      while(test != 2){
	printf("Coordenadas invalidas, escolha as coordeadas do tiro (row, col):");
	test = scanf("%d %d", &y, &x);
	clean_buffer();
      }
      #ifdef MAT
      x--;
      y--;
      #endif
    }while(inside_table(&player1, y, x));

    //Como as matrizes tem o mesmo size verificamos só para o player1 se as coordenadas sao validas ou nao;

    /* Aqui tratamos dos turnos
     * Usamos o aim_fire para verificar o resultado do tiro e fazer as alteracoes necessaria
     * Verificamos se o jogo acabou, o num_ships do adversario == 0
     */
    if(turn == 1){
#ifdef QUAD
      temp = CheckQuadTree(player1.root, y, x, X, Y, Lx, Ly);
      res = aim_fire(&player2, y, x, X, Y, Lx, Ly);
      if(temp == NULL){
        new = CreatePNode(4);
        new->x = x;
        new->y = y;
        new->Value.ship = NULL;
        if(res == -1){
          new->Value.shot = 1;
        }else{
          new->Value.shot = 1;
        }
        PRInsert(new, &player1.root, X,Y,Lx,Ly);
      }
      else{
        if(res == -1){
          temp->Value.shot = 1;
        }else{
          temp->Value.shot = 2;
        }
      }
#else
      res = aim_fire(&player2, y, x);
      if(res == -1){
	player1.matrix[y][x].shot = 1; //Acertou na agua
      }else{
	player1.matrix[y][x].shot = 2; //Acertou num navio
      }
#endif

      if(player2.num_ships == 0){
	printf("\n*       *       *  *  *      *   \t  ****   *          *      *   *  *****  ****     *  **\n *     * *     *   *  * *    *  *\t  *   *  *         * *      * *   *      *   *   **  **\n  *   *   *   *    *  *  *   *   \t  ****   *        *****      *    *****  ****   * *  **\n   * *     * *     *  *   *  *  *\t  *      *       *     *     *    *      **       *    \n    *       *      *  *    * *   \t  *      *****  *       *    *    *****  * *     *** **\n");
#ifdef MAT
	free_memory(&player1, &player2, num);
#endif
	return 0;
      }
    }else{

#ifdef QUAD
      temp = CheckQuadTree(player2.root, y, x, X, Y, Lx, Ly);
      res = aim_fire(&player1, y, x, X, Y, Lx, Ly);
      if(temp == NULL){
        new = CreatePNode(4);
        new->x = x;
        new->y = y;
        new->Value.ship = NULL;
        if(res == -1){
          new->Value.shot = 1;
        }else{
          new->Value.shot = 1;
        }
        PRInsert(new, &player2.root, X,Y,Lx,Ly);
      }
      else{
        if(res == -1){
          temp->Value.shot = 1;
        }else{
          temp->Value.shot = 2;
        }
      }
#else
      res = aim_fire(&player1, y, x);

      if(res == -1){
	player2.matrix[y][x].shot = 1; //Acertou na agua
      }else{
	player2.matrix[y][x].shot = 2; //Acertou num navio
      }
#endif
      if(player1.num_ships == 0){
	printf("\n*       *       *  *  *      *   \t  ****   *          *      *   *  *****  ****    ***    **\n *     * *     *   *  * *    *  *\t  *   *  *         * *      * *   *      *   *  *   *   **\n  *   *   *   *    *  *  *   *   \t  ****   *        *****      *    *****  ****       *   **\n   * *     * *     *  *   *  *  *\t  *      *       *     *     *    *      **       *       \n    *       *      *  *    * *   \t  *      *****  *       *    *    *****  * *     ****   **\n");
#ifdef MAT
	free_memory(&player1, &player2, num);
#else
  free_tree(player1.root);
  free_tree(player2.root);
#endif
	return 0;
      }
    }

    //Escolhe quem joga a seguir se o jogo nao acabar
    if(turn == 1 && res == -1){
      turn = 2;
      printf("------------------------------------------------\n");
      printf("\nVez do Player%d\n", turn);
#ifdef MAT
      print_game(player2, player1);
#else
      print_game(player2, X,Y,Lx,Ly);
#endif
    }else if(turn == 1 && res == 0){
      turn = 1;
    }else if(turn == 2 && res == -1){
      turn = 1;
      printf("------------------------------------------------\n");
      printf("\nVez do Player%d\n", turn);
#ifdef MAT
      print_game(player1, player2);
#else
      print_game(player1, X,Y,Lx,Ly);
#endif
    }else{
      turn = 2;
    }
  }
  return 0;
}
