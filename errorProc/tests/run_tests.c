#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "../../errorProc/errorProc.h"
#include "../../workWithUser/workWithUser.h"
#include "../../workWithUser/workWithUser.c"
#define run_tests main

int passed_tests = 0;

void getResult(int result, char *funcName)
{   Sleep( (rand()%1000));
    if (result != 0)
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
    
    //system("CLS");

    printf("\nTests for \"errorProc\" module:\n\n");

    getResult(checkErrors(0), "checkErrors");

    if (passed_tests != 1)
        printf("\n\x1b[31mSome tests failed!\x1b[0m\n");
    else
        printf("\n\x1b[32mAll tests have been passed!\x1b[0m\n");
    

}