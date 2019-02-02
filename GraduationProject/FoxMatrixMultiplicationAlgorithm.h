#pragma once
#define _WIN32_WINNT 0x0600 
#include <windows.h>
class FoxMatrixMultiplicationAlgorithm
{
public:
	//���캯��
	FoxMatrixMultiplicationAlgorithm(int N,long** matrix1,long** matrix2);
	~FoxMatrixMultiplicationAlgorithm();
	//�����߳�����
	void setThreadNumber(int threadNumber);
	//��ӡ���
	void printResult();
	//Fox�˷���������
	void foxCompute();
	long** matrix1;
	long** matrix2;
	long** result;

	int getSubMatrixLength();
private:
	int AVAILABLE_PROCESSORS = 4;
	int N;

};

