#include "pch.h"
#include "CannonMatrixMultiplicationAlgorithm.h"
#include "OrdinaryMatrixMultiplicationAlgorithm.h"
#include "FoxMatrixMultiplicationAlgorithm.h"
#include "JacobiIterationSerialAlgorithm.h"
#include "JacobiIterationParallelAlgorithm.h"
#include "GaussSedelIterationSerialAlgorithm.h"
#include "GaussSedelIterationParallelAlgorithm.h"
#include "ProducerAndConsumer.h"
#include <math.h>
#include<iostream>
#include <ctime>
using namespace std;


long ** createMatrix(int length) {
	long **matrix1 = new long *[length];
	for (int i = 0; i < length; ++i)
	{
		matrix1[i] = new long[length];
	}

	for (long i = 0; i < length; i++) {
		for (long j = 0; j < length; j++) {
			matrix1[i][j] = j+1;
		}
	}
	return matrix1;
}

void printMatrix(long ** matrix,int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j]<<" ";
		}
		cout << endl;
	}
}

void printMatrix(double ** matrix, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	//int length = 16;
	//CannonMatrixMultiplicationAlgorithm c = CannonMatrixMultiplicationAlgorithm(length, createMatrix(length), createMatrix(length));
	 long beg_time = clock();
	//c.cannonCompute();
	 long end_time = clock();
	//cout << "cannon算法用时:" << (end_time - beg_time) << "ms" << endl;
	//c.printResult();
	//OrdinaryMatrixMultiplicationAlgorithm o = OrdinaryMatrixMultiplicationAlgorithm(length, createMatrix(length), createMatrix(length));
 //   beg_time = clock();
	////long** res = o.computeByArray();
	//end_time = clock();
	////cout << "普通矩阵乘法算法用时:" << (end_time - beg_time) << "ms" << endl;
	////printMatrix(res, length);

	////Fox乘法测试
	//FoxMatrixMultiplicationAlgorithm fox = FoxMatrixMultiplicationAlgorithm(length, createMatrix(length), createMatrix(length));
	//beg_time = clock();
	//fox.foxCompute();
	//end_time = clock();
	//cout << "Fox算法用时:" << (end_time - beg_time) << "ms" << endl;
	//fox.printResult();
	//freopen("G:\\Jacobi.txt", "r", stdin);
	//double  **a = new double*[3];
	//double  b[3] = { -12,20,3 };
	//double  x[3] = { 0,0,0 };
	////= { 5,2,1,-1,4,2,2,-3,10 }
	//for (int i = 0; i < 3; i++) {
	//	a[i] = new double[3];
	//}
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		cin >> a[i][j];
	//	}
	//}
	//JacobiIterationSerialAlgorithm j = JacobiIterationSerialAlgorithm(3,a,b,x);
	//beg_time = clock();
	//j.jacobiIterationCompute();
	//end_time = clock();
	//cout << "串行雅克比迭代的用时为:" << (end_time - beg_time) << " ms" << endl;
	//j.printResult();
	//

	//JacobiIterationParallelAlgorithm j1 = JacobiIterationParallelAlgorithm(3, a, b, x);
	//beg_time = clock();
	//j1.jacobiIterationCompute();
	//end_time = clock();
	//cout << "并行雅克比迭代的用时为:" << (end_time - beg_time) << " ms" << endl;
	//j1.printResult();

	//GaussSedelIterationSerialAlgorithm g = GaussSedelIterationSerialAlgorithm(3, a, b, x);
	//beg_time = clock();
	//g.gaussSedelIteration();
	//end_time = clock();
	//cout << "串行高斯赛尔德比迭代的用时为:" << (end_time - beg_time) << " ms" << endl;
	//g.printResult();

	//GaussSedelIterationParallelAlgorithm g1 = GaussSedelIterationParallelAlgorithm(3, a, b, x);
	//beg_time = clock();
	//g1.gaussSedelIteration();
	//end_time = clock();
	//cout << "并行高斯赛尔德比迭代的用时为:" << (end_time - beg_time) << " ms" << endl;
	//g1.printResult();
	ProducerAndConsumer producerAndConsumer;
	producerAndConsumer.showProducersAndConsumers();
	while (true) {

	}
	getchar();
}

 
