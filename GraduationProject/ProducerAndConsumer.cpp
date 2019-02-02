#include "pch.h"
#include "ProducerAndConsumer.h"
#include <math.h>
#include <windows.h>
#include<iostream>
#include<stdlib.h>
#include<process.h>
using namespace std;

void producer(void * context) {
	ProducerAndConsumer* producerAndConsumer = (ProducerAndConsumer*)(context);
	while (true) {
		if (producerAndConsumer->flag) {
			break;
		}
		//���������ߵĻ�������
		EnterCriticalSection(&producerAndConsumer->producer_mutex);
		while (producerAndConsumer->buffer.size() == producerAndConsumer->buffer_length)
		{
			printf("buffer.size enter : %zd. \n", producerAndConsumer->buffer.size());
			//����������Ѿ����ˣ���ô�޷������� ��Ҫ�ͷ�����������
			WakeConditionVariable(&producerAndConsumer->CV);
			SleepConditionVariableCS(&producerAndConsumer->PV, &producerAndConsumer->producer_mutex,INFINITE);
		}
		DWORD currentThreadId = GetCurrentThreadId();
		int value = rand();
		printf("�߳�%d ������:%d \n", currentThreadId, value);
		producerAndConsumer->buffer.push(value);
		producerAndConsumer->size_now++;
		if (producerAndConsumer->size_now >= producerAndConsumer->producer_limit) {
			LeaveCriticalSection(&producerAndConsumer->producer_mutex);
			producerAndConsumer->flag = true;
			break;
		}
		WakeConditionVariable(&producerAndConsumer->CV);
		LeaveCriticalSection(&producerAndConsumer->producer_mutex);
	}
}

void consumer(void * context) {
	ProducerAndConsumer* producerAndConsumer = (ProducerAndConsumer*)(context);
	while (true) {
		if (producerAndConsumer->flag&&producerAndConsumer->buffer.empty()) {
			break;
		}
		//���������ߵĻ�������
		EnterCriticalSection(&producerAndConsumer->consumer_mutex);
		while (producerAndConsumer->buffer.size() == 0)
		{
			//���������Ϊ�գ���ô�޷����� ���Ի���һ���������߳�Ȼ���ͷ�����������
			WakeConditionVariable(&producerAndConsumer->PV);
			SleepConditionVariableCS(&producerAndConsumer->CV, &producerAndConsumer->consumer_mutex, INFINITE);
		}
		DWORD currentThreadId = GetCurrentThreadId();
		int value = producerAndConsumer->buffer.front();
		producerAndConsumer->buffer.pop();
		printf("�߳�%d ������:%d \n", currentThreadId, value);
		WakeConditionVariable(&producerAndConsumer->PV);
		LeaveCriticalSection(&producerAndConsumer->consumer_mutex);
	}
}


void ProducerAndConsumer::showProducersAndConsumers()
{
	//��ʼ�����������ͻ�����
	InitializeCriticalSection(&this->producer_mutex);
	InitializeConditionVariable(&this->PV);
	InitializeCriticalSection(&this->consumer_mutex);
	InitializeConditionVariable(&this->CV);
	HANDLE* producers = new HANDLE[this->producer_number];
	HANDLE* consumers = new HANDLE[this->consumer_number];
	for (int i = 0; i < this->producer_number; i++) {
		producers[i] = (HANDLE)_beginthread(&producer, 0, this);
	}

	for (int i = 0; i < this->consumer_number; i++) {
		consumers[i] = (HANDLE)_beginthread(&consumer, 0, this);
	}

	WaitForMultipleObjects(this->producer_number, producers, TRUE, INFINITE);
	WaitForMultipleObjects(this->consumer_number, consumers, TRUE, INFINITE);

	for (int i = 0; i < this->producer_number; i++) {
		CloseHandle(producers[i]);
	}

	for (int i = 0; i < this->consumer_number; i++) {
		CloseHandle(consumers[i]);  
	}
	delete[] producers;
	delete[] consumers;

	DeleteCriticalSection(&this->producer_mutex);
	DeleteCriticalSection(&this->consumer_mutex);

}


ProducerAndConsumer::ProducerAndConsumer()
{
}


ProducerAndConsumer::~ProducerAndConsumer()
{
}