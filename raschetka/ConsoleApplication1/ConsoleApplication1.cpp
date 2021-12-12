#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
using namespace std;
bool graph[1000][1000];

int searchingfordiametr(int N);

int main()
{
	setlocale(LC_ALL, "Russian");
	int N;
	cout << "Введите кол-во вершин графа: ";
	cin >> N;

	cout << "Матрица смежности графа" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> graph[i][j];
		}
	}

    int diametr = searchingfordiametr(N);
    cout << diametr;

}

int searchingfordiametr(int N)
{
    int** edge = new int* [N];

    for (int i = 0; i < N; i++)
    {
        edge[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            edge[i][j] = graph[i][j]; 
            if (!edge[i][j])
            {
                edge[i][j] = 10000;
            }
        }
    }

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i != j)
                {
                    edge[i][j] = min(edge[i][j], edge[i][k] + edge[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (edge[i][j] == 10000)
            {
                edge[i][j] = 0;
            }
        }
    }

    int max = edge[0][1];
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++) {
            if (edge[i][j] > max)
            {
                max = edge[i][j];
            }
        }
    }

    return max;
    delete[] edge;
}
