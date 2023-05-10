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
	for (int i = 0; i < numProcesses; i++) {
		alloc[i] = new int[numResources];
	}
	int** max = new int* [numProcesses];
	for (int i = 0; i < numProcesses; i++) {
		max[i] = new int[numResources];
	}
	int** need = new int* [numProcesses];
	for (int i = 0; i < numProcesses; i++) {
		need[i] = new int[numResources];
	}

	readMatrix("alloc.txt", alloc, numProcesses, numResources);
	readMatrix("max.txt", max, numProcesses, numResources);
	readVector("available.txt", available, numResources);

	calculateNeed(need, alloc, max, numProcesses, numResources);

	tableView(alloc, max, need, available, numProcesses, numResources);

	// solve
	int safeSeq[numProcesses]{};
	vector<int> work;
	for (int i = 0; i < available.size(); i++) {
		work.push_back(available[i]);
	}

	int index = 0;
	while (index < numProcesses) {
		bool found = false;
		for (int i = 0; i < numProcesses; i++) {
			if (finished[i] == 0) {
				int j;
				for (j = 0; j < numResources; j++) {
					if (need[i][j] > work[j])
						break;
				}

				if (j == numResources) {
					for (int k = 0; k < numResources; k++) {
						work[k] += alloc[i][k];
					}

					safeSeq[index++] = i;

					finished[i] = 1;

					found = true;
				}
			}
		}
		if (found == false) {
			cout << "System is not in safe state";
			return 0;
		}
	}

	cout << "System is in safe state.\nSafe sequence is: ";
	for (int i = 0; i < numProcesses; i++)
		cout << "P" << safeSeq[i] << " ";


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
