#include "pch.h"
#include "CannonMatrixMultiplicationAlgorithm.h"
#include <math.h>
#include<iostream>
using namespace std;


long ** createMatrix(int length) {
	long **matrix1 = new long *[length];
	for (int i = 0; i < length; ++i)
	{
		matrix1[i] = new long[length];
	}

	for (long i = 0; i < length; i++) {
		for (long j = 0; j < length; j++) {
			matrix1[i][j] = j+1;
		}
	}
	return matrix1;
}

void printMatrix(long ** matrix,int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j]<<" ";
		}
		cout << endl;
	}
}

int main()
{
	CannonMatrixMultiplicationAlgorithm c = CannonMatrixMultiplicationAlgorithm(36, createMatrix(36), createMatrix(36));
	c.cannonCompute();
	c.printResult();
	getchar();
}

 
