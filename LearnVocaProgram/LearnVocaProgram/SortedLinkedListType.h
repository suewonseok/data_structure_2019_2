#pragma once
#pragma once
#include<iostream>
using namespace std;

template <typename T>
struct NodeType
{
	T data;							//NodeType의 데이터
	NodeType<T>* pre = nullptr;		//이전 Node를 가리키는 포인터
	NodeType<T>* next = nullptr;	//다음 Node를 가리키는 포인터
};

template <typename T>
class SortedLinkedListType {
public:
	/**
	*	@brief	기본 생성자
	*	@post	LinkedList의 모든 멤버변수를 초기화한다.
	*/
	SortedLinkedListType();

	/**
	*	@brief	소멸자
	*	@post	LinkedList의 동적할당된 모든 요소들을 할당 해제한다.
	*/
	~SortedLinkedListType();

	/**
	*	@brief	복사 생성자
	*	@post	기존에 존재하던 SortedLinkedListType의 객체로부터 모든 노드들을 deep copy한다.
	*/
	SortedLinkedListType(const SortedLinkedListType& list);

	/**
	*	@brief	LinkedList에 새로운 노드를 추가한다.
	*	@pre	        data를 입력받는다.
	*	@post	LinkedList에 새로운 노드가 추가된다.
	*   @return     노드 추가에 성공하면 1, 그렇지 않으면 0을 반환한다.
	*/
	int Insert(T& data);

	/**
	*	@brief	LinkedList에서 특정 노드를 삭제한다.
	*	@pre	        Get함수로 중복 data갖는 Node를 검사해야한다.
	*	@post	LinkedList에서 특정 노드가 삭제된다.
	*       @return     노드 삭제에 성공하면 1, 그렇지 않으면 0을 반환한다.
	*/
	int Delete(T& data);

	/**
	*    @brief    LinkedList에서 특정 노드를 갱신한다.
	*    @pre    Get함수로 중복 data갖는 Node를 검사해야한다.
	*    @post    LinkedList에서 특정 노드가 수정된다.
	*/
	void Replace(const T& data);

	/**
	*	@brief	LinkedList의 모든 요소들을 삭제한다.
	*	@pre	Get함수로 지우려는 data를 갖는 Node가 존재하는지 검사해야한다.
	*	@post	LinkedList의 모든 요소들이 삭제된다.
	*/
	void MakeEmpty();

	/**
	*	@brief	LinkedList에서 반복자를 이동시켜 해당 반복자가 가리키는 Node의 data로 갱신한다.
	*	@pre	data를 입력받는다.
	*	@post	LinkedList에서 반복자를 이동되고 해당 반복자가 가리키는 Node의 data가 갱신된다.
	*	@return	반복자가 끝까지 갔다면 nullptr, 아니라면 반복자가 가리키는 Node의 포인터를 반환한다.
	*/
	NodeType<T>* GetNext(T& data);

	//LinkedList의 반복자를 pre방향으로 이동시키고 그때 가리키는 Node의 data를 반환한다.
	NodeType<T>* GetPre(T& data);

	/**
	*	@brief	LinkedList의 반복자를 초기화한다.
	*	@pre	LinkedLIst가 초기화 되어있어야한다.
	*	@post	LinkedList의 반복자가 초기화된다.
	*/
	void ResetList();

	//LinkedList의 반복자를 pre방향으로 순회하도록 초기화한다.
	void ResetListForGetPre();

	/**
	*	@brief	LinkedList 내의 노드 갯수를 반환한다.
	*	@pre	LinkedList가 초기화 되어있어야한다.
	*	@post	LinkedList 내의 노드 갯수가 반환된다.
	*	@return	LinkedList 내의 노드 갯수
	*/
	int GetLength() const;

	/**
	*	@brief	LinkedList 내의 노드가 비었는지 검사한다.
	*	@pre	LinkedList가 초기화 되어있어야한다.
	*	@post	LinkedList 내의 노드가 비었는지 검사하게된다.
	*	@return	비었으면 true, 아니라면 false를 반환
	*/
	bool isEmpty() const;

	/**
	*	@brief	메모리상에 노드가 더 들어갈 수 있는지 검사한다.
	*	@pre	LinkedList가 초기화 되어있어야한다.
	*	@post	메모리상에 노드가 더 들어갈 수 있는지 검사하게된다.
	*	@return	꽉찼으면 true, 아니라면 false를 반환
	*/
	bool isFull() const;

	/**
	*	@brief	LinkedList에 동일한 data를 가진 Node가 존재하는지 검사한다.
	*	@pre	data를 입력받는다.
	*	@post	LinkedList 내에 동일 data를 가진 Node의 존재 여부를 알게 된다.
	*	@return	존재한다면 1, 아니라면 0을 반환
	*/
	int Get(T& data);

	//LinkedList 맨뒤의 data와 찾으려는 data를 비교해서 맞으면 1 otherwise 0 반환.
	int CheckBack(T& data);
	
