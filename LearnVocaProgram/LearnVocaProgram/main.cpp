/**
*
*	@date				2019.11.29
*	@team				자료구조 2조
*	@특이사항
*	@진행해야할 내용                DoublyLinkedList 관련 된 곳 다 수정하기, 정답률 업데이트 부분 수정하기
*                                   ShowRank()에 적절한 자료구조 선택해서 다시 구현하기
*                                   user가 시험을 다시 볼때나, 유저가 삭제될 때 rankList의 갱신이 복잡한 점을 들어서
*                                   ShowRank()에서 임시 변수형태로 RankerList를 생성하는 방식이 될거 같음.
*									heap이 이런 상황에서 좋은 자료구조가 될거 같다.
*                                   simpleUserType의 operator의 기준은 testScore에 하나 더 추가하기(m_id)
*/

#include <iostream>
#include"Application.h"
#include "SimpleUserType.h"
using namespace std;

int main() {
	SimpleUserType u1;
	cout << sizeof(u1);
	//Application app;
	//app.Run();

	return 0;
}
