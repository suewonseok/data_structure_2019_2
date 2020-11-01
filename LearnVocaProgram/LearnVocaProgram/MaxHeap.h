#pragma once
#include <iostream>
using namespace std;
#define MAXSIZE 1000


template <class T>
class MaxHeap {
public:
    MaxHeap();
    MaxHeap(int size);
    ~MaxHeap() {
        MakeEmpty();
    }
    bool IsEmpty();
    bool IsFull();

    int GetLength() const;
    void MakeEmpty();

    int Add(T item); // 아이템 추가
    int Delete(T item); // item의 id를 기준으로 아이템 삭제
    T Pop(); // 루트 노드 pop
    void RetrieveItem(T& item, bool& found); // item의 id가 맞는거 찾기
    void PrintHeap(ostream& os);

    void ReheapDown(int iparent, int ibottom); // iparent는 부모 노드, ibottom 키 노트
    void ReheapUp(int iroot, int ibottom); //
    void Delete(T item, bool& found, int iparent);
    void Retrieve(T& item, bool& found, int iparent);
private:
    T* m_pHeap;
    int m_iLastNode;
    int m_nMaxSize;
};
template <typename T>
MaxHeap<T>::MaxHeap() {
    m_iLastNode = 0;
    m_nMaxSize = MAXSIZE;
    m_pHeap = new T[m_nMaxSize];
}

template <typename T>
MaxHeap<T>::MaxHeap(int size) {
    m_iLastNode = 0;
    m_nMaxSize = size;
    m_pHeap = new T[m_nMaxSize];
}
template <typename T>
bool MaxHeap<T>::IsFull() {
    return (m_iLastNode == m_nMaxSize);
}

template <typename T>
bool MaxHeap<T>::IsEmpty() {
    return (m_iLastNode == 0);
}

template <typename T>
void MaxHeap<T>::MakeEmpty() {
    m_iLastNode = 0;
    m_pHeap = nullptr;
}

template <typename T>
int MaxHeap<T>::Add(T item) {
    m_pHeap[m_iLastNode++] = item;
    ReheapUp(0, m_iLastNode - 1);
    return 1;
}

template <typename T>
int MaxHeap<T>::Delete(T item) {
    bool found;
    int iparent = 0;
    Delete(item, found, iparent);

    return found;
}


template <typename T>
T MaxHeap<T>::Pop() {
    T temp;
    temp = m_pHeap[0];
    m_pHeap[0] = m_pHeap[m_iLastNode - 1];
    m_iLastNode--;
    ReheapDown(0, m_iLastNode - 1);
    return temp;

}
template <typename T>
void MaxHeap<T>::RetrieveItem(T& item, bool& found) {
    int iparent = 0;
    Retrieve(item, found, iparent);
}

template <typename T>
void MaxHeap<T>::PrintHeap(ostream& out) {
    for (int i = 0; i < m_iLastNode; i++)
        out << m_pHeap[i] << ' ';
}

template <typename T>
void MaxHeap<T>::ReheapDown(int iparent, int ibottom) {
    int maxChild, rightChild, leftChild;

    leftChild = iparent * 2 + 1;
    rightChild = iparent * 2 + 2;

    if (leftChild <= ibottom) {
        if (leftChild == ibottom)
            maxChild = leftChild;
        else {
            if (m_pHeap[leftChild] <= m_pHeap[rightChild])
                maxChild = rightChild;
            else
                maxChild = leftChild;
        }
        if (m_pHeap[iparent] < m_pHeap[maxChild]) {
            swap(m_pHeap[iparent], m_pHeap[maxChild]);
            ReheapDown(maxChild, ibottom);
        }
    }
}

template <typename T>
void MaxHeap<T>::ReheapUp(int iparent, int ibottom) {
    int parent = 0;
    if (ibottom > iparent) {
        parent = (ibottom - 1) / 2;
        if (m_pHeap[parent] < m_pHeap[ibottom]) {
            swap(m_pHeap[parent], m_pHeap[ibottom]);
            ReheapUp(iparent, parent);
        }
    }
}

template <typename T>
void MaxHeap<T>::Delete(T item, bool& found, int iparent) {
    if (m_pHeap[iparent] == item) {
        m_pHeap[iparent] = m_pHeap[--m_iLastNode];
        ReheapDown(iparent, m_iLastNode - 1);
        found = true;
        return;
    }
    else
        Delete(item, found, ++iparent);
}

template <typename T>
void MaxHeap<T>::Retrieve(T& item, bool& found, int iparent) {
    if (iparent == m_iLastNode)
        return;

    if (item == m_pHeap[iparent]) {
        item = m_pHeap[iparent];
        found = true;
    }
    else
        Retrieve(item, found, iparent++);
}

template <typename T>
int MaxHeap<T>::GetLength() const {
    return m_iLastNode;
}