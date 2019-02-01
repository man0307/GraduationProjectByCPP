#include "pch.h"
#include "JacobiIterationParallelAlgorithm.h"
#include <math.h>
#include <windows.h>
#include<iostream>
#include<process.h>
using namespace std;

struct JacobiIterationContext{
public:
	 double** A;
	 double* B;
	 double* X;
	 double* result;
	 int index;
	 int N;
	 JacobiIterationContext(double** A, double* B, double* X, double* result, int index,int N) {
		 this->A = A;
		 this->B = B;
		 this->X = X;
		 this->result = result;
		 this->index = index;
		 this->N = N;
	 }
};

/**
 *雅克比迭代的并行计算单元
**/
void JacobiComputingUnit(void * context) {
	JacobiIterationContext* jContext = (JacobiIterationContext*)(context);
	int N = jContext->N;
	double mid_result = 0.0;
	for (int j = 0; j < N; j++) {
		mid_result += jContext->A[jContext->index][j] * jContext->X[j];
	}
	mid_result -= jContext->X[jContext->index] * jContext->A[jContext->index][jContext->index];
	jContext->result[jContext->index] = (jContext->B[jContext->index] - mid_result) / jContext->A[jContext->index][jContext->index];
}

JacobiIterationParallelAlgorithm::JacobiIterationParallelAlgorithm(int N, double ** A, double * B, double * X)
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

JacobiIterationParallelAlgorithm::~JacobiIterationParallelAlgorithm()
{
}

double* JacobiIterationParallelAlgorithm::jacobiIterationCompute()
{
	int N = this->N;
	int times = 0;
	while (times<this->getIterationTimes()) {
		HANDLE* works = (HANDLE*)malloc(N * sizeof(HANDLE));
		int index = 0; 
		for (int i = 0; i < N; i++) {
			JacobiIterationContext* jContext = new JacobiIterationContext(this->A,this->B,this->X,this->result,i,N);
			works[index++] = (HANDLE)_beginthread(&JacobiComputingUnit, 0, jContext);
		}
		WaitForMultipleObjects(N, works, true, INFINITE);
		if (meetTheAccuracyRequirements(X, result, getPrecision(),N)) {
			break;
		}
		for (int i = 0; i < N; i++) {
			this->X[i] = this->result[i];
		}
		times++;
	}
	return result;
}

int JacobiIterationParallelAlgorithm::getIterationTimes()
{
	return this->iterationTimes;
}

void JacobiIterationParallelAlgorithm::setIterationTimes(int iterationTimes)
{
	this->iterationTimes = iterationTimes;
}

double JacobiIterationParallelAlgorithm::getPrecision()
{
	return this->precision;
}

void JacobiIterationParallelAlgorithm::setPrecision(double precision)
{
	this->precision = precision;
}

void JacobiIterationParallelAlgorithm::printResult()
{
	cout << "并行雅克比迭代的结果为:";
	for (int i = 0; i < N; i++) {
		cout << this->result[i] << " ";
	}
	cout << endl;
}

void JacobiIterationParallelAlgorithm::setThreadNumber(int threadNumber)
{
	this->threadNumber = threadNumber;
}

int JacobiIterationParallelAlgorithm::getThreadNumber()
{
	return this->threadNumber;
}

bool JacobiIterationParallelAlgorithm::meetTheAccuracyRequirements(double * x, double * result, double errorLimit, int length)
{
	for (int i = 0; i < length; i++) {
		if (abs(x[i] - result[i]) > errorLimit) {
			return false;
		}
	}
	return true;
}
