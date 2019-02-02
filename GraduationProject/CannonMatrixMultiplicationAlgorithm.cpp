#include "pch.h"
#include "CannonMatrixMultiplicationAlgorithm.h"
#include <math.h>
#include <windows.h>
#include<iostream>
#include<process.h>

using namespace std;

struct CannonContext
{
public:
	int i;
	int j;
	int times;
	int subMatrixLength;
	CannonMatrixMultiplicationAlgorithm* c;
	CannonContext(int i, int j, int times, int subMatrixLength, CannonMatrixMultiplicationAlgorithm* c) {
		this->i = i;
		this->j = j;
		this->times = times;
		this->subMatrixLength = subMatrixLength;
		this->c = c;
	}
};

CannonMatrixMultiplicationAlgorithm::CannonMatrixMultiplicationAlgorithm(int N, long ** matrix1, long ** matrix2)
{
	this->matrix1 = matrix1;
	this->matrix2 = matrix2;
	this->N = N;
	this->result = new long*[N];
	for (int i = 0; i < N; i++) {
		this->result[i] = new long[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			this->result[i][j] = 0;
		}
	}
}

CannonMatrixMultiplicationAlgorithm::~CannonMatrixMultiplicationAlgorithm()
{
	
}

void CannonMatrixMultiplicationAlgorithm::setThreadNumber(int threadNumber)
{
	this->AVAILABLE_PROCESSORS = threadNumber;
}


void computingUnit(void * context)
{
	CannonContext* c = (CannonContext*)(context);
	int rowBeg = c->i * c->subMatrixLength;
	int columnBeg = c->j * c->subMatrixLength;
	int rowData = (c->i + c->times) % (c->c->N / c->subMatrixLength) * c->subMatrixLength;
	int columnData = (c->j + c->times) % (c->c->N / c->subMatrixLength) * c->subMatrixLength;
	for (int h = 0; h < c->subMatrixLength; h++) {
		for (int m = 0; m < c->subMatrixLength; m++) {
			for (int k = 0; k < c->subMatrixLength; k++) {
				c->c->result[rowBeg + h][columnBeg + m] += c->c->matrix1[rowBeg + h][columnData + k] * c->c->matrix2[rowData + k][columnBeg + m];
			}
		}
	}
}


long ** CannonMatrixMultiplicationAlgorithm::cannonCompute()
{

	int matrixLength = N;
	int subMatrixLength = getSubMatrixLength(matrixLength);
	//数据对准
	dataAlignment(matrix1, matrix2, subMatrixLength);
	//计算点积
	int blockNum = matrixLength / subMatrixLength;
	for (int m = 0; m < blockNum; m++) {
		
		HANDLE* works = (HANDLE*)malloc(blockNum*blockNum * sizeof(HANDLE));
		int index = 0;
		for (int i = 0; i < blockNum; i++) {
			for (int j = 0; j < blockNum; j++) {
				CannonContext* c = new CannonContext(i,j,m, subMatrixLength,this);
			    works[index++] = (HANDLE)_beginthread(&computingUnit,0,c);
			}
		}
		//主线程在此阻塞等待 直至线程池中的任务都完成再继续执行
		WaitForMultipleObjects(blockNum*blockNum, works,true,INFINITE);
		index = 0;
		delete[] works;
	}
	return result;
}



void CannonMatrixMultiplicationAlgorithm::loopLeftShiftByRow(long ** matrix, int subMatrixLength, int rowNum, int step)
{
	int colMatrixCount = getMatrixCount(N, subMatrixLength);
	long** subMatrix = extractSubMatrix(matrix, rowNum, 0, subMatrixLength);
	int nowIndex = 0;
	for (int k = 0; k < colMatrixCount; k++) {
		int nextIndex = (nowIndex + step) % colMatrixCount;
		subMatrix = copyMatrixToPointIndex(matrix, subMatrix, rowNum, nextIndex);
		nowIndex = nextIndex;
	}
}

