#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class VocaType {
public:
	VocaType();												//생성자(m_id, m_english, m_korean을 초기화한다.)
	int GetId() const;											//id를 반환한다.
	string GetEnglish() const;									//spelling을 반환한다.
	string GetKorean() const;										//뜻을 반환한다
	double GetCorrect() const;
	double GetWrong() const;
	double GetCorrectPercent() const;
	void PlusCorrect();
	void PlusWrong();
	void SetId(int id);										//id를 입력한다.
	void SetEnglish(string english);						//spelling을 입력한다.
	void SetKorean(string korean);							//뜻을 입력한다.
	void SetVoca(int id, string english, string korean);	//id, spelling, 뜻을 입력한다.
	void SetIdFromKB();										//id를 키보드로 입력한다.
	void SetEnglishFromKB();								//spelling을 키보드로 입력한다.
	void SetKoreanFromKB();									//뜻을 키보드로 입력한다.
	void SetVocaFromKB();									//id, spelling, 뜻을 입력한다.
	void DisplayId() const;										//id값을 화면에 출력한다.
	void DisplayEnglish() const;									//spelling을 화면에 출력한다.
	void DisplayKorean() const;									//뜻을 화면에 출력한다.
	void DisplayVoca() const;										//id, spelling, 뜻을 화면에 출력한다.
	void DisplayCorrectPercent() const;
	bool operator<(const VocaType& voca);					//인자와 spelling을 비교하고 인자보다 작으면 true반환, 아니면 false
	bool operator>(const VocaType& voca);					//인자와 spelling을 비교하고 인자보다 크면 true반환, 아니면 false
	bool operator==(const VocaType& voca);					//인자와 spelling을 비교하고 인자보다 같은면 true반환, 아니면 false
	int ReadDataFromFile(ifstream& fin);					//입력 파일디스크립터로부터 Voca타입을 복사해온다. id, english, korean순서로 받아온다는 것을 명심
	int WriteDataToFile(ofstream& fout);					//출력 파일디스크립터에 Voca타입을 작성한다.

private:
	int m_id;												//단어의 고유 id값
	string m_english;										//단어의 spelling을 저장하는 변수이며 단어검색, 내 단어장 관리에서 key값
	string m_korean;										//단어의 뜻을 저장하는 변수
	double m_correct;
	double m_wrong;
};