#include<iostream>
#include<fstream>
#include<vector>
#include"support.h"
using namespace std;

int main() {
	int numResources = 5;
	int numProcesses = 3;
	vector<int> available;

	// allocate
	int** alloc = new int* [numResources];
	for (int i = 0; i < numResources; i++) {
		alloc[i] = new int[numProcesses];
	}
	int** max = new int* [numResources];
	for (int i = 0; i < numResources; i++) {
		max[i] = new int[numProcesses];
	}
	int** need = new int* [numResources];
	for (int i = 0; i < numResources; i++) {
		need[i] = new int[numProcesses];
	}

	readMatrix("alloc.txt", alloc, numResources, numProcesses);
	readMatrix("max.txt", max, numResources, numProcesses);
	readVector("available.txt", available, numProcesses);

	calculateNeed(need, alloc, max, numResources, numProcesses);

	cout << "Alloc: \n";
	print(alloc, numResources, numProcesses);
	cout << endl;
	cout << "Max: \n";
	print(max, numResources, numProcesses);
	cout << endl;
	cout << "Need: \n";
	print(need, numResources, numProcesses);
	cout << endl;
	cout << "Available: \n";
	for (int i = 0; i < available.size(); i++)
		cout << available[i] << " ";

	// dispose
	for (int i = 0; i < numResources; i++) {
		delete[] alloc[i];
		delete[] max[i];
		delete[] need[i];
	}
	delete[] alloc;
	delete[] max;
	delete[] need;
}