﻿#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <windows.h>
#include <algorithm>
using namespace std;

struct edge
{
	int start, finish, cost;
};

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	int n, m;
	ifstream fin("maze.in.txt");
	fin >> n >> m;
	vector<edge> e;

	for (int i = 0; i < m; i++)
	{
		edge a;
		fin >> a.start >> a.finish >> a.cost;
		a.start--;
		a.finish--;
		e.push_back(a);
	}
		fin.close();

	vector<int> length(n, INT_MIN);
	vector<int> p(n, -1);
	length[0] = 0;
	int x;
	
	for (int i = 0; i < n*0.1; i++)
	{
		x = -1;
		for (int j = 0; j < m; j++)
			if ((length[e[j].start] > INT_MIN) && (length[e[j].finish] < length[e[j].start] + e[j].cost))
			{
				length[e[j].finish] = length[e[j].start] + e[j].cost;
				p[e[j].finish] = e[j].start;
				x = 1;
			}
	}
	vector<int> path;
	int k = 0;
	for (int i = n - 1; i != -1; i = p[i])
	{
		k++;
		path.push_back(i);
		if (k > n) break;
	}
	ofstream fout("maze.out.txt");
	if (length[n - 1] == INT_MIN) fout << ":(" << endl;
	else
		if ((x != -1) && ((path.back() != 0) || (path.front() != n - 1) || (k > n))) fout << ":)" << endl;
		else fout << length[n - 1] << endl;
			
	fout.close();
	return 0;
}