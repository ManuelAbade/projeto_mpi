#include <stdio.h>   // Biblioteca para input/output (printf, scanf)
#include <time.h>    // Biblioteca para usar time() (seed aleatória)
#include <stdlib.h>  // Biblioteca para rand(), srand(), system()

//Se estiver a compilar no Windows 
#ifdef _WIN32 
    #include <windows.h> // Para usar Sleep() e limpar consola
#else
//Caso seja Mac/Linux
    #include <unistd.h> // Para usar sleep()
#endif

// Definição do tamanho do tabuleiro
#define ROWS 4 
#define COLS 4
#define SIZE (ROWS*COLS) // Total de cartas
#define TEST  0 // 0 -> modo normal; outro valor ativa mensagens de teste

// Estrutura que representa uma jogada (linha e coluna)
typedef struct{
    int row,col;
} Guess;

// Protótipos das funções
void test_message(char message[]);
void wait_clean(unsigned int temp_sec);
void shuffle(char array[SIZE]);
void create_board(char board[ROWS][COLS],char init[]);
void print_board(char board[ROWS][COLS]);
void guess(int round, Guess *guess);

int main()
{  
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    int done = 0;  // Número de pares encontrados
    int moves = 0;  // Número de jogadas válidas feitas
    char array[] = {'A','A','B','B','C','C','D','D','E','E','F','F','G','G','H','H'}; //array com os valores a ser baralhados

    char board[ROWS][COLS]; // Tabuleiro real (valores escondidos)
    char board_hidden[ROWS][COLS]; // Tabuleiro visível ao jogador
  
    // Cria o tabuleiro com cartas baralhadas
    create_board(board,array);

    // Inicializa o tabuleiro visível com '*'
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board_hidden[i][j] = '*';
        }
    }

    // Ciclo principal do jogo
    while(done < SIZE/2) // Termina quando todos os pares forem encontrados
    {
        
        Guess guess_1;
        Guess guess_2;

        print_board(board_hidden); // Mostra o estado atual
      
        guess(1,&guess_1); // Primeira jogada

        //Verificar se a posição da primeira jogada ainda não foi jogada (Se ainda está com *)
        if(board_hidden[guess_1.row][guess_1.col] == '*') 
        {
            wait_clean(1); // Espera 1 segundo e limpa consola

            // Revela primeira carta
            board_hidden[guess_1.row][guess_1.col] = board[guess_1.row][guess_1.col];
            print_board(board_hidden);


            guess(2,&guess_2); //Segunda Jogada

            //Verificar se aquela posição ainda não foi selecionada anteriormente (inclusivamente na primeira jogada)
            if(board_hidden[guess_2.row][guess_2.col] != '*') 
            {
                printf("Nao podes jogar em casas que ja jogaste!");
                //Caso a jogada seja inválida a casa selecionada na primeira jogada passa a * 
                board_hidden[guess_1.row][guess_1.col] = '*'; 
                wait_clean(3); 
                continue; // Recomeça a jogada
            }
        }else{
            printf("Ja jogaste essa posicao!"); //Primeira jogada inválida
            wait_clean(3);
            continue;
        }

        wait_clean(1);

        // Verificar se as duas cartas são iguais
        if(board[guess_1.row][guess_1.col] == board[guess_2.row][guess_2.col])
        {
            // Revela definitivamente a segunda carta
            board_hidden[guess_2.row][guess_2.col] = board[guess_2.row][guess_2.col];
            print_board(board_hidden);

            printf("ACERTASTE!!!");
            done++; // Incrementa pares encontrados
        }else
        {
            // Revela temporariamente a segunda carta
            board_hidden[guess_2.row][guess_2.col] = board[guess_2.row][guess_2.col]; 
            print_board(board_hidden);

            // Volta a esconder ambas
            board_hidden[guess_1.row][guess_1.col] = '*';
            board_hidden[guess_2.row][guess_2.col] = '*';
            printf("ERRASTE!");
        }
        
        moves++; // Conta jogada válida
        wait_clean(2);
        printf("\n");
    }

    // Mensagem final
    printf("PARABENS!!!!\n"); 
    printf("Realizou %d jogadas válidas.\n", moves); 
    return 0; 
}

