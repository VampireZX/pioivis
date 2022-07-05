#include <iostream>
using namespace std;
const int N = 100;


void matriza_smezhnosti(int kolvovershin, int graph[N][N]);
void find_diametr(int graph[N][N], int kolvovershin, int d);

int main()
{
	setlocale(LC_ALL, "Rus");
	int kolvovershin, diametr = 0, graph[N][N];
	cout << "Количество вершин в графе: ";
	cin >> kolvovershin;
	find_diametr(graph, kolvovershin, diametr);
	return 0;
}

void find_diametr(int graph[N][N], int kolvovershin, int d) {

	matriza_smezhnosti(kolvovershin, graph);
	for (int i = 0; i < kolvovershin; i++)
		graph[i][i] = 0;

	for (int k = 0; k < kolvovershin; k++)					//Алгоритм флойда - уоршелла
		for (int i = 0; i < kolvovershin; i++)
			for (int j = 0; j < kolvovershin; j++)
				if (graph[i][k] && graph[k][j] && i != j)
					if (graph[i][k] + graph[k][j] < graph[i][j] || graph[i][j] == 0)
						graph[i][j] = graph[i][k] + graph[k][j];

	for (int i = 0; i < kolvovershin; i++)					//сравниваем кратчайшие пути
		for (int j = 0; j < kolvovershin; j++)
			if (graph[i][j] > d)
				d = graph[i][j];
	cout << "Диаметр: " << d << endl;
}

void matriza_smezhnosti(int kolvovershin, int graph[N][N]) {
	cout << "Введите матрицу смежности:\n";
	for (int i = 0; i < kolvovershin; i++)
		for (int j = 0; j < kolvovershin; j++)
			cin >> graph[i][j];
}