#include <stdio.h>
#include "./src/GameLogic/GameLogic.h"
#include "./src/UserIO/UserIO.h"
#include "./src/GameController/GameController.h"
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
//DEBUG:
/*
void SetPosition(int X, int Y)
{
	//Сделано для отладки. В основной проект не входит!
	HANDLE Screen;
	Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { X, Y };

	SetConsoleCursorPosition(Screen, Position);
}

void debugDraw(char field_data[10][40])
{
	//Сделано для отладки. В основной проект не входит!
	SetPosition(0, 0);

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
				case 1:	//Потенциально позже внедрим цвета
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
}*/

int main()
{
	startController();
	return 0;
}

int zaaamain()
{
	//Минимальный код для запуска тетриса БЕЗ НИЧЕГО
	//Сделано для отладки
	char buffer_data[10][40];

	while(1)
	{
		system("CLS");
		int selection = showMenu();
		
		switch(selection)
		{
			case MENU_START:
			{
				system("CLS");
				gameReset();
				while(1)
				{
					if (kbhit())
					{
						int code = getch();
						int tetris_code = 0;
						switch (code)
						{
							case 'a':
							{
								tetris_code = TETRIS_LEFT;
								break;
							}
							case 'd':
							{
								tetris_code = TETRIS_RIGHT;
								break;
							}
							case 'r':
							{
								tetris_code = TETRIS_ROTATE;
								break;
							}
							case 's':
							{
								tetris_code = TETRIS_DOWN;
								break;
							}
						}
						onInput(tetris_code);
					}
					int res = onTick();
					if(res < 0)
						break;
					Sleep(15);
					//printf("\033[1;31m");
					GetDrawData(&buffer_data[0][0]);
					DrawField(buffer_data);
					//debugDraw(buffer_data);
				}
				break;
			}
			
			case MENU_END:
			{
				return 0;
				break;
			}
		}
	}
	return 0;
}

