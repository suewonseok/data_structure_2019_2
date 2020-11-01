#pragma once
/*
*	@To do list:
					1.=연산자 오버로딩
					2.늘리고 줄이기(특정 기준에서의 재동적할당)
*/

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class SortedArrayList {
public:
	
	/*
	*	기본 생성자
	*/
	SortedArrayList();

	//복사생성자
	SortedArrayList(const SortedArrayList<T>& s_l);

	~SortedArrayList();

	//리스트의 반복자를 갱신(다음 데이터를 가리키도록)
	int GetNext(T& data);

	//리스트의 반복자를 초기화
	int ResetList();

	//리스트에서 입력받은 인자가 존재하는지 검색
	int Get(T& data);

	// 리스트에 데이터를 추가
	int Insert(T& data);

	int Delete(T& data);

	// 반복자가 가리키는 데이터의 포인터를 반환한다.
	T* GetCurPtr() const;

	/**
	*	@brief      인자와 동일한 인덱스에 위치한 데이터를 포인터형으로 반환한다.
	*	@pre	        i가 m_length를 넘으면 안된다.
	*	@post       없음
	*	@return     m_AllVocaList의 i번째 데이터
	*/
	T GetIndexOfData(int i);

	//리스트 길이 정보를 반환한다.
	int GetLength() const;

	//리스트가 비었는지 검사한다.
	bool isEmpty() const;

	//리스트가  꽉찼는지 검사한다.
	bool isFull() const;

	//리스트를 비운다.
	void MakeEmpty();

	/*
	*	@brief	배열리스트의 사이즈를 500만큼 확장한다.
	*	@pre	배열리스트가 꽉차야한다.
	*	@post	배열리스트의 사이즈가 500개만큼 커진다.
	*/
	void ExpandSize();


	/*
	*	@brief	배열리스트의 사이즈를 500만큼 줄인다.
	*	@pre	배열리스트가 비어있거나 m_maxsize가 1000이면 실행되지 않는다.
	*	@post	배열리스트의 사이즈가 500개 줄어든다.
	*/
	void ReduceSize();


	SortedArrayList<T>& operator=(const SortedArrayList<T>& s_l);

private:
	T* m_List;					//리스트
	int m_maxsize;				//리스트의 사이즈
	int m_curPos;				//리스트의 반복자
	int m_length;				//리스트 내에 존재하는 데이터의 갯수
};

/**
*	기본 생성자
*/
template <typename T>
SortedArrayList<T>::SortedArrayList() {
	m_length = 0;
	m_curPos = -1;
	m_maxsize = 1000;
	m_List = new T[m_maxsize];
}

template <typename T>
SortedArrayList<T>::SortedArrayList(const SortedArrayList<T>& s_l) {
	MakeEmpty();
	m_length = s_l.m_length;
	m_maxsize = s_l.m_maxsize;
	if (m_maxsize > 1000) {
		m_List = new T[m_maxsize];
	}
	else {
		m_List = new T[m_maxsize];
	}
	for (int i = 0; i < m_length; i++) {
		m_List[i] = s_l.m_List[i];
	}
	m_curPos = -1;
}

template <typename T>
SortedArrayList<T>::~SortedArrayList() {
	delete[] m_List;
}

//리스트의 반복자를 갱신(다음 데이터를 가리키도록)
template <typename T>
int SortedArrayList<T>::GetNext(T& data) {
	m_curPos++;	// list pointer 증가
	if (m_curPos >= m_length)	// end of list이면 -1을 리턴
		return -1;

	data = m_List[m_curPos];	// 현재 list pointer의 레코드를 복사
	return m_curPos;
}

//리스트의 반복자를 초기화
template <typename T>
int SortedArrayList<T>::ResetList() {
	m_curPos = -1;
	return 1;
}

//리스트에서 입력받은 인자가 존재하는지 검색
template <typename T>
int SortedArrayList<T>::Get(T& data) {
	if (m_length > 0)
	{
		ResetList();
		int head = 0;
		int tail = m_length - 1;

		while (head <= tail)
		{
			m_curPos = (tail + head) / 2;
			if (data == m_List[m_curPos]) {
				data = m_List[m_curPos];
				return 1;
			}
			else if (data > m_List[m_curPos]) {
				head = m_curPos + 1;
			}
			else if (data < m_List[m_curPos]) {
				tail = m_curPos - 1;
			}
		}
		return 0;
	}
	else
		return 0;
}

