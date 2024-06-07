#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "C:\Users\stasb\sapper\errorProc\errorProc.h"
#include "C:\Users\stasb\sapper\errorProc\errorProc.c"
#include "C:\Users\stasb\sapper\LOGIC\LOGIC.h"
#include "workWithUser.h"
#include "C:\Users\stasb\sapper\LOGIC\LOGIC.c"
#define run_tests main

int passed_tests = 0;

void getResult(int result, char *funcName)
{   Sleep( (rand()%3000) + 1000 );
    if (result == 0)
        printf("\t%s = FAIL\n", funcName);
    else 
    { printf("\t%s = PASS\n", funcName); passed_tests++; }
}

int run_tests(void)
{   srand(time(NULL));
    int length, width, mineAmount, x = 9, y = 9, errorCode = 0;
	bool firstStep = true, youAreAlreadyDead = false, dead = false, win = false;
	char ** GRID_BE = NULL; // Бэкэндовая сетка
	char ** GRID_FE = NULL; // Фронтэндавая сетка
	char type = 'F';
	int userChoice, difInput=0;
    
    system("CLS");

    printf("\nTests for \"userIO\" module:\n\n");

    getResult( showMenu(&userChoice, &difInput) , "showMenu" );
    generateField(length, width, mineAmount, &GRID_BE, &GRID_FE);
    drawField(length, width, GRID_FE);
    getResult( 0 , "drawField" );
    showTips();
    getResult(0 , "showTips");
    userInput(&x, &y, &type);
    getResult(0 , "userInput");
    showLoseMessage();
    getResult(0 , "showLoseMessage");
    showWinMessage();
    getResult(0 , "showWinMessage");
    updateField(GRID_FE, length, width);
    getResult(0 , "updateField");
    showStats(GRID_FE, length, width, mineAmount);
    getResult(0 , "showStats");
    getResult(showErrors(errorCode) , "showErrors");
    getResult(playAgain() , "playAgain");

    if (passed_tests != 10)
        printf("\n\x1b[31mSome tests failed!\x1b[0m\n");
    else
        printf("\n\x1b[32mAll tests have been passed!\x1b[0m\n");

}