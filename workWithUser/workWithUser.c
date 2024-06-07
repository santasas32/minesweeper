#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
*@brief showMenu - функция вывода главного меню
*@return choice - выбор пользователя
*@param *userChoice - выбор пользователя
*@param *difInput - выбор сложности
*/
int showMenu(int *userChoice,int *difInput){
	if (*difInput == 0){
	printf( "\n"   "\x1b[1;31m"
		   "\t\t\t   *********        ****         **********   ***********   ***********  \n"
		   "\t\t\t  **********      ***  ***      ************  ************  ************ \n"
		   "\t\t\t  *****          ***    ***     ***      ***  ****          ***      *** \n"
		   "\t\t\t  ***           ***      ***    ***      ***  ***********   ***      *** \n"
		   "\t\t\t  ***          ***        ***   ***      ***  ************  ***********  \n"
		   "\t\t\t  ***         ****************  ***      ***  ***********   *********    \n"
		   "\t\t\t  *****       ****************  ***      ***  ****          ***          \n"
		   "\t\t\t  **********  ***          ***  ***      ***  ************  ***          \n" 
		   "\t\t\t   *********  ***          ***  ***      ***  ***********   ***          \n\n\n" "\x1b[0m");

	printf( "\t\t\t\t                    **                       \n" 
		    "\t\t\t\t          ****      **       ****               \n" 
			"\t\t\t\t            ****   ****    ****                  \n"
			"\t\t\t\t              ***************                        \n"
			"\t\t\t\t               ************                    \n"
			"\t\t\t\t             ****************                      \n"
			"\t\t\t\t        ***************************                      \n"
			"\t\t\t\t    **********************************                       \n"
			"\t\t\t\t        ***************************                       \n"
			"\t\t\t\t             ****************                      \n"
			"\t\t\t\t               ************                     \n" 
			"\t\t\t\t              ***************                     \n"
			"\t\t\t\t            ****   ****    ****                \n"
			"\t\t\t\t          ****      **       ****              \n" 
			"\t\t\t\t                    **                  \n");

	printf("Choose action:\n"
		"\t1) play\n\t2) exit\n");
	if ( scanf("%d", userChoice) != 1)
		return 1;

	if (*userChoice != 1 && *userChoice != 2)
		return 1;
}
	if (*userChoice == 1)
	{	printf("Choose difficulty (1: Easy, 2: Normal, 3: Hard)\n>>>");
		
		if ( scanf("%d", difInput) != 1 ) 
			return 1;
		
		if (*difInput != 1 && *difInput != 2 && *difInput != 3 && *difInput != 666)
			return 1;
	}


	system("cls");

	return 0;
}

/**
*@brief drawField - функция отрисовки поля
*@param width - ширина поля
*@param length - высота поля
*@param **GRID_FE - бекэндовая сетка
*/
void drawField(int length, int width, char **GRID_FE)
{   for (int i = 0; i <= length; i++)									// Выводим сетку
	{	for (int j = 0; j <= width; j++)								// для игрока
		{	if (i == 0 && j == 0) {	printf("%2d", j); continue;	}
			else if (i == 0 && i > 9) {	printf("%2d", j); continue;	}
            else if (i == 0 && i < 10) {	printf("%3d", j); continue;	}
			if (j == 0)		printf("%2d", i);
			printf("%3c", GRID_FE[i - 1][j]);
		}
		printf("\n");
	}
}

/**
*@brief showTips - функция вывода подсказок
*/
void showTips() {
	printf("\nEnter the coordinate and type of selection(x, y, F-flag, O-open, ?-not sure)\n");
}

/**
*@brief userInput - функция общения с пользователем
*@pointer x координата по Х
*@pointer у координата по У
*@pointer type тип клетки
*/
int userInput(int *x, int *y, char *type){   
    printf("Enter the coordinate of X and Y:\n");
    if (scanf("%d%d", x, y) != 2)
		return 1;

    printf("Enter the type of selection:\n");
    getchar();

    if (scanf("%c", type) != 1)
		return 1;

	if (*type != 'F' && *type != 'O' && *type != '?')
		return 2;
	
	return 0;
}

/**
*@brief showLoseMessage - функция вывода сообщения о проигрыше
*/
void showLoseMessage(){
	printf(	"\n\n"
			"\t\t\t **         ******    *******  ********\n"
			"\t\t\t **        **    **  ******    ***     \n"
			"\t\t\t **        *      *    ***     ***     \n"
			"\t\t\t **        *      *     ***    ********\n"
			"\t\t\t **        *      *      ***   ***     \n"
			"\t\t\t ********  **    **    ******  ***     \n"
			"\t\t\t ********   ******   ********  ********\n");

}

