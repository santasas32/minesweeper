#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "LOGIC.h"
#define run_tests main

int passed_tests = 0;

void getResult(int result, char *funcName)
{   Sleep( (rand()%1000));

{   //Sleep( (rand()%3000) + 1000 );
    if (result != 0)
        printf("\t%s = FAIL\n", funcName);
    else 
    { printf("\t%s = PASS\n", funcName); passed_tests++; }
}
}
int run_tests(void)
{   srand(time(NULL));
    int length, width, mineAmount, x = 9, y = 9, errorCode = 0;
	bool firstStep = true, youAreAlreadyDead = false, dead = false, win = false;
	char ** GRID_BE = NULL; // Бэкэндовая сетка
	char ** GRID_FE = NULL; // Фронтэндавая сетка
	char type = 'F';
	int userChoice, difInput;
    
    //system("CLS");

    printf("\nTests for \"LOGIC\" module:\n\n");

    getResult( setDifficulty(666, &length, &width, &mineAmount), "setDifficulty" );
    getResult( generateField(length, width, mineAmount, &GRID_BE, &GRID_FE), "generateField" );
    getResult( fillField(length, width, mineAmount, x - 1, y - 1, GRID_BE, youAreAlreadyDead), "fillField" );
    getResult( !checkFirstStep(length, width, &mineAmount, firstStep, &youAreAlreadyDead), "checkFirstStep" );
    getResult( setStep(x, y, length, width, mineAmount, type, GRID_BE, GRID_FE, &firstStep, &dead), "setStep" );
    getResult( checkWin(GRID_BE, GRID_FE, length, width, mineAmount), "checkWin" );
    getResult( endGame(GRID_BE, GRID_FE, length, width, dead, win), "endGame" );
    getResult( dealloc(length, width, &GRID_BE, &GRID_FE), "dealloc" );

    if (passed_tests != 8)
        printf("\n\x1b[31mSome tests failed!\x1b[0m\n");
    else
        printf("\n\x1b[32mAll tests have been passed!\x1b[0m\n");
    
}