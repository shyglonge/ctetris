#pragma once
#define INITIAL_CAPACITY 20
#define MAX_NAME_LENGTH 50

#define ERROR_OPEN_FILE 0x001
#define ERROR_LOCK_FILE 0x002
#define ERROR_MEMORY_ALLOCATION 0x003
#define ERROR_INVALID_FILENAME 0x004
#define ERROR_INVALID_SCORE 0x005
#define ERROR_WRITE_FILE 0x006
#define ERROR_EMPTY_FILE 0x007

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} LeaderboardEntry;

/*
 * @brief LoadLeaderBoard функция загрузки таблицы лидеров из файла
 *
 * Эта функция открывает файл "leaderboard.txt", загружает данные о лидерах
 * и их счетах из этого файла в массив структур LeaderboardEntry.
 *
 * @param entries указатель на указатель на массив структур LeaderboardEntry, в который будут загружены данные о лидерах
 * @param size указатель на переменную, в которую будет записано количество загруженных записей
 * @return возвращает 0 в случае успешной загрузки, -1 в случае ошибки
 */
int LoadLeaderBoard(LeaderboardEntry **entries, int *size);

/*
 * @brief addScore функция добавления очков игроку
 *
 * Эта функция ищет игрока с заданным именем в таблице лидеров.
 * Если игрок найден, его счет обновляется на указанное количество очков.
 * Если игрок не найден, он добавляется в таблицу лидеров с указанным именем и счетом.
 *
 * @param entries указатель на указатель на массив структур LeaderboardEntry, представляющий таблицу лидеров
 * @param size указатель на переменную, содержащую текущее количество записей в таблице лидеров
 * @param name имя игрока, для которого добавляются очки
 * @param score количество очков, которое нужно добавить игроку
 * @return возвращает 0 в случае успешного добавления или обновления счета, -1 в случае ошибки
 */
int addScore(LeaderboardEntry **entries, int *size, const char *name, int score) ;

/*
 * @brief SaveLeaderBoard функция сохранения таблицы лидеров в файл
 *
 * Эта функция сохраняет текущее состояние таблицы лидеров в файл "leaderboard.txt".
 *
 * @param entries массив структур LeaderboardEntry, представляющий таблицу лидеров
 * @param size текущее количество записей в таблице лидеров
 * @return возвращает 0 в случае успешного сохранения, -1 в случае ошибки
 */
int SaveLeaderBoard(LeaderboardEntry *entries, int size);
