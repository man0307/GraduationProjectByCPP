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
	
	//���л����ſ˱ȼ���
	double* jacobiIterationCompute();

	//��ӡ���
	void printResult();

private:
	//����������
	int iterationTimes = 10000;
	//��С���Ҫ��
	double precision = 0.001;
	//ϵ������
	double** A;
	//������
	double* B;
	//δ֪����
	double* X;

	//���
	double* result;
	//���󳤶�
	int N;

	//�����֤����
	
	bool meetTheAccuracyRequirements(double* x, double* result, double errorLimit,int length);

};

