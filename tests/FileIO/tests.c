#include <stdio.h>
#include <stdlib.h> 
#include "../../src/FileIO/FileIO.h" // Включаем заголовочный файл с объявлениями функций

// Функция для вывода результата теста
void printTestResult(int result) {
    if (result == 0) {
        printf("PASS\n"); // Зеленый цвет - успешно
    } else {
        printf("FAIL\n"); // Красный цвет - ошибка
    }
}

int main() {
    // Тест функции LoadLeaderBoard
	printf("\n_________________________\n");
	printf("FileIO Module Tests:\n");
	
    printf("Testing LoadLeaderBoard: ");
    LeaderboardEntry *entries = NULL;
    int size = 0;
    int loadResult = LoadLeaderBoard(&entries, &size);
    printTestResult(loadResult);

    // Тест функции addScore
    printf("Testing addScore: ");
    int addScoreResult = addScore(&entries, &size, "Player1", 100);
    printTestResult(addScoreResult);
	
  // Тест функции SaveLeaderBoard
    printf("Testing SaveLeaderBoard: ");
    int saveResult = SaveLeaderBoard(entries, size);
    printTestResult(saveResult);

    // Освобождаем выделенную память
    free(entries);

    return loadResult | addScoreResult | saveResult;
}
