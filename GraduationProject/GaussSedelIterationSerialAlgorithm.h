#pragma once
class GaussSedelIterationSerialAlgorithm
{
public:
	GaussSedelIterationSerialAlgorithm(int N,double** A, double* B, double* X);
	~GaussSedelIterationSerialAlgorithm();

	//���еĸ�˹-�������㷨
	double* gaussSedelIteration();

	double getErrorLimit();

	void setErrorLimit(double errorLimit);

	int getMaxIterationTimes();

	void setMaxIterationTimes(int maxIterationTimes);


	//��ӡ���
	void printResult();

private:

	//�����
    double errorLimit = 0.0001;

	//����������
	int maxIterationTimes = 10000;

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

	bool meetTheAccuracyRequirements(double* x, double* result, double errorLimit, int length);
};

