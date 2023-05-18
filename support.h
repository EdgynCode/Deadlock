#pragma once
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void readMatrix(string fn, int** matrix, int m, int n);
void readVector(string fn, vector<int>& vec, int n);
void calculateNeed(int** need, int** alloc, int** max, int m, int n);
void tableView(int** alloc, int** max, int** need, vector<int> available, int m, int n);
// safety check
bool safetyAlgo(int** alloc, int** need, vector<int> available, vector<bool> finished, int P, int R);

// resource allocation
bool compare(vector<int> request, int R, int** need, int i);
bool compare(vector<int> request, vector<int> available, int R);
bool resourceAllocation(int** alloc, int** max, int** need, vector<bool> finished, vector<int> available, int P, int R, int i);

// deadlock detection
bool deadlockDetection(int** alloc, int** max, int** need, int** request, vector<bool> finished, vector<int> available, int P, int R);
void readMatrix(string fn, int** matrix, int m, int n) {
	ifstream fi;
	try {
		fi.open(fn);
		if (fi.is_open()) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					fi >> matrix[i][j];
				}
			}
			fi.close();
		}
	}
	catch (exception ex) {
		cout << "Error while reading file...";
	}
}

void calculateNeed(int** need, int** alloc, int** max, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
}

void readVector(string fn, vector<int>& vec, int n) {
	ifstream fi;
	int tmp;
	try {
		fi.open(fn);
		if (fi.is_open()) {
			while (fi >> tmp)
				vec.push_back(tmp);
		}
		fi.close();
	}
	catch (exception ex) {
		cout << "Error while reading file...";
	}
}

void tableView(int** alloc, int** max, int** need, vector<int> available, int m, int n) {
	cout << "Available: ";
	for (int i = 0; i < available.size(); i++)
		cout << available[i] << " ";
	cout << endl;

	cout << left << "Alloc"
		<< "\t\t" << left << "Max"
		<< "\t\t" << left << "Need" << endl;

	cout << setfill('-') << setw(45) << "" << endl;

	for (int i = 0; i < m; i++) {
		// print alloc
		for (int j = 0; j < n; j++) {
			cout << alloc[i][j] << " ";
		}
		cout << "\t\t";
		// print max
		for (int j = 0; j < n; j++) {
			cout << max[i][j] << " ";
		}
		// print need
		cout << "\t\t";
		for (int j = 0; j < n; j++) {
			cout << need[i][j] << " ";
		}
		cout << "\n";
	}
}

bool safetyAlgo(int** alloc, int** need, vector<int> available, vector<bool> finished, int P, int R) {
	// init
	vector<int> work;
	vector<int> safeSeq;

	// work = available
	for (int i = 0; i < available.size(); i++)
		work.push_back(available[i]);

	// safe sequence init
	for (int i = 0; i < P; i++)
		safeSeq.push_back(0);

	// While all processes are not finished or system is not in safe state.
	int index = 0;
	while (index < P) {
		// Find a process which is not finish and whose needs can be satisfied with current work[] resources.
		bool found = false;
		for (int i = 0; i < P; i++) {

			// Check if a process is finished
			if (finished[i] == 0) {

				// need[i] > work: break
				int j;
				for (j = 0; j < R; j++) {
					if (need[i][j] > work[j])
						break;
				}

				if (j == R) {

					// free resources
					for (int k = 0; k < R; k++) {
						work[k] += alloc[i][k];
					}

					// add to safe sequence
					safeSeq[index++] = i;

					// mark as finished
					finished[i] = 1;

					found = true;
				}
			}
		}
		if (found == false) {
			cout << "System is not in safe state\n";
			return false;
		}
	}

	cout << "System is in safe state.\nSafe sequence is: ";
	for (int i = 0; i < P; i++)
		cout << "P" << safeSeq[i] << " ";

	return true;
}

bool resourceAllocation(int** alloc, int** max, int** need, vector<bool> finished, vector<int> available, int P, int R, int i) {
	vector<int> request;

	cout << "Request: ";
	for (int i = 0; i < R; i++) {
		int tmp;
		cin >> tmp;
		request.push_back(tmp);
	}

	if (compare(request, R, need, i) == false) {
		cout << "Overflow. Resources cannot be allocated.";
		return false;
	}
	else {
		if (compare(request, available, R)) {
			for (int j = 0; j < R; j++) {
				available[j] -= request[j];
				alloc[i][j] += request[j];
				need[i][j] -= request[j];
			}
			tableView(alloc, max, need, available, P, R);
			bool isSafe = safetyAlgo(alloc, need, available, finished, P, R);
			if (isSafe) {
				cout << "Resources allocated immediately.";
				return true;
			}
			else {
				for (int j = 0; j < R; j++) {
					available[j] += request[j];
					alloc[i][j] -= request[j];
					need[i][j] += request[j];
				}
				cout << "Resources cannot be allocated immediately.";
				return false;
			}
		}
		else {
			cout << "Resources cannot be allocated.";
			return false;
		}
	}
	return true;
}

bool compare(vector<int> request, int R, int** need, int i) {
	for (int j = 0; j < R; j++) {
		if (request[j] > need[i][j]) {
			return false;
		}
	}
	return true;
}

bool compare(vector<int> request, vector<int> available, int R) {
	for (int j = 0; j < R; j++) {
		if (request[j] > available[j]) {
			return false;
		}
	}
	return true;
}

bool deadlockDetection(int** alloc, int** max, int** need, int** request, vector<bool> finished, vector<int> available, int P, int R) {
	// init
	vector<int> work;
	vector<int> deadSeq;

	for (int i = 0; i < P; i++) {
		for (int j = 0; j < R; j++) {
			need[i][j] = request[i][j] - alloc[i][j];
		}
	}

	// work = available
	for (int i = 0; i < available.size(); i++)
		work.push_back(available[i]);

	int flag = 1;
	while (flag) {
		flag = 0;
		for (int i = 0; i < P; i++) {
			int count = 0;
			for (int j = 0; j < R; j++) {
				if ((finished[i] == 0) && (need[i][j] <= work[j])) {
					count++;
					if (count == R) {
						for (int k = 0; k < R; k++) {
							work[k] += alloc[i][j];
							finished[i] = 1;
							flag = 1;
						}
						if (finished[i] == 1) {
							i = P;
						}
					}
				}
			}
		}
	}
	flag = 0;
	int l = 0;
	for (int i = 0; i < P; i++) {
		if (finished[i] == 0) {
			deadSeq.push_back(l);
			l++;
			flag = 1;
		}
	}
	if (flag == 1) {
		cout << "\n\nSystem is in Deadlock and the Deadlock process are\n";
		for (int i = 0; i < P; i++) {
			cout << "P" << deadSeq[i] << "\t";
		}
		return true;
	}
	else {
		cout << "\nNo Deadlock Occurred";
		return false;
	}
}