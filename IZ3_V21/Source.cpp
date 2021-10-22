/*���������� ����������� ������� �������*/

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

// ���������, ����������� ���������� ������
typedef struct Node {
	long int value;
	struct Node* next;
};

//������� ��� �������� ��������� ������������������ 
// ����������, �� ������� ������������ ������� ��������, � 
//����������, �� ������� ����������� �������
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

// �������� ������ (� ���������� �� ������ �������)
Node* init(int a)
{
	Node* head;
	head = (Node*)malloc(sizeof(Node));
	head->value = a;
	head->next = NULL;
	return(head);
}

//������� �������� �������
void analyzing(int n, double CPU)
{
	int input = 0;
	double max = 0, med = 0, min = 0;
	cout << "������� ������������������ - " << CPU << endl;
	if (n >= 1000 && n < 10000)
		input = 1;
	if (n >= 10000 && n < 50000)
		input = 2;
	if (n >= 50000)
		input = 3;
	switch (input)
	{
	case 1:     //����������� ��������
		max = 0.0000005747989681748921335 * n - 0.00001168019382801812002 * log2(n) + 0.0030572370974122095268;
		med = 0.00000046382236175752834584 * n - 0.00009341455792423495836 * log2(n) + 0.0027860602998098018321;
		min = 0.0000021691094921838422787 * n - 0.003782815507595332023 * log2(n) + 0.036368454388274890194;
		break;
	case 2:     //������� ��������
		max = 0.00000082991581735006579519 * n + 0.0033595217324135622364 * log2(n) - 0.000539902779723291888;
		med = 0.00000057378728146321467883 * n - 0.0000704743764127345199 * log2(n) + 0.02235856106561796771;
		min = 0.0000002772366398671569641 * n - 0.00031377455496139303829 * log2(n) + 0.0059003244553500644988;
		break;
	case 3:     //������������ ��������
		max = 0.0000030030579208643025329 * n - 0.0036898978370479017003 * log2(n) + 0.084806918326814218575;
		med = 0.0000021594974072840153837 * n - 0.025501103842008803498 * log2(n) + 0.61527990986211934903;
		min = 0.00000046136442297493451382 * n - 0.0098915147518651975044 * log2(n) + 0.13658411669141766604;
		break;
	}
	cout << "������� ���������� ��������� ��� n = " << n << endl;
	cout << "����������� �����: " << CPU * min << endl;
	cout << "������� �����: " << CPU * med << endl;
	cout << "������������ �����: " << CPU * max << endl;
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

// ����� ����� ���������
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

// ���������� ������� �������

/* ������� ��� �������� ����� �������� ������*/
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

/*������� ������� ���� �������*/
void merge(Node** start1, Node** end1,
	Node** start2, Node** end2)
{
	Node* temp = NULL;
	// ��������, ��� �������� start1 > �������� start2. ���� ���, ������ ��������� �������.
	if ((*start1)->value > (*start2)->value)
	{
		swap(*start1, *start2);
		swap(*end1, *end2);
	}

	//������� ���������� �����
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

/*������� ���������� ��������*/
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
			// ���� ��� 1 ��������
			bool isFirstIter = 0;
			if (start1 == *head)
				isFirstIter = 1;

			// ������ ����� ��� �������
			int counter = gap;
			end1 = start1;
			while (--counter && end1->next)
				end1 = end1->next;

			// ������ ����� ��� �������
			start2 = end1->next;
			if (!start2)
				break;
			counter = gap;
			end2 = start2;
			while (--counter && end2->next)
				end2 = end2->next;

			// ��������� ��� ��������� ��������
			Node* temp = end2->next;

			// ������� ���� ������
			merge(&start1, &end1, &start2, &end2);
			if (select != false)
			{
				cout << "��������� " << step * 100 / maxStep << "%" << endl;
				Sleep(500);
			}
			//now_step++;
			//if (progress == 2)
			//{
			//	if (n >= 1000 && now_step % 17 == 0)
			//		show_progress(now_step, maxStep);
			//}
			//��������� ������ ��� ������ ��������, ����� ������������ prevend ����������� ������ �� start1 ���������� ������
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
		cout << "��������� " << maxSize * 100 / maxStep << "%" << endl;
		Sleep(500);
	}
	//if (progress == 2)
	//{
	//	if (n >= 1000) // ����� ����� ��������� ��� ���������� ������� ������� ��������� �������
	//		show_progress(maxStep, maxStep);
	//}
}


