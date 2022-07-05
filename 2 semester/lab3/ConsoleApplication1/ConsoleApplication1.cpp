#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;
void inputSet(vector<string>& set)
{
	string buffer;
	int choice, size, l;

	set.clear();

	cout << "Введите кол-во элементов: ";
	cin >> size;

	for (int i = 0; i < size; i++) {
		cout << "Введите " << i + 1 << "-ый элемент множесвта: ";
		cin >> buffer;
		set.push_back(buffer);
		
		
	}
	cout << "Введённое вами множество: ";

	for (int i = 0; i != set.size(); i++) 
	{
		
		cout << set[i] << " ";
	}
		
	cout << endl;

	if (adjacent_find(set.begin(), set.end()) != set.end())
	{
		cout << "Во множестве присутсвуют повторяющиеся элементы.\n1 - Перезаполнить множество\n2 - Удалить все повторяющиеся элементы\nВаш выбор: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			inputSet(set);
			break;
		case 2:

			vector<string>::iterator ip;

			// Сортировка массива
			sort(set.begin(), set.end());

			ip = unique(set.begin(), set.begin() + size);

			set.resize(distance(set.begin(), ip));

			cout << "Множество после удаления повторяющихся элементов:\n";
			for (ip = set.begin(); ip != set.end(); ++ip) {  
				cout << *ip << " ";
			}

			cout << endl;
			break;
		}
	}
}

void checkIsSubset(vector<string> firstSet, vector<string> secondSet)
{
	int count = 0;
	for (int i = 0; i < secondSet.size(); i++)
	{
		if (find(firstSet.begin(), firstSet.end(), secondSet[i]) != firstSet.end())
			count++;
	}

	if (count == secondSet.size())
		cout << "Множество является подмножеством";
	else
		cout << "Множество не является подмножеством";

}

int main()
{
	system("chcp 1251");
	system("cls");
	vector<string> firstSet, secondSet;

	cout << "Введите первое множество:\n";
	inputSet(secondSet);
	cout << "\n\n";

	cout << "Введите второе множество для проверки:\n";
	inputSet(firstSet);
	cout << "\n\n";

	cout << "Проверка первого множества:\n";
	checkIsSubset(firstSet, secondSet);
	cout << "\n\n";

	cout << "Проверка второго множества:\n";
	checkIsSubset(secondSet, firstSet);
	cout << "\n\n";

	return 0;
}