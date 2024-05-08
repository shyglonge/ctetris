#include "GameLogic.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>


void shuffle(int* array, int n)
{
	for(int i = n-1; i > 0; --i)
	{
		int j = rand() % (i+1);
		int tmp = array[j];
		array[j] = array[i];
		array[i] = tmp;
	}
	
}

void fill_stash()
{
	stash_index = 0;
	
	for(int i = 0; i < stash_size; ++i)
	{
		stash[i] = i;
	}	
	
	shuffle(&stash[0], sizeof(stash)/sizeof(stash[0]));
	
	
	/*for(size_t i = 0; i < stash_size; ++i)
	{
		printf("Stash: %d\n", stash[i]);
		
	}
	
	system("pause");*/
}


void generate_piece()	//get random figure
{
	if(stash_index == stash_size)
	{
		fill_stash();
	}
	
	int fig = stash[stash_index];
	
	//printf("%d : %d\n", stash_index, stash[stash_index]);
	
	++stash_index;
	
	
	
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
	fill_stash();
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

void ddebugDraw(char field_data[10][40])
{

	for (int y = 0; y < 40; ++y)
	{
		for (int x = 0; x <= 10; ++x)
		{
			if (x == 10)
			{
				printf("|");
				continue;
			}
			switch (field_data[x][y])
			{
				case 0:
				{
					printf("  ");
					break;
				}
				case 1:
				{
					printf("%c%c", 219, 219);
					break;
				}
			}
			//printf("%d ", (int)draw_field[x][y]);
		}
		printf("\n");
	}

	printf("Score:%d\n", GetNewScore());
}


int isFull_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	int res;
	gameReset();
	game_field[0][5] = 1;

	res = onTick();

	if (res < 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int getScore_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	gameReset();
	int res;

	for (int x = 0; x < ROWS; ++x)
	{
		game_field[x][30] = 1;
	}

	{
		int old_score = GetNewScore();
		res = onTick();

		if (res < 0 || GetNewScore() == old_score)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

int CompleteLines_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	int res;
	gameReset();

	for (int x = 0; x < ROWS; ++x)
	{
		game_field[x][30] = 1;
	}

	{
		res = onTick();

		if (res < 0 || game_field[0][30])
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}


int MatrixOrigin_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	{
		char matrix[4][4] = {
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,1},
			{0,0,1,1}
		};

		char matrix_cmp[4][4] = {
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		};

		MatrixOrigin(matrix);


		if (memcmp(matrix, matrix_cmp, sizeof(matrix)) == 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}


int RotateMatrix_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);

	{
		char matrix[4][4] =
		{
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		};

		char matrix_cmp[4][4] =
		{
			{1,1,0,0},
			{0,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		};

		rotateMatrix(matrix);
		MatrixOrigin(matrix);


		if (memcmp(matrix, matrix_cmp, sizeof(matrix)) == 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}


int gameReset_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	gameReset();
	char tfield[ROWS][COLUMNS] = { 0 };

	onTick();

	if (memcmp(&tfield, &draw_field, sizeof(tfield)) == 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}

}


int getMatrixRealWidth_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	char fig[FIGURE_SIZE][FIGURE_SIZE] = {
		{1,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,0,0,0},
	};
	int wid = getMatrixRealWidth(fig);
	//printf("VAL=%d", wid);
	if (wid != 2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


int RotateMatrix_test2(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);

	gameReset();

	current_y = 8;
	current_x = 7;
	memcpy(&current_piece, &shape_bitmap[2], sizeof(shape_bitmap[0]));//L inverted

	char ddata[ROWS][COLUMNS];


	onTick();

	onInput(TETRIS_ROTATE);
	current_x = 8;
	onTick();

	onInput(TETRIS_ROTATE);
	onTick();

	GetDrawData(&ddata[0][0]);

	bool isFailed = false;

	for (int y = 0; y < COLUMNS; ++y)
	{
		if (ddata[0][y])
		{
			isFailed = true;
			break;
		}
	}

	if (isFailed)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


int SetInput_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	gameReset();
	onInput(TETRIS_LEFT);

	if (current_input != TETRIS_LEFT)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int checkCollision_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	gameReset();
	onTick();
	onTick();
	onTick();
	onTick();
	current_x = 9;
	if (!checkCollision(current_x, current_y))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
//printf("\033[31mFAIL\033[0m\n");
//printf("\033[32mPASS\033[0m\n");

int GetDrawData_test(char* output, size_t output_len)
{
	snprintf(output, output_len, "%s", __FUNCTION__);
	gameReset();
	onTick();

	char ddata[ROWS][COLUMNS];

	memset(&ddata[0][0], 0, sizeof(ddata));

	GetDrawData(&ddata[0][0]);
	bool isEmpty = true;
	for (int x = 0; x < ROWS; ++x)
	{
		for (int y = 0; y < COLUMNS; ++y)
		{
			if (ddata[x][y])
			{
				isEmpty = false;
				break;
			}
		}
	}

	if (isEmpty)
	{
		return -1;
	}
	else
	{
		return 0;
	}

}

int runTest()
{
	int failflag = 0;
	int res = 0;
	
	const size_t bufsize = 512;
	char buffer[512] = { 0};
	
	res = isFull_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	res = getScore_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	res = CompleteLines_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	res = MatrixOrigin_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	res = RotateMatrix_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	
	res = gameReset_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	
	res = getMatrixRealWidth_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	res = RotateMatrix_test2(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	res = SetInput_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	res = checkCollision_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	
	
	
	
	res = GetDrawData_test(buffer, bufsize);
	printf("%s\t",buffer);
	if(res < 0)
	{
		printf("FAIL\n");
		failflag = -1;
	}
	else
	{
		printf("PASS\n");
	}
	return failflag;

}