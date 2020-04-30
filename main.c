#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "barcos.h"
#include "tabuleiro.h"
#include "io.h"

int main(){

    Game player1;
    Game player2;
    int num; //Pedir num_ships
    int num_type[5]; //Guarda o numero total de barcos de cada tipo
    int option;  //Serve para escolher no menu
    int ships_matrix; //Numero de barcos possíveis na matrix
    int aux = 0; //Variavel aux para criar varios barcos do mesmo tipo usado no ciclo for;

    //Menu
    printf("\n****   *****  *     *\t\t*       *  *  *      *  ****   *****  **\n*   *  *      * * * *\t\t *     *   *  * *    *  *   *  *   *  **\n****   *****  *  *  *\t\t  *   *    *  *  *   *  *   *  *   *  **\n*   *  *      *     *\t\t   * *     *  *   *  *  *   *  *   *    \n****   *****  *     *\t\t    *      *  *    * *  ****   *****  **\n");

    printf("\nPressione:\n1- Colocacao manual\n2- Colocacao automatica\nOutra tecla- Exit\n");
    scanf("%d", &option);

    //Caso seja acionada a colocacao manual
    if(option == 1){

        printf("\nInsira o tamanho do tabuleiro entre 20 e 40: ");

        scanf("%d", &player1.size);

        while(player1.size < 20 || player1.size > 40){
            printf("Por favor insira um numero entre 20 e 40: ");
            scanf("%d", &player1.size);
        }

        ships_matrix = (player1.size*player1.size) / 25;
        player2.size = player1.size;

        printf("\nTipos de Barcos:  1\t 2\t 3\t  4\t  5   \n                  *\t *\t *\t ***\t  ***\n                 \t *\t *\t  *  \t  *  \n                 \t  \t *\t     \t  *  \n");

        printf("\nAlgumas regras de escolha:\n1- No minimo tem de escolher 1 barco de cada tipo.\n2- O numero total de barcos nao pode exceder %d.\nInsira o numero de barcos a colocar no tabuleiro: ", ships_matrix);

        scanf("%d", &num);

        while(num < 5 || num > ships_matrix){
            printf("\nNumero insuficiente para incluir todos os tipos de barco ou o numero excede o limite permitido!!\nQuantos barcos vao querer no tabuleiro: ");
            scanf("%d", &num);
        }

	player1.num_ships = num;
        player2.num_ships = player1.num_ships;

        create_table(&player1);
        create_table(&player2);

        do{
            for(int i = 0; i < 5; i++) num_type[i] = 0;

            for(int i = 0; i < 5; i++){
                printf("Numero de barcos do tipo %d: ", i+1);
                scanf("%d", &num_type[i]);
           }
           printf("\n");
       }while(check(num_type) != player1.num_ships); //A funcao check vai verificar se todos os tipos estao com barcos e se a soma = num_ships

       ///////ATRIBUIR OS TIPOS AOS BARCOS/////////
       aux = 0;
       for(int i = 0; i < 5; i++){
           for(int j = 0; j < num_type[j]; j++){
               player1.ships[aux].type = i+1;
               player2.ships[aux].type = i+1;
               aux++;
           }
       }
       ///////////////////////////////////////////

       for(int i = 0; i < player1.num_ships; i++){
           create_ship(&player1.ships[i], player1.ships[i].type);
           create_ship(&player2.ships[i], player2.ships[i].type);
       }

       printf("\n\nPlayer 1:\n");
       insert_ships(&player1, 0);

       printf("\n\nPlayer 2:\n");
       insert_ships(&player2, 0);

    }else if(option == 2){ //Caso seja acionada a opcao automatica
        srand(time(0));

        player1.size = (rand() % (40-20+1)) + 20;
        player2.size = player1.size;

        ships_matrix = (player1.size*player1.size) / 25;

        player1.num_ships = (rand() % (ships_matrix-5+1)) + 5;
        player2.num_ships = player1.num_ships;

        create_table(&player1);
        create_table(&player2);

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

        for(int i = 0; i < player1.num_ships; i++){
            create_ship(&player1.ships[i], player1.ships[i].type);
            create_ship(&player2.ships[i], player2.ships[i].type);
        }

        insert_ships(&player1, 1);
        insert_ships(&player2, 1);

    }else{ //Caso seja acionada a opcao de sair do jogo
        printf("Ficamos a sua espera ;)\n");
        return 0;
    }

    /////////////////// jogo //////////////////////////////////

    printf("\n*       *   *      *     *  ****  ****        ****  ****  *****      *      ****  * *\n *     *   * *     * * * *  *  *  *              *  *  *  *         * *     *  *  * *\n  *   *   *****    *  *  *  *  *  ****           *  *  *  * ***    *****    ****  * *\n   * *   *     *   *     *  *  *     *        *  *  *  *  *   *   *     *   **       \n    *   *       *  *     *  ****  ****        ****  ****  *****  *       *  * *   * *\n");

    int x;
    int y;
    int turn = 1;
    int res;

    printf("\nVez do Player%d\n", turn);
    print_game(player1, player2);
    while (player1.num_ships > 0 && player2.num_ships > 0 ) {

        do{
            printf("\nEscolha as coordeadas do tiro (row, col): ");
            scanf("%d %d", &y, &x);
            x--;
            y--;
        }while(inside_table(&player1, y, x));
        //Como as matrizes tem o mesmo size verificamos só para o player1;

        if(turn == 1){
            res = aim_fire(&player2, y, x);

            if(player2.num_ships == 0){
	      printf("\n*       *       *  *  *      *   \t  ****   *          *      *   *  *****  ****     *  **\n *     * *     *   *  * *    *  *\t  *   *  *         * *      * *   *      *   *   **  **\n  *   *   *   *    *  *  *   *   \t  ****   *        *****      *    *****  ****   * *  **\n   * *     * *     *  *   *  *  *\t  *      *       *     *     *    *      **       *    \n    *       *      *  *    * *   \t  *      *****  *       *    *    *****  * *     *** **\n");
		free_memory(&player1, &player2, num);
		return 0;
            }
         }else{
            res = aim_fire(&player1, y, x);

            if(player1.num_ships == 0){
               	printf("\n*       *       *  *  *      *   \t  ****   *          *      *   *  *****  ****    ***    **\n *     * *     *   *  * *    *  *\t  *   *  *         * *      * *   *      *   *  *   *   **\n  *   *   *   *    *  *  *   *   \t  ****   *        *****      *    *****  ****       *   **\n   * *     * *     *  *   *  *  *\t  *      *       *     *     *    *      **       *       \n    *       *      *  *    * *   \t  *      *****  *       *    *    *****  * *     ****   **\n");
		free_memory(&player1, &player2, num);
		return 0;
            }
        }

	//Escolhe quem joga a seguir
        if(turn == 1 && res == -1){
            turn = 2;
            printf("------------------------------------------------\n");
            printf("\nVez do Player%d\n", turn);
            print_game(player2, player1);
        }else if(turn == 1 && res == 0){
            turn = 1;
        }else if(turn == 2 && res == -1){
            turn = 1;
            printf("------------------------------------------------\n");
            printf("\nVez do Player%d\n", turn);
            print_game(player1, player2);
        }else{
            turn = 2;
        }
   }

   return 0;
}
