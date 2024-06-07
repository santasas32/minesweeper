#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//__________________________________________________________________________________________________________//

int setDifficulty(int input, int *length, int *width, int *mineAmount)
{   
    switch (input)
    {   case 1:
        *length = 10; *width = 10;
        *mineAmount = (*length) * (*width) * 0.14;
        break;
        case 2:
        *length = 15; *width = 15;
        *mineAmount = (*length) * (*width) * 0.14;
        break;
        case 3:
        *length = 30; *width = 30;
        *mineAmount = (*length) * (*width) * 0.14;
        break;
        case 666:
        *length = 30; *width = 30;
        *mineAmount = (*length) * (*width) * 0.667 + 66;
        break;
        default:
        //exit(1);
        return 1;
        break;
    }

    return 0;
}

//__________________________________________________________________________________________________________//

int generateField(int length, int width, int mineAmount, char ***GRID_BE, char ***GRID_FE)
{	//printf("TEST");
	*GRID_BE = (char **) calloc(length, sizeof(char *)); 		// Выедляем память 
	if (*GRID_BE == NULL) return 3;				// под нашу сетку
	for(int i = 0; i < length; i++)					// с минами
	{	(*GRID_BE)[i] = (char *) calloc(width, sizeof(char));
		if ( (*GRID_BE)[i] == NULL ) return 3;
	}


	//printf("-------------------------------\n");
	*GRID_FE = (char **) calloc(length, sizeof(char *));
	if (*GRID_BE == NULL) return 3;						// Выделяем память
	for(int i = 0; i < length; i++)							// под сетку
	{	(*GRID_FE)[i] = (char *) calloc(width, sizeof(char));		// которую будет видеть
		if ( (*GRID_FE)[i] == NULL ) return 3;				// игрок		
	}

	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)	(*GRID_FE)[i][j] = 'X';	
	
	return 0;
}

//__________________________________________________________________________________________________________//

int kOutOfBounds(int i, int k, int length)
{	if ( (i == 0 && k < i) || (i == length - 1 && k > i) )
		return 1;
	return 0;
}
int lOutOfBounds(int j, int l, int width)
{	if ( (j == 0 && l < j) || (j == width - 1 && l > j) )
		return 1;
	return 0;
}

int fillField(int length, int width, int mineAmount, int x, int y, char **GRID_BE, bool secret)
{	
	if (x > length - 1 || x < 0 || y > width - 1 || y < 0)
        return 2;

	for (int i = 0; i < length; i++)				// Заполняем сетку
	{	for (int j = 0; j < width; j++)				// с минами
			GRID_BE[i][j] = '0';					// пустыми клетками
	}

	// Тестовый входной контроль )))
	if (mineAmount > length * width) {	printf("\nС таким количеством мин ты отправишься в бесконечный цикл, дружище.\n"); exit(1);	}
	//printf("Случайно сгенерированные координаты для каждой мины:\n"); 	// Посмотреть координаты для мин (для тестов)
	for(int i = 0; i < mineAmount; i++)							
	{	int ri = rand() % length; int rj = rand() % width;		
		/*printf("i = %d ri = %d, rj = %d\n", i, ri, rj);*/
		if (GRID_BE[ri][rj] == '*' || (ri == x && rj == y)) 	// Заполняем сетку
		{	i--;												// с минами
			continue;											// этими самыми минами
		}
		GRID_BE[ri][rj] = '*';
	}


	for (int i = 0; i < length; i++)						// Заполняем каждую
        for (int j = 0; j < width; j++)						// пустую клетку
        {   if (GRID_BE[i][j] != '*')						// количеством мин
            {   int localCount = 0;							// находящимся рядом
                for (int k = i - 1; k <= i + 1; k++)		// с этой клеткой
                    for (int l = j - 1; l <= j + 1; l++)
                    {   if (kOutOfBounds(i, k, length)) continue;
						if (lOutOfBounds(j, l, width)) continue;
						if (GRID_BE[k][l] == '*') localCount++;
                    }
                GRID_BE[i][j] = (char) localCount + '0';	// весь этот алгоритм просто какой-то сумашедший вышел
            }												// я вообще хз, как я до него додумался O_O

        }

	if (secret) GRID_BE[x][y] = '9';

	//printf("\n\n");

	return 0;

}

//__________________________________________________________________________________________________________//

int checkFirstStep(int length, int width, int *mineAmount, bool firstStep, bool *youAreAlreadyDead)
{   if (firstStep)
    {
        int chance = rand() % 100;
        //printf("\nchance = %d", chance);
        if (chance == 1)
        {   *youAreAlreadyDead = true;
            *mineAmount = (length * width) - 1;
        }

        return 1;
    }

    return 0;
}

//__________________________________________________________________________________________________________//

bool checkZeroth(char **GRID_BE, int d1, int d2, int length, int width, bool *active)
{   if (d1 < 0 || d1 > length - 1) { *active = false; return false; }
    if (d2 < 0 || d2 > width - 1) { *active = false; return false; }
    
    if (GRID_BE[d1][d2] == '0')
        return true;

    *active = false;
    return false;
}

void revealCells(char **GRID_BE, char **GRID_FE, int d1, int d2, int length, int width)
{   
    for (int k = d1 - 1; k <= d1 + 1; k++)
        for (int l = d2 - 1; l <= d2 + 1; l++)
        {   if (kOutOfBounds(d1, k, length)) continue;
			if (lOutOfBounds(d2, l, width)) continue;
            if (GRID_BE[k][l] == '*') continue;
            GRID_FE[k][l] = GRID_BE[k][l];
        }
}

