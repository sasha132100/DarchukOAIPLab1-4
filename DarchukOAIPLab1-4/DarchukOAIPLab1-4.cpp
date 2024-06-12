//Дарчук 4183 
//Программирование и основы алгоритмизации 
//Лаборатоная работа 1

#include <iostream>

using namespace std;

void substitution_strcat_s(char* str, size_t strSize, const char* str2) {
    if (str == nullptr || str2 == nullptr) {
        cout << "Одна или обе строки пустые!" << endl;
        return;
    }
    if (strSize == 0) {
        cout << "Размер буфера не может быть равен нулю!" << endl;
        return;
    }

    size_t strLen = strlen(str);
    size_t str2Len = strlen(str2);

    if (strLen + str2Len + 1 > strSize) {
        cout << "Слишком маленький размер буфера!" << endl;
        return;
    }

    char* ptr = str + strlen(str);
    while (*str2 != '\0') {
        *ptr++ = *str2++;
    }
    *ptr = '\0'; 
    return;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    try {
        const size_t bufferSize = 255;
        char buffer[bufferSize] = "Строка1 ";
        char buffer1[bufferSize] = "Строка12 ";

        substitution_strcat_s(buffer, bufferSize, "Строка2");
        strcat_s(buffer1, bufferSize, "Строка22");

        cout << "Самописный метод: " << buffer << endl << endl;
        cout << "Официальный метод: " << buffer1 << endl;
    }
    catch (const exception& e) {
        cout << "Произошла ошибка при выполнении программы: " << e.what() << endl;
    }

    return 0;
}
