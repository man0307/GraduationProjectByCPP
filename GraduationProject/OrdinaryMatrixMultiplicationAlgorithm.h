#pragma once
class OrdinaryMatrixMultiplicationAlgorithm
{
public:
	OrdinaryMatrixMultiplicationAlgorithm(int N,long** matrix1, long** matrix2);
	~OrdinaryMatrixMultiplicationAlgorithm();
	long** computeByArray();
private:
	long** matrix1;
	long** matrix2;
	int N;
};

