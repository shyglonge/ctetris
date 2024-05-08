#include <stdio.h>
#include "../../src/GameLogic/GameLogic.h"
#include <stdio.h>
#include <Windows.h>
#include <conio.h>



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

int GameLogic_runTest()
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


int main()
{
	printf("\n\n_________________________\n");
	printf("GameLogic Module Tests:\n");
	return GameLogic_runTest();
}