/*Сортировка посредством слияния списков*/

#include <iostream>
#include<fstream>
#include "windows.h"
#include <math.h>
#include <time.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define MY_PERFORMANCE 290
using namespace std;
using namespace std::chrono;

// Структура, описывающая одосвязный список
typedef struct Node {
	long int value;
	struct Node* next;
};

//Функция для подсчёта отношения производительносей 
// компьютера, на котором определялись функции прогноза, и 
//компьютера, на котором выполняется прогноз
double correct()
{
	int i = 0;
	clock_t start, finish;
	start = clock();
	while (i < 100000000)
		i++;
	finish = clock();
	double time = (double)(finish - start);
	double time_cpu = time / MY_PERFORMANCE;
	return time_cpu;
}

// Создание списка (с указателем на первый элемент)
Node* init(int a)
{
	Node* head;
	head = (Node*)malloc(sizeof(Node));
	head->value = a;
	head->next = NULL;
	return(head);
}

//Функция прогноза времени
void analyzing(int n, double CPU)
{
	int input = 0;
	double max = 0, med = 0, min = 0;
	cout << "Разница производительности - " << CPU << endl;
	if (n >= 1000 && n < 10000)
		input = 1;
	if (n >= 10000 && n < 50000)
		input = 2;
	if (n >= 50000)
		input = 3;
	switch (input)
	{
	case 1:     //минимальный диапазон
		max = 0.0000005747989681748921335 * n - 0.00001168019382801812002 * log2(n) + 0.0030572370974122095268;
		med = 0.00000046382236175752834584 * n - 0.00009341455792423495836 * log2(n) + 0.0027860602998098018321;
		min = 0.0000021691094921838422787 * n - 0.003782815507595332023 * log2(n) + 0.036368454388274890194;
		break;
	case 2:     //средний диапазон
		max = 0.00000082991581735006579519 * n + 0.0033595217324135622364 * log2(n) - 0.000539902779723291888;
		med = 0.00000057378728146321467883 * n - 0.0000704743764127345199 * log2(n) + 0.02235856106561796771;
		min = 0.0000002772366398671569641 * n - 0.00031377455496139303829 * log2(n) + 0.0059003244553500644988;
		break;
	case 3:     //максимальный диапазон
		max = 0.0000030030579208643025329 * n - 0.0036898978370479017003 * log2(n) + 0.084806918326814218575;
		med = 0.0000021594974072840153837 * n - 0.025501103842008803498 * log2(n) + 0.61527990986211934903;
		min = 0.00000046136442297493451382 * n - 0.0098915147518651975044 * log2(n) + 0.13658411669141766604;
		break;
	}
	cout << "Прогноз выполнения процедуры для n = " << n << endl;
	cout << "Минимальное время: " << CPU * min << endl;
	cout << "Среднее время: " << CPU * med << endl;
	cout << "Максимальное время: " << CPU * max << endl;
	system("pause");
}

Node* addNode(Node* curr, long int a)
{
	Node* temp, * p;
	temp = (Node*)malloc(sizeof(Node));
	p = curr->next;
	curr->next = temp;
	temp->value = a;
	temp->next = p;
	return(temp);
}

// Вывод шкалы прогресса
//void show_progress(int i, int n)
//{
//	char bar[] = "-------------------------";
//	double pr = ((i + 1) * 100 / n);
//
//	for (int j = 0; (j < pr / 4) && (j < 25); j++) {
//		bar[j] = '=';
//	}
//
//	cout << "\rReady : [" << bar << "](" << (int)pr << " %) ";
//
//	Sleep(50);
//}

// сортировка слияния списков

/* Функция для подсчёта длины связного списка*/
int length(Node* current)
{
	int count = 0;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return count;
}

/*Функция слияния двух списков*/
void merge(Node** start1, Node** end1,
	Node** start2, Node** end2)
{
	Node* temp = NULL;
	// Проверка, что значение start1 > значения start2. Если так, меняем указатели местами.
	if ((*start1)->value > (*start2)->value)
	{
		swap(*start1, *start2);
		swap(*end1, *end2);
	}

	//Слияние оставшихся узлов
	Node* astart = *start1, * aend = *end1;
	Node* bstart = *start2, * bend = *end2;
	Node* bendnext = (*end2)->next;
	while (astart != aend && bstart != bendnext)
	{
		if (astart->next->value > bstart->value)
		{
			temp = bstart->next;
			bstart->next = astart->next;
			astart->next = bstart;
			bstart = temp;
		}
		astart = astart->next;
	}
	if (astart == aend)
		astart->next = bstart;
	else
		*end2 = *end1;
}

