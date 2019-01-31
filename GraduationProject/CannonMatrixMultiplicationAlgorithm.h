#pragma once
#define _WIN32_WINNT 0x0600 
#include <windows.h>
class CannonMatrixMultiplicationAlgorithm
{
public:
	CannonMatrixMultiplicationAlgorithm(int N, long** matrix1, long** matrix2);
	~CannonMatrixMultiplicationAlgorithm();

	
	//Cannon�㷨
	long** cannonCompute();

	//��ͨ�ľ����ӡ
	void printMatrix(long** matrix);

	//��ӡ���
	void printResult();

	//��ǰ��ʹ�õļ��������
	int AVAILABLE_PROCESSORS = 4;

	//����ĳ���
	int N;

	//��˵ľ���1
	long** matrix1;

	//��˵ľ���2
	long** matrix2;

	//�������
	long** result;

private:

	//����һ���Ĺ��򽫾���ֳɵĿ鰴ĳ��ѭ���ƶ�
	void loopLeftShiftByRow(long** matrix, int subMatrixLength, int rowNum, int step);

	//����һ���Ĺ��򽫾���ֳɵĿ鰴ĳ��ѭ���ƶ�
	void loopUpShiftByColumn(long** matrix, int subMatrixLength, int columnNum, int step);

	//����С���ο�Ĵ�С
	int getMatrixCount(int matrixLength, int subMatrixLength);

	//�����Ӿ����ų�ȡ�Ӿ���
	long** extractSubMatrix(long** matrix, int i, int j, int subMatrixLength);

	//��ָ�����Ӿ��󿽱�����Ӧ��λ�ý�ԭ�Ӿ���Ԫ�ط���
	long** copyMatrixToPointIndex(long** matrix, long** subMatrix, int i, int j);

	//�õ��Ӿ���ĳ���
	int getSubMatrixLength(int matrixLength);

	//���ݶ�׼
	void dataAlignment(long** matrix1, long** matrix2, int subMatrixLength);


};

