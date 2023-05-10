#pragma once
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void readMatrix(string fn, int** matrix, int m, int n);
void readVector(string fn, vector<int>& vec, int n);
void calculateNeed(int** need, int** alloc, int** max, int m, int n);
void tableView(int** alloc, int** max, int** need, vector<int> available, int m, int n);
bool safetyAlgo(int** alloc, int** need, vector<int> available);

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
		 << "\t" << left << "Max"
		 << "\t" << left << "Need" << endl;
	
	cout << setfill('-') << setw(45) << "" << endl;

	for (int i = 0; i < m; i++) {
		// print alloc
		for (int j = 0; j < n; j++) {
			cout << alloc[i][j] << " ";
		}
		cout << "\t";
		// print max
		for (int j = 0; j < n; j++) {
			cout << max[i][j] << " ";
		}
		// print need
		cout << "\t";
		for (int j = 0; j < n; j++) {
			cout << need[i][j] << " ";
		}
		cout << "\n";
	}
}

bool safetyAlgo(int** alloc, int** need, vector<int> available, vector<bool> finished, int P, int R) {
	vector<int> work;
	vector<int> safeSeq;
	for (int i = 0; i < available.size(); i++)
		work.push_back(available[i]);

	for (int i = 0; i < P; i++)
		safeSeq.push_back(0);

	int index = 0;
	while (index < P) {
		bool found = false;
		for (int i = 0; i < P; i++) {
			if (finished[i] == 0) {
				int j;
				for (j = 0; j < R; j++) {
					if (need[i][j] > work[j])
						break;
				}

				if (j == R) {
					for (int k = 0; k < R; k++) {
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
			return false;
		}
	}

	cout << "System is in safe state.\nSafe sequence is: ";
	for (int i = 0; i < P; i++)
		cout << "P" << safeSeq[i] << " ";

	return true;
}