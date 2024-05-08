#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define TETRIS_LEFT 1
#define TETRIS_RIGHT 2
#define TETRIS_DOWN 3
#define TETRIS_ROTATE 4
#define ROWS 10
#define COLUMNS 40
#define FIGURE_SIZE 4

enum TColor
{
	empty = 0,
	white = 1,
	red,
	green,
	blue,
	yellow,
	purple,
	cyan
};

enum TAction
{
	Left = 1,
	Right = 2,
	Down,
	Rotate
};

static char game_field[ROWS][COLUMNS] = { 0 };
static char draw_field[ROWS][COLUMNS] = { 0 };
static int global_score = 0;
static char current_piece[FIGURE_SIZE][FIGURE_SIZE] = { 0 };
static int current_x = 0;
static int current_y = 0;
static int current_input;

static char shape_bitmap[][FIGURE_SIZE][FIGURE_SIZE] =
{
	{//BOX
		white, white, 0, 0,
		white, white, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	},
	{//L shape
		red, 0, 0, 0,
		red, 0, 0, 0,
		red, red, 0, 0,
		0, 0, 0, 0
	},
	{//L Inverted
		0, green, 0, 0,
		0, green, 0, 0,
		green, green, 0, 0,
		0, 0, 0, 0
	},
	{//Z
		blue, 0, 0, 0,
		blue, blue, 0, 0,
		0, blue, 0, 0,
		0, 0, 0, 0
	},
	{//Z inverted
		0, yellow, 0, 0,
		yellow, yellow, 0, 0,
		yellow, 0, 0, 0,
		0, 0, 0, 0
	},
	{//I
		purple, 0, 0, 0,
		purple, 0, 0, 0,
		purple, 0, 0, 0,
		purple, 0, 0, 0
	},
	{//T
		cyan, cyan, cyan, 0,
		0, cyan, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	}
};

static int stash[sizeof(shape_bitmap)/sizeof(shape_bitmap[0])];

static int tick_cnt = 0;

/**
* @function onInput
* @param code: Код движения тетриса. TETRIS_LEFT, TETRIS_RIGHT, TETRIS_DOWN, TETRIS_ROTATE
* @return возвращает 0
*/
void onInput(int code);

//Абстрактно обозначить движение вправо/влево и т.д. Отвязать от реальных кодов кнопок

/**
* @function onTick
* @brief Вызывается каждый тик, в ней обрабатывается игровая логика
* поворот, падение, стыковка блоков, сброс строчек вниз, начисление очков
* Проверяет на проигрыш.
* @return возвращает 0, если -1 - игра завершена
*/
int onTick();

/**
* @function GetDrawData
* @param gamefield Игровое поле. char[10][40]
* @brief 0 в ячейке - ячейка пустая
* число отличное от нуля - код клетки фигуры, для каждой фигуры свой (от 1 до 4)
* (Число отличное от нуля - ячейка закрашена цветом, зависящим от значения в ячейке
* в теме по дефолту:
* 1 - Квадрат
* 2 - L
* 3 - T
* 4 - I)
* @return 0 - поле скопировано. -1 - ошибка
*/
int GetDrawData(char* field_data);


/**
* @function GetNewScore
* @brief Возвращает текущее количество игровых очков
* @return возвращает текущее количество очков
*/
int GetNewScore();

/**
* @function gameReset
* @brief Начинает игру с самого начала. Обнуляет счетчик тиков, очков и игровое поле
* @return void
*/
void gameReset();

//-------------------------------------------------------

//Внутренние функции:

/**
*	@function rotateMatrix
*	@param char matrix[FIGURE_SIZE][FIGURE_SIZE];
*   @brief Поворот матрицы фигуры на 90 градусов по часовой стрелке
*/
void rotateMatrix(char matrix[FIGURE_SIZE][FIGURE_SIZE]);


/**
*	@function MatrixOrigin
*	@param char matrix[FIGURE_SIZE][FIGURE_SIZE] - матрица фигуры
*   @brief Возвращает фигуру в матрице на координаты (0;0);
*/
void MatrixOrigin(char matrix[FIGURE_SIZE][FIGURE_SIZE]);

/**
*	@function generate_piece
*   @brief Генерирует случайную фигуру и задает ей координаты
*/
void generate_piece();

/**
*	@function generate_piece
*   @param int x_coord, X координата фигуры
*   @param int y_coord, Y координата фигуры
*   @brief Проверяет, сталкивается ли фигура на данных координатах со стенками или другими блоками
*/
bool checkCollision(int x_coord, int y_coord);

/**
*	@function completeLines
*   @brief Находит заполненные строки, обнуляет их и "сваливает" все строки выше неё
*/
void completeLines();

/**
*	@function merge_piece
*	@param char piece[FIGURE_SIZE][FIGURE_SIZE] - Фигура
*	@param char field[ROWS][COLUMNS] - Поле
*   @brief делает фигуру статичной и "впечатывает" его в игровое поле как группу статичных блоков
*/
void merge_piece(char piece[FIGURE_SIZE][FIGURE_SIZE], char field[ROWS][COLUMNS]);




int runTest();