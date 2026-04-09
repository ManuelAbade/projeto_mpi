#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define ROWS 4
#define COLS 4
#define SIZE (ROWS*COLS)

void wait_clean(unsigned int temp_sec);
void shuffle(char *array);
void create_board(char **board,char init[]);
void print_board(char **lista);
void guess(int round, int guess[]);
int verify(int guess_1[],int guess_2[],char **board,char **board_hiden,int **played);

int main()
{  
    srand(time(NULL));
    int done = 0;
    int tries = 0;
    char mtrx[] = {'A','A','B','B','C','C','D','D','E','E','F','F','G','G','H','H'};

    char **board = malloc(ROWS*sizeof(char*));
    char **board_hiden = malloc(ROWS*sizeof(char*));
    int **played = malloc(ROWS*sizeof(char*));
    
    for(int i = 0; i< ROWS; i++){
        board[i] = malloc(COLS*sizeof(char));
    }

    for(int i = 0; i< ROWS; i++){
        board_hiden[i] = malloc(COLS*sizeof(char));
    }
    
    for(int i = 0; i< ROWS; i++){
        played[i] = malloc(COLS*sizeof(char));
    }
    
    //Create initial board with * in each position
    for(int i = 0; i< ROWS; i++){
        for (int j = 0; j < COLS; j++)
        {
            board_hiden[i][j] = '*';
        }
    }

    //Initialize played with 0 because no cards have been played yet
    for(int i = 0; i< ROWS; i++){
        for (int j = 0; j < COLS; j++)
        {
            played[i][j] = 0;
        }
    }

    create_board(board,mtrx);//Set the board with the cards

    print_board(board); //Print the board and show for 5 seconds
    wait_clean(10);
    

    while(done < SIZE/2){
        int guess_1[2] = {0,0};
        int guess_2[2] = {0,0};

        print_board(board_hiden);
        guess(1,guess_1);
        if(guess_1[0]< ROWS && guess_1[0]>=0 &&guess_1[1]< ROWS && guess_1[1]>=0)
        {
            wait_clean(2);
            verify(guess_1,guess_2,board,board_hiden,played);
            guess(2,guess_2);
            if(!(guess_2[0]< ROWS && guess_2[0]>=0 &&guess_2[1]< ROWS && guess_2[1]>=0))
            {
                printf("Posicao invalida!");
                wait_clean(3);
                continue;
            }
        }else{
            printf("Posicao invalida!");
            wait_clean(3);
            continue;
        }
        if(guess_1[0] == guess_2[0] && guess_1[1] == guess_2[1])
        {
            printf("Nao podes escolher a mesma carta!");
            wait_clean(3);
            continue;
        }
        tries++;
        wait_clean(2);
        if(verify(guess_1,guess_2,board,board_hiden,played))
        {
            done++;
        }
        wait_clean(2);
        printf("\n");
    }
    printf("PARABENS!!!!");
    free(board);
    free(board_hiden);
    free(played);
    board = NULL;
    board_hiden = NULL;
    played = NULL;

    return 0; 
}



void wait_clean(unsigned int tem_sec){
    Sleep(tem_sec*1000);
    system("cls");
}

//Create the Board with suffeled elements
void create_board(char **board,char *init)
{   
    shuffle(init);
    for (int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            board[i][j] = init[i*(ROWS)+j];
        }
    }
}

//Fisher-Yates Shuffle
void shuffle(char *array)
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
void print_board(char **board)
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


void guess(int round, int guess[])
{
    do
    {
        printf(" Escolhe a %dª carta (linha coluna): ",round);
        if (scanf("%d %d", &guess[0], &guess[1]) != 2) {
            printf("Erro: precisa digitar dois números!\n");
        }
    }while (!guess[0] || !guess[1]);
    guess[0] = guess[0]-1;
    guess[1] = guess[1]-1;
  
}

int verify(int guess_1[],int guess_2[],char **board,char **board_hiden,int **played)
{
    if(guess_2[0] != 0 && guess_2 [0] != 0 && board[guess_1[0]][guess_1[1]] == board[guess_2[0]][guess_2[1]] && played[guess_1[0]][guess_1[1]] == 0 && played[guess_2[0]][guess_2[1]] == 0 )
    {
        board_hiden[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
        board_hiden[guess_2[0]][guess_2[1]] = board[guess_2[0]][guess_2[1]];
        print_board(board_hiden);
        played[guess_1[0]][guess_1[1]] +=1;
        played[guess_2[0]][guess_2[1]] +=1;
        printf("Acertaste!");
        return 1;
    }else if (guess_2[0] == 0 && guess_2 [0] == 0 && played[guess_1[0]][guess_1[1]] == 0)
    {
        char **temporary = malloc(ROWS*sizeof(char*));
        for(int i = 0; i< ROWS; i++){
            temporary[i] = malloc(COLS*sizeof(char));
        }

        //Create initial board with * in each position
        for(int i = 0; i< ROWS; i++){
            for (int j = 0; j < COLS; j++)
            {
                temporary[i][j] = board_hiden[i][j];
            }
        }
        temporary[guess_1[0]][guess_1[1]] = board[guess_1[0]][guess_1[1]];
        print_board(temporary);
        free(temporary);
        temporary = NULL;
        return 0; 
    }
    else if(played[guess_1[0]][guess_1[1]] == 0 && played[guess_2[0]][guess_2[1]] == 0)
    {
        char **faild = malloc(ROWS*sizeof(char*));
        for(int i = 0; i< ROWS; i++){
            faild[i] = malloc(COLS*sizeof(char));
        }

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
        printf("Erras-te!");
        free(faild);
        faild = NULL;
        return 0;

    }else
    {
        printf("Nao podes jogar em casas que ja jogas-te!");
    }
}

