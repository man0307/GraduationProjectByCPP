#pragma once
#define _WIN32_WINNT 0x0600 
#include <windows.h>
class FoxMatrixMultiplicationAlgorithm
{
public:
	//构造函数
	FoxMatrixMultiplicationAlgorithm(int N,long** matrix1,long** matrix2);
	~FoxMatrixMultiplicationAlgorithm();
	//设置线程数量
	void setThreadNumber(int threadNumber);
	//打印结果
	void printResult();
	//Fox乘法计算流程
	void foxCompute();
	long** matrix1;
	long** matrix2;
	long** result;

	int getSubMatrixLength();
private:
	int AVAILABLE_PROCESSORS = 4;
	int N;

};

