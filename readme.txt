Ao inicializarmos o jogo é-nos mostrado um menu onde pede para escolhermos uma opção. Ao introduzir '1' vamos entrar na colocação manual, '2' na colocação automática e qualquer outra tecla o programa termina e o jogo acaba.

Opção 1 (Manual):
De seguida, é nos pedido um int com o tamanho do tabuleiro, ao inserir por exemplo 20 será criado um tabuleiro 20*20. O número total de barcos a inserir no tabuleiro por jogador, que no minimo tem de ser 5 e para cada tipo de barco é pedido o respetivo numero de barcos a inserir desse tipo.

Por fim, temos de inserir as coordenadas e a rotação de todos os barcos. Por exemplo, para inserir na linha 5, coluna 10 e rotação 90 é necessário inserir "5 10 90".

Opção 2 (Automático):
É tudo feito automaticamente,  quer a decisão do tamanho do tabuleiro quer as coordenadas e rotação dos barcos.


Passando agora ao jogo em si:
Em cada inicio de turno serão mostradas 2 tabelas. Uma com o tabuleiro do jogador onde é mostrado as posições dos barcos e se já foi atingido ou não ("X" se tiver atingido e uma letra predefinida de acordo com o tipo de barco caso ainda não tenha sido atingido) e uma segunda tabela onde será mostrado os tiros efetuados no tabuleiro adversário. Posteriormente são pedidas as coordenadas de tiro, aqui basta indicar a linha e a coluna. Para colocar na linha 1 e coluna 1 é necessário introduzir "1 1". O jogo continua assim até acabar, mudando de turno cada vez que um jogador não acerta num barco adversário, caso acerte continua a jogar até falhar. 

