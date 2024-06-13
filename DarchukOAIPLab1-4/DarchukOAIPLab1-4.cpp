//Дарчук 4183 
//Программирование и основы алгоритмизации 
//Лаборатоная работа 2

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>

#define MAX 30

struct STUDENT
{
	char fio[20]; // фамилии и.о.
	char oc[4]; // 5 оценок + '\n' + '\0'
};

struct EL_TAB
{
	char fio[20]; // фамилия и.о.
	int oc[4]; // оценки
	float srball; // средний балл
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
		puts("-------------------------------------------------------");
		nom = getchar();
		switch (nom)
		{
		case '1': PechTab(tab, n); break;
		case '2': Stud(tab, n); break;
		case '3': break;
		default: puts("\nНужно ввести номер от 1 до 3");
		}

		if (nom != '3')
		{
			puts("\nДля продолжения нажмите любую клавишу");
			_getch();
		}
	} while (nom != '3');
}
