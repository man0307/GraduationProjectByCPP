#pragma once
class CannonMatrixMultiplicationAlgorithm
{
public:
	CannonMatrixMultiplicationAlgorithm(int N);
	~CannonMatrixMultiplicationAlgorithm();
	
	long** cannonComputeBySerial(long** matrix1, long** matrix2);
	
	long** cannonComputeByParallel(long** matrix1, long** matrix2);

	void printMatrix(long** matrix);

	void printResult(long** matrix);

private:
	static int AVAILABLE_PROCESSORS;
	int N;
	long** matrix1;
	long** matrix2;
	long** result;

	void loopLeftShiftByRow(long** matrix, int subMatrixLength, int rowNum, int step);

	void loopUpShiftByColumn(long** matrix, int subMatrixLength, int columnNum, int step);

	int getMatrixCount(int matrixLength, int subMatrixLength);

	long** extractSubMatrix(long** matrix, int i, int j, int subMatrixLength);

	long** copyMatrixToPointIndex(long** matrix, long** subMatrix, int i, int j);

	int getSubMatrixLength(int matrixLength);


	void dataAlignment(long** matrix1, long** matrix2, int subMatrixLength);

	void computingUnitTask(int i, int j, int times, int subMatrixLength);
};

