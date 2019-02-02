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

	//生产者的数量
	int producer_number = 5;
	//消费者的数量
	int consumer_number = 5;
	//生产者的互斥量
	CRITICAL_SECTION producer_mutex;
	//消费者的互斥量
	CRITICAL_SECTION consumer_mutex;
	//缓冲区的长度
	size_t buffer_length = 10;
	//生产者的条件变量
	CONDITION_VARIABLE PV;
	//消费者的条件变量
	CONDITION_VARIABLE CV;
	//缓冲区
	queue<int> buffer;
	//当前缓冲区的大小
	size_t size_now = 0;
	//当前缓冲区是否已满的标志
	bool flag;
	//生产者生产值的总数量
	int producer_limit = 1000;
};

