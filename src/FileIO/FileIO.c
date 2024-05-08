#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileIO.h" // Включаем заголовочный файл, содержащий объявления функций


// Функция сравнения для qsort
int compareEntries(const void *a, const void *b) {
    const LeaderboardEntry *entryA = (const LeaderboardEntry *)a;
    const LeaderboardEntry *entryB = (const LeaderboardEntry *)b;

    // Сравниваем счета в обратном порядке
    return (entryB->score - entryA->score);
}


int LoadLeaderBoard(LeaderboardEntry **entries, int *size) {
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        // Если файл отсутствует, создаем его
        file = fopen("leaderboard.txt", "w");
        if (file == NULL) {
            return ERROR_OPEN_FILE; // Ошибка открытия/создания файла
        }
        fclose(file);
        *size = 0; // Устанавливаем размер как 0, так как файл новый и пустой
        return 0; // Успешное создание файла
    }

    // Проверка наличия записей в файле
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    if (fileSize == 0) {
        fclose(file);
        *size = 0; // Устанавливаем размер как 0, так как файл пустой
        return 0; // Файл пуст, но открыт успешно
    }

    // Выделение памяти для хранения данных
    *entries = (LeaderboardEntry*)malloc(INITIAL_CAPACITY * sizeof(LeaderboardEntry));
    if (*entries == NULL) {
        fclose(file);
        return ERROR_MEMORY_ALLOCATION; // Ошибка выделения памяти
    }

    // Загрузка данных из файла в структуры
    *size = 0;
    while (fscanf(file, "%s %d", (*entries)[*size].name, &(*entries)[*size].score) != EOF) {
        (*size)++;
    }

    fclose(file);
    return 0; // Успешная загрузка
}



int addScore(LeaderboardEntry **entries, int *size, const char *name, int score) {
    // Загрузка данных из файла leaderboard.txt
    int loadResult = LoadLeaderBoard(entries, size);
    if (loadResult != 0) {
        return loadResult; // Возвращаем код ошибки, если загрузка не удалась
    }
    
    // Проверка наличия имени игрока
    if (name == NULL || strlen(name) == 0 || strlen(name) >= MAX_NAME_LENGTH) {
        return ERROR_INVALID_FILENAME; // Некорректное имя игрока
    }
    
    // Проверка значения очков
    if (score < 0) {
        return ERROR_INVALID_SCORE; // Некорректное количество очков
    }
    
    // Выделение памяти для новой записи
    LeaderboardEntry *newEntry = (LeaderboardEntry*)malloc(sizeof(LeaderboardEntry));
    if (newEntry == NULL) {
        return ERROR_MEMORY_ALLOCATION; // Ошибка выделения памяти
    }
    
    // Копирование имени и значения очков в новую запись
    strcpy(newEntry->name, name);
    newEntry->score = score;
    
    // Увеличение размера массива и добавление новой записи
    (*size)++;
    *entries = (LeaderboardEntry*)realloc(*entries, *size * sizeof(LeaderboardEntry));
    if (*entries == NULL) {
        free(newEntry);
        return ERROR_MEMORY_ALLOCATION; // Ошибка перевыделения памяти
    }
    (*entries)[(*size) - 1] = *newEntry;
    free(newEntry);
    
    // Сортировка массива по убыванию очков
    qsort(*entries, *size, sizeof(LeaderboardEntry), compareEntries);
    
    // Сохранение данных в файл leaderboard.txt
    int saveResult = SaveLeaderBoard(*entries, *size);
    if (saveResult != 0) {
        return saveResult; // Возвращаем код ошибки, если сохранение не удалось
    }
    
    return 0; // Успешное добавление и сохранение
}


int SaveLeaderBoard(LeaderboardEntry *entries, int size) {
    FILE *file = fopen("leaderboard.txt", "w");
    if (file == NULL) {
        return ERROR_OPEN_FILE; // Ошибка открытия файла для записи
    }

    // Запись данных из структур в файл
    int i;
    for (i = 0; i < size; i++) {
        fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
    }

    fclose(file);
    return 0; // Успешная запись в файл
}
