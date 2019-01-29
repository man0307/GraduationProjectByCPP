#include "pch.h"
#include "CannonMatrixMultiplicationAlgorithm.h"


CannonMatrixMultiplicationAlgorithm::CannonMatrixMultiplicationAlgorithm(int N)
{
}


CannonMatrixMultiplicationAlgorithm::~CannonMatrixMultiplicationAlgorithm()
{
}

long ** CannonMatrixMultiplicationAlgorithm::cannonComputeBySerial(long ** matrix1, long ** matrix2)
{
	return nullptr;
}

long ** CannonMatrixMultiplicationAlgorithm::cannonComputeByParallel(long ** matrix1, long ** matrix2)
{
	return nullptr;
}

void CannonMatrixMultiplicationAlgorithm::printMatrix(long ** matrix)
{
}

void CannonMatrixMultiplicationAlgorithm::printResult(long ** matrix)
{
}

void CannonMatrixMultiplicationAlgorithm::loopLeftShiftByRow(long ** matrix, int subMatrixLength, int rowNum, int step)
{
}

void CannonMatrixMultiplicationAlgorithm::loopUpShiftByColumn(long ** matrix, int subMatrixLength, int columnNum, int step)
{
}

int CannonMatrixMultiplicationAlgorithm::getMatrixCount(int matrixLength, int subMatrixLength)
{
	return 0;
}

long ** CannonMatrixMultiplicationAlgorithm::extractSubMatrix(long ** matrix, int i, int j, int subMatrixLength)
{
	return nullptr;
}

long ** CannonMatrixMultiplicationAlgorithm::copyMatrixToPointIndex(long ** matrix, long ** subMatrix, int i, int j)
{
	return nullptr;
}

int CannonMatrixMultiplicationAlgorithm::getSubMatrixLength(int matrixLength)
{
	return 0;
}

void CannonMatrixMultiplicationAlgorithm::dataAlignment(long ** matrix1, long ** matrix2, int subMatrixLength)
{
}

void CannonMatrixMultiplicationAlgorithm::computingUnitTask(int i, int j, int times, int subMatrixLength)
{
}
