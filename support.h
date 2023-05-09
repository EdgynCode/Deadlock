#pragma once
#include<fstream>
#include<string>
#include<vector>
using namespace std;

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

void print(int** matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}