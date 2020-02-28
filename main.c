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
void add_ship_table(struct Ship *barco1, struct Game *player, int x, int y, char pos){
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

  int y, x;
  char pos;
  for(int i = 0; i < 5; i++){
      printf("Insira x, y, pos: ");
      scanf("%d %d %c", &x, &y,&pos);
      add_ship_table(&teste, &player1, y, x, pos); //(y,x)
      print_table(&player1);
  }
  //add_ship_table(&teste, &player1, 2, 3, 0); //(y,x)


  return 0;
}
