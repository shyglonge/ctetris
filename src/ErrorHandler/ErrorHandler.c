#include <stdio.h>
#include "ErrorHandler.h"



const char* error_handler(int str1) {
    switch (str1) {
    case 0x001:
        return "0x001 - ERROR_OPEN_FILE. Ошибка открытия файла\x00";
    case 0x002:
        return "0x002 - ERROR_LOCK_FILE. Не удалось заблокировать файл.\x00";
    case 0x003:
        return "0x003 - ERROR_MAX_ENTRIES. Слишком много рекордов.\x00";
    case 0x004:
        return "0x004 - ERROR_MEMORY_ALLOCATION. Ошибка выделения памяти.\x00";
    case 0x005:
        return "0x005 - ERROR_INVALID_NAME. Недопустимое имя.\x00";
    case 0x006:
        return "0x006 - ERROR_INVALID_SCORE. Недопустимый результат\x00";
    case 0x007:
        return "0x007 - ERROR_WRITE_FILE. Ошибка записи файла.\x00";
    case 0x008:
        return "0x008 - ERROR_EMPTY_FILE. Ошибка пустого файла.\x00";
    default:
        return "UNKNOWN_ERROR_CODE. - Неизвестный код ошибки \x00";
    }
}