#include "RBT.h"
#include <fstream>
using namespace std;

void test(bool x) {
	if (x == 1)
		cout << '\t' << '\t' << "RIGHT!" << endl;
	else
		cout << '\t' << '\t' << "WRONG!" << endl;

}

int RedGoestoRed(RBTree x, ifstream& file)
{
	int kol = 0;
	if (&file) {
		int n, key;
		file >> n;
		for (int i = 0; i < n; i++) {
			file >> key;
			if (x.searchTree(key)->color == 1 && (x.searchTree(key)->left->color == 1 || x.searchTree(key)->right->color == 1))
				kol++;
		}
	}
	file.close();
	return kol;

}

int CheckingExisting(RBTree x, ifstream& file) {
	int kol = 0;
	if (&file) {
		int n, key;
		file >> n;
		int ar[100];
		for (int i = 0; i < n; i++) {
			file >> key;
			for (int t = 0; t < n; t++) {
				if (key == ar[t])
					kol++;
			}
			ar[i] = key;
		}
	}
	return kol;
}

//general insert test
bool InsertTesting1() {

	RBTree example;

	ifstream IT1("InsertTest1.txt");
	if (IT1) {
		int n, fdata, fcolor, fkol, key;
		int kol = 0;
		IT1 >> n;
		for (int i = 0; i < n; i++) {
			IT1 >> key;
			example.insert(key);
		}
		IT1 >> n;
		for (int i = 0; i < n; i++) {
			IT1 >> key;
			IT1 >> fdata;
			IT1 >> fcolor;
			if (example.searchTree(key)->data == fdata && example.searchTree(key)->color == fcolor)
				kol++;

		}
		IT1 >> fkol;
		if (kol == fkol)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	IT1.close();
}

//repeating node insert
bool InsertTesting2() {
	RBTree example;
	ifstream IT2("InsertTest2.txt");
	if (IT2) {
		int n, key;
		IT2 >> n;
		for (int i = 0; i < n; i++) {
			IT2 >> key;
			example.insert(key);
		}
		if (CheckingExisting(example, IT2) != n)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	IT2.close();
}

//genereal deleting
bool DeleteTesting1() {

	RBTree example;

	ifstream DT1("DeleteTest1.txt");
	if (DT1) {
		int n, m, fdata, fcolor, fkol, key;
		int kol = 0;
		DT1 >> n;
		for (int i = 0; i < n; i++) {
			DT1 >> key;
			example.insert(key);
		}
		DT1 >> m;
		for (int i = 0; i < m; i++) {
			DT1 >> key;
			example.deleteNode(key);
		}

		DT1 >> n;
		for (int i = 0; i < n; i++) {
			DT1 >> key;
			DT1 >> fdata;
			DT1 >> fcolor;
			if (example.searchTree(key)->data == fdata && example.searchTree(key)->color == fcolor)
				kol++;

		}
		DT1 >> fkol;
		if (kol == fkol)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	DT1.close();
}

//delete non-existing node
bool DeleteTesting2() {
	RBTree example;
	ifstream DT2("DeleteTest2.txt");
	if (DT2) {
		int n, m, key;
		DT2 >> n;
		for (int i = 0; i < n; i++) {
			DT2 >> key;
			example.insert(key);
		}
		DT2 >> m;
		for (int i = 0; i < m; i++)
		{
			DT2 >> key;
			example.deleteNode(key);
		}
		if (CheckingExisting(example, DT2) != n - m)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	DT2.close();
}

//generalsearch
bool SearchTesting1() {
	RBTree example;

	ifstream ST1("SearchTest1.txt");
	if (ST1) {
		int n, m, key;
		ST1 >> n;
		for (int i = 0; i < n; i++) {
			ST1 >> key;
			example.insert(key);
		}
		ST1 >> m;
		if (example.searchTree(m)->data == m && example.searchTree(m)->color == 0)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	ST1.close();
}

//search for non-existing node
bool SearchTesting2() {
	RBTree example;

	ifstream ST2("SearchTest2.txt");
	if (ST2) {
		int n;
		ST2 >> n;
		if (example.searchTree(n) == example.TNULL)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	ST2.close();
}

//general test	
bool MaxFinderTesting1() {
	RBTree example;

	ifstream MaT1("MaxTest1.txt");
	if (MaT1) {
		int n, m, key;
		MaT1 >> n;
		for (int i = 0; i < n; i++) {
			MaT1 >> key;
			example.insert(key);
		}
		MaT1 >> m;
		if (example.globalMaximum() == m)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	MaT1.close();
}

//in an empty tree
bool MaxFinderTesting2() {
	RBTree example;

	if (example.globalMaximum() == NULL)
		return 1;
	else
		return 0;
}

//general test
bool MinFinderTesting1() {
	RBTree example;

	ifstream MiT1("MinTest1.txt");
	if (MiT1) {
		int n, m, key;
		MiT1 >> n;
		for (int i = 0; i < n; i++) {
			MiT1 >> key;
			example.insert(key);
		}
		MiT1 >> m;
		if (example.globalMinimum() == m)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	MiT1.close();
}

//in an empty tree
bool MinFinderTesting2() {
	RBTree example;

	if (example.globalMinimum() == NULL)
		return 1;
	else
		return 0;
}

//general test
bool ClosestLesserTesting1() {
	RBTree example;

	ifstream LT1("LesserTest1.txt");
	if (LT1) {
		int n, m, key, result;
		LT1 >> n;
		for (int i = 0; i < n; i++) {
			LT1 >> key;
			example.insert(key);
		}
		LT1 >> m;
		LT1 >> result;
		if (example.closestLesser(m) == result)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	LT1.close();
}

//in an empty tree
bool ClosestLesserTesting2() {
	RBTree example;

	ifstream LT2("LesserTest2.txt");
	if (LT2) {
		int n;
		LT2 >> n;
		if (example.closestLesser(n) == NULL)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	LT2.close();
}

//the key is smaller than minimum
bool ClosestLesserTesting3() {
	RBTree example;

	ifstream LT3("LesserTest3.txt");
	if (LT3) {
		int n, key, m;
		LT3 >> n;
		for (int i = 0; i < n; i++) {
			LT3 >> key;
			example.insert(key);
		}
		LT3 >> m;
		if (example.closestLesser(m) == NULL)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	LT3.close();
}

//general test
bool ClosestGreaterTesting1() {
	RBTree example;

	ifstream GT1("GreaterTest1.txt");
	if (GT1) {
		int n, m, key, result;
		GT1 >> n;
		for (int i = 0; i < n; i++) {
			GT1 >> key;
			example.insert(key);
		}
		GT1 >> m;
		GT1 >> result;
		if (example.closestGreater(m) == result)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	GT1.close();
}

//in an empty tree
bool ClosestGreaterTesting2() {
	RBTree example;

	ifstream GT2("GreaterTest2.txt");
	if (GT2) {
		int n;
		GT2 >> n;
		if (example.closestGreater(n) == NULL)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	GT2.close();
}

//the key is bigger than maximum 
bool ClosestGreaterTesting3() {
	RBTree example;

	ifstream GT3("GreaterTest3.txt");
	if (GT3) {
		int n, key, m;
		GT3 >> n;
		for (int i = 0; i < n; i++) {
			GT3 >> key;
			example.insert(key);
		}
		GT3 >> m;
		if (example.closestGreater(m) == NULL)
			return 1;
		else
			return 0;
	}
	else
		return 0;
	GT3.close();
}

int main()
{
	cout << "Performing testing..." << endl;
	cout << '\n' << '\t' << "Testing insert function..." << '\n' << '\t' << "Test 1 (inserting normal numbers): ";
	test(InsertTesting1());
	cout << '\t' << "Test 2 (inserting already existing node): ";
	test(InsertTesting2());
	cout << '\n' << '\t' << "Testing delete function..." << '\n' << '\t' << "Test 1 (deleting a node): ";
	test(DeleteTesting1());
	cout << '\t' << "Test 2 (deleting the node that doesn't exist): ";
	test(DeleteTesting2());
	cout << '\n' << '\t' << "Testing search function..." << '\n' << '\t' << "Test 1 (searching for a node): ";
	test(SearchTesting1());
	cout << '\t' << "Test 2 (searching for a node that doesn't exist): ";
	test(SearchTesting2());
	cout << '\n' << '\t' << "Testing search for the maximum function..." << '\n' << '\t' << "Test 1 (searching for the maximum): ";
	test(MaxFinderTesting1());
	cout << '\t' << "Test 2 (searching for the maximum in an empty tree): ";
	test(MaxFinderTesting2());
	cout << '\n' << '\t' << "Testing search for the minimum function..." << '\n' << '\t' << "Test 1 (searching for the minimum): ";
	test(MinFinderTesting1());
	cout << '\t' << "Test 2 (searching for the minimum in an empty tree): ";
	test(MinFinderTesting2());
	cout << '\n' << '\t' << "Testing search the closest lesser function..." << '\n' << '\t' << "Test 1 (searching for the closest lesser): ";
	test(ClosestLesserTesting1());
	cout << '\t' << "Test 2 (searching for the closest lesser in an empty tree): ";
	test(ClosestLesserTesting2());
	cout << '\t' << "Test 3 (the input number is lesser than minimum): ";
	test(ClosestLesserTesting3());
	cout << '\n' << '\t' << "Testing search the closest greater function..." << '\n' << '\t' << "Test 1 (searching for the closest greater): ";
	test(ClosestGreaterTesting1());
	cout << '\t' << "Test 2 (searching for the closest greater in an empty tree): ";
	test(ClosestGreaterTesting2());
	cout << '\t' << "Test 3 (the input number is bigger than maximum): ";
	test(ClosestGreaterTesting3());
	cout << '\n' << "The tests finished." << endl;
	exit(0);
}