#pragma once
class GaussSedelIterationParallelAlgorithm
{
public:
	GaussSedelIterationParallelAlgorithm(int N, double ** A, double * B, double * X);
	~GaussSedelIterationParallelAlgorithm();

	//并行的高斯-赛尔德迭代算法
	double* gaussSedelIteration();

	int getIterationTimes();

	void setIterationTimes(int iterationTimes);

	double getPrecision();

	void setPrecision(double precision);

	//打印结果
	void printResult();

	void setThreadNumber(int threadNumber);

	int getThreadNumber();

	//系数矩阵
	double** A;
	//常数项
	double* B;
	//未知数项
	double* X;

	//结果
	double* result;

private:
	int threadNumber = 4;

	//最大迭代次数
	int iterationTimes = 10000;
	//最小误差要求
	double precision = 0.001;


	//矩阵长度
	int N;

	//误差验证函数

	bool meetTheAccuracyRequirements(double* x, double* result, double errorLimit, int length);
};