void CannonMatrixMultiplicationAlgorithm::loopUpShiftByColumn(long ** matrix, int subMatrixLength, int columnNum, int step)
{
	int colMatrixCount = getMatrixCount(N, subMatrixLength);
	long** subMatrix = extractSubMatrix(matrix, 0, columnNum, subMatrixLength);
	int nowIndex = 0;
	for (int k = 0; k < colMatrixCount; k++) {
		int nextIndex = (nowIndex + step) % colMatrixCount;
		subMatrix = copyMatrixToPointIndex(matrix, subMatrix, nextIndex, columnNum);
		nowIndex = nextIndex;
	}
}

int CannonMatrixMultiplicationAlgorithm::getMatrixCount(int matrixLength, int subMatrixLength)
{
	return matrixLength / subMatrixLength;
}

long ** CannonMatrixMultiplicationAlgorithm::extractSubMatrix(long ** matrix, int i, int j, int subMatrixLength)
{
	long** subMatrix ;
	subMatrix = new long * [subMatrixLength];
	for (int i = 0; i < subMatrixLength; i++) {
		subMatrix[i] = new long[subMatrixLength];
	}
	int begRow = i * subMatrixLength;
	int begCol = j * subMatrixLength;
	for (int row = 0; row < subMatrixLength; row++) {
		for (int col = 0; col < subMatrixLength; col++) {
			subMatrix[row][col] = matrix[begRow + row][begCol + col];
		}
	}
	return subMatrix;
}

long ** CannonMatrixMultiplicationAlgorithm::copyMatrixToPointIndex(long ** matrix, long ** subMatrix, int i, int j)
{

	int subMatrixLength = sizeof(subMatrix[0]) / sizeof(long);
	long** oldSubMatrix;
	oldSubMatrix = new long *[subMatrixLength];
	for (int i = 0; i < subMatrixLength; i++) {
		oldSubMatrix[i] = new long[subMatrixLength];
	}
	int begRow = i * subMatrixLength;
	int begCol = j * subMatrixLength;
	for (int row = 0; row < subMatrixLength; row++) {
		for (int col = 0; col < subMatrixLength; col++) {
			oldSubMatrix[row][col] = matrix[begRow + row][begCol + col];
			matrix[begRow + row][begCol + col] = subMatrix[row][col];
		}
	}
	return oldSubMatrix;
}

int CannonMatrixMultiplicationAlgorithm::getSubMatrixLength(int matrixLength)
{
	int mod = (int)sqrt(this->AVAILABLE_PROCESSORS);
	while (mod > 0 && matrixLength % mod != 0) {
		mod--;
	}
	return matrixLength / mod;
}

void CannonMatrixMultiplicationAlgorithm::dataAlignment(long ** matrix1, long ** matrix2, int subMatrixLength)
{
	int mastrixBlockLength = this->N / subMatrixLength;
	for (int i = 1; i < mastrixBlockLength / subMatrixLength; i++) {
		loopLeftShiftByRow(matrix1, subMatrixLength, i, i);
	}
	for (int j = 1; j < mastrixBlockLength / subMatrixLength; j++) {
		loopUpShiftByColumn(matrix2, subMatrixLength, j, j);
	}
}



void CannonMatrixMultiplicationAlgorithm::printMatrix(long ** matrix)
{
	int matrixRow = this->N;
 	int matrixCol = this->N;
	for (int i = 0; i < matrixRow; i++) {
		for (int j = 0; j < matrixCol; j++) {
			cout << this->result[i][j];
		}
		cout << endl;
	}
}

void CannonMatrixMultiplicationAlgorithm::printResult()
{
	int mastrixBlockLength = this->N;
	cout << "结果矩阵为:" << endl;
	for (int i = 0; i < mastrixBlockLength; i++) {
		for (int j = 0; j < mastrixBlockLength; j++) {
			cout << this->result[i][j]<<"  ";
		}
		cout << endl;
	}
}


