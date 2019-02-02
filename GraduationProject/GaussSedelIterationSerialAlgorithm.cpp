#include "pch.h"
#include "GaussSedelIterationSerialAlgorithm.h"
#include <math.h>
#include <windows.h>
#include<iostream>
#include<process.h>
using namespace std;

GaussSedelIterationSerialAlgorithm::GaussSedelIterationSerialAlgorithm(int N, double** A, double* B, double* X)
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


GaussSedelIterationSerialAlgorithm::~GaussSedelIterationSerialAlgorithm()
{

}

double * GaussSedelIterationSerialAlgorithm::gaussSedelIteration()
{
	int N = this->N;
	int iterationTimes = 0;
	while (iterationTimes < this->getMaxIterationTimes()) {
		for (int i = 0; i < N; i++) {
			double midRes = 0.0;
			for (int j = 0; j < i; j++) {
				midRes += this->A[i][j] * this->result[j];
			}
			for (int j = i + 1; j < N; j++) {
				midRes += this->A[i][j] * this->X[j];
			}
			this->result[i] = (this->B[i] - midRes) / this->A[i][i];
		}
		if (meetTheAccuracyRequirements(X, this->result, getErrorLimit(),N)) {
			break;
		}
		for (int i = 0; i < N; i++) {
			this->X[i] = this->result[i];
		}
	}
	return this->result;
}

double GaussSedelIterationSerialAlgorithm::getErrorLimit() {
	return errorLimit;
}

void GaussSedelIterationSerialAlgorithm::setErrorLimit(double errorLimit) {
	this->errorLimit = errorLimit;
}

int GaussSedelIterationSerialAlgorithm::getMaxIterationTimes() {
	return maxIterationTimes;
}

void GaussSedelIterationSerialAlgorithm::setMaxIterationTimes(int maxIterationTimes) {
	this->maxIterationTimes = maxIterationTimes;
}

void GaussSedelIterationSerialAlgorithm::printResult()
{
	cout << "串行高斯赛尔德迭代的结果为:";
	for (int i = 0; i < N; i++) {
		cout << this->result[i] << " ";
	}
	cout << endl;
}

bool GaussSedelIterationSerialAlgorithm::meetTheAccuracyRequirements(double * x, double * result, double errorLimit, int length)
{
	for (int i = 0; i < length; i++) {
		if (abs(x[i] - result[i]) > errorLimit) {
			return false;
		}
	}
	return true;
}
