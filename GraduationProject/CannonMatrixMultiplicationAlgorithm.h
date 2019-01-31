#pragma once
#define _WIN32_WINNT 0x0600 
#include <windows.h>
class CannonMatrixMultiplicationAlgorithm
{
public:
	CannonMatrixMultiplicationAlgorithm(int N, long** matrix1, long** matrix2);
	~CannonMatrixMultiplicationAlgorithm();

	
	//Cannon算法
	long** cannonCompute();

	//普通的矩阵打印
	void printMatrix(long** matrix);

	//打印结果
	void printResult();

	//当前可使用的计算机核数
	int AVAILABLE_PROCESSORS = 4;

	//方阵的长度
	int N;

	//相乘的矩阵1
	long** matrix1;

	//相乘的矩阵2
	long** matrix2;

	//结果矩阵
	long** result;

private:

	//按照一定的规则将矩阵分成的块按某行循环移动
	void loopLeftShiftByRow(long** matrix, int subMatrixLength, int rowNum, int step);

	//按照一定的规则将矩阵分成的块按某列循环移动
	void loopUpShiftByColumn(long** matrix, int subMatrixLength, int columnNum, int step);

	//计算小矩形块的大小
	int getMatrixCount(int matrixLength, int subMatrixLength);

	//按照子矩阵编号抽取子矩阵
	long** extractSubMatrix(long** matrix, int i, int j, int subMatrixLength);

	//将指定的子矩阵拷贝到相应的位置将原子矩阵元素返回
	long** copyMatrixToPointIndex(long** matrix, long** subMatrix, int i, int j);

	//得到子矩阵的长度
	int getSubMatrixLength(int matrixLength);

	//数据对准
	void dataAlignment(long** matrix1, long** matrix2, int subMatrixLength);


};