	//LinkedList 맨뒤의 data보다 넣으려는 data가 큰 경우 data를 맨 뒤에 삽입한다(비어있을 경우에도 넣는다), 성공시 1 otherwise 0반환.
	int InsertTail(T& data);

	//LinkedList 맨뒤의 data가 삭제하려는 data와 같은 값일 경우 삭제한다, 성공시 1 otherwise 0반환.
	int DeleteTail(T& data);

	// 반복자가 가리키는 데이터의 포인터를 반환한다.
	T* GetCurPtr() {
		return &(m_curPtr->data);
	}

	// 대입 연산자 오버로딩
	SortedLinkedListType<T>& operator=(const SortedLinkedListType<T>& list);

private:
	NodeType<T>* m_head;			//LinkedList에서 제일 앞에 위치한 노드를 가리키는 포인터
	NodeType<T>* m_tail;			//LinkedList에서 제일 뒤에 위치한 노드를 가리키는 포인터
	NodeType<T>* m_curPtr;			//LinkedList내에 존재하는 노드의 갯수를 저장하는 int형 변수
	int m_length;
};

//LinkedList의 멤버변수들을 초기화한다.
template <typename T>
SortedLinkedListType<T>::SortedLinkedListType() {
	m_head = new NodeType<T>;
	m_tail = new NodeType<T>;
	m_head->pre = nullptr;
	m_head->next = m_tail;
	m_tail->next = nullptr;
	m_tail->pre = m_head;
	m_curPtr = m_head;
	m_length = 0;
}

//기존에 존재하던 SortedLinkedListType의 객체로부터 모든 노드들을 deep copy한다.
template <typename T>
SortedLinkedListType<T>::SortedLinkedListType(const SortedLinkedListType& list) {
	m_head = new NodeType<T>;
	m_tail = new NodeType<T>;
	m_head->pre = nullptr;
	m_head->next = m_tail;
	m_tail->next = nullptr;
	m_tail->pre = m_head;
	m_curPtr = m_head;
	m_length = list.m_length;
	/*
		list 내의 모든 노드에서 data만을 뽑아와 해당 SortedLinkedListType객체의 리스트를 구성한다.
	*/
	NodeType<T>* list_curPtr = list.m_head;
	while (list_curPtr->next != list.m_tail) {
		list_curPtr = list_curPtr->next;
		NodeType<T>* tempPtr = new NodeType<T>;
		tempPtr->data = list_curPtr->data;
		while (m_curPtr->next != m_tail)
			m_curPtr = m_curPtr->next;
		m_curPtr->next->pre = tempPtr;
		tempPtr->next = m_curPtr->next;
		tempPtr->pre = m_curPtr;
		m_curPtr->next = tempPtr;
	}
}

//LinkedList의 동적할당된 모든 요소들을 할당 해제한다.
template <typename T>
SortedLinkedListType<T>::~SortedLinkedListType() {
	MakeEmpty();
	delete m_head;
	delete m_tail;
}

//LinkedList에 새로운 노드를 추가한다.
template <typename T>
int SortedLinkedListType<T>::Insert(T& data) {
	if (isFull()) {
		return 0;
	}
	else if (InsertTail(data)) {
		return 1;
	}
	else {
		NodeType<T>* tempPtr = new NodeType<T>;
		tempPtr->data = data;

		m_curPtr = m_head;
		while (m_curPtr->next != m_tail) {            //넣으려는 Node가 맨 뒤에 붙는게 아닌 경우
			m_curPtr = m_curPtr->next;
			if (m_curPtr->data > data) {
				m_curPtr->pre->next = tempPtr;
				tempPtr->pre = m_curPtr->pre;
				m_curPtr->pre = tempPtr;
				tempPtr->next = m_curPtr;
				m_length++;
				return 1;
			}
		}
		return 0;
	}
}

//LinkedList에서 특정 노드를 삭제한다.
template <typename T>
int SortedLinkedListType<T>::Delete(T& data) {
	if (isEmpty()) {
		return 0;
	}
	else if (DeleteTail(data)) {
		return 1;
	}
	else {
		m_curPtr = m_head;
		while (m_curPtr->next != m_tail) {
			m_curPtr = m_curPtr->next;
			if (m_curPtr->data == data) {
				m_curPtr->next->pre = m_curPtr->pre;
				m_curPtr->pre->next = m_curPtr->next;
				delete m_curPtr;
				m_length--;
				return 1;
			}
		}
		return 0;
	}
}

//LinkedList에서 특정 노드를 갱신한다.
template <typename T>
void SortedLinkedListType<T>::Replace(const T& data) {
	m_curPtr = m_head;
	while (m_curPtr->next != m_tail) {
		m_curPtr = m_curPtr->next;
		if (m_curPtr->data == data) {
			m_curPtr->data = data;
			return;
		}
	}
}

