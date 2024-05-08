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
* @param code: ��� �������� �������. TETRIS_LEFT, TETRIS_RIGHT, TETRIS_DOWN, TETRIS_ROTATE
* @return ���������� 0
*/
void onInput(int code);

//���������� ���������� �������� ������/����� � �.�. �������� �� �������� ����� ������

/**
* @function onTick
* @brief ���������� ������ ���, � ��� �������������� ������� ������
* �������, �������, �������� ������, ����� ������� ����, ���������� �����
* ��������� �� ��������.
* @return ���������� 0, ���� -1 - ���� ���������
*/
int onTick();

/**
* @function GetDrawData
* @param gamefield ������� ����. char[10][40]
* @brief 0 � ������ - ������ ������
* ����� �������� �� ���� - ��� ������ ������, ��� ������ ������ ���� (�� 1 �� 4)
* (����� �������� �� ���� - ������ ��������� ������, ��������� �� �������� � ������
* � ���� �� �������:
* 1 - �������
* 2 - L
* 3 - T
* 4 - I)
* @return 0 - ���� �����������. -1 - ������
*/
int GetDrawData(char* field_data);


/**
* @function GetNewScore
* @brief ���������� ������� ���������� ������� �����
* @return ���������� ������� ���������� �����
*/
int GetNewScore();

/**
* @function gameReset
* @brief �������� ���� � ������ ������. �������� ������� �����, ����� � ������� ����
* @return void
*/
void gameReset();

//-------------------------------------------------------

//���������� �������:

/**
*	@function rotateMatrix
*	@param char matrix[FIGURE_SIZE][FIGURE_SIZE];
*   @brief ������� ������� ������ �� 90 �������� �� ������� �������
*/
void rotateMatrix(char matrix[FIGURE_SIZE][FIGURE_SIZE]);


/**
*	@function MatrixOrigin
*	@param char matrix[FIGURE_SIZE][FIGURE_SIZE] - ������� ������
*   @brief ���������� ������ � ������� �� ���������� (0;0);
*/
void MatrixOrigin(char matrix[FIGURE_SIZE][FIGURE_SIZE]);

/**
*	@function generate_piece
*   @brief ���������� ��������� ������ � ������ �� ����������
*/
void generate_piece();

/**
*	@function generate_piece
*   @param int x_coord, X ���������� ������
*   @param int y_coord, Y ���������� ������
*   @brief ���������, ������������ �� ������ �� ������ ����������� �� �������� ��� ������� �������
*/
bool checkCollision(int x_coord, int y_coord);

/**
*	@function completeLines
*   @brief ������� ����������� ������, �������� �� � "���������" ��� ������ ���� ��
*/
void completeLines();

/**
*	@function merge_piece
*	@param char piece[FIGURE_SIZE][FIGURE_SIZE] - ������
*	@param char field[ROWS][COLUMNS] - ����
*   @brief ������ ������ ��������� � "�����������" ��� � ������� ���� ��� ������ ��������� ������
*/
void merge_piece(char piece[FIGURE_SIZE][FIGURE_SIZE], char field[ROWS][COLUMNS]);




int runTest();