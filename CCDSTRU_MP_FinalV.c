/******************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and 
applying the concepts learned. We have constructed the functions and their respective algorithms
and corresponding code by ourselves. The program was run, tested, and debugged by our own efforts. We 
further certify that we have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons.

Romeo Rasay Jr., DLSU ID# 12374288
Keane Pleno, DLSU ID# ...
Jedidiah Kyle Martin Julian, DLSU ID# ...

Last modified: 3/25/24
******************************************************************/ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int row;
    int column;
} Pair;

bool element_of_set(Pair compare_set[], int size, Pair element){
	int i;
    for(i = 0; i < size; i++){
        if(compare_set[i].row == element.row && compare_set[i].column == element.column && compare_set[i].row != 0 && compare_set[i].column != 0){
            return true;
        }
    }
    return false;
}

void union_of_sets(Pair set1[], int size, Pair set2){
    int index, found;
	
	found = 0;
	for(index = 0; index < size && !element_of_set(set1, size, set2) && !found; index++){
        if(set1[index].row == 0 && set1[index].column == 0){
        	set1[index].row = set2.row;
        	set1[index].column = set2.column;
        	found = 1;
		}
	}
}

int intersection_with_Sset(Pair set1[], Pair set2[][6], Pair C1[], Pair C2[], bool nextPlayerMove){
	int numElements = 0;

	if(element_of_set(set1, 36, set2[0][0]) && element_of_set(set1, 36, set2[0][1]) && element_of_set(set1, 36, set2[0][2]) && element_of_set(set1, 36, set2[0][3]) && element_of_set(set1, 36, set2[0][4])){
		numElements++;
	}
		
	if(element_of_set(set1, 36, set2[1][0]) && element_of_set(set1, 36, set2[1][1]) && element_of_set(set1, 36, set2[1][2]) && element_of_set(set1, 36, set2[1][3]) && element_of_set(set1, 36, set2[1][4])){
		numElements++;
	}

	if(element_of_set(set1, 36, set2[2][0]) && element_of_set(set1, 36, set2[2][1]) && element_of_set(set1, 36, set2[2][2]) && element_of_set(set1, 36, set2[2][3]) && element_of_set(set1, 36, set2[2][4])){
		numElements++;
	}
	
	if(element_of_set(set1, 36, set2[3][0]) && element_of_set(set1, 36, set2[3][1]) && element_of_set(set1, 36, set2[3][2]) && element_of_set(set1, 36, set2[3][3]) && element_of_set(set1, 36, set2[3][4]) && element_of_set(set1, 36, set2[3][5])){
		numElements++;
	}
	return numElements;
}

// CHECK WHETHER PATTERN 1 OR PATTERN 2 HAS BEEN CREATED BY PLAYER A or PLAYER B
int CheckWinningCond1(Pair set1[], Pair set2[][2]){
	int GameOver = 0;
	if(element_of_set(set1, 4, set2[0][0]) && element_of_set(set1, 4, set2[0][1])){
		GameOver = 1;
	}
	
	if(element_of_set(set1, 4, set2[1][0]) && element_of_set(set1, 4, set2[1][1])){
		GameOver = 1;
	}
		
	return GameOver;
}

int count_elements(Pair set[], int size) {
    int count = 0, i;
    for (i = 0; i < size; i++) {
        if (set[i].row > 0 && set[i].column > 0){
            count++;
        }
    }
    return count;
}

void newF3(Pair playerA[], Pair playerB[], Pair F3[]){
	Pair F[36] = {{1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6},
			{2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6},
			{3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6},
			{4,1}, {4,2}, {4,3}, {4,4}, {4,5}, {4,6},
			{5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6},
			{6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}
	};
	int i, j = 0;
	
	for (i = 0; i < 36; i++){
		if(!element_of_set(playerA, 36, F[i]) && !element_of_set(playerB, 36, F[i])){
			F3[j].row = F[i].row;
			F3[j].column = F[i].column;
			j++;
		}
	}
	while(j < 36){
		F3[j].row = 0;
		F3[j].column = 0;
		j++;
	}		
}

