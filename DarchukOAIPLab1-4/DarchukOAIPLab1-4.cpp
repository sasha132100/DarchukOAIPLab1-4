//Дарчук 4183 
//Программирование и основы алгоритмизации 
//Лаборатоная работа 4
//1 - Ж, 2 - А, 3 - В, 4 - Б 
//ж) предпоследний элемент;
//а) k-го по порядку элемента списка;
//в) следующих до заданного идентификатора.
//б) все идентификаторы, начинающиеся с заданной буквы;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

using namespace std;

#define MAXDL 9 

struct EL_SP 
{
	char id[MAXDL]; 
	struct EL_SP* sled; 
};

void Vkl(struct EL_SP** p, char t_id[])
{
	struct EL_SP* pt, * k, * j = NULL; 

	pt = (struct EL_SP*)malloc(sizeof(struct EL_SP));
	strcpy_s(pt->id, t_id);

	if (*p == NULL || strcmp(pt->id, (*p)->id) < 0)
	{
		pt->sled = *p; *p = pt;
	}
	else
	{
		k = *p;
		while (k != NULL && strcmp(pt->id, k->id) >= 0)
		{
			j = k;
			k = k->sled;
		}

		if (j != NULL)
			j->sled = pt;
		else
			*p = pt;

		pt->sled = k;
	}
}

void PechSp(struct EL_SP* p)
{
	struct EL_SP* i; 
	printf("\nРезультат:\n");
	for (i = p; i != NULL; i = i->sled)
		puts(i->id);
}

void deleteLastMinus1(struct EL_SP** p) {

	if (*p == NULL || (*p)->sled == NULL || (*p)->sled->sled == NULL) {
		printf("В списке меньше трёх элементов, предпоследний элемент нельзя удалить.\n");
		return;
	}

	struct EL_SP* pred = NULL;
	struct EL_SP* current = *p;

	while (current->sled->sled != NULL) {
		pred = current;
		current = current->sled;
	}

	struct EL_SP* temp = current->sled;
	free(current);
	if (pred != NULL) {
		pred->sled = temp;
	}
	else {
		*p = temp;
	}

	printf("\nПредпоследний элемент удалён.\n");
}

void changeElementK(struct EL_SP** p, unsigned k, char t_id[]) {
	struct EL_SP* current = *p;
	unsigned count = 1;

	while (current != NULL && count < k) {
		current = current->sled;
		count++;
	}

	if (current != NULL) {
		strcpy_s(current->id, t_id);
		printf("\nЗначение %d-го элемента изменено на \"%s\".\n", k, t_id);
	}
	else 
		printf("В списке меньше %u элементов, невозможно изменить %u-й элемент.\n", k, k);
}

int counterToM(struct EL_SP** p, char t_id[]) {
	struct EL_SP* current = *p;
	unsigned count = 0;

	while (current != NULL && strcmp(current->id, t_id) != 0) {
		count++;
		current = current->sled;
	}

	return count;
}

void addToArr(struct EL_SP* p, char letter, char A[][MAXDL]) {
	struct EL_SP* current = p;
	int counter = 0;

	for (int i = 0; i < 9; i++) {
		A[i][0] = '\0';
	}

	while (current != NULL) {
		if (current->id[0] == letter) {
			strcpy_s(A[counter], current->id);
			counter++;
		}
		current = current->sled;
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");

	struct EL_SP* p; 
	unsigned n, i, k, counter; 
	char t_id[MAXDL], letter, A[9][MAXDL]; 

	printf("Введите число идентификаторов n = ");
	scanf_s("%u", &n);
	getchar(); 
	p = NULL; 

	printf("\nВведите идентификаторы (после каждого нажимайте клавишу <Enter>)\n");

	for (i = 1; i <= n; i++)
	{
		gets_s(t_id);
		Vkl(&p, t_id); 
	}

	PechSp(p);

	deleteLastMinus1(&p);

	PechSp(p);

	printf("\nВведите порядковый номер элемента для замены: ");
	scanf_s("%u", &k);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	printf("Введите новый элемент для замены: ");
	gets_s(t_id);
	changeElementK(&p, k, t_id);

	PechSp(p);

	printf("\nВведите элемент до которого нужно вести учет: ");
	gets_s(t_id);
	counter = counterToM(&p, t_id);
	if (counter > n)
		printf("Среди элементов строки не был наден заданный элмент.");
	else
		printf("\nКоличество элементов, которые находятся до %s элемента равно: %u", t_id, counter);

	printf("\n\nВведите букву, по которой нужно отобрать идентификаторы: ");
	scanf_s("%c", &letter); 
	addToArr(p, letter, A);

	printf("\nМассив, состоящий из элементов, начинающихся на букву %c: \n", letter);
	for (int c = 0; c < 9; c++) {
		if (A[c][0] != '\0') 
			printf("%s\n", A[c]);
	}

	printf("\nДля завершения нажмите любую клавишу\n");

	_getch();
	return;
}
