#pragma once
#include "VocaType.h"
#include "SimpleVocaType.h"
#include "SortedLinkedListType.h"
#include "QueueType.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

enum permission
{
	USER = 1,
	ADMIN = 2
};

class UserType {
public:
	UserType();
	~UserType() {}

	bool operator<(const UserType& person);
	bool operator>(const UserType& person);
	bool operator==(const UserType& person);
	
	void SetId(string id);
	void SetPassword(string pw);
	void SetName(string name);
	void SetRecord(string id, string pw, string name, int status);
	void SetDate();
	void SetStatus(int status);
	void SetTestScore(int testScore);
	void SetLearnLevel(int learnLevel);

	string GetId();
	string GetPassword();
	string GetName();
	int GetLearnLevel();
	int GetTestScore();
	int GetStatus();

	void SetIdFromKB();
	void SetPwFromKB();
	void SetNameFromKB();
	void SetRecordFromKB();
	SortedLinkedListType<SimpleVocaType>* GetList();
	Queue<SimpleVocaType>* GetQueue();
	const string currentDateTime();

	void DisplayId();
	void DisplayName();
	void DisplayPassword();
	void DisplayTestScore();
	void DisplayLearnLevel();
	void DisplayLogTime();
	void DisplayStatus();
	void DisplayAll();

	int AddVoca(SimpleVocaType& simpleVoca);
	int DeleteVoca(SimpleVocaType& simplevoca);
	void DisplayVoca();
	void DisplayVocaReverse();
	void DeleteAllVoca();

private:
	string m_id; // User Id
	string m_name; // User name
	string m_password; // User password
	string m_recentLoginTime;
	int m_testScore; // word test score
	int m_learnLevel;
	SortedLinkedListType<SimpleVocaType> m_MyVocaList;
	Queue<SimpleVocaType> m_recentSearchList;
	int m_status; //User permission
};