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
  int up_size;
  int down_size;
  int left_size;
  int right_size;

};

  //int alive = 1;
  /* Se a posicao (x,y) corresponder a um barco e ainda nao tiver sido
  atingida aumentamos a var shot e mudamos o simbolo no Table. Se shot == dim
  mudamos o atributo alive para 0
  */


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


void add_weird_ship_table(struct Ship *ship1, struct Game *player, int row, int col, char pos){
  //Se coordeadas introduzidas não pertcerem as dimensoes do map
  if(row > player->linhas || col > player->colunas){
      printf("Erro: posicao fora dos limites");
      return;
  }



}

int add_ship_table(struct Ship *ship1, struct Game *player, int row, int col, char pos){
  /*mudar os returns para zeros ou 1 para poder lidar com os erros*/

  //Se coordeadas introduzidas não pertcerem as dimensoes do map
  if(row > player->linhas || col > player->colunas){
      printf("Erro: posicao fora dos limites");
      return 0;
  }

  switch (pos) {
    /*Nas opçoes de posicionamento onde ha deslocamento vertical o valor das colunas é fixo e o das linhas varia*/
    //up//Se coordeadas introduzidas não pertcerem as dimensoes do map
  if(row > player->linhas || col > player->colunas){
      printf("Erro: posicao fora dos limites");
      return 0;
  }
    case 'u': if(row - (ship1->dim) + 1 < 0){
                printf("Ultrapassa os limites do mapa\n");
                return 0;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = row - ship1->dim + 1 ; i <= row; i++){
                if((player->map[i][col] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return 0;
                }
              }

              //Se tiver todas as condições favoraveis para add o navio

              for(int i = row - ship1->dim + 1 ; i <= row; i++){
                player->map[i][col] = '*';
              }
              break;

    //down
    case 'd': if(row + (ship1->dim) -1 > player->linhas - 1){
                printf("Ultrapassa os limites do mapa\n");
                return 0;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = row ; i <= row + ship1->dim - 1; i++){
                if((player->map[i][col] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return 0;
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
                return 0;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = col - ship1->dim + 1 ; i <= col; i++){
                if((player->map[row][i] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return 0;
                }
              }

              //Se tiver todas as condições favoraveis para add o navio

              for(int i = col - ship1->dim + 1 ; i <= col; i++){
                player->map[row][i] = '*';
              }
              break;

    //right
    case 'r': if(col  + (ship1->dim) -1 > player->linhas -1 ){
                printf("Ultrapassa os limites do mapa\n");
                return 0;
              }
              //começa a analisar dese da posiçao final do barco ate a cordenada introduzida se o espaço esta livre
              for(int i = col ; i <= col + ship1->dim - 1; i++){
                if((player->map[row][i] == '*')){
                    printf("Posicao ja ocupada com outro navio\n");
                    return 0;
                }
              }

              //Se tiver todas as condições favoraveis para add o navio

              for( int i = col ; i <= col + ship1->dim - 1; i++){
                player->map[row][i] = '*';
              }
              break;
    default: printf("\nInsira uma opção valida!!\n" );
            return 0;
  }
  return 1;
}

//funçao atirar
void aim_fire(struct Game *player, int row, int col){
  if(player->map[row][col] == 'o'){
    printf("Tiro na agua!\n");
  }
  else if(player->map[row][col] == 'x'){
    printf("Posi ja foi atingida");
  }
  else if(player->map[row][col] == '*'){
    player->map[row][col] = 'x';
    printf("Acertou");
    //atualizar pontuação
  }
}

//////////////////////////////////////////////////////////////////////7

int main(){
  /*printf("Bem vindo ao BattleShip!\n"
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
  }*/

  struct Game player1;
  struct Game player2;

  int map_size;
  int n_ships;
  int option;

  printf("BattleShip\n");

  printf("Map size:\n");
  scanf("%d", &map_size);

  printf("Nº Ships\n");
  scanf("%d", &n_ships);
  printf("1-Manual  2- Auto\n");
  scanf("%d", &option);

  player1.linhas = map_size;
  player1.colunas = map_size;
  create_table(&player1);
  print_table(&player1);

  struct Ship teste;
  teste.dim = 3;

  int row;
  int col;
  char pos;

  /*for(int i = 0; i < n_ships; i++){
    printf("Insira row, col, pos: ");
    scanf("%d %d %c", &row, &col,&pos);
    if(add_ship_table(&teste, &player1, row-1, col-1, pos) == 1){
      print_table(&player1);
    }
    else i--;
  }*/

  for(int i = 0; i < n_ships; i++){
    int aux_pos = rand()%4;

    switch (aux_pos) {
      case 0: pos = 'u';
              break;

      case 1: pos = 'd';
              break;

      case 2: pos = 'l';
              break;
      case 3: pos = 'r';
              break;
    }
    printf("\nposiçao gerada aleatoria mente: %d %c\n", aux_pos, pos);

    if(add_ship_table(&teste, &player1, rand() % player1.linhas, rand() % player1.colunas, pos) == 1){
      print_table(&player1);
    }
    else {i--;}
  }

  return 0;
}