// 리스트에 데이터를 추가
template <typename T>
int SortedArrayList<T>::Insert(T& data) {
	if (isFull()) {
		return 0;
	}
	else {
		T tempData;
		ResetList();
		while (GetNext(tempData) != -1) {
			if ((tempData > data)) {	//넣으려는 값이 배열 속 데이터보다 작다면 그 상태의 m_curPos에서 고정시킴
				break;
			}
		}
		for (int i = m_length; i > m_curPos; i--) {
			m_List[i] = m_List[i - 1];
		}
		m_List[m_curPos] = data;
		m_length++;
		return 1;
	}
}

template <typename T>
int SortedArrayList<T>::Delete(T& data) {
	if (isEmpty())
	{
		return 0;
	}
	else {
		T tempData;
		ResetList();
		while (GetNext(tempData) != -1) {
			if ((tempData == data)) {	//넣으려는 값이 배열 속 데이터보다 작다면 그 상태의 m_curPos에서 고정시킴
				for (int i = m_curPos + 1; i < m_length; i++) {
					m_List[i - 1] = m_List[i];
				}
				m_length--;
				return 1;
			}
		}
		return 0;
	}
}

// 반복자가 가리키는 데이터의 포인터를 반환한다.
template <typename T>
T* SortedArrayList<T>::GetCurPtr() const {
	return &m_List[m_curPos];
}

/**
*	@brief      인자와 동일한 인덱스에 위치한 데이터를 포인터형으로 반환한다.
*	@pre	    i가 m_length를 넘으면 안된다.
*	@post       없음
*	@return     m_List의 i번째 데이터
*/
template <typename T>
T SortedArrayList<T>::GetIndexOfData(int i) {
	return (m_List[i]);
}

//리스트 길이 정보를 반환한다.
template <typename T>
int SortedArrayList<T>::GetLength() const {
	return m_length;
}

//리스트가 비었는지 검사한다.
template <typename T>
bool SortedArrayList<T>::isEmpty() const {
	return (m_length == 0);
}

//리스트가  꽉찼는지 검사한다.
template <typename T>
bool SortedArrayList<T>::isFull() const {
	return (m_length == m_maxsize);
}

template <typename T>
void SortedArrayList<T>::MakeEmpty() {
	m_length = 0;
	m_curPos = -1;
	if (m_maxsize > 1000) {
		m_maxsize = 1000;
		delete[] m_List;
		m_List = new T[m_maxsize];
	}
}

/*
*	@brief	배열리스트의 사이즈를 500만큼 확장한다.
*	@pre	배열리스트가 꽉차야한다.
*	@post	배열리스트의 사이즈가 500개만큼 커진다.
*/
template <typename T>
void SortedArrayList<T>::ExpandSize() {
	if (isFull()) {
		SortedArrayList<T> temp(*this);
		delete[] m_List;
		m_List = new T[temp.m_maxsize + 500];
		m_maxsize = temp.m_maxsize + 500;
		m_length = temp.m_length;
		m_curPos = -1;
		for (int i = 0; i < m_length; i++) {
			m_List[i] = temp.m_List[i];
		}
		return;
	}
	else {
		return;
	}
}

template <typename T>
void SortedArrayList<T>::ReduceSize() {
	if (isEmpty() || m_maxsize == 1000) {
		return;
	}
	else if(m_maxsize - m_length > 500){
		SortedArrayList<T> temp(*this);
		delete[] m_List;
		m_List = new T[temp.m_maxsize - 500];
		m_maxsize = temp.m_maxsize - 500;
		m_length = temp.m_length;
		m_curPos = -1;
		for (int i = 0; i < m_length; i++) {
			m_List[i] = temp.m_List[i];
		}
		return;
	}
	else {
		return;
	}
}

//대입연산자
template <typename T>
SortedArrayList<T>& SortedArrayList<T>::operator=(const SortedArrayList<T>& s_l) {
	MakeEmpty();
	m_length = s_l.m_length;
	m_maxsize = s_l.m_maxsize;
	if (m_maxsize > 1000) {
		m_List = new T[m_maxsize];
	}
	else {
		m_List = new T[m_maxsize];
	}
	for (int i = 0; i < m_length; i++) {
		m_List[i] = s_l.m_List[i];
	}
	m_curPos = -1;
	return *this;
}