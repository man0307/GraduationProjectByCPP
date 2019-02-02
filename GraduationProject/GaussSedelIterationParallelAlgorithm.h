#pragma once
class GaussSedelIterationParallelAlgorithm
{
public:
	GaussSedelIterationParallelAlgorithm(int N, double ** A, double * B, double * X);
	~GaussSedelIterationParallelAlgorithm();

	//���еĸ�˹-�����µ����㷨
	double* gaussSedelIteration();

	int getIterationTimes();

	void setIterationTimes(int iterationTimes);

	double getPrecision();

	void setPrecision(double precision);

	//��ӡ���
	void printResult();

	void setThreadNumber(int threadNumber);

	int getThreadNumber();

	//ϵ������
	double** A;
	//������
	double* B;
	//δ֪����
	double* X;

	//���
	double* result;

private:
	int threadNumber = 4;

	//����������
	int iterationTimes = 10000;
	//��С���Ҫ��
	double precision = 0.001;


	//���󳤶�
	int N;

	//�����֤����

	bool meetTheAccuracyRequirements(double* x, double* result, double errorLimit, int length);
};