// Mostra mensagens de teste se TEST estiver ativo
void test_message(char message[])
{
    if(TEST)printf("%s \n",message);
}

// Espera alguns segundos e limpa o ecrã
void wait_clean(unsigned int temp_sec){
    
    #ifdef _WIN32
        //Para Windows
        Sleep(temp_sec * 1000); // Espera em milissegundos
        system("cls");          // Limpa consola Windows
    #else
        //Para Mac/Linux 
        sleep(temp_sec);        // Espera em segundos
        printf("\033[H\033[J"); // Limpa consola Unix
    #endif
}

// Cria o tabuleiro com os elementos baralhados
void create_board(char board[ROWS][COLS],char init[])
{   
    shuffle(init); // Baralha o array inicial

    // Copia para o tabuleiro original
    for (int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            board[i][j] = init[i*(COLS)+j];
        }
    }
}

// Algoritmo de Fisher-Yates para baralhar o array
void shuffle(char array[SIZE])
{
    for(int i = 0; i<SIZE; i++)
    {
        // Escolhe posição aleatória válida
        unsigned int j = rand() % (SIZE-i) + i;
        //Dá sempre um número entre o que está a ser baralhado e os seguintes, impedindo que se altere os elementos anteriores (fixos), por exemplo, na para a posição de indice 2 devolve um número entre 2 e SIZE-1;Ex.: rand() % (SIZE-2) -> 0 a SIZE - 3, +2 -> 2 a SIZE -1 ou seja o 0 e o 1 já estão fixos

        // Troca elementos
        char k = array[i];
        array[i] = array[j];
        array[j] = k;
    }
}

// Imprime o tabuleiro formatado
void print_board(char board[ROWS][COLS])
{   
    //Imprime tabuleiros, com o número das colunas em cima e o número das linhas no inicio de cada uma
    printf("  ");

    // Imprime números das colunas
    for (int i = 1; i <= ROWS; i++)
    {
        printf("%d ",i);
    }
    printf("\n");

    // Imprime cada linha
    for(int i = 0; i<ROWS; i++)
    {   
        printf("%d ",i+1);
        for(int j = 0;  j<COLS; j++){
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}

// Função para obter uma jogada válida do jogador
void guess(int round, Guess *guess)
{
    int valid = 0;
    do
    {
        // Pedir coordenadas
        printf("Escolhe a %dª carta (linha coluna): ", round);//Pede a linha e a coluna separadas por um espaço

        // Validar input
        if (scanf("%d %d", &guess->row, &guess->col) != 2) { // verifica que foram introduzidos dois números
            printf("Erro: precisa digitar dois números!\n"); //Se o scanf falhar
            while(getchar() != '\n'); // Limpar o buffer 
            continue;
        }
        // Ajusta para índice (0-based)
        guess->row -=1; 
        guess->col -=1;

        while(getchar() != '\n'); //limpar o buffer ->Elimina o lixo da consola. 
        //Ex.: input : 3 3 3 | caso não se limpasse o buffer a jogara atual seria 3 3 e a segunte seria 3 (primeiro número introduzido na jogada seguinte) e depois o segundo elemento afetaria a jogada seguinte e assim por diante.

        if(!(guess->row< ROWS && guess->row>=0 &&guess->col< COLS && guess->col>=0))//Verificação de posição inválida
        {
            printf("Posicao fora do tabuleiro!\n");
            continue;
        }

        valid = 1;
    }while (!valid);
    
    // Mensagens de debug
    char temp0[] = {'0','-',' ', guess->row + '0', '\0'};
    char temp1[] = {'1','-',' ', guess->col + '0', '\0'};
    test_message(temp0);
    test_message(temp1);
}