/*Функция сортировки слиянием*/
void MergeSort(Node** head, bool select, int n, int progress)
{
	if (*head == NULL)
	{
		//if (progress == 2)
		//{
		//	show_progress(n - 1, n);
		//}
		return;
	}
	double step = log2(n);
	double maxStep = step * n;
	int maxSize = n;

	Node* start1 = NULL, * end1 = NULL, * start2 = NULL, * end2 = NULL;
	Node* prevend = NULL;

	int len = length(*head);

	for (int gap = 1; gap < len; gap = gap * 2)
	{
		start1 = *head;
		while (start1)
		{
			// Если это 1 итерация
			bool isFirstIter = 0;
			if (start1 == *head)
				isFirstIter = 1;

			// Первая часть для слияния
			int counter = gap;
			end1 = start1;
			while (--counter && end1->next)
				end1 = end1->next;

			// Вторая часть для слияния
			start2 = end1->next;
			if (!start2)
				break;
			counter = gap;
			end2 = start2;
			while (--counter && end2->next)
				end2 = end2->next;

			// Сохраняем для следующей итерации
			Node* temp = end2->next;

			// Слияние двух частей
			merge(&start1, &end1, &start2, &end2);
			if (select != false)
			{
				cout << "Выполнено " << step * 100 / maxStep << "%" << endl;
				Sleep(500);
			}
			//now_step++;
			//if (progress == 2)
			//{
			//	if (n >= 1000 && now_step % 17 == 0)
			//		show_progress(now_step, maxStep);
			//}
			//Обновляем начало для первой итерации, иначе присоединить prevend предыдущего списка со start1 следующего списка
			if (isFirstIter)
				*head = start1;
			else
				prevend->next = start1;

			prevend = end2;
			start1 = temp;
		}
		prevend->next = start1;
	}
	if (select != false)
	{
		cout << "Выполнено " << maxSize * 100 / maxStep << "%" << endl;
		Sleep(500);
	}
	//if (progress == 2)
	//{
	//	if (n >= 1000) // вывод шкалы прогресса при достаточно большом размере исходного массива
	//		show_progress(maxStep, maxStep);
	//}
}


// Меню взаимодействия с пользователем
void menu(int& n, int& input, int& output, int& progress)
{
	cout << "Введите количество элементов в списке: ";
	cin >> n;
	cout << endl;

	cout << "Укажите способ ввода последовательности чисел для списка:"
		<< "\n1 - с клавиатуры, 2 - из файла, 3 - случайная последовательность:\n";
	cin >> input;
	cout << endl;

	cout << "Укажите способ вывода результата:"
		<< "\n1 - в файл, 2 - на экран, 3 - частичный вывод на экран:\n";
	cin >> output;
	cout << endl;

	cout << "Укажите способ отслеживания результата:"
		<< "\n1 - с измерением времени, 2 - с выводом процента выполнения процедуры и шкалы прогресса:\n";
	cin >> progress;
	cout << endl;
}

// Ввод данных
void inputArrayAsList(int n, long* listArray, int input)
{
	int c;
	ifstream file;
	switch (input)
	{
	case 1: //Ввод данных с клавиатуры
		cout << "Введите " << n << " элементов:" << endl;
		for (int i = 0; i < n; i++) {
			cin >> c;
			listArray[i] = c;
		}
		break;
	case 2: //Ввод данных с файла
		file.open("input.txt");
		if (file) {
			for (int i = 0; i < n; i++)
			{
				file >> c;
				listArray[i] = c;
			}
		}
		file.close();
		break;
	case 3: //Генерация случайной последовательности
		srand(time(0));
		for (int i = 0; i < n; i++)
		{
			listArray[i] = rand();
		}
		break;
	default:
		cout << "Ошибка";
	}
}

