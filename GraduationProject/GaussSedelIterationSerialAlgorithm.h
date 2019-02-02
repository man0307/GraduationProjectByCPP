#pragma once
class GaussSedelIterationSerialAlgorithm
{
public:
	GaussSedelIterationSerialAlgorithm(int N,double** A, double* B, double* X);
	~GaussSedelIterationSerialAlgorithm();

	//串行的高斯-赛尔德算法
	double* gaussSedelIteration();

	double getErrorLimit();

	void setErrorLimit(double errorLimit);

	int getMaxIterationTimes();

	void setMaxIterationTimes(int maxIterationTimes);


	//打印结果
	void printResult();

private:

	//误差率
    double errorLimit = 0.0001;

	//最大迭代次数
	int maxIterationTimes = 10000;

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

	bool meetTheAccuracyRequirements(double* x, double* result, double errorLimit, int length);
};

