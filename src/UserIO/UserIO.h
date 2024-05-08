#define ROWS 10
#define COLUMNS 40
#include "struct.h"
#include "../FileIO/FileIO.h"
enum menu_keys {
    MENU_START = 1,
    MENU_LEADERBOARD = 2,
    MENU_END
};

/**
* @function showMenu
* @brief Функция,которая отвечает за вывод меню
* @return возвращает целое число - выбор опции меню, соответствует enum menu_keys
*/
int showMenu();


/**
* @function print_game_field
* @brief Функция,которая отрисовывает игровое поле
* @param char field_data[10][40] - игровое поле
* @return void
*/
void DrawField(char field_data[ROWS][COLUMNS]);


/**
* @function getPlayerName
* @brief Функция,которая считывает имя игрока из консоли в массив char по указателю
* @param char* playername (OUT)
* @return void
*/
void getPlayerName(char* playername);


/**
* @function showLeaderBoard
* @brief Функция,которая меня размер игрового поля по желанию пользователя
* @param массив LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];
* @return void
*/
void showLeaderBoard(LeaderboardEntry* leaderboard, size_t size);

/**
* @function end_game
* @brief Функция,которая отвечает за прекращением игрового процесса. Закрывает программу
* @return void
*/
void end_game();

/**
* @function getInput
* @brief Функция,которая возвращает код нажатой кнопки
* @return int (код нажатой кнопки
*/
int getInput();