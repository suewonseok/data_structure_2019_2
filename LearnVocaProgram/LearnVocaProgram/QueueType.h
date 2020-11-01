#pragma once
#include<iostream>
using namespace std;

#define maxQueue 200

/**
*	@brief	Exception class thrown by Enqueue when queue is full.
*/
class FullQueue
{
public:
	/**
	*	@brief	Display a message for full queue on screen.
	*/
	void print()
	{
		cout << "FullQueue exception thrown." << endl;
	}
};


/**
*	@brief	Exception class thrown by Dequeue when queue is empty.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	Display a message for empty queue on screen.
	*/
	void print()
	{
		cout << "EmtpyQueue exception thrown." << endl;
	}
};


template <typename T>					//영어단어 학습 프로그램에서는 T를 VocaType의 간단 버전으로 둘 예정.
class Queue {
public:
	Queue();							//생성자
	int GetLength() const;					//학습단어 목록에서 남아있는 단어 갯수를 반환
	void enQueue(T& voca);				//학습단어 목록에 단어를 추가한다.
	int deQueue(T& voca);				//학습단어 목록에서 단어를 추출한다.
	bool isFull() const;						//학습단어 목록이 꽉 찼는지 검사한다.
	bool isEmpty() const;						//학습단어 목록이 비었는지 검사한다.
	void MakeEmpty();					//학습단어 목록을 비운다.
	void ResizeQueue(int i);
private:
	T* m_LearnVocaList;	//T형 데이터 타입을 요소로 갖는 크기 200의 배열
	int m_iFront;						//Queue의 First 포인터
	int m_iRear;						//Queue의 Rear 포인터
	int m_length;						//Queue 자료구조 내에 삽입된 데이터의 갯수
	int m_MaxSize;						//Queue 자료구조의 사이즈
};

//생성자
template <typename T>
Queue<T>::Queue() {
	m_LearnVocaList = new T[maxQueue + 1];
	m_MaxSize = maxQueue + 1;
	m_iFront = maxQueue;
	m_iRear = maxQueue;
	m_length = 0;
}

//학습단어 목록이 꽉 찼는지 검사한다.
template <typename T>
bool Queue<T>::isFull() const {
	return(m_iFront == ((m_iRear + 1) % m_MaxSize));
}

//학습단어 목록이 비었는지 검사한다.
template <typename T>
bool Queue<T>::isEmpty() const {
	return(m_iFront == m_iRear);
}

//학습단어 목록을 비운다.
template <typename T>
void Queue<T>::MakeEmpty() {
	m_iFront = maxQueue;
	m_iRear = maxQueue;
	m_length = 0;
	return;
}

//학습단어 목록에 단어를 추가한다.
template <typename T>
void Queue<T>::enQueue(T& item) {
	if (isFull()) {
		//throw FullQueue();
		T dummy;
		deQueue(dummy);
		enQueue(item);
	}
	else {
		m_iRear = (m_iRear + 1) % m_MaxSize;
		m_LearnVocaList[m_iRear] = item;
		//cout << "\t\nenQueue 성공\n";
		m_length++;
	}
	return;
}

//학습단어 목록에서 단어를 추출한다.
template <typename T>
int Queue<T>::deQueue(T& item) {
	if (isEmpty()) {
		//throw EmptyQueue();
		return 0;
	}
	else {
		m_iFront = (m_iFront + 1) % m_MaxSize;
		item = m_LearnVocaList[m_iFront];
		m_length--;
		return 1;
	}
}

//학습단어 목록에서 남아있는 단어 갯수를 반환
template <typename T>
int Queue<T>::GetLength() const {
	return m_length;
}

template <typename T>
void Queue<T>::ResizeQueue(int i) {
	delete[] m_LearnVocaList;
	m_LearnVocaList = new T[i + 1];
	m_MaxSize = i + 1;
	m_iFront = i;
	m_iRear = i;
	m_length = 0;
}