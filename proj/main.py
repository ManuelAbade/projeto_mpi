from random import shuffle
from time import sleep
import os
import copy

def criar_tabuleiro()->list:
    mtrx = ['@','@','#','#','$','$','%','%','&','&','£','£','§','§','?','?']
    shuffle(mtrx)
    sec = []
    for i in range(4):
        sec.append([])
        for j in range(4):
            sec[i].append(mtrx[i*4+j])
    return sec

def imprimir_tab(lista:list):
    print(' ',*range(1,5) )
    for i in range(len(lista)):
        print(i +1,*lista[i])
    

def guess(round) -> list:
    while True:
        g = input(f"Escolhe a {round}ª carta (linha coluna): ").split()
        if len(g) == 2 and all(x.isdigit() for x in g):
            return [int(g[0]), int(g[1])]
        print("Input inválido!")


def verificar(first:list,second:list,tabuleiro:list,escondido:list,jogadas:list)-> bool:
    if tabuleiro[first[0]][first[1]] == tabuleiro[second[0]][second[1]] and jogadas[first[0]][first[1]] == None and jogadas[second[0]][second[1]] ==None:
        escondido[first[0]][first[1]] = tabuleiro[first[0]][first[1]]
        escondido[second[0]][second[1]] = tabuleiro[second[0]][second[1]]
        imprimir_tab(escondido)
        jogadas[first[0]][first[1]] = 1
        jogadas[second[0]][second[1]] = 1
        print("Acertas-te!")
        return True
    elif jogadas[first[0]][first[1]] == None and jogadas[second[0]][second[1]] == None:
        esc2 = copy.deepcopy(escondido)
        esc2[first[0]][first[1]] = tabuleiro[first[0]][first[1]]
        esc2[second[0]][second[1]] = tabuleiro[second[0]][second[1]]
        imprimir_tab(esc2)
        print("Erras-te!")
        return False
    else:
        print("Não podes jogar em casas que já jogaste")


def jogar():
    acabar = False
    tentativas = 0

    tab = [['*' for _ in range(4)] for _ in range(4)]
    jogadas = [[None for _ in range(4)] for _ in range(4)]
    sec = criar_tabuleiro()

   
    
    os.system('cls')
    imprimir_tab(sec)
    sleep(5)
    os.system('cls')
    certas = 0
    while certas != 16:

        guess_1 = [0,0]
        guess_2 = [0,0]
        valid = [0,1,2,3]
        print(' ',*range(1,5) )
        for i in range(len(tab)):
            print(i +1,*tab[i])
        #print(guess)
        guess_1 = guess(1)
        if guess_1[0] - 1 in valid and guess_1[1] -1 in valid:
            guess_1[0] -= 1
            guess_1[1] -= 1
            guess_2 = guess(2)
            if not (guess_2[0] -1 in valid) or not(guess_2[1] -1 in valid):
                print("Posição inválida!")
                sleep(2)
                os.system('cls')
                continue
            guess_2[0] -= 1
            guess_2[1] -= 1
        else:
            print("Posição inválida!")
            sleep(2)
            os.system('cls')
            continue
        
        if guess_1 == guess_2:
            print("Não podes escolher a mesma carta!")
            continue
        tentativas += 1
        if verificar(guess_1,guess_2,sec,tab,jogadas):
            certas += 2

        sleep(5)
        os.system('cls')
    print(f"PARABÉNS!!! Concluiste o jogo com {tentativas}!!")
jogar()
        
        
