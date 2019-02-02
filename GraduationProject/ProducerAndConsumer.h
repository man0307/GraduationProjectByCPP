#pragma once
#include <Windows.h>
#include <map>
#include <queue>
using namespace std;
class ProducerAndConsumer
{
public:
	ProducerAndConsumer();
	
	~ProducerAndConsumer();

	void showProducersAndConsumers();

	//�����ߵ�����
	int producer_number = 5;
	//�����ߵ�����
	int consumer_number = 5;
	//�����ߵĻ�����
	CRITICAL_SECTION producer_mutex;
	//�����ߵĻ�����
	CRITICAL_SECTION consumer_mutex;
	//�������ĳ���
	size_t buffer_length = 10;
	//�����ߵ���������
	CONDITION_VARIABLE PV;
	//�����ߵ���������
	CONDITION_VARIABLE CV;
	//������
	queue<int> buffer;
	//��ǰ�������Ĵ�С
	size_t size_now = 0;
	//��ǰ�������Ƿ������ı�־
	bool flag;
	//����������ֵ��������
	int producer_limit = 1000;
};