int setStep(int x, int y, int length, int width, int mineAmount, char inputAction, char **GRID_BE, char **GRID_FE, bool *firstStep, bool *dead)
{   bool youAreAlreadyDead = false;
    x--; y--;

    if (x > length - 1 || x < 0 || y > width - 1 || y < 0)
        return 2;

    switch(inputAction)
    {   case 'F':
        if (GRID_FE[x][y] == 'X' || GRID_FE[x][y] == '?')
        {   GRID_FE[x][y] = 'F';
            return 0;
        }
        if (GRID_FE[x][y] == 'F')
        {   GRID_FE[x][y] = 'X';
            return 0;
        }
        return 0;
        break;
        
        case '?':
        if (GRID_FE[x][y] == 'X' || GRID_FE[x][y] == 'F')
        {   GRID_FE[x][y] = '?';
            return 0;
        }
        if (GRID_FE[x][y] == '?')
        {   GRID_FE[x][y] = 'X';
            return 0;
        }
        return 0;
        break;

        case 'O':
        break;

        default:
        return 1;
        break;
    }


    // if (*firstStep)
    // {   *firstStep = false;
    //     int chance = rand() % 100;
    //     //printf("\nchance = %d", chance);
    //     if (chance == 1)
    //     {   youAreAlreadyDead = true;
    //         mineAmount = (length * width) - 1;
    //     }

    //     fillField(length, width, mineAmount, x, y, GRID_BE, youAreAlreadyDead);
    //     GRID_FE[x][y] = GRID_BE[x][y];
    // }
    
    

    switch(GRID_BE[x][y])
    {   case '*':
        *dead = true;
        //updateField();
        break;

        case '0':
        {
        GRID_FE[x][y] = GRID_BE[x][y];

        int du = x - 1, dd = x + 1, dl = y - 1, dr = y + 1;

        bool active[8] = {true, true, true, true, true, true, true, true};

        while(true)
        {   bool limit = true;
            if (checkZeroth(GRID_BE, du, y, length, width, &active[0]) && active[0]) {GRID_FE[du][y] = GRID_BE[du][y]; revealCells(GRID_BE, GRID_FE, du, y, length, width);}
            if (checkZeroth(GRID_BE, dd, y, length, width, &active[1]) && active[1]) {GRID_FE[dd][y] = GRID_BE[dd][y]; revealCells(GRID_BE, GRID_FE, dd, y, length, width);}
            if (checkZeroth(GRID_BE, x, dl, length, width, &active[2]) && active[2]) {GRID_FE[x][dl] = GRID_BE[x][dl]; revealCells(GRID_BE, GRID_FE, x, dl, length, width);}
            if (checkZeroth(GRID_BE, x, dr, length, width, &active[3]) && active[3]) {GRID_FE[x][dr] = GRID_BE[x][dr]; revealCells(GRID_BE, GRID_FE, x, dr, length, width);}
            if (checkZeroth(GRID_BE, du, dl, length, width, &active[4]) && active[4]) {GRID_FE[du][dl] = GRID_BE[du][dl]; revealCells(GRID_BE, GRID_FE, du, dl, length, width);}
            if (checkZeroth(GRID_BE, du, dr, length, width, &active[5]) && active[5]) {GRID_FE[du][dr] = GRID_BE[du][dr]; revealCells(GRID_BE, GRID_FE, du, dr, length, width);}
            if (checkZeroth(GRID_BE, dd, dl, length, width, &active[6]) && active[6]) {GRID_FE[dd][dl] = GRID_BE[dd][dl]; revealCells(GRID_BE, GRID_FE, dd, dl, length, width);}
            if (checkZeroth(GRID_BE, dd, dr, length, width, &active[7]) && active[7]) {GRID_FE[dd][dr] = GRID_BE[dd][dr]; revealCells(GRID_BE, GRID_FE, dd, dr, length, width);}
            du--; dd++; dl--; dr++;
            for (int i = 0; i < 8; i++)
            {   //printf("\nactive[%d] = %d", i, active[i]);
                if (active[i])
                {   limit = false;
                    break;
                }
            }
            if (limit) break;
        }
        //updateField();
        }
        break;

        default:
        {
        GRID_FE[x][y] = GRID_BE[x][y];
        //updateField();
        }
        break;
    }

    return 0;
}

//__________________________________________________________________________________________________________//

bool checkWin(char **GRID_BE, char **GRID_FE, int length, int width, int mineamount)
{   int currentFlags = 0;
    for (int i = 0; i < length; i++)
    {    for (int j = 0; j < width; j++)
            if (GRID_FE[i][j] == 'F')
            {   if (GRID_BE[i][j] == '*')
                    currentFlags++;
                else break;
            }
    }
    if (currentFlags == mineamount) return true;
    else return false;
}

//__________________________________________________________________________________________________________//

int endGame(char **GRID_BE, char **GRID_FE, int length, int width, bool dead, bool win)
{   if (dead)
    {   for (int i = 0; i < length; i++)
            for (int j = 0; j < width; j++)
                GRID_FE[i][j] = GRID_BE[i][j];
    }

    if (win)
	{	for (int i = 0; i < length; i++)
			for (int j = 0; j < width; j++)
			{	if (GRID_FE[i][j] == 'F') continue;
				else GRID_FE[i][j] = GRID_BE[i][j];			
			}
	}

	return 0;
}

//__________________________________________________________________________________________________________//

int dealloc(int length, int width, char ***GRID_BE, char ***GRID_FE)
{   if (*GRID_BE == NULL || *GRID_FE == NULL)
        return 3;

    for(int i = 0; i < length; i++)
        free((*GRID_BE)[i]);
    free(*GRID_BE);

	for(int i = 0; i < length; i++)
        free((*GRID_FE)[i]);
    free(*GRID_FE);

	return 0;
}

//__________________________________________________________________________________________________________//