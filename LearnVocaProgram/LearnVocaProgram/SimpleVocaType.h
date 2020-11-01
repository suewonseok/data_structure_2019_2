#include "VocaType.h"

#pragma once
class SimpleVocaType {
public:

	//기본생성자
	SimpleVocaType() {
		m_ptr = nullptr;
	}

	//m_ptr 값을 초기화한다.
	void SetPtr(VocaType* ptr) {
		m_ptr = ptr;
	}

	//m_ptr을 반환한다.
	VocaType* GetPtr() const {
		return m_ptr;
	}

	//인자가 가리키는 VocaType의 id값과 비교하고 인자보다 작으면 true반환, 아니면 false
	bool operator < (const SimpleVocaType& s_voca) {
		return (m_ptr->GetId() < s_voca.GetPtr()->GetId());
	}

	//인자가 가리키는 VocaType의 id값과 비교하고 인자보다 크면 true반환, 아니면 false
	bool operator > (const SimpleVocaType& s_voca) {
		return (m_ptr->GetId() > s_voca.GetPtr()->GetId());
	}

	//인자가 가리키는 VocaType의 id값과 비교하고 인자와 같으면 true반환, 아니면 false
	bool operator == (const SimpleVocaType& s_voca) {
		return (m_ptr->GetId() == s_voca.GetPtr()->GetId());
	}

	//m_id 값을 초기화한다.
	/*
	void SetId(int id) {
		m_id = id;
	}
	*/

	//m_id를 반환한다.
	/*
	int GetId() {
		return m_id;
	}
	*/

private:
	//int m_id;				//SimpleVoca의 고유 id값
	VocaType* m_ptr;		//SimplaVoca의 포인터 변수
};