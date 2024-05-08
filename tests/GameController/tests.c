#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tests.h"
#include "../../src/GameController/GameController.h"

int testGetMoveCode();
int testWaitDeltaClokcs();
int testPlayGame();
int testStartController();

static char field[ROWS][COLUMNS];
static char playerName[50];
static LeaderboardEntry* leaderboard = 0;
static int sizeLeaderboard = 0;
static int capacityLeaderboard = 0;

static int counterSteps;

int testGetMoveCode(){
    if (getMoveCode('a') != TETRIS_LEFT){
        return -1;
    }
    if (getMoveCode('s') != TETRIS_DOWN){
        return -1;
    }
    if (getMoveCode('d') != TETRIS_RIGHT){
        return -1;
    }
    if (getMoveCode('r') != TETRIS_ROTATE){
        return -1;
    }
    return 0;
}

int testWaitDeltaClokcs(){
    int clocks = clock();
    waitDeltaClocks(clocks);
    if (clock() < clocks + DELTA_CLOCKS){
        return -1;
    }
    return 0;
}

int testPlayGame()
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

    capacityLeaderboard = addScore(&leaderboard,&sizeLeaderboard, &capacityLeaderboard ,playerName,GetNewScore());
    int state = SaveLeaderBoard(leaderboard, sizeLeaderboard);
    if (state != 0) {
        const char* err_str = error_handler(state);
		printf("Error: %s", err_str);
		system("pause");
		
    }
    return 0;
}

int testStartController()
{
    int current_mode = -1;
	
	leaderboard = (LeaderboardEntry*)malloc(5*sizeof(LeaderboardEntry));
	memset(leaderboard, 0, 5*sizeof(LeaderboardEntry));
	sizeLeaderboard = 5;
	capacityLeaderboard = 5;
	
    int state = LoadLeaderBoard(&leaderboard,&sizeLeaderboard);
    if (state != 0) {
        const char* err_str = error_handler(state);
		printf("Error: %s\n", err_str);
		
        
    }
	capacityLeaderboard = sizeLeaderboard;
    getPlayerName(playerName);


    while (current_mode != MENU_END)
	{
        current_mode = showMenu();
		
        switch (current_mode){
            case (MENU_START) :
                playGame();
                counterSteps++;
                break;
            case (MENU_LEADERBOARD) :
				if(!leaderboard)
					break;
                showLeaderBoard(leaderboard, sizeLeaderboard);
                counterSteps++;
                break;
            case (MENU_END) :
                end_game();
                counterSteps++;
                break;
        }
    }
    if (counterSteps != 3){
        return -1;
    }
    return 0;
}

int FullTestGameController(){
    int result1 = testStartController();
    int result2 = testWaitDeltaClokcs();
    int result3 = testGetMoveCode();
    if (result1 == 0) {
        printf("StartController(): PASS\n");
    } 
    else {
        printf("StartController(): FAIL\n");
    }
    if (result2 == 0) {
        printf("WaitDeltaClokcs(): PASS\n");
    } 
    else {
        printf("WaitDeltaClokcs(): FAIL\n");
    }
    if (result3 == 0) {
        printf("GetMoveCode(): PASS\n");
    } 
    else {
        printf("GetMoveCode(): FAIL\n");
    }
    return result1 | result2 | result3;
}

int main()
{
	printf("\n_________________________\n");
	return FullTestGameController();
}