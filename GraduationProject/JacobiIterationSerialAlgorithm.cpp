#include "pch.h"
#include "JacobiIterationSerialAlgorithm.h"
#include <math.h>
#include <windows.h>
#include<iostream>
#include<process.h>
using namespace std;



JacobiIterationSerialAlgorithm::JacobiIterationSerialAlgorithm(int N, double ** A, double * B, double * X)
{
	this->N = N;
	this->A = A;
	this->B = B;
	this->X = X;
	this->result = new double[N];
	for (int i = 0; i < N; i++) {
		result[i] = 0.0;
	}
}

JacobiIterationSerialAlgorithm::~JacobiIterationSerialAlgorithm()
{
}
int JacobiIterationSerialAlgorithm::getIterationTimes() {
	return iterationTimes;
}

void JacobiIterationSerialAlgorithm::setIterationTimes(int iterationTimes) {
	this->iterationTimes = iterationTimes;
}

double JacobiIterationSerialAlgorithm::getPrecision() {
	return precision;
}

void JacobiIterationSerialAlgorithm::setPrecision(double precision) {
	this->precision = precision;
}

double * JacobiIterationSerialAlgorithm::jacobiIterationCompute()
{
	int N = this->N;
	double temp = 0.0;
	while (true) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				temp += this->A[i][j] * this->X[j];
			}
			temp -= this->X[i] * this->A[i][i];
			this->result[i] = (this->B[i] - temp) / this->A[i][i];
			temp = 0.0;
		}
		if (meetTheAccuracyRequirements(X, result, this->getPrecision(),N)) {
			break;
		}
		for (int i = 0; i < N; i++) {
			this->X[i] = this->result[i];
		}
	}
	return result;
}

void JacobiIterationSerialAlgorithm::printResult()
{
	cout << "雅克比迭代的结果为:";
	for (int i = 0; i < N; i++) {
		cout << this->result[i]<<" ";
	}
	cout << endl;
}

bool JacobiIterationSerialAlgorithm::meetTheAccuracyRequirements(double* x, double* result, double errorLimit,int length) {
	for (int i = 0; i < length; i++) {
		if (abs(x[i] - result[i]) > errorLimit) {
			return false;
		}
	}
	return true;
}