// ���� �������������� � �������������
void menu(int& n, int& input, int& output, int& progress)
{
	cout << "������� ���������� ��������� � ������: ";
	cin >> n;
	cout << endl;

	cout << "������� ������ ����� ������������������ ����� ��� ������:"
		<< "\n1 - � ����������, 2 - �� �����, 3 - ��������� ������������������:\n";
	cin >> input;
	cout << endl;

	cout << "������� ������ ������ ����������:"
		<< "\n1 - � ����, 2 - �� �����, 3 - ��������� ����� �� �����:\n";
	cin >> output;
	cout << endl;

	cout << "������� ������ ������������ ����������:"
		<< "\n1 - � ���������� �������, 2 - � ������� �������� ���������� ��������� � ����� ���������:\n";
	cin >> progress;
	cout << endl;
}

// ���� ������
void inputArrayAsList(int n, long* listArray, int input)
{
	int c;
	ifstream file;
	switch (input)
	{
	case 1: //���� ������ � ����������
		cout << "������� " << n << " ���������:" << endl;
		for (int i = 0; i < n; i++) {
			cin >> c;
			listArray[i] = c;
		}
		break;
	case 2: //���� ������ � �����
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
	case 3: //��������� ��������� ������������������
		srand(time(0));
		for (int i = 0; i < n; i++)
		{
			listArray[i] = rand();
		}
		break;
	default:
		cout << "������";
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
		std::cout << "����� ����������: " << elapsed_mics.count() << " �����������\n";
	}
	else
	{
		bool select = true;
		MergeSort(head, select, n, progress);
		cout << "��������� 100%" << endl;
	}
}

//����� ������ � ����
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

//����� ������ � �������
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
	case 1: //������ � ����
		file.open("output.txt");
		if (file)
		{
			printListIntoFile(head, file);
			file.close();
			break;
		}
	case 2: //������ � �������
		printListIntoConsole(head);
		break;
	case 3: //��������� �����
		selective_print(n, head);
		break;
	}
}

void menu_exit(int& exit)
{
	cout << "��������� ���������� ���������?" << endl;
	cout << "1 - ��, ���������;" << endl;
	cout << "2 - ���, ����� �� ���������" << endl;
	cout << "��� ����� - ";
	cin >> exit;
}

int main() {
	bool process = true;
	// ����� ������� �������� ������� ������������������
	double CPU = correct();
	while (process == true)
	{
		setlocale(LC_ALL, "Russian");
		int n, input, output, progress, exit;
		long* listArray;

		menu(n, input, output, progress);
		if (n <= 0)
		{
			cout << "������! ���� ������� ������������ ���������� ���������!" << endl;
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


		////������������ ����������
		//if (progress == 1) //� ���������� �������
		//{
		//	unsigned int start = clock();
		//	cout << "Start:" << start;
		//	MergeSort(&head, n, progress);
		//	unsigned int end = clock();
		//	cout << " End:" << end << endl;
		//	double f = (double)(end - start) / CLOCKS_PER_SEC;
		//	cout << "����� ����������: " << f << " c";
		//	cout << endl << endl;
		//}
		////else � ������� ����� ���������
		//MergeSort(&head, n, progress);

		removeDisplay(progress, &head, n);

		cout << "\n";
		print(output, head, n);
		menu_exit(exit);
		if (exit == 2) {
			process = false;
			cout << "���������� ������";
		}
	}
	return 0;
}