//LinkedList의 모든 요소들을 삭제한다.
template <typename T>
void SortedLinkedListType<T>::MakeEmpty() {
	while (m_tail->pre != m_head) {
		m_curPtr = m_tail->pre;
		m_curPtr->next->pre = m_curPtr->pre;
		m_curPtr->pre->next = m_curPtr->next;
		delete m_curPtr;
	}
	m_length = 0;
}

//LinkedList에서 반복자를 이동시켜 해당 반복자가 가리키는 Node의 data로 갱신한다.
template <typename T>
NodeType<T>* SortedLinkedListType<T>::GetNext(T& data) {
	if (m_curPtr->next != m_tail) {
		m_curPtr = m_curPtr->next;
		data = m_curPtr->data;
		return m_curPtr;
	}
	else {
		m_curPtr = m_head;
		return nullptr;
	}
}

template <typename T>
NodeType<T>* SortedLinkedListType<T>::GetPre(T& data) {
	if (m_curPtr->pre != m_head) {
		m_curPtr = m_curPtr->pre;
		data = m_curPtr->data;
		return m_curPtr;
	}
	else {
		m_curPtr = m_tail;
		return nullptr;
	}
}



//LinkedList의 반복자를 초기화한다.
template <typename T>
void SortedLinkedListType<T>::ResetList() {
	m_curPtr = m_head;
}

//LinkedList의 반복자를 초기화한다.
template <typename T>
void SortedLinkedListType<T>::ResetListForGetPre() {
	m_curPtr = m_tail;
}

//LinkedList 내의 노드 갯수를 반환한다.
template <typename T>
int SortedLinkedListType<T>::GetLength() const {
	return m_length;
}

//LinkedList 내의 노드가 비었는지 검사한다.
template <typename T>
bool SortedLinkedListType<T>::isEmpty() const {
	return (m_length == 0);
}

//메모리상에 노드가 더 들어갈 수 있는지 검사한다.
template <typename T>
bool SortedLinkedListType<T>::isFull() const {
	NodeType<T>* tempPtr;
	try
	{
		tempPtr = new NodeType<T>;
		delete tempPtr;
		return false;
	}
	catch (bad_alloc exception)
	{
		return true;
	}
}

//LinkedList에 동일한 data를 가진 Node가 존재하는지 검사한다.
template <typename T>
int SortedLinkedListType<T>::Get(T& data) {
	if (m_length == 0) {
		return 0;
	}
	else if (CheckBack(data)){
		return 1;
	}
	else {
		m_curPtr = m_head;
		while (m_curPtr->next != m_tail) {
			m_curPtr = m_curPtr->next;
			if (m_curPtr->data == data) {
				data = m_curPtr->data;
				return 1;
			}
		}
	}
	return 0;
}

template <typename T>
int SortedLinkedListType<T>::CheckBack(T& data) {
	if (m_length == 0) {
		return 0;
	}
	else if(m_tail->pre->data == data) {
		data = m_tail->pre->data;
		return 1;
	}
	else {
		return 0;
	}
}

template <typename T>
int SortedLinkedListType<T>::InsertTail(T& data) {
	if (isFull()) {
		return 0;
	}
	else {
		if (m_length == 0 || m_tail->pre->data < data) {
			NodeType<T>* temp = new NodeType<T>;
			temp->data = data;
			
			temp->next = m_tail;
			temp->pre = m_tail->pre;
			m_tail->pre->next = temp;
			m_tail->pre = temp;

			m_length++;
			return 1;
		}
		else {
			return 0;
		}
	}
}


template <typename T>
int SortedLinkedListType<T>::DeleteTail(T& data) {
	if (m_length == 0) {
		return 0;
	}
	else if (m_tail->pre->data == data) {
		m_curPtr = m_tail->pre;
		m_curPtr->pre->next = m_tail;
		m_tail->pre = m_curPtr->pre;
		m_length--;
		delete m_curPtr;
		m_curPtr = nullptr;
		return 1;
	}
	else {
		return 0;
	}
}

//대입연산자 오버로딩
template <typename T>
SortedLinkedListType<T>& SortedLinkedListType<T>::operator=(const SortedLinkedListType<T>& list) {
	MakeEmpty();
	m_head->pre = nullptr;
	m_head->next = m_tail;
	m_tail->next = nullptr;
	m_tail->pre = m_head;
	m_curPtr = m_head;
	m_length = list.m_length;
	/*
		list 내의 모든 노드에서 data만을 뽑아와 해당 SortedLinkedListType객체의 리스트를 구성한다.
	*/
	NodeType<T>* list_curPtr = list.m_head;
	while (list_curPtr->next != list.m_tail) {
		list_curPtr = list_curPtr->next;
		NodeType<T>* tempPtr = new NodeType<T>;
		tempPtr->data = list_curPtr->data;
		while (m_curPtr->next != m_tail)
			m_curPtr = m_curPtr->next;
		m_curPtr->next->pre = tempPtr;
		tempPtr->next = m_curPtr->next;
		tempPtr->pre = m_curPtr;
		m_curPtr->next = tempPtr;
	}
	return *this;
}



