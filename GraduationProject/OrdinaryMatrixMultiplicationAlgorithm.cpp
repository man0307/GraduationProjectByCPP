#include "pch.h"
#include<cstring>
#include<iostream>
#include "OrdinaryMatrixMultiplicationAlgorithm.h"
using namespace std;


OrdinaryMatrixMultiplicationAlgorithm::OrdinaryMatrixMultiplicationAlgorithm(int N, long ** matrix1, long ** matrix2)
{
	this->N = N;
	this->matrix1 = matrix1;
	this->matrix2 = matrix2;
}

OrdinaryMatrixMultiplicationAlgorithm::~OrdinaryMatrixMultiplicationAlgorithm()
{
}

long ** OrdinaryMatrixMultiplicationAlgorithm::computeByArray()
{
	int row = this->N;
	int column = this->N;
	int computeLength = this->N;
	long** result = new long*[row];
	for (int i = 0; i < this->N; i++) {
		result[i] = new long[column];
		memset(result[i], 0, column * sizeof(long));
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			for (int k = 0; k < computeLength; k++) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return result;
}
