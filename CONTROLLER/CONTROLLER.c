#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "LOGIC.h"
#include "workWithUser.h"
#include "errorProc.h"
#define CONTROLLER main

int CONTROLLER(void)
{
	//setlocale(0, "");
	srand(time(NULL));
	bool active = true;	
while (active)
{	system("cls");
	int length, width, mineAmount, x = 9, y = 9, errorCode = 0;
	bool firstStep = true, youAreAlreadyDead = false, dead = false, win = false;
	char ** GRID_BE = NULL; // Бэкэндовая сетка
	char ** GRID_FE = NULL; // Фронтэндавая сетка
	char type;
	int userChoice, difInput = 0;
	do { system("CLS"); errorCode = showMenu(&userChoice, &difInput);
	checkErrors(errorCode); } while(errorCode != 0);
	setDifficulty(difInput, &length, &width, &mineAmount);
	switch (userChoice){
	case 1: {
		if ( (errorCode = generateField(length, width, mineAmount, &GRID_BE, &GRID_FE)) != 0 )
		{ checkErrors(errorCode); exit(1); }
		drawField(length, width, GRID_FE);

//__________________________________________________________________________________________________________//
		
		while(true)
		{	errorCode = 0;
		showTips();
		if ( (errorCode = userInput(&x, &y, &type)) != 0 )
		{ checkErrors(errorCode); system("CLS"); showStats(GRID_FE, length, width, mineAmount); updateField(GRID_FE, length, width); continue; }

		if ( checkFirstStep(length, width, &mineAmount, firstStep, &youAreAlreadyDead) )
		{	if ( (errorCode = fillField(length, width, mineAmount, x - 1, y - 1, GRID_BE, youAreAlreadyDead)) != 0)
			{	checkErrors(errorCode);
				system("cls");
				drawField(length, width, GRID_FE);
				continue;
			}
			GRID_FE[x-1][y-1] = GRID_BE[x-1][y-1];
			firstStep = false;
		}

		system("cls");

		errorCode = setStep(x, y, length, width, mineAmount, type, GRID_BE, GRID_FE, &firstStep, &dead);
		win = checkWin(GRID_BE, GRID_FE, length, width, mineAmount);
		checkErrors(errorCode);
		showStats(GRID_FE, length, width, mineAmount);
		if (dead || win) break;
		updateField(GRID_FE, length, width);
		}

//__________________________________________________________________________________________________________//

		endGame(GRID_BE, GRID_FE, length, width, dead, win);
		if (win) showWinMessage();
		if (dead) showLoseMessage();
		updateField(GRID_FE, length, width);
		dealloc(length, width, &GRID_BE, &GRID_FE);
		getchar();
		active = playAgain();

	}; break;

//__________________________________________________________________________________________________________//

	case 2: exit(0);
	break;

	default: exit(1);
	break;
	}
}

	return 0;
}
