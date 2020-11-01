#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include "QueueType.h"
#include "StackType.h"
#include "VocaType.h"
#include "SimpleVocaType.h"
#include "SortedArrayListType.h"
#include "SortedLinkedListType.h"
#include "User.h"
#include "SimpleUserType.h"
#include "SimpleUserType2.h"
#include "MaxHeap.h"
#include "UnsortedLinkedListType.h"
#define FILENAMESIZE 1024

using namespace std;

class Application {
public:
	Application();					//생성자
	void Run();						//프로그램 실행함수
	void LogIn();					//유저가 영어단어 학습 프로그램에 접속한다.
	int GetCommand();				//프로그램 실행함수에서 사용자의 명령을 받는다.
	int GetCommandLogIn();			//학습 프로그램에서 사용자의 명령을 입력받는다.
	int GetCommandManageUser();		//유저관리에서 사용자의 명령을 받는다.
	/**
	*	@brief      유저의 로그인 정보를 입력받고 정보가 적합한지 검사하고 권한을 분류한다.
	*	@pre	        유저리스트가 초기화되어있어야한다.
	*	@post       m_curUser가 로그인한 유저를 가리키게 된다.
	*	@return     로그인에 실패하면 0, 일반 유저 로그인에 성공하면 1, 관리자 로그인에 성공하면 2를 반환한다.
	*/
	int VerifyLogIn();
	void LogOut();					//유저가 영어단어 학습 프로그램에서 나간다.
	void CreateUser();				//유저를 추가한다.
	void DeleteUser();				//유저를 삭제한다.
	void CheckAllUser();			//모든 유저정보를 화면에 출력한다.
	void EditUser();				//유저 정보를 수정한다.
	void ShowRanker();				//랭커의 정보를 화면에 출력한다.
	void CheckMyInfo();				//본인 계정의 정보를 화면에 출력한다.
	void EditMyInfo();				//본인 계정의 정보를 수정한다.
	void SearchVoca();			    //영어단어를 검색한다.
	void TestVoca();				//영어단어 시험을 본다.
	void LearnVoca();				//영어단어 학습 실행함수
	int GetCommandLearnLevel();	    //학습레벨 선택에서 사용자의 명령을 입력받는다.
	void SetLearnList(int level);	//영어학습 단어리스트가 입력된 레벨에 맞게 채워진다.
	int ExecuteLearn();			    //넣어진 영어학습 단어리스트를 토대로 학습을 실행한다.
	void ManageMyVocaList();		//내 단어장 관리 실행함수
	int GetCommandMyVocaList();	    //내 단어장 관리에서 사용자의 명령을 입력받는다.
	void AddMyVoca();				//내 단어장에 영어단어를 추가한다.
	void DeleteMyVoca();			//내 단어장에서 영어단어를 삭제한다.
	void InitWordBook();			//프로그램 영어단어를 파일로부터 초기화한다.

private:
	int m_command;										//사용자 명령어
	SortedArrayList<VocaType> m_AllVocaList;			//모든 영어단어리스트
	SortedArrayList<SimpleVocaType> m_AllSimpleList;	//모든 약식형 영어단어리스트
	StackType<SimpleVocaType> m_TestVocaList;			//영어단어 시험용 리스트
	Queue<SimpleVocaType> m_LearnVocaList;				//영어단어 학습용 리스트
	ifstream m_InFile;									//입력파일 디스크립터
	ofstream m_OutFile;									//출력파일 디스크립터
	UnsortedLinkedList<UserType> m_AllUserList;			//모든 유저리스트
	SortedArrayList<SimpleUserType2> m_AllSimpleUList;	//모든 약식형 유저리스트
	UserType* m_curUser;								//현재 로그인된 유저
	//SortedArrayList<SimpleUserType> m_RankerList;     //랭커 리스트
};
