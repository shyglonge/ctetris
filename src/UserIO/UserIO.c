#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UserIO.h"
#include <Windows.h>
#include "../GameLogic/GameLogic.h"
#include "../FileIO/FileIO.h"

void SetPosition(int X, int Y)
{
	//Сделано для отладки. В основной проект не входит!
	HANDLE Screen;
	Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { X, Y };

	SetConsoleCursorPosition(Screen, Position);
}

void getPlayerName(char* playername) 
{
    printf("Enter your nickname: ");
    scanf("%50s", playername);	//read no more than 50 characters
}
int showMenu() 
{
	printf("#########################\n");
	printf("#\t\t\t#\n");
	printf("#       TETRIS  \t#\n");
	printf("#\t\t\t#\n");
	printf("#\t1)Start\t\t#\n");
	printf("#\t2)Leaderboard\t#\n");
	printf("#\t3)Quit\t\t#\n");
	printf("#\t\t\t#\n");
	printf("#########################\n");
	
	int selection = getch();
	switch(selection)
	{
		case '1':
		{
			return MENU_START;
			break;
		}
		
		case '2':
		{
			return MENU_LEADERBOARD;
			break;
		}
		
		case '3':
		{
			return MENU_END;
			break;
		}
		
		default:
		{
			return -1;
			break;
		}
	}
	
	return -1;
}

/*
	empty = 0,
	white = 1,
	red,
	green,
	blue,
	yellow,
	purple,
	cyan
*/

void DrawField(char field_data[ROWS][COLUMNS]) 
{
	SetPosition(0,0);
    printf("Game Field \n");
    for (int y = 0; y < COLUMNS; ++y) 
	{
        printf("%c", 186);
        for (int x = 0; x < ROWS; ++x) 
		{
			switch(field_data[x][y])
			{
				case empty:
				{
					printf("  ");
					break;
				}
				
				case white:
				{
					printf("\033[0;37m");
					printf("%c%c", 219, 219);
					break;
				}
				
				case red:
				{
					printf("\033[0;31m");
					printf("%c%c", 219, 219);
					printf("\033[0;37m");
					break;
				}
				
				case green:
				{
					printf("\033[0;32m");
					printf("%c%c", 219, 219);
					printf("\033[0;37m");
					break;
				}
				
				case blue:
				{
					printf("\033[0;34m");
					printf("%c%c", 219, 219);
					printf("\033[0;37m");
					break;
				}
				
				case yellow:
				{
					printf("\033[0;33m");
					printf("%c%c", 219, 219);
					printf("\033[0;37m");
					break;
				}
				
				case purple:
				{
					printf("\033[0;35m");
					printf("%c%c", 219, 219);
					printf("\033[0;37m");
					break;
				}
				
				case cyan:
				{
					printf("\033[0;36m");
					printf("%c%c", 219, 219);
					printf("\033[0;37m");
					break;
				}
			}
        }
        printf("%c\n", 186);
    }
    printf("%c", 200);
    for (int x = 0; x < ROWS*2; ++x) 
	{
        printf("%c", 205);
    }
    printf("%c\n", 188);
	printf("Score: %d", GetNewScore());
}




void showLeaderBoard(LeaderboardEntry* leaderboard, size_t size) 
{
    printf("#########################\n");
    printf("#\t\t\t#\n");
    printf("#       Top 5:  \t#\n");
    for (int i = 0; i < size && i < 5; i++) 
	{
		if(!leaderboard[i].score)
			continue;
        printf("# %d. %s - %d\t#\n", i + 1, leaderboard[i].name, leaderboard[i].score);
    }
    printf("#\t\t\t#\n");
    printf("#       Best Score:  \t#\n");
    printf("#          %d\t\t#\n", leaderboard[0].score);
    printf("#########################\n");
}

void end_game() 
{
    printf("Game over\n");
}

int getInput() 
{
    int key = 0;
    if (kbhit()) //Неблокирущее считывание кода нажатой кнопки
	{
        key = getch();
    }
    return key;
}