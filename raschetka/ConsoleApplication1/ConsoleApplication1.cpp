#include <iostream>
using namespace std;
const int N = 1000;
int kolvovershin, diametr = 0, graph[N][N];

void matrizasmezhnosti(int kolvovershin);
void algorithmfloydayorshela(int graph[N][N], int kolvovershin);

int main()
{
	setlocale(LC_ALL, "Rus");

	cout << "Количество вершин в графе: ";
	cin >> kolvovershin;

	cout << "Введите матрицу смежности:\n";
	matrizasmezhnosti(kolvovershin);

	cout << "Диаметр: " << endl;
	algorithmfloydayorshela(graph, kolvovershin);

}

void algorithmfloydayorshela(int graph[N][N], int kolvovershin)
{
	int k;
	for (int i = 0; i < kolvovershin; i++) graph[i][i] = 0;

	for (k = 0; k < kolvovershin; k++) //Алгоритм флойда - уоршелла
	{
		for (int i = 0; i < kolvovershin; i++)
		{
			for (int j = 0; j < kolvovershin; j++)
			{
				if (graph[i][k] && graph[k][j] && i != j)
				{
					if (graph[i][k] + graph[k][j] < graph[i][j] || graph[i][j] == 0)
					{
						graph[i][j] = graph[i][k] + graph[k][j];
					}
				}
			}
		}
	}

	for (int i = 0; i < kolvovershin; i++) //сравнивание кратчайших путейй
	{
		for (int j = 0; j < kolvovershin; j++)
		{
			if (graph[i][j] > diametr)
			{
				diametr = graph[i][j];
			}
		}
	}

	cout << diametr << endl;
}

void matrizasmezhnosti(int kolvovershin) {
	for (int i = 0; i < kolvovershin; i++)
	{
		for (int j = 0; j < kolvovershin; j++)
		{
			cin >> graph[i][j];
		}
	}
}