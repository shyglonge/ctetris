#pragma once
#include "../../src/GameController/GameController.h"
#define DELTA_CLOCKS 25
#define TETRIS_LEFT 1
#define TETRIS_RIGHT 2
#define TETRIS_DOWN 3
#define TETRIS_ROTATE 4
#define ROWS 10
#define COLUMNS 40
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} LeaderboardEntry;

enum menu_keys {
    MENU_START = 1,
    MENU_LEADERBOARD = 2,
    MENU_END
};

static int menuState;

int FullTestGameController();
int onInput(){
    return 0;
};
int getInput(){
    return 0;
};
int GetDrawData(){
    return 0;
};
int GetNewScore(){
    return 0;
};
int DrawField(){
    return 0;
};

int addScore(){
    return 0;
};
int SaveLeaderBoard(){
    return 0;
};
int LoadLeaderBoard(){
    return 0;
};
int showLeaderBoard(){
    return 0;
};
int getPlayerName(){
    return 0;
};
int end_game(){
    return 0;
};
int gameReset(){
    return 0;
};

int showMenu()
{
    menuState++;
    return menuState%4;
};


const char *error_handler(int code){
    return "ERROR_HANDLER_WRAPPER\x00";
};
int onTick(){
    return -1;
};