#include <stdio.h>
#include <string.h> // Для функции strcmp
#include "../../src/ErrorHandler/ErrorHandler.h"
#include <locale.h> // Для функции setlocale


int test_error_handler() {
    int code = 0x001;
    const char* str2 = "0x001 - ERROR_OPEN_FILE. Ошибка открытия файла";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

int test_error_handler2() {
    int code = 0x002;
    const char* str2 = "0x002 - ERROR_LOCK_FILE. Не удалось заблокировать файл.";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

int test_error_handler3() {
    int code = 0x003;
    const char* str2 = "0x003 - ERROR_MAX_ENTRIES. Слишком много рекордов.";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}


int test_error_handler_U() {
    int code = 0x00;
    const char* str2 = "UNKNOWN_ERROR_CODE. - Неизвестный код ошибки ";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}
int test_error_handler4() {
    int code = 0x004;
    const char* str2 = "0x004 - ERROR_MEMORY_ALLOCATION. Ошибка выделения памяти.";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}


int test_error_handler5() {
    int code = 0x005;
    const char* str2 = "0x005 - ERROR_INVALID_NAME. Недопустимое имя.";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

int test_error_handler6() {
    int code = 0x006;
    const char* str2 = "0x006 - ERROR_INVALID_SCORE. Недопустимый результат";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

int test_error_handler7() {
    int code = 0x007;
    const char* str2 = "0x007 - ERROR_WRITE_FILE. Ошибка записи файла.";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

int test_error_handler8() {
    int code = 0x008;
    const char* str2 = "0x008 - ERROR_EMPTY_FILE. Ошибка пустого файла.";
    const char* str1 = error_handler(code);

    // Используем strcmp без указания типов и int перед вызовом функции
    if (strcmp(str1, str2) == 0) {
        return 0;
    }
    else {
        return -1;
    }
}





int main() {
    // Проверяем каждую функцию тестирования и сохраняем результаты
    setlocale(LC_ALL, "Russian");
	printf("\n_________________________\n");
	printf("Error Handler Module Tests\n");
	
    int result1 = test_error_handler();
    int result2 = test_error_handler2();
    int result3 = test_error_handler3();
    int resultU = test_error_handler_U();
    int result4 = test_error_handler4();
    int result5 = test_error_handler5();
    int result6 = test_error_handler6();
    int result7 = test_error_handler7();
    int result8 = test_error_handler8();
    
    // Печатаем результат
    if (result1 == 0) {
        printf("test_error_handler(): PASS\n");
    }
    else {
        printf("test_error_handler(): FAIL\n");
    }


    if (result2 == 0) {
        printf("test_error_handler2(): PASS\n");
    }
    else {
        printf("test_error_handler2(): FAIL\n");
    }
	

    if (result3 == 0) {
        printf("test_error_handler3(): PASS\n");
    }
    else {
        printf("test_error_handler3(): FAIL\n");
    }


    if (result4 == 0) {
        printf("test_error_handler4(): PASS\n");
    }
    else {
        printf("test_error_handler4(): FAIL\n");
    }

    if (result5 == 0) {
        printf("test_error_handler(): PASS\n");
    }
    else {
        printf("test_error_handler(): FAIL\n");
    }

    if (result6 == 0) {
        printf("test_error_handler(): PASS\n");
    }
    else {
        printf("test_error_handler(): FAIL\n");
    }

    if (result7 == 0) {
        printf("test_error_handler(): PASS\n");
    }
    else {
        printf("test_error_handler(): FAIL\n");
    }

    if (result8 == 0) {
        printf("test_error_handler(): PASS\n");
    }
    else {
        printf("test_error_handler(): FAIL\n");
    }


    // Возвращаем общий результат (можно использовать любой)
    return result1;
}