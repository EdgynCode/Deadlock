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

	// allocate
	int** alloc = new int* [numProcesses];
	int** max = new int* [numProcesses];
	int** need = new int* [numProcesses];
	int** request = new int* [numProcesses];
	for (int i = 0; i < numProcesses; i++) {
		alloc[i] = new int[numResources];
		max[i] = new int[numResources];
		need[i] = new int[numResources];
		request[i] = new int[numResources];
	}

	readMatrix("alloc.txt", alloc, numProcesses, numResources);
	readMatrix("max.txt", max, numProcesses, numResources);
	readVector("available.txt", available, numResources);
	readMatrix("request.txt", request, numProcesses, numResources);

	calculateNeed(need, alloc, max, numProcesses, numResources);

	tableView(alloc, max, need, available, numProcesses, numResources);

	cout << endl << endl;

	int n;
	cout << "1. Perform safety check.\n";
	cout << "2. Check if resources allocatable.\n";
	cout << "3. Deadlock detection.\n";
	cout << "0. Exit.\n";
	cout << "Choose an option: "; cin >> n;

	switch (n) {
	case 0:
		return 0;
	case 1:
		safetyAlgo(alloc, need, available, finished, numProcesses, numResources);
	case 2:
		int process;
		cout << "Process number: "; cin >> process;
		resourceAllocation(alloc, max, need, finished, available, numProcesses, numResources, process);
	case 3:
		tableView(alloc, max, need, request, available, numProcesses, numResources);
		bool isDeadlocked = safetyAlgo(alloc, request, available, finished, numProcesses, numResources);
		isDeadlocked ? cout << "No deadlock detected." : cout << "Deadlock detected.";
	}


	// dispose
	for (int i = 0; i < numProcesses; i++) {
		delete[] alloc[i];
		delete[] max[i];
		delete[] need[i];
		delete[] request[i];
	}
	delete[] alloc;
	delete[] max;
	delete[] need;
	delete[] request;
	
	return 0;
}