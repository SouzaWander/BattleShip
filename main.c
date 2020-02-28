#include <stdio.h>
#define SIZE 9

/*
o - água
x - barco atingido
* - posicao dos barcos
*/


struct Game{
    char** map; //Matriz
    int linhas;
    int colunas;
};


//Cria a tabela
void create_table(struct Game *player){

   //Alocar dinamicamente a memoria para char player1_map[SIZE][SIZE];
   player->map = (char **) malloc(player->linhas * sizeof(char*)); //Linhas
   for(int i = 0; i < player->linhas; i ++){
       player->map[i] = (char *) malloc (sizeof (char) * player->colunas); //Colunas
   }

  //Preencher tudo a 'o' (Agua)
  for(int i = 0; i < player->linhas; i++){
    for(int j = 0; j < player->colunas; j++){
      player->map[i][j] = 'o';
    }
  }
}

//Faz print do tabueleiro
void print_table(struct Game *player){
  for(int i = 0; i < player->linhas; i++){
    for(int j = 0; j < player->colunas; j++){
      printf("%c", player->map[i][j]);
    }
    printf("\n");
  }
}


///////////////////////////////////////////////////

struct Ship{
  //Atributes
  int dim, x, y;
  char pos;
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


/*
 * MENU:
 * Tamanho do mapa escolhido pelos dois utilizadores
 * Predefinir tipos de barcos
 * Perguntar quantos numeros de  cada tipo de barco
 * Quantos barcos querem ultizar e o tamanho?
 */


//Pos == V -> Vertical
//Pos == H -> Horizontal
/*void add_ship_table(struct Ship *barco1, struct Game *player, int x, int y, char pos){
    if(x > player->linhas || y > player->colunas){
        printf("Erro: posicao fora dos limites");
        return;
    }

    int aux = 0;
    for(int i = 0; aux < barco1->dim; i++,aux++){
        if((pos == 0 && i+y > player->colunas) ||(pos == 1 && i+x > player->linhas)){
            printf("Ultrapassa os limites do tabuleiro\n");
            return;
        }else if((player->map[x-1][i+y-1] == '*')){
            printf("Posicao ja ocupada com outro navio\n");
            return;
        }
    }

    if(pos == 'H'){ //Horizontal
        aux = 0;
        for(int i = 0; aux < barco1->dim; i++, aux++){
           player->map[i+x-1][y-1] = '*';
        }
    }else{   //Vertical
        aux = 0;
        for(int i = 0; aux < barco1->dim; i++, aux++){
           //printf("%d:%d\n",i,y);
           player->map[x-1][i+y-1] = '*';
        }
      return;
    }
}*/

void add_ship_table(struct Ship *ship1, struct Game *player, int row, int col, char pos){
  /*mudar os returns para zeros ou 1 para poder lidar com os erros*/

  //Se coordeadas introduzidas não pertcerem as dimensoes do map
  if(row > player->linhas || col > player->colunas){
      printf("Erro: posicao fora dos limites");
      return;
  }

  switch (pos) {
    /*Nas opçoes de posicionamento onde ha deslocamento vertical o valor das colunas é fixo e o das linhas varia*/
    //up
    case 'u': if(row - (ship1->dim) + 1 < 0){
                printf("Ultrapassa os limites do mapa\n");
                return;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = row - ship1->dim + 1 ; i <= row; i++){
                if((player->map[i][col] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return;
                }
              }

              //Se tiver todas as condições favoraveis para add o navio

              for(int i = row - ship1->dim + 1 ; i <= row; i++){
                player->map[i][col] = '*';
              }
              break;

    //down
    case 'd': if(row + (ship1->dim) -1 > player->linhas){
                printf("Ultrapassa os limites do mapa\n");
                return;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = row ; i <= row + ship1->dim - 1; i++){
                if((player->map[i][col] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return;
                }
              }

              //Se tiver todas as condições favoraveis para add o navio

              for( int i = row ; i <= row + ship1->dim - 1; i++){
                player->map[i][col] = '*';
              }
              break;
    /*Nas opçoes de posicionamento onde ha deslocamento lateral o valor da linha é fixo e o das colunas varia*/
    //left
    case 'l': if(col - (ship1->dim) + 1 < 0){
                printf("Ultrapassa os limites do mapa\n");
                return;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = col - ship1->dim + 1 ; i <= col; i++){
                if((player->map[row][i] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return;
                }
              }

              //Se tiver todas as condições favoraveis para add o navio

              for(int i = col - ship1->dim + 1 ; i <= col; i++){
                player->map[row][i] = '*';
              }
              break;

    //right
    case 'r': if(col + (ship1->dim) -1 > player->linhas){
                printf("Ultrapassa os limites do mapa\n");
                return;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = col ; i <= col + ship1->dim - 1; i++){
                if((player->map[row][i] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return;
                }
              }

              //Se tiver todas as condições favoraveis para add o navio

              for( int i = col ; i <= col + ship1->dim - 1; i++){
                player->map[row][i] = '*';
              }
              break;
    default: printf("\nInsira uma opção valida!!\n" );
  }
}

//////////////////////////////////////////////////////////////////////7

int main(){



  printf("Bem vindo ao BattleShip!\n"
         "Antes de comecarmos o jogo gostaria de vos conhecer melhor...\n"
         "Nome do primeiro jogador: \n"
         "Nome do segundo jogador: \n"
         "Bem vindos ... e ...! Para comecarmos o jogo preciso de saber:\n"
         "1 - Introducao manual\n"
         "2 - Introducao automatica\n");

  struct Game player1;
  struct Game player2;

  struct Ship teste;
  teste.dim = 3;

  player1.linhas = 10;
  player1.colunas = 10;

  create_table(&player1);

  int row, col;
  char pos;
  for(int i = 0; i < 5; i++){
      printf("Insira row, col, pos: ");
      scanf("%d %d %c", &row, &col,&pos);
      add_ship_table(&teste, &player1, row-1, col-1, pos);
      print_table(&player1);
  }
  //add_ship_table(&teste, &player1, 2, 3, 0); //(y,x)


  return 0;
}