bool Over(Pair playerA[], Pair playerB[], Pair F3[], Pair C1[], Pair C2[], Pair P[][2]){
	newF3(playerA, playerB, F3);
	if(count_elements(F3, 36) == 0 || CheckWinningCond1(C1, P) || CheckWinningCond1(C2, P)){
		return true;
	}
	
	return false;
}

void playerMove(bool nextPlayerMove, bool over, bool good, Pair playerA[], Pair playerB[], Pair F3[], Pair C1[], Pair C2[], Pair P[][2], Pair S[][6]) {
    int a, b, c, d;
    Pair position;
    Pair cd;
	
	newF3(playerA, playerB, F3);
	do{
		printf("Enter the nth number of row: ");
	    scanf("%d", &a);
	    printf("Enter the nth number of column: ");
	    scanf("%d", &b);
		if(!element_of_set(F3, 36, position))
			printf("Invalid Input.\n");
	    position.row = a;
	    position.column = b;
    }while(!element_of_set(F3, 36, position));
	
	c = ((a - 1) / 3) + 1;
    d = ((b - 1) / 3) + 1;
    cd.row = c;
    cd.column = d;
		
    if (over == false && nextPlayerMove && element_of_set(F3, 36, position)) {
        good = !good;
        union_of_sets(playerA, 36, position);
    } else if (over == false && !nextPlayerMove && element_of_set(F3, 36, position)) {
        good = !good;
        union_of_sets(playerB, 36, position);
	}

	if (over == false && good && nextPlayerMove && intersection_with_Sset(playerA, S, C1, C2, nextPlayerMove) > count_elements(C1, 4)){
		union_of_sets(C1, 4, cd);
    } else if (over == false && good && !nextPlayerMove && intersection_with_Sset(playerB, S, C1, C2, nextPlayerMove) > count_elements(C2, 4)) {
        union_of_sets(C2, 4, cd);
    }
	
	if (over == false && good){
        good = !good;
    }
}	

void PrintBoard(Pair playerA[], Pair playerB[])
{
    int i, j, index = 0;
    Pair board[36] = {{1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6},
		{2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6},
		{3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6},
		{4,1}, {4,2}, {4,3}, {4,4}, {4,5}, {4,6},
		{5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6},
		{6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}
	};

    printf("\n");

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
	        if (element_of_set(playerA, 36, board[index]))
	        {
	            printf(" X");
	        } 
	        else if (element_of_set(playerB, 36, board[index]))
	        {
	            printf(" O");
	        }
	        else
	        {
	            printf(" %c", 254);
	        }
	        index++;
        }
        printf("\n");
    }
}

int main(){
    Pair P[2][2] = {
		{{1, 1}, {2, 2}},
        {{1, 2}, {2, 1}},
    };

    Pair S[4][6] = {
        {{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}},
        {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}},
        {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}},
        {{4, 1}, {4, 3}, {5,1}, {5, 3}, {6, 1}, {6, 3}},
    };
    
	Pair C1[4] = {{0,0}, {0,0}, {0,0}, {0,0}};
	Pair C2[4] = {{0,0}, {0,0}, {0,0}, {0,0}};
	Pair playerA[36] = {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, 
				  {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}};
	Pair playerB[36] = {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, 
				  {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}};
	Pair F3[36] = {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, 
				  {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}};

	bool good = false;
	bool nextPlayerMove = true;
	bool over = false;
	
	do{	
		PrintBoard(playerA, playerB);
		
	    if (nextPlayerMove) {
	        printf("\nPlayer A's Turn:\n");
	    } else if (!nextPlayerMove) {
	        printf("\nPlayer B's Turn:\n");
		}
		
		playerMove(nextPlayerMove, over, good, playerA, playerB, F3, C1, C2, P, S);
		over = Over(playerA, playerB, F3, C1, C2, P);
		
		if(!over){
			nextPlayerMove = !nextPlayerMove;
		}
		system("cls");
	}while(!over);
	
	if(over == true && nextPlayerMove && CheckWinningCond1(C1, P)){
		printf("Player A won! Congratulations!");
	}
	else if(over == true && !nextPlayerMove && CheckWinningCond1(C2, P)){
		printf("Player B won! Congratulations!");
	}

	return 0;
}
