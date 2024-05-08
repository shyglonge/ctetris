#include "GameLogic.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>

void generate_piece()	//get random figure
{
	int max_fig = sizeof(shape_bitmap) / sizeof(shape_bitmap[0]);
	int fig = rand() % max_fig;
	current_y = 0;
	current_x = 5;
	memcpy(&current_piece, &shape_bitmap[fig], sizeof(shape_bitmap[0]));
}

void MatrixOrigin(char matrix[FIGURE_SIZE][FIGURE_SIZE])
{
	int min_x = 3;
	int max_x = 0;
	int min_y = 3;
	int max_y = 0;

	for (int y = 0; y < FIGURE_SIZE; ++y)
	{
		for (int x = 0; x < FIGURE_SIZE; ++x)
		{
			if (!matrix[x][y])
				continue;
			if (x > max_x)
				max_x = x;

			if (x < min_x)
				min_x = x;

			if (y > max_y)
				max_y = y;

			if (y < min_y)
				min_y = y;
		}
	}

	char nmatrix[FIGURE_SIZE][FIGURE_SIZE] = { 0 };

	for (int y = min_y; y <= max_y; ++y)
	{
		for (int x = min_x; x <= max_x; ++x)
		{
			nmatrix[x - min_x][y - min_y] = matrix[x][y];

		}
	}

	memcpy(&matrix[0][0], &nmatrix[0][0], sizeof(nmatrix));
}

bool checkCollision(int x_coord, int y_coord)
{

	for (int y = 0; y < FIGURE_SIZE; ++y)
	{
		for (int x = 0; x < FIGURE_SIZE; ++x)
		{
			if (!current_piece[x][y])
				continue;

			if (current_piece[x][y] && game_field[x_coord + x][y_coord + y])
				return true;
			

			if (x_coord + x < 0)//x_coord + x >= 10 ||
				return true;

			if (x_coord + x >= ROWS)
				return true;

			if (y_coord + y >= COLUMNS || y_coord+y < 0)
				return true;
		}
	}

	return false;
}



void merge_piece(char piece[FIGURE_SIZE][FIGURE_SIZE], char field[ROWS][COLUMNS])
{
	for (int y = 0; y < FIGURE_SIZE; ++y)
	{
		for (int x = 0; x < FIGURE_SIZE; ++x)
		{
			if(piece[x][y])
				field[current_x + x][current_y + y] = piece[x][y];
		}
	}
}

void onInput(int code)
{
	current_input = code;
}

int GetDrawData(char* field_data)
{
	memcpy(field_data, draw_field, sizeof(draw_field));
	return 0;
}

void gameReset()
{
	srand(time(NULL));
	memset(&game_field, 0, sizeof(game_field));
	global_score = 0;
	current_y = 20;
	current_x = 5;
	tick_cnt = 0;
	generate_piece();

}


void rotateMatrix(char matrix[FIGURE_SIZE][FIGURE_SIZE])
{
	const int N = 4;
	for (int x = 0; x < N / 2; x++) 
	{

		for (int y = x; y < N - x - 1; y++) 
		{

			int temp = matrix[x][y];

			matrix[x][y] = matrix[y][N - 1 - x];

			matrix[y][N - 1 - x] = matrix[N - 1 - x][N - 1 - y];

			matrix[N - 1 - x][N - 1 - y] = matrix[N - 1 - y][x];

			matrix[N - 1 - y][x] = temp;
		}
	}
}


void completeLines()
{
	for (int y = 0; y < COLUMNS; ++y)
	{
		int isComplete = 1;
		for (int x = 0; x < ROWS; ++x)
		{
			if (!game_field[x][y])
			{
				isComplete = 0;
				break;
			}
		}
		if (!isComplete)
			continue;

		if (isComplete)
		{
			for (int x = 0; x < ROWS; ++x)
			{
				game_field[x][y] = 0;		//clear the row
			}

			for (int yk = y; yk > 0; --yk)	//CHECK
			{
				for (int xk = 0; xk < ROWS; ++xk)
				{
					game_field[xk][yk] = game_field[xk][yk - 1];
				}
			}
			global_score += 10;
		}

	}
}


bool isFull()
{
	for (int x = 0; x < 10; ++x)
	{
		if (game_field[x][5])
			return true;
	}
	return false;
}

int getMatrixRealWidth(char figure[FIGURE_SIZE][FIGURE_SIZE])
{
	int mmax = 0;
	for (int y = 0; y < FIGURE_SIZE; ++y)
	{
		for (int x = 0; x < FIGURE_SIZE; ++x)
		{
			if (figure[x][y])
			{
				if (x > mmax)
					mmax = x;
			}
		}
	}
	return mmax;
}

int getMatrixRealHeight(char figure[FIGURE_SIZE][FIGURE_SIZE])
{
	int mmax = 0;
	for (int y = 0; y < FIGURE_SIZE; ++y)
	{
		for (int x = 0; x < FIGURE_SIZE; ++x)
		{
			if (figure[x][y])
			{
				if (y > mmax)
					mmax = y;
			}
		}
	}
	return mmax;
}


int onTick()
{
	if (isFull())
	{
		return -1;
	}
	
	++tick_cnt;
	

	switch (current_input)
	{
		case TETRIS_ROTATE:
		{			
			rotateMatrix(current_piece);
			MatrixOrigin(current_piece);
			int width = getMatrixRealWidth(current_piece);
			int height = getMatrixRealHeight(current_piece);
			
			char old_figure[FIGURE_SIZE][FIGURE_SIZE] = {0};
			
			memcpy(&old_figure[0][0], &current_piece[0][0], sizeof(current_piece));
			
			int old_x = current_x;
			
			if (current_x + width+1 >= ROWS)
			{
				current_x = ROWS - width-1;
			}
			
			if(current_y + height + 1 >= COLUMNS)
			{
				current_y = COLUMNS - height-1;
			}
			
			if(checkCollision(current_x, current_y))
			{
				for(size_t j = 0; j < 3; ++j)
				{
					rotateMatrix(current_piece);
					MatrixOrigin(current_piece);
				}
				current_x = old_x;
			}

			break;
		}
		case TETRIS_LEFT:
		{
			if (current_x - 1 >= 0)
			{
				if (!checkCollision(current_x - 1, current_y))
					--current_x;
			}
			break;
		}
		case TETRIS_RIGHT:
		{
			if (current_x + 1 >= 0)
			{
				if (!checkCollision(current_x + 1, current_y))
					++current_x;
			}

			break;
		}
	}
	
	if (tick_cnt % 5 == 0 || current_input == TETRIS_DOWN)
	{
		if (!checkCollision(current_x, current_y+1))
		{
			++current_y;
			merge_piece(current_piece, draw_field);
		}
		else
		{
			merge_piece(current_piece, draw_field);
			merge_piece(current_piece, game_field);//stick it
			generate_piece();
			++global_score;
		}
	}

	memcpy(&draw_field, &game_field, sizeof(game_field));

	merge_piece(current_piece, draw_field);
	
	completeLines();

	current_input = 0;

	return 0;
}

int GetNewScore()
{
	return global_score;
}
