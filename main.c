#include<stdio.h>
#include "struct.h"

int main(){

    Game player1;
    Game player2;
    int num_ships; //numero total de barcos
    int option;  //Serve para escolher no menu

    printf("BEM VINDO!!\nInsira o tamanho do tabuleiro entre 10 e 20: ");

    scanf("%d", &player1.size);

    while(player1.size < 10 || player1.size > 20){
        printf("Por favor insira um numero entre 10 e 20: ");
        scanf("%d", &player1.size);
    }

    player1.size++;
    player2.size = player1.size;

    printf("\nTipos de Barcos:  1\t 2\t 3\t  4\t  5   \n "
           "                 *\t *\t *\t ***\t  ***\n"
           "                 \t *\t *\t  *  \t  *  \n"
           "                 \t  \t *\t     \t  *  \n");

    printf("Pressione:\n1- Colocacao manual\n2- Colocacao automatica\n3- Exit\n");
    scanf("%d", &option);

    if(option == 3){
        printf("Ficamos a sua espera ;)\n");
        return 0;

    }else if(option == 1){

        printf("\nAlgumas regras de escolha:\n"
               "1- No minimo tem de escolher 1 barco de cada tipo.\n"
               "2- O numero total de barcos nao pode exceder 16.\n"
               "Insira o numero de barcos a colocar no tabuleiro: ");

       scanf("%d", &num_ships);

       while(num_ships < 5){
        printf("\nNumero insuficiente para incluir todos os tipos de barco!!\n"
               "Quantos barcos vao querer no tabuleiro: ");
        scanf("%d", &num_ships);
       }

       //Criacao de matrix de jogo
       /////////////////////////////
       create_table(&player1, num_ships);
       create_table(&player2, num_ships);
       ////////////////////////////


       int num_type[5];

       do{
            for(int i = 0; i < 5; i++) num_type[i] = 0;

            for(int i = 0; i < 5; i++){

               do{
                printf("Numero de barcos do tipo %d: ", i+1);
                scanf("%d", &num_type[i]);
               }while(num_type[i] < 1 || num_type[i] > 5);


            player1.ships[i].type = i+1;
            player2.ships[i].type = i+1;
         }
         printf("\n");
       }while(check(num_type) != num_ships); //A funcao check vai verificar se todos os tipos estao com barcos e se a soma = num_ships

       printf("\n\nVamos agora comecar a inserir os barcos no tabuleiro segundo a ordem escolhida. Jogador2 fecha os olhos!!");

       for(int i = 0; i < num_ships; i++){
           create_ship(&player1.ships[i], player1.ships[i].type);
           create_ship(&player2.ships[i], player2.ships[i].type);
       }


       //Player1 posiciona os barcos no tabuleiro
       for(int i = 0; i < num_ships; i++){
           do{
                printf("\nCoordenadas do barco %d e a sua rotacao: ", player1.ships[i].type);
                scanf("%d %d %d", &player1.ships[i].row, &player1.ships[i].col, &player1.ships[i].rot);
                rotate(&player1.ships[i]);
           }while(add_ship_table(&player1.ships[i], &player1) == -1);

           printf("\n");
           print_table(player1);
       }


       //Player2 posiciona os barcos no tabuleiro
       printf("\n\nVamos agora comecar a inserir os barcos no tabuleiro segundo a ordem escolhida. Jogador1 fecha os olhos!!");
       for(int i = 0; i < num_ships; i++){
           do{
                printf("\nCoordenadas do barco %d e a sua rotacao: ", player1.ships[i].type);
                scanf("%d %d %d", &player2.ships[i].row, &player2.ships[i].col, &player2.ships[i].rot);
                rotate(&player2.ships[i]);
           }while(add_ship_table(&player2.ships[i], &player2) == -1);

           printf("\n");
           print_table(player2);
       }
     }


     else{


    }

    /////////////////// jogo//////////////////////////////////

  return 0;
}