/**
*@brief showWinMessage - функция вывода сообщения о выигрыше
*/
void showWinMessage(){
	printf( "\n\n"
			"\t\t\t **                    **  **  ****      **\n"
			"\t\t\t  **                  **       ** **     **\n"
			"\t\t\t   **       **       **    **  **  **    **\n"
			"\t\t\t    **     ****     **     **  **   **   **\n"
			"\t\t\t     **   **  **   **      **  **    **  **\n"
			"\t\t\t      ** **    ** **       **  **     ** **\n"
			"\t\t\t       ***      ***        **  **      ****\n"
		);
}


/**
*@bried updateField - функция обновления поля для пользователя
*@param length - длина поля
*@param width - ширина поля
*@param *GRID_FE - флонтондовая сетка
*/
void updateField(char **GRID_FE, int length, int width)
{	
	printf("\n\n");
	for (int i = 0; i <= length; i++){	
		for (int j = 0; j <= width; j++){	
			if (i == 0 && j == 0) {	
				printf("%2d", j); continue;	}
			else if (i == 0 && i > 9) {	
				printf("%2d", j); continue;	}
            else if (i == 0 && i < 10) {	
            	printf("%3d", j); continue;	}
			if (j == 0) {		
				printf("%2d", i);
			}
			if  (GRID_FE[i-1][j] == '0') printf("\033[1;32m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '1') printf("\033[1;34m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '2') printf("\033[1;34m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '3') printf("\033[1;35m%3c\033[0m", GRID_FE[i - 1][j]); 
			else if  (GRID_FE[i-1][j] == '4') printf("\033[1;35m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '5') printf("\033[1;33m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '6') printf("\033[1;33m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '7') printf("\033[1;31m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '8') printf("\033[1;31m%3c\033[0m", GRID_FE[i - 1][j]); 
			else if  (GRID_FE[i-1][j] == '9') printf("\033[1;31m%3c\033[0m", GRID_FE[i - 1][j]); 
			else if  (GRID_FE[i-1][j] == 'F') printf("\033[1;31m%3c\033[0m", GRID_FE[i - 1][j]);
			else if  (GRID_FE[i-1][j] == '?') printf("\033[1;38;5;135m%3c\033[0m", GRID_FE[i - 1][j]);
			else printf("\033[1;37m%3c\033[0m", GRID_FE[i - 1][j]);
			

			// Черный: 30
			// Красный: 31
			// Зеленый: 32
			// Желтый: 33
			// Синий: 34
			// Пурпурный: 35
			// Голубой: 36
			// Белый: 37
			// Сброс: 0
			
		}
		printf("\n");
	}
}

/**
*@brief showStats - функция вывода статистики
*@param length - длина поля
*@param width - ширина поля
*@param *GRID_FE - флонтондовая сетка
*@param mineAmount - кол-во мин
*/
void showStats(char **GRID_FE, int length, int width, int mineAmount)
{  printf("\n\tMine amount: %d", mineAmount);
  for (int i = 0; i < length; i++)
    for (int j = 0; j < width; j++)
      if (GRID_FE[i][j] == 'F')
      mineAmount--;
	if (mineAmount < 0) mineAmount = 0;
  printf("/Flag amount: %d", mineAmount);
}

/**
*@brief showErrors - функция вывода ошибок
*@param num_error - номер ошибки
*/
int showErrors(int num_error) {
  if(num_error == 0) {
    return 0;
  }
  if(num_error == 1) {
    printf("\nError #1: Incorrect input!\n"); // Некорректный ввод данных
	system("PAUSE");
  }
  if(num_error == 2) {
    printf("\nError #2: Incorrect coordinate or operation input!\n"); // Некорректное значение координат
	system("PAUSE");
  }
  if(num_error == 3) {
    printf("\nError #3: Memory allocation error!\n"); // ошибка выделения памяти
	system("PAUSE");
  }
  if(num_error == 7) {
    printf("\nError #7: Inform the Developer!\n"); // Критическая идентифицированная ошибка, природа которой не ясна
    return -1; // Завершаем выполнение функции, поскольку обычно 7-й ошибкой обозночаются критические
  }
//   else {
//     printf("Unidentified error: Inform the Developer!\n"); // Критическая неидентифицированная ошибка, природа которой не ясна
//     return -1; // Завершаем выполнение функции, поскольку природа ошибки не ясна, а значит продолжать - не самая лучшая идея
//   }

  return 0;
}


bool playAgain()
{	char input;
	printf("\n\t\tPlay again?\n[Y/N]>>>");
	scanf("%c", &input);
	if (input == 'Y' || input == 'y')
	{	while (getchar() != '\n');
		return true;
	}

	return false;
}