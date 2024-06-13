//Дарчук 4183 
//Программирование и основы алгоритмизации 
//Лаборатоная работа 2

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

struct Student {
    char name[20]; 
    char grades[4]; 
    double average;
};

double calculateAverage(const char* grades) {
    double sum = 0.0;
    for (int i = 0; i < 4; i++) {
        sum += grades[i] - '0'; 
    }
    return sum / 4;
}

void clearFile(const string& filename) {
    ofstream ofs(filename, ofstream::out | ofstream::trunc);
    ofs.close();
}

int main() {
    setlocale(LC_ALL, ""); 

    ifstream inputFile("st.txt");
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла st.txt" << endl;
        return 1;
    }

    Student students[100]; 
    int numStudents = 0;

    string line;
    while (getline(inputFile, line)) {
        line.copy(students[numStudents].name, 19, 0);
        students[numStudents].name[19] = '\0'; 

        line.copy(students[numStudents].grades, 4, 20);

        students[numStudents].average = calculateAverage(students[numStudents].grades);

        numStudents++;
    }

    inputFile.close();

    string outputFileName;
    cout << "Введите имя файла для записи результатов: ";
    getline(cin, outputFileName);
    outputFileName += ".txt";

    ifstream checkFile(outputFileName);
    if (checkFile.good()) {
        clearFile(outputFileName);
        cout << "Файл " << outputFileName << " уже существует и был очищен перед записью." << endl;
    }
    checkFile.close();

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла " << outputFileName << endl;
        return 1;
    }

    outputFile << left << setw(20) << "Фамилия И. О." << "Ср. балл" << endl;
    outputFile << "-------------------------------------" << endl;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].average >= 4.0)
            outputFile << left << setw(20) << students[i].name << students[i].average << endl;
    }

    outputFile.close();
    cout << "Результаты записаны в файл " << outputFileName << endl;

    return 0;
}