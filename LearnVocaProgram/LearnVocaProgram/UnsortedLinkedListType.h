#pragma once
#include<iostream>

using namespace std;

template <typename T>
struct SinglyNodeType
{
	T data;
	SinglyNodeType<T>* next = nullptr;
};

template <typename T>
class UnsortedLinkedList {
public:
	UnsortedLinkedList();									//생성자(m_Length, m_List, m_curPos를 초기화한다)

	UnsortedLinkedList(const UnsortedLinkedList<T>& u_l);	//복사생성자

	~UnsortedLinkedList();									//소멸자(객체내 동적할당 요소들을 전부 할당 해제)

	int Insert(T& data);									//리스트 내에 요소 추가함수(성공시 1, 실패시 0 반환)

	int Delete(T& data);									//리스트 내에 요소 제거함수(성공시 1, 실패시 0 반환)

	void Replace(const T& data);

	void MakeEmpty();				//리스트 내의 모든 요소 제거함수(객체내 동적할당 요소들을 전부 할당 해제)

	int GetLength() const;				//리스트 내의 요소 개수 반환함수

	bool IsFull() const;					//리스트가 꽉찼는지 검사하는 함수

	bool IsEmpty() const;					//리스트가 비었는지 검사하는 함수

	int Get(T data);				//입력받은 요소와 같은 값을 갖는 요소가 리스트 내에 있는지 검사한다
									//(있으면 1, 없으면 0반환)

	void GetNext(T& data);			//리스트 내의 요소를 가리키는 m_curPos를 다음 요소를 가르키도록 움직인다.

	void ResetList();				//리스트 내의 요소를 가리키는 m_curPos를 제일 처음 설정으로 되돌린다.

	UnsortedLinkedList<T>& operator= (const UnsortedLinkedList<T> & u_l);

	// 반복자가 가리키는 데이터의 포인터를 반환한다.
	T* GetCurPtr() {
		return &(m_curPos->data);
	}
private:
	int m_Length;					//리스트 내의 요소들의 갯수
	SinglyNodeType<T>* m_List;			//리스트의 시작점
	SinglyNodeType<T>* m_curPos;			//리스트 내의 요소들을 가리킬 수 있는 포인터
};

template <typename T>
UnsortedLinkedList<T>::UnsortedLinkedList() {
	m_Length = 0;
	m_List = nullptr;
	m_curPos = nullptr;
}

template <typename T>
UnsortedLinkedList<T>::UnsortedLinkedList(const UnsortedLinkedList<T>& u_l) {
	MakeEmpty();
	m_Length = u_l.m_Length;
	m_curPos = u_l.m_List;
	SinglyNodeType<T>* temp_cur = nullptr;
	int cnt = 0;
	while (m_curPos != nullptr) {
		SinglyNodeType<T>* temp = new SinglyNodeType<T>;
		temp->data = m_curPos->data;
		if (cnt == 0) {
			m_List = temp;
			temp_cur = temp;
			cnt++;
		}
		else {
			temp_cur->next = temp;
			temp_cur = temp_cur->next;
		}
		m_curPos = m_curPos->next;
	}
	m_curPos = nullptr;
}

template <typename T>
UnsortedLinkedList<T>::~UnsortedLinkedList() {
	MakeEmpty();
}

template <typename T>
int UnsortedLinkedList<T>::Insert(T& data) {
	if (IsFull()) {
		return 0;
	}
	else {
		SinglyNodeType<T>* node = new SinglyNodeType<T>;
		SinglyNodeType<T>* preLoc = m_List;
		node->data = data;
		if (IsEmpty()) {
			m_List = node;
			m_Length++;
			m_curPos = m_List;
		}
		else {
			m_curPos = m_List;
			while (m_curPos != nullptr) {
				preLoc = m_curPos;
				m_curPos = m_curPos->next;
			}
			m_curPos = node;
			preLoc->next = m_curPos;
			m_Length++;
		}
		return 1;
	}
}

template <typename T>
int UnsortedLinkedList<T>::Delete(T& data) {
	if (IsEmpty()) {
		return 0;
	}
	else {
		m_curPos = m_List;
		SinglyNodeType<T>* preLoc = nullptr;
		while (m_curPos != nullptr) {
			if (m_curPos->data == data) {
				SinglyNodeType<T>* tempPtr = m_curPos;
				m_curPos = m_curPos->next;
				delete tempPtr;
				m_Length--;
				if (preLoc == nullptr) {
					m_List = m_curPos;
				}
				else {
					preLoc->next = m_curPos;
				}
				return 1;
			}
			else {
				preLoc = m_curPos;
				m_curPos = m_curPos->next;
			}
		}
	}
	return 0;
}

//LinkedList에서 특정 노드를 갱신한다.
template <typename T>
void UnsortedLinkedList<T>::Replace(const T& data) {
	m_curPos = m_List;
	while (m_curPos != nullptr) {
		if (m_curPos->data == data) {
			m_curPos->data = data;
			return;
		}
		m_curPos = m_curPos->next;
	}
}

template <typename T>
void UnsortedLinkedList<T>::MakeEmpty() {
	while (m_List != nullptr) {
		SinglyNodeType<T>* tempPtr = m_List;
		m_List = m_List->next;
		delete tempPtr;
	}
	m_Length = 0;
}

template <typename T>
int UnsortedLinkedList<T>::GetLength() const {
	return m_Length;
}

//메모리상에 노드가 더 들어갈 수 있는지 검사한다.
template <typename T>
bool UnsortedLinkedList<T>::IsFull() const {
	SinglyNodeType<T>* tempPtr;
	try
	{
		tempPtr = new SinglyNodeType<T>;
		delete tempPtr;
		return false;
	}
	catch (bad_alloc exception)
	{
		return true;
	}
}

template <typename T>
bool UnsortedLinkedList<T>::IsEmpty() const {
	return (m_Length == 0);
}

template <typename T>
int UnsortedLinkedList<T>::Get(T data) {
	m_curPos = m_List;
	while (m_curPos != nullptr) {
		if (data == m_curPos->data) {
			return 1;
		}
		m_curPos = m_curPos->next;
	}
	return 0;
}

template <typename T>
void UnsortedLinkedList<T>::GetNext(T& data) {
	if (m_curPos == nullptr) {
		m_curPos = m_List;
		if (m_curPos != nullptr)
			data = m_curPos->data;
	}
	else {
		m_curPos = m_curPos->next;
		if (m_curPos != nullptr)
			data = m_curPos->data;
	}
}

template <typename T>
void UnsortedLinkedList<T>::ResetList() {
	m_curPos = nullptr;
}

template <typename T>
UnsortedLinkedList<T>& UnsortedLinkedList<T>::operator= (const UnsortedLinkedList<T> & u_l){
	MakeEmpty();
	m_Length = u_l.m_Length;
	m_curPos = u_l.m_List;
	SinglyNodeType<T>* temp_cur = nullptr;
	int cnt = 0;
	while (m_curPos != nullptr) {
		SinglyNodeType<T>* temp = new SinglyNodeType<T>;
		temp->data = m_curPos->data;
		if (cnt == 0) {
			m_List = temp;
			temp_cur = temp;
			cnt++;
		}
		else {
			temp_cur->next = temp;
			temp_cur = temp_cur->next;
		}
		m_curPos = m_curPos->next;
	}
	m_curPos = nullptr;
	return *this;
}