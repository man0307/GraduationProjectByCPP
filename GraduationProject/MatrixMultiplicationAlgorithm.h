#pragma once

class MatrixMultiplicationCannonAlgorithm
{
public:
	MatrixMultiplicationCannonAlgorithm();
	~MatrixMultiplicationCannonAlgorithm();
	bool judgeMatrixLegal(long** matrix1, long** matrix2);
	long** computeByArray(long** matrix1, long** matrix2);
	void printMatrix(int** matrix);
private:

};

