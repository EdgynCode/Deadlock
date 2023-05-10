#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include"support.h"
using namespace std;

int main() {
	int numResources = 5;
	int numProcesses = 3;
	vector<int> available;
	vector<bool> finished(numResources);

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

	tableView(alloc, max, need, available, finished, numResources, numProcesses);

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
