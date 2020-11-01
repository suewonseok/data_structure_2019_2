#pragma once
#define MAX_SIZE 50

#include <iostream>
using namespace std;

class FullStack {
public:
	void print() { cout << "Caution" << endl; }
};
class EmptyStack {
public:
	void print() { cout << "Caution" << endl; }
};

template <typename T>
class StackType {
	T m_TestVocaList[MAX_SIZE];
	int m_top;
	int m_length;
public:
	StackType() {
		m_length = 0;
		m_top = -1;
	}
	int push(T& voca) {
		//테스트 단어 목록에 단어를 추가한다.
		if (!isFull()) {
			m_TestVocaList[++m_top] = voca;
			m_length++;
			return 1;
		}
		else
			throw FullStack();
	}
	int pop(T& voca) {
		//테스트 단어 목록에서 단어를 추출한다.
		if (!isEmpty()) {
			voca = m_TestVocaList[m_top--];
			m_length--;
			return 1;
		}
		else
			throw EmptyStack();
	}
	bool isFull() const {
		//테스트 단어 목록이 꽉 찼는지 검사한다.
		if (m_length == MAX_SIZE)
			return 1;
		else
			return 0;
	}
	bool isEmpty() const {
		//테스트 단어 목록이 비었는지 검사한다.
		if (m_length == 0)
			return 1;
		else
			return 0;
	}
	int getLength() const {
		//테스트 단어 목록의 단어 수를 반환한다.
		return m_length;
	}
	void MakeEmpty() {
		//테스트 단어 목록을 비운다.
		m_top = -1;
		m_length = 0;
	}
};
