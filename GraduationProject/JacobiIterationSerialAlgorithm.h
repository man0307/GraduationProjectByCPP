#pragma once
#define _WIN32_WINNT 0x0600 
#include <windows.h>
class JacobiIterationSerialAlgorithm
{
public:
	JacobiIterationSerialAlgorithm(int N,double** A, double* B, double* X);
	~JacobiIterationSerialAlgorithm();
	
	
	int getIterationTimes();

	void setIterationTimes(int iterationTimes);

	double getPrecision();

	void setPrecision(double precision);
	
	//串行化的雅克比计算
	double* jacobiIterationCompute();

	//打印结果
	void printResult();

private:
	//最大迭代次数
	int iterationTimes = 10000;
	//最小误差要求
	double precision = 0.001;
	//系数矩阵
	double** A;
	//常数项
	double* B;
	//未知数项
	double* X;

	//结果
	double* result;
	//矩阵长度
	int N;

	//误差验证函数
	
	bool meetTheAccuracyRequirements(double* x, double* result, double errorLimit,int length);

};

