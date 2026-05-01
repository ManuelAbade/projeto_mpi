#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//Se estiver a compilar no Windows 
#ifdef _WIN32 
    #include <windows.h>
#else
//Caso seja Mac/Linux
    #include <unistd.h>
#endif

#define ROWS 4
#define COLS 4
#define SIZE (ROWS*COLS)
#define TEST  0 // 0 -> Entrega; Outro -> Teste

//Struct jogada
typedef struct{
    int row,col;
} Guess;

void test_message(char message[]);
void wait_clean(unsigned int temp_sec);
void shuffle(char array[SIZE]);
void create_board(char board[ROWS][COLS],char init[]);
void print_board(char board[ROWS][COLS]);
void guess(int round, Guess *guess);

int main()
{  
    srand(time(NULL));
    int done = 0; 
    int moves = 0; 
    char array[] = {'A','A','B','B','C','C','D','D','E','E','F','F','G','G','H','H'}; //array com os valores a ser baralhados
    char board[ROWS][COLS]; //Tabuleiro com as cartas (original para comparação);
    char board_hidden[ROWS][COLS]; //Tabuleiro com * em cada posição exceto naquelas que já foram revelados
  
    create_board(board,array);

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board_hidden[i][j] = '*';
        }
    }
    
    while(done < SIZE/2)
    {
        
        Guess guess_1;
        Guess guess_2;

        print_board(board_hidden);
      
        guess(1,&guess_1);//Primeira Jogada
        if(board_hidden[guess_1.row][guess_1.col] == '*') //Se a posição da primeira jogada ainda não foi jogada (Se ainda está com *)
        {
            wait_clean(1); //Espera 1s e limpa o cmd

            board_hidden[guess_1.row][guess_1.col] = board[guess_1.row][guess_1.col];
            print_board(board_hidden);//Imprime o tabuleiro escondido com a primeira jogada


            guess(2,&guess_2); //Segunda Jogada
            if(board_hidden[guess_2.row][guess_2.col] != '*') //Verifica se aquela posição ainda não foi selecionada anteriormente (inclusivamente na primeira jogada)
            {
                printf("Nao podes jogar em casas que ja jogaste!");
                board_hidden[guess_1.row][guess_1.col] = '*'; //Caso a Jogada seja inválida a casa selecionada na sprimeira jogada passa a * denovo
                wait_clean(3); //Espera 3 segundos e limpa o cmd
                continue;
            }
        }else{
            printf("Ja jogaste essa posicao!"); //Primeira jogada inválida
            wait_clean(3);
            continue;
        }

        wait_clean(1);
        if(board[guess_1.row][guess_1.col] == board[guess_2.row][guess_2.col]) // Se as cartas selecionadas forem iguais
        {
            board_hidden[guess_2.row][guess_2.col] = board[guess_2.row][guess_2.col]; //Revela a carta 2 
            print_board(board_hidden); //Imprime o tabuleiro
            printf("ACERTASTE!!!");
            done++;
        }else
        {
            board_hidden[guess_2.row][guess_2.col] = board[guess_2.row][guess_2.col]; //revela a segunda carta
            print_board(board_hidden);//Imprime o tabuleiro a mostrar as cartas
            //Esconde ambas de novo
            board_hidden[guess_1.row][guess_1.col] = '*';
            board_hidden[guess_2.row][guess_2.col] = '*';
            printf("ERRASTE!");
        }
        
        moves++; //caso a jogada seja válida, então conta mais uma
        wait_clean(2);
        printf("\n");
    }

    printf("PARABENS!!!!\n"); //Mensagem de vitória
    printf("Realizou %d jogadas válidas.\n", moves); //Mostra o número de jogadas
    return 0; 
}


void test_message(char message[])
{
    if(TEST)printf("%s \n",message);
}

void wait_clean(unsigned int temp_sec){
    
    #ifdef _WIN32
        //Para Windows
        Sleep(temp_sec * 1000);
        system("cls");
    #else
        //Para Mac/Linux
        sleep(temp_sec);
        printf("\033[H\033[J");
    #endif
}

// Cria o tabuleiro com os elementos baralhados
void create_board(char board[ROWS][COLS],char init[])
{   
    shuffle(init);
    for (int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            board[i][j] = init[i*(COLS)+j];
        }
    }
}

//Fisher-Yates Shuffle
void shuffle(char array[SIZE])
{
    for(int i = 0; i<SIZE; i++)
    {
        unsigned int j = rand() % (SIZE-i) + i;//Dá sempre um número entre o que está a ser baralhado e os seguintes, impedindo que se altere os já escolhidos, por exemplo, na para a posição de indice 2 devolve um número entre 2 e SIZE-1;Ex.: rand() % (SIZE-2) -> 0 a SIZE - 3, +2 -> 2 a SIZE -1 ou seja o 0 e o 1 já estão fixos

        //troca
        char k = array[i];
        array[i] = array[j];
        array[j] = k;
    }
}

//Print Board
void print_board(char board[ROWS][COLS])
{   
    //Imprime tabuleiros, com o número das colunas em cima e o número das linhas no inicio de cada uma
    printf("  ");
    for (int i = 1; i <= ROWS; i++)
    {
        printf("%d ",i);
    }
    printf("\n");

    for(int i = 0; i<ROWS; i++)
    {   
        printf("%d ",i+1);
        for(int j = 0;  j<COLS; j++){
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}

//void guess(int round, int guess[],int *life)
void guess(int round, Guess *guess)
{
    int valid = 0;
    do
    {
        printf("Escolhe a %dª carta (linha coluna): ", round);//Pede a linha e a coluna separadas por um espaço
        if (scanf("%d %d", &guess->row, &guess->col) != 2) { // verifica que foram introduzidos dois números
            printf("Erro: precisa digitar dois números!\n"); //Se o scanf falhar
            while(getchar() != '\n'); //limpar o buffer
            continue;
        }
        guess->row -=1; //retira uma unidade a cada pois é introduzido de 1 a ROWS então para servir de indice passa de 0 a ROWS-1
        guess->col -=1;
        while(getchar() != '\n'); //limpar o buffer
        
        if(!(guess->row< ROWS && guess->row>=0 &&guess->col< COLS && guess->col>=0))//Verificação de posição inválida
        {
            printf("Posicao fora do tabuleiro!\n");
            continue;
        }
        valid = 1;
    }while (!valid);
    //Mensagem de teste
    char temp0[] = {'0','-',' ', guess->row + '0', '\0'};
    char temp1[] = {'1','-',' ', guess->col + '0', '\0'};
    test_message(temp0);
    test_message(temp1);
}