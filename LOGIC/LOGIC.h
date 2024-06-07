#ifndef LOGIC_H
#define LOGIC_H
//__________________________________________________________________________________________________________//

/*@brief setDifficulty - функция установки сложности
 *@param input - значение, получаемое от пользователя
 *@param pointer *length - длина игрового поля
 *@param pointer *width - ширина игрового поля
 *@param pointer *mineAmount - количество мин на поле
 *@return - возвращает 0 при успешной установке сложности, 1 - в случае ошибки
 */
int setDifficulty(int input, int *length, int *width, int *mineAmount);

//__________________________________________________________________________________________________________//

/*@brief generateField - функция генерации игрового поля
 *@param length - длина игрового поля
 *@param width - ширина игрового поля
 *@param pointer *mineAmount - количество мин на поле
 *@param pointer ***GRID_BE - сетка для заполнения минами
 *@param pointer ***GRID_FE - сетка, которую видит пользователь
 *@return - возвращает 0 при успешной генерации, 1 - в случае ошибки
 */
int generateField(int length, int width, int mineAmount, char ***GRID_BE, char ***GRID_FE);

//__________________________________________________________________________________________________________//

/*@brief kOutOfBounds - функция, которая проверяет на выход индекса k за границы сетки
 *@param i - i-тая строка сетки
 *@param k - k-тая строка подсетки
 *@param length - длина сетки
 *@return - 1 в случае, если param k находится за пределами сетки; 0 в обратном случае
 */
int kOutOfBounds(int i, int k, int length);

/*@brief lOutOfBounds - функция, которая проверяет на выход индекса l за границы сетки
 *@param j - j-тая строка сетки
 *@param l - l-тая строка подсетки
 *@param width - ширина сетки
 *@return - 1 в случае, если param l находится за пределами сетки; 0 в обратном случае
 */
int lOutOfBounds(int j, int l, int width);


/*@brief fillField - функция заполнения сетки минами
 *@param length - длина игрового поля
 *@param width - ширина игрового поля
 *@param mineAmount - количество мин на поле
 *@param x - координата сетки x
 *@param y - координата сетки y
 *@param pointer ***GRID_BE - сетка для заполнения минами
 *@param secret - переменная, отвечающая за особое заполнение сетки минами
 *@return - возвращает 0 при успешном выполнении функции
 */
int fillField(int length, int width, int mineAmount, int x, int y, char **GRID_BE, bool secret);

//__________________________________________________________________________________________________________//

/*@brief checkFirstStep - проверки первого хода игрока
 *@param length - длина игрового поля
 *@param width - ширина игрового поля
 *@param pointer *mineAmount - количество мин на поле
 *@param pointer *youAreAlreadyDead - переменная, отвечающая за особое заполнение сетки минами
 *@return - возвращает 1, если игрок уже сделал первый шаг, 0 в случае отсутсвия предыдущих шагов
 */
int checkFirstStep(int length, int width, int *mineAmount, bool firstStep, bool *youAreAlreadyDead);

//__________________________________________________________________________________________________________//

/*@brief checkZeroth - функция, которая проверяет текущую клетку на нулевую клетку
 *@param pointer **GRID_BE - сетка с минами
 *@param d1 - координата строки
 *@param d2 - координата столбца
 *@param length - длина сетки
 *@param width - ширина сетки
 *@return - true в случае, если клетка являтся нулевой; false в обратном случае
 */
bool checkZeroth(char **GRID_BE, int d1, int d2, int length, int width, bool *active);

/*@brief checkZeroth - функция, которая проверяет текущую клетку на нулевую клетку
 *@param pointer **GRID_BE - сетка с минами
 *@param pointer **GRID_FE - сетка для вывода в консоль
 *@param d1 - координата строки
 *@param d2 - координата столбца
 *@param length - длина сетки
 *@param width - ширина сетки
 *@return - void
 */
void revealCells(char **GRID_BE, char **GRID_FE, int d1, int d2, int length, int width);

/*@brief setStep – функция, исполняющая и анализирующая шаг игрока
 *@param x - координата сетки x
 *@param y - координата сетки y
 *@param lengh - длина сетки
 *@param width - ширина сетки
 *@param mineAmount - количество мин на поле
 *@param inputAction - действие игрока
 *@param pointer **GRID_BE - сетка с минами
 *@param pointer **GRID_FE - сетка для вывода в консоль
 *@param pointer *firstStep - переменная, обозначающая первый ход игрока
 *@param pointer *dead - переменная статуса игрока
 *@return - возвращает 0 при успешном исполнении функции, 1 - в случае ошибки
 */
int setStep(int x, int y, int length, int width, int mineAmount, char inputAction, char **GRID_BE, char **GRID_FE, bool *firstStep, bool *dead);

//__________________________________________________________________________________________________________//

/*@brief checkWin – функция, проверяющая состояние игровой сетки на соответствие условиям победы
 *@param pointer **GRID_BE - сетка с минами
 *@param pointer **GRID_FE - сетка для вывода в консоль
 *@param length - длина сетки
 *@param width - ширина сетки
 *@param mineAmount - количество мин на поле
 *@return - возвращает true, если состояние сетки соответствует условиям победы, false в обратном случае
 */
bool checkWin(char **GRID_BE, char **GRID_FE, int length, int width, int mineamount);

//__________________________________________________________________________________________________________//

/*@brief endGame – функция, которая открывает сетку в зависимости от победы/поражения игрока
 *@param pointer **GRID_BE - сетка с минами
 *@param pointer **GRID_FE - сетка для вывода в консоль
 *@param length - длина сетки
 *@param width - ширина сетки
 *@param dead - переменная статуса игрока
 *@param win - переменная статуса состояния игры
 *@return - возвращает true, если состояние сетки соответствует условиям победы, false в обратном случае
 */
int endGame(char **GRID_BE, char **GRID_FE, int length, int width, bool dead, bool win);

//__________________________________________________________________________________________________________//

/*@brief dealloc - функция, освобождающая память, выделенную под сетки
 *@param length - длина игрового поля
 *@param width - ширина игрового поля
 *@param pointer ***GRID_BE - сетка для заполнения минами
 *@param pointer ***GRID_FE - сетка, которую видит пользователь
 *@return - 0 при успешном освобождении памяти
 */
int dealloc(int length, int width, char ***GRID_BE, char ***GRID_FE);

//__________________________________________________________________________________________________________//

#endif