//Дарчук 4183 
//Программирование и основы алгоритмизации 
//Лаборатоная работа 3

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <string>

#define MAX 30

using namespace std;

struct STUDENT
{
	char fio[20]; 
	char oc[6]; 
};

struct EL_TAB
{
	char fio[20]; 
	int oc[4]; 
	float srball;
};

void PechTab(EL_TAB* tab, int n)
{
	int j;
	puts("\nФамилия И.О. Ср.балл");
	puts("------------------------------");
	for (j = 0; j < n; j++)
	{
		printf("%s %.1f\n", tab[j].fio, tab[j].srball);
	}
}

void Stud(EL_TAB* tab, int n)
{
	char searchFio[20], lastName[20];
	cout << "Введите фамилию студента: ";
	cin >> searchFio;

	bool found = false;
	for (int j = 0; j < n; j++)
	{
		char* spacePos = strchr(tab[j].fio, ' ');
		if (spacePos != NULL)
		{
			int length = spacePos - tab[j].fio;
			strncpy_s(lastName, tab[j].fio, length);
		}
		else 
			break;

		if (strcmp(lastName, searchFio) == 0)
		{
			cout << "Фамилия И.О.: " << tab[j].fio << endl;
			cout << "Оценки: ";
			for (int k = 0; k < 4; k++)
			{
				cout << tab[j].oc[k] << " ";
			}
			cout << endl;
			cout << "Средний балл: " << tab[j].srball << endl;
			found = true;
			break;
		}
	}

	if (!found)
	{
		cout << "Студент с фамилией " << searchFio << " не найден." << endl;
	}
}

void sortByAvgMark(EL_TAB* tab, int n) 
{
	EL_TAB temp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (tab[j].srball < tab[j + 1].srball)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
		}
	}

	PechTab(tab, n);
}

void foundOnlyGreat(EL_TAB* tab, int n) 
{
	int j;
	puts("\nОтличники группы (Балл больше или равен 4.5): ");
	puts("\nФамилия И.О. Ср.балл");
	puts("------------------------------");
	for (j = 0; j < n; j++)
	{
		if (tab[j].srball >= 4.5) {
			printf("%s %.1f\n", tab[j].fio, tab[j].srball);
		}
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");

	FILE* f; 
	STUDENT tz;
	EL_TAB tab[MAX]; 
	int n, i;
	float s; 

	fopen_s(&f, "st.txt", "r");
	if (f == NULL)
	{
		puts("Файл st.txt не найден");
		return;
	}

	n = 0;
	while (fgets((char*)&tz, sizeof(struct STUDENT), f) != NULL)
	{
		for (i = 0, s = 0; i < 4; i++)
		{
			int ocenka = tz.oc[i] - '0';
			tab[n].oc[i] = ocenka;
			s += ocenka;
		}
		tz.fio[19] = '\0';
		strcpy_s(tab[n].fio, tz.fio);
		tab[n++].srball = s / 4;
	}
	fclose(f);

	char nom; 
	do
	{
		puts("------------------------------------------------------");
		puts("Выберите номер пункта меню:");
		puts("1 - Средние баллы студентов");
		puts("2 - Информация о заданном студенте");
		puts("3 - Выход");
		puts("4 - Вывести студентов отсортированных по успеваемости");
		puts("5 - Вывести только отличников группы");
		puts("-------------------------------------------------------");
		nom = getchar();
		switch (nom)
		{
		case '1': 
			PechTab(tab, n); 
			break;

		case '2':
			Stud(tab, n); 
			break;

		case '3': 
			break;

		case '4':
			sortByAvgMark(tab, n);
			break;

		case '5':
			foundOnlyGreat(tab, n);
			break;

		default: 
			puts("\nНужно ввести номер от 1 до 5");
		}

		if (nom != '3')
		{
			puts("\nДля продолжения нажмите любую клавишу");
			_getch();
		}
	} while (nom != '3');
}
