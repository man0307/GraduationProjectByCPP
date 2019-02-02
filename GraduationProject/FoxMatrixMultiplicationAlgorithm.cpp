#include "pch.h"
#include "FoxMatrixMultiplicationAlgorithm.h"
#include <math.h>
#include <windows.h>
#include<iostream>
#include<process.h>
using namespace std;

struct FoxContext
{
public:
	int i;
	int j;
	int row;
	int column;
	int resultRow;
	int resultColumn;
	int subMatrixLength;
	FoxMatrixMultiplicationAlgorithm* f;
	FoxContext(FoxMatrixMultiplicationAlgorithm* f, int i, int j, int row, int column,int resultRow, int resultColumn, int subMatrixLength) {
		this->f = f;
		this->i = i;
		this->j = j;
		this->row = row;
		this->column = column;
		this->resultRow = resultRow;
		this->resultColumn = resultColumn;
		this->subMatrixLength = subMatrixLength;
	}

};

void foxComputingUnit(void * context) {
	FoxContext* foxContext = (FoxContext*)(context);
	int rowBeg = foxContext->i * foxContext->subMatrixLength;
	int columnBeg = foxContext->j * foxContext->subMatrixLength;
	int rowData = foxContext->row * foxContext->subMatrixLength;
	int columnData = foxContext->column * foxContext->subMatrixLength;
	int resRow = foxContext->resultRow * foxContext->subMatrixLength;
	int resColumn = foxContext->resultColumn * foxContext->subMatrixLength;
	for (int h = 0; h < foxContext->subMatrixLength; h++) {
		for (int m = 0; m < foxContext->subMatrixLength; m++) {
			for (int k = 0; k < foxContext->subMatrixLength; k++) {
			   foxContext->f->result[resRow + h][resColumn + m] += 
				   foxContext->f->matrix1[rowBeg + h][columnBeg + k] * foxContext->f->matrix2[rowData + k][columnData + m];
			}
		}
	}
}
 
FoxMatrixMultiplicationAlgorithm::FoxMatrixMultiplicationAlgorithm(int N, long ** matrix1, long ** matrix2)
{
	this->N = N;
	this->matrix1 = matrix1;
	this->matrix2 = matrix2;
	this->result = new long*[N];
	for (int i = 0; i < N; i++) {
		result[i] = new long[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			this->result[i][j] = 0;
		}
	}
}

FoxMatrixMultiplicationAlgorithm::~FoxMatrixMultiplicationAlgorithm()
{

}


void FoxMatrixMultiplicationAlgorithm::setThreadNumber(int threadNumber)
{
	this->AVAILABLE_PROCESSORS = threadNumber;
}

void FoxMatrixMultiplicationAlgorithm::printResult()
{
	int mastrixBlockLength = this->N;
	cout << "结果矩阵为:" << this->N<< endl;
	for (int i = 0; i < mastrixBlockLength; i++) {
		for (int j = 0; j < mastrixBlockLength; j++) {
			cout << this->result[i][j] << "  ";
		}
		cout << endl;
	}
}

void FoxMatrixMultiplicationAlgorithm::foxCompute()
{
	int matrixLength = N;
    int subMatrixLength = getSubMatrixLength();
	//Fox算法无需数据对准 直接进行√p 次的算法循环即可
	int blockNum = matrixLength / subMatrixLength;
	for (int m = 0; m < blockNum; m++) {
		HANDLE* works = (HANDLE*)malloc(blockNum*blockNum * sizeof(HANDLE));
		int index = 0;
		//选取对角块
		for (int i = 0; i < blockNum; i++) {
			int colNum = (i + m) % (blockNum);
			for (int h = 0; h < blockNum; h++) {
				FoxContext * f = new FoxContext(this, i, colNum, (i + m) % (blockNum), h, i, h, subMatrixLength);
				works[index++] = (HANDLE)_beginthread(&foxComputingUnit, 0, f);
			}
		}
		WaitForMultipleObjects(blockNum*blockNum, works, true, INFINITE);
	}
}

int FoxMatrixMultiplicationAlgorithm::getSubMatrixLength()
{
	int mod = (int)sqrt(AVAILABLE_PROCESSORS);
	while (mod > 0 && N % mod != 0) {
		mod--;
	}
	return N / mod;
}
