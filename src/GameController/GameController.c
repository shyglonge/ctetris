#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../UserIO/UserIO.h"
#include "../GameLogic/GameLogic.h"
#include "../FileIO/FileIO.h"
#include "../ErrorHandler/ErrorHandler.h"
#include "GameController.h"
#include <time.h>

#define DELTA_CLOCKS 25



static char field[ROWS][COLUMNS];
static char playerName[50];
static LeaderboardEntry* leaderboard = 0;
static int sizeLeaderboard = 0;
static int capacityLeaderboard = 0;


void waitDeltaClocks(int clocks){
    while (clock() < clocks + DELTA_CLOCKS){
        //
    }
}

int getMoveCode(int code){
    short result = -1;
    switch(code){
        case ('a' ) :
            result = TETRIS_LEFT;
            break;
        case ('s' ) :
            result = TETRIS_DOWN;
            break;
        case ('d' ) :
            result = TETRIS_RIGHT;
            break;
        case ('r' ) :
            result = TETRIS_ROTATE;
            break;

    }
    return result;
}

void playGame()
{
    gameReset();
    short ifGameRun;
    while (ifGameRun != -1){
        onInput(getMoveCode(getInput()));

        ifGameRun = onTick();
        GetDrawData(&field[0][0]);
        DrawField(field);
        waitDeltaClocks(clock());
    }

    capacityLeaderboard = addScore(&leaderboard,&sizeLeaderboard,playerName,GetNewScore());
    short state = SaveLeaderBoard(leaderboard, sizeLeaderboard);
    if (state != 0) {
        const char* err_str = error_handler((int)state);
		printf("Error: %s", err_str);
		system("pause");
		
    }

}


void startController()
{
	system("CLS");
    int current_mode = -1;
	
	leaderboard = (LeaderboardEntry*)malloc(5*sizeof(LeaderboardEntry));
	memset(leaderboard, 0, 5*sizeof(LeaderboardEntry));
	sizeLeaderboard = 5;
	capacityLeaderboard = 5;
	
    short state = LoadLeaderBoard(&leaderboard,&sizeLeaderboard);
    if (state != 0) {
        const char* err_str = error_handler((int)state);
		printf("Error: %s\n", err_str);
		system("pause");
        
    }
	capacityLeaderboard = sizeLeaderboard;
    getPlayerName(playerName);


    while (current_mode != MENU_END)
	{
        current_mode = showMenu();
		system("CLS");
        switch (current_mode){
            case (MENU_START) :
                playGame();
                break;
            case (MENU_LEADERBOARD) :
				if(!leaderboard)
					break;
                showLeaderBoard(leaderboard, sizeLeaderboard);
                break;
            case (MENU_END) :
                end_game();
                break;
        }
    }

}