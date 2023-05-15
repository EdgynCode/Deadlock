#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include"support.h"
using namespace std;

int main() {
	const int numProcesses = 5;
	const int numResources = 3;
	vector<int> available;
	vector<bool> finished(numProcesses);
	vector<int> request(numResources);

	// allocate
	int** alloc = new int* [numProcesses];
	int** max = new int* [numProcesses];
	int** need = new int* [numProcesses];
	for (int i = 0; i < numProcesses; i++) {
		alloc[i] = new int[numResources];
		max[i] = new int[numResources];
		need[i] = new int[numResources];
	}

	readMatrix("alloc.txt", alloc, numProcesses, numResources);
	readMatrix("max.txt", max, numProcesses, numResources);
	readVector("available.txt", available, numResources);

	calculateNeed(need, alloc, max, numProcesses, numResources);

	tableView(alloc, max, need, available, numProcesses, numResources);

	// solve
	safetyAlgo(alloc, need, available, finished, numProcesses, numResources);

	// resource allocation
	request[0] = 3;
	request[1] = 3;
	request[2] = 0;
	cout << endl;
	resourceAllocation(alloc, max, need, request, finished, available, numProcesses, numResources, 4);

	// dispose
	for (int i = 0; i < numProcesses; i++) {
		delete[] alloc[i];
		delete[] max[i];
		delete[] need[i];
	}
	delete[] alloc;
	delete[] max;
	delete[] need;
	
	return 0;
}
