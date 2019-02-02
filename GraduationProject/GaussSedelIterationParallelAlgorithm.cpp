#include "pch.h"
#include "GaussSedelIterationParallelAlgorithm.h"
#include <math.h>
#include <windows.h>
#include<iostream>
#include<process.h>
using namespace std;

GaussSedelIterationParallelAlgorithm::GaussSedelIterationParallelAlgorithm(int N, double ** A, double * B, double * X)
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


GaussSedelIterationParallelAlgorithm::~GaussSedelIterationParallelAlgorithm()
{
}


struct GaussSedelIterationContext {
public:
	double** A;
	double* B;
	double* X;
	double* result;
	int index;
	int N;
	GaussSedelIterationContext(double** A, double* B, double* X, double* result, int index, int N) {
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
void GaussSedeComputingUnit(void * context) {
	GaussSedelIterationContext* gContext = (GaussSedelIterationContext*)(context);

	int N = gContext->N;
	double midRes = 0.0;
	for (int j = 0; j < gContext->index; j++) {
		midRes += gContext->A[gContext->index][j] * gContext->result[j];
	}
	for (int j = gContext->index + 1; j < N; j++) {
		midRes += gContext->A[gContext->index][j] * gContext->X[j];
	}
	gContext->result[gContext->index] = (gContext->B[gContext->index] - midRes) / gContext->A[gContext->index][gContext->index];
 
}


double* GaussSedelIterationParallelAlgorithm::gaussSedelIteration()
{
	int N = this->N;
	int times = 0;
	while (times < this->getIterationTimes()) {
		HANDLE* works = (HANDLE*)malloc(N * sizeof(HANDLE));
		int index = 0;
		for (int i = 0; i < N; i++) {
			GaussSedelIterationContext* jContext = new GaussSedelIterationContext(this->A, this->B, this->X, this->result, i, N);
			works[index++] = (HANDLE)_beginthread(&GaussSedeComputingUnit, 0, jContext);
		}
		WaitForMultipleObjects(N, works, true, INFINITE);
		if (meetTheAccuracyRequirements(X, result, getPrecision(), N)) {
			break;
		}
		for (int i = 0; i < N; i++) {
			this->X[i] = this->result[i];
		}
		times++;
	}
	return result;
}

int GaussSedelIterationParallelAlgorithm::getIterationTimes()
{
	return this->iterationTimes;
}

void GaussSedelIterationParallelAlgorithm::setIterationTimes(int iterationTimes)
{
	this->iterationTimes = iterationTimes;
}

double GaussSedelIterationParallelAlgorithm::getPrecision()
{
	return this->precision;
}

void GaussSedelIterationParallelAlgorithm::setPrecision(double precision)
{
	this->precision = precision;
}

void GaussSedelIterationParallelAlgorithm::printResult()
{
	cout << "并行雅克比迭代的结果为:";
	for (int i = 0; i < N; i++) {
		cout << this->result[i] << " ";
	}
	cout << endl;
}

void GaussSedelIterationParallelAlgorithm::setThreadNumber(int threadNumber)
{
	this->threadNumber = threadNumber;
}

int GaussSedelIterationParallelAlgorithm::getThreadNumber()
{
	return this->threadNumber;
}

bool GaussSedelIterationParallelAlgorithm::meetTheAccuracyRequirements(double * x, double * result, double errorLimit, int length)
{
	for (int i = 0; i < length; i++) {
		if (abs(x[i] - result[i]) > errorLimit) {
			return false;
		}
	}
	return true;
}