void removeDisplay(int progress, Node** head, int n)
{
	if (progress == 1)
	{
		auto begin = steady_clock::now();
		bool select = false;
		MergeSort(head, select, n, progress);
		auto end = steady_clock::now();
		auto elapsed_mics = duration_cast<microseconds>(end - begin);
		std::cout << "Время сортировки: " << elapsed_mics.count() << " микросекунд\n";
	}
	else
	{
		bool select = true;
		MergeSort(head, select, n, progress);
		cout << "Выполнено 100%" << endl;
	}
}

//Вывод списка в файл
void printListIntoFile(Node* head, ostream& file)
{
	Node* curr = head;
	while (curr != NULL)
	{
		file << curr->value << ' ';
		curr = curr->next;
	}
	cout << endl;
}

//Вывод списка в консоль
void printListIntoConsole(Node* head)
{
	Node* curr = head;
	while (curr != NULL)
	{
		cout << curr->value << ' ';
		curr = curr->next;
	}
	cout << endl;
}

void selective_print(int n, Node* head)
{
	Node* curr = head;
	int i = 0/*, j = 0*/;
	if (n > 9)
	{
		while (curr != NULL)
		{
			cout << curr->value << ' ';
			curr = curr->next;
			i++;
			if (i == 3)
			{
				i = 0;
				curr = head;
				cout << "... ";
				break;
			}
		}
		while (curr != NULL)
		{
			curr = curr->next;
			i++;
			if (i == n / 2)
			{
				while (curr != NULL)
				{
					cout << curr->value << ' ';
					curr = curr->next;
					i++;
					if (i == (n / 2) + 3)
					{
						i = 0;
						curr = head;
						//j = 0;
						cout << "... ";
						break;
					}
				}
				break;
			}
		}
		while (curr != NULL)
		{
			curr = curr->next;
			i++;
			if (i == n - 3)
			{
				while (curr != NULL)
				{
					cout << curr->value << ' ';
					curr = curr->next;

				}
			}
		}
	}
	else
	{
		printListIntoConsole(head);
	}
}

void print(int output, Node* head, int n)
{
	ofstream file;
	switch (output)
	{
	case 1: //Печать в файл
		file.open("output.txt");
		if (file)
		{
			printListIntoFile(head, file);
			file.close();
			break;
		}
	case 2: //Печать в консоль
		printListIntoConsole(head);
		break;
	case 3: //частичный вывод
		selective_print(n, head);
		break;
	}
}

void menu_exit(int& exit)
{
	cout << "Повторить выполнение программы?" << endl;
	cout << "1 - Да, повторить;" << endl;
	cout << "2 - Нет, выйти из программы" << endl;
	cout << "Ваш выбор - ";
	cin >> exit;
}

int main() {
	bool process = true;
	// Вызов функции подсчёта разницы производительности
	double CPU = correct();
	while (process == true)
	{
		setlocale(LC_ALL, "Russian");
		int n, input, output, progress, exit;
		long* listArray;

		menu(n, input, output, progress);
		if (n <= 0)
		{
			cout << "Ошибка! Было введено неправильное количество элементов!" << endl;
			return -1;
		}
		listArray = new long[n];
		analyzing(n, CPU);
		inputArrayAsList(n, listArray, input);
		cout << endl << endl << endl;
		Node* head = NULL;

		if (n > 0)
			head = init(listArray[0]);

		Node* curr = head;
		for (int i = 1; i < n; i++)
		{
			curr = addNode(curr, listArray[i]);
		}


		////Отслеживание результата
		//if (progress == 1) //С изменением времени
		//{
		//	unsigned int start = clock();
		//	cout << "Start:" << start;
		//	MergeSort(&head, n, progress);
		//	unsigned int end = clock();
		//	cout << " End:" << end << endl;
		//	double f = (double)(end - start) / CLOCKS_PER_SEC;
		//	cout << "Время выполнения: " << f << " c";
		//	cout << endl << endl;
		//}
		////else с выводом шкалы прогресса
		//MergeSort(&head, n, progress);

		removeDisplay(progress, &head, n);

		cout << "\n";
		print(output, head, n);
		menu_exit(exit);
		if (exit == 2) {
			process = false;
			cout << "Завершение работы";
		}
	}
	return 0;
}