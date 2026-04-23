#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define ROWS 4
#define COLS 4
#define SIZE (ROWS*COLS)
//#define LIFE 4
#define test  0 // 0 -> Entrega; Outro -> Teste

void test_mensage(char mensage[]);
void wait_clean(unsigned int temp_sec);
void shuffle(char array[SIZE]);
void create_board(char board[ROWS][COLS],char init[]);
void print_board(char lista[ROWS][COLS]);
//void guess(int round, int guess[],int *life);
void guess(int round, int guess[]);
//int verify(int guess_1[],int guess_2[],char board[ROWS][COLS],char board_hiden[ROWS][COLS],int played[ROWS][COLS],int *life);
int verify(int guess_1[],int guess_2[],char board[ROWS][COLS],char board_hiden[ROWS][COLS],int played[ROWS][COLS]);
void show_first_guess(int guess_1[],char board[ROWS][COLS],char board_hiden[ROWS][COLS],int played[ROWS][COLS]);

int main()
{  
    srand(time(NULL));
    int done = 0;
    char mtrx[] = {'A','A','B','B','C','C','D','D','E','E','F','F','G','G','H','H'};
    //int life = LIFE;
    char board[ROWS][COLS];
    char board_hiden[ROWS][COLS];
    int played[ROWS][COLS];
    
    create_board(board,mtrx);//Set the board with the cards

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board_hiden[i][j] = '*';
            played[i][j] = 0;
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
        print_board(board_hiden);
        //guess(1,guess_1,&life);
        guess(1,guess_1);
        if( played[guess_1[0]][guess_1[1]] == 0)
        {
            wait_clean(1);
            // printf("VIDA: ");
            // for(int i = 0; i < life; i++)
            // {
            //     printf("# ");
            // }
            //printf("\n");
            show_first_guess(guess_1,board,board_hiden,played);
            //guess(2,guess_2,&life);
            guess(2,guess_2);

            
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
        //if(verify(guess_1,guess_2,board,board_hiden,played,&life))
        if(verify(guess_1,guess_2,board,board_hiden,played))
        {
            done++;
        }
        wait_clean(2);
        printf("\n");
    }
    // if(life != 0)printf("PARABENS!!!!");
    //else printf("Perdeste!!!!");
    printf("PARABENS!!!!");
    return 0; 
}

void test_mensage(char mensage[])
{
    if(test)printf("%s \n",mensage);
}

void wait_clean(unsigned int tem_sec){
    Sleep(tem_sec*1000);
    system("cls");
}

//Create the Board with suffeled elements
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
    printf("%2.c",' ');
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
        printf(" Escolhe a %dª carta (linha coluna): ",round);
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
    char temp0[10] = {'0','-',' ', guess[0] + '0', '\0'};
    char temp1[10] = {'1','-',' ', guess[1] + '0', '\0'};
    test_mensage(temp0);
    test_mensage(temp1);
  
}

//int verify(int guess_1[],int guess_2[], char board[ROWS][COLS],char board_hiden[ROWS][COLS],int played[ROWS][COLS],int *life)
int verify(int guess_1[],int guess_2[], char board[ROWS][COLS],char board_hiden[ROWS][COLS],int played[ROWS][COLS])
{
    if(board[guess_1[0]][guess_1[1]] == board[guess_2[0]][guess_2[1]] && played[guess_2[0]][guess_2[1]] == 0 )
    {
        board_hiden[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
        board_hiden[guess_2[0]][guess_2[1]] = board[guess_2[0]][guess_2[1]];
        print_board(board_hiden);
        played[guess_1[0]][guess_1[1]] = 1;
        played[guess_2[0]][guess_2[1]] = 1;
        printf("Acertaste!\n");
        // if(*life != LIFE){
        //     printf("+1 Vida");
        //     (*life)++;
        // }
        return 1;
    }
    else if(played[guess_1[0]][guess_1[1]] == 0 && played[guess_2[0]][guess_2[1]] == 0)
    {
        char faild[ROWS][COLS];
        //Create initial board with * in each position
        for(int i = 0; i< ROWS; i++){
            for (int j = 0; j < COLS; j++)
            {
                faild[i][j] = board_hiden[i][j];
            }
        }
        faild[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
        faild[guess_2[0]][guess_2[1]] = board[guess_2[0]][guess_2[1]];
        print_board(faild);
        printf("Erraste!");
        //(*life)--;
        return 0;

    }else
    {
        printf("Nao podes jogar em casas que ja jogaste!");
        //(*life)--;
        return 0;
    }
}

void show_first_guess(int guess_1[],char board[ROWS][COLS],char board_hiden[ROWS][COLS],int played[ROWS][COLS])
{
    if ( played[guess_1[0]][guess_1[1]] == 0)
    {
        char temporary[ROWS][COLS];
        for(int i = 0; i< ROWS; i++){
            for (int j = 0; j < COLS; j++)
            {
                temporary[i][j] = board_hiden[i][j];
            }
        }
        temporary[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
        print_board(temporary);
    }
}