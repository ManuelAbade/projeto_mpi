#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define ROWS 4
#define COLS 4
#define SIZE (ROWS*COLS)
//#define LIFE 4
#define TEST  0 // 0 -> Entrega; Outro -> Teste

void test_message(char message[]);
void wait_clean(unsigned int temp_sec);
void shuffle(char array[SIZE]);
void create_board(char board[ROWS][COLS],char init[]);
void print_board(char board[ROWS][COLS]);
//void guess(int round, int guess[],int *life);
void guess(int round, int guess[]);
//int verify(int guess_1[],int guess_2[],char board[ROWS][COLS],char board_hiden[ROWS][COLS],int *life);
int verify(int guess_1[],int guess_2[],char board[ROWS][COLS]);


int main()
{  
    srand(time(NULL));
    int done = 0; 
    int moves = 0; 
    char array[] = {'A','A','B','B','C','C','D','D','E','E','F','F','G','G','H','H'};
    //int life = LIFE;
    char board[ROWS][COLS];
    char board_hidden[ROWS][COLS];
  
    
    create_board(board,array);

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board_hidden[i][j] = '*';

        }
    }

    //while(done < SIZE/2 && life != 0)
    while(done < SIZE/2)
    {
        
        int guess_1[2] = {0,0};
        int guess_2[2] = {0,0};
        // printf("VIDA: ");
        // for(int i = 0; i < life; i++)
        // {
        //     printf("# ");
        // }
        // printf("\n");
        print_board(board_hidden);
        //guess(1,guess_1,&life);
        guess(1,guess_1);
        if(board_hidden[guess_1[0]][guess_1[1]] == '*')
        {
            wait_clean(1);
            // printf("VIDA: ");
            // for(int i = 0; i < life; i++)
            // {
            //     printf("# ");
            // }
            //printf("\n");
            board_hidden[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
            print_board(board_hidden);
            //guess(2,guess_2,&life);
            guess(2,guess_2);
            if(board_hidden[guess_2[0]][guess_2[1]] != '*')
            {
                printf("Nao podes jogar em casas que ja jogaste!");
                board_hidden[guess_1[0]][guess_1[1]] = '*';
                //(*life)--;
                wait_clean(3);
                continue;
            }
        }else{
            printf("Ja jogaste essa posicao!");
            //life--;
            wait_clean(3);
            continue;
        }
        if(guess_1[0] == guess_2[0] && guess_1[1] == guess_2[1])
        {
            printf("Nao podes escolher a mesma carta!");
            //life--;
            wait_clean(3);
            continue;
        }
        
        wait_clean(1);
        //if(verify(guess_1,guess_2,board,board_hiden,&life))
        if(verify(guess_1,guess_2,board,board_hidden))
        {
            board_hidden[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
            board_hidden[guess_2[0]][guess_2[1]] = board[guess_2[0]][guess_2[1]];
            print_board(board_hidden);
            printf("ACERTASTE!!!");
            done++;
        }else
        {
            board_hidden[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
            board_hidden[guess_2[0]][guess_2[1]] = board[guess_2[0]][guess_2[1]];
            print_board(board_hidden);
            board_hidden[guess_1[0]][guess_1[1]] = '*';
            board_hidden[guess_2[0]][guess_2[1]] = '*';
            printf("ERRASTE!");
        }
        
        moves++;
        wait_clean(2);
        printf("\n");
    }
    // if(life != 0)printf("PARABENS!!!!");
    //else printf("Perdeste!!!!");
    printf("PARABENS!!!!\n");
    printf("Realizou %d jogadas válidas.\n", moves);
    return 0; 
}


void test_message(char message[])
{
    if(TEST)printf("%s \n",message);
}

void wait_clean(unsigned int temp_sec){
    Sleep(temp_sec*1000);
    system("cls");
}

// Create the board with shuffled elements
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
        unsigned int j = rand() % (SIZE-i) + i;
        char k = array[i];
        array[i] = array[j];
        array[j] = k;
    }
}

//Print Board
void print_board(char board[ROWS][COLS])
{   
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
void guess(int round, int guess[])
{
    int valid = 0;
    do
    {
        printf("Escolhe a %dª carta (linha coluna): ", round);
        if (scanf("%d %d", &guess[0], &guess[1]) != 2) {
            printf("Erro: precisa digitar dois números!\n");
            while(getchar() != '\n'); //limpar o buffer
        }
        guess[0]--;
        guess[1]--;
        
        if(!(guess[0]< ROWS && guess [0]>=0 &&guess[1]< COLS && guess[1]>=0))
        {
            printf("Posicao fora do tabuleiro!\n");
            //(*life)--;
            continue;
        }
        valid = 1;
    }while (!valid);
    char temp0[] = {'0','-',' ', guess[0] + '0', '\0'};
    char temp1[] = {'1','-',' ', guess[1] + '0', '\0'};
    test_message(temp0);
    test_message(temp1);
  
}

//int verify(int guess_1[],int guess_2[], char board[ROWS][COLS],char board_hiden[ROWS][COLS],int *life)
int verify(int guess_1[],int guess_2[], char board[ROWS][COLS])
{
    if(board[guess_1[0]][guess_1[1]] == board[guess_2[0]][guess_2[1]])
    {
        // if(*life != LIFE){
        //     printf("+1 Vida");
        //     (*life)++;
        // }
        return 1;
    }
    else 
    {
        //(*life)--;
        return 0;
    }
}

