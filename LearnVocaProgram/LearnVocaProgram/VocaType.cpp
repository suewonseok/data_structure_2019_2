#include "VocaType.h"

//생성자(m_id, m_english, m_korean을 초기화한다.)
VocaType::VocaType() {
	m_id = -1;
	m_english = " ";
	m_korean = " ";
	m_correct = 0;
	m_wrong = 0;
}

//id를 반환한다.
int VocaType::GetId() const {
	return m_id;
}

//spelling을 반환한다.
string VocaType::GetEnglish() const {
	return m_english;
}

//뜻을 반환한다.
string VocaType::GetKorean() const {
	return m_korean;
}


double VocaType::GetCorrect() const {
	return m_correct;
}

double VocaType::GetWrong() const {
	return m_wrong;
}

double VocaType::GetCorrectPercent() const {
	if (m_correct == 0 && m_wrong == 0)
		return 0;
	else if (m_correct > 0 && m_wrong == 0)
		return 100;
	else {
		double m_correctPercent = double(double(m_correct / (m_correct + m_wrong)) * 100);
		return m_correctPercent;
	}
}

void VocaType::PlusCorrect() {
	++m_correct;
}

void VocaType::PlusWrong() {
	++m_wrong;
}


//id를 입력한다.
void VocaType::SetId(int id) {
	m_id = id;
}

//spelling을 입력한다.
void VocaType::SetEnglish(string english) {
	m_english = english;
}

//뜻을 입력한다.
void VocaType::SetKorean(string korean) {
	m_korean = korean;
}

//id, spelling, 뜻을 입력한다.
void VocaType::SetVoca(int id, string english, string korean) {
	SetId(id);
	SetEnglish(english);
	SetKorean(korean);
}

//id를 키보드로 입력한다.
void VocaType::SetIdFromKB() {
	cout << "\n\tid: ";
	cin >> m_id;
}

//spelling을 키보드로 입력한다.
void VocaType::SetEnglishFromKB() {
	cout << "\n\t English: ";
	cin >> m_english;
}

//뜻을 키보드로 입력한다.
void VocaType::SetKoreanFromKB() {
	cout << "\n\t Korean: ";
	cin >> m_korean;
}

//id, spelling, 뜻을 입력한다.
void VocaType::SetVocaFromKB() {
	SetIdFromKB();
	SetEnglishFromKB();
	SetKoreanFromKB();
}

//id값을 화면에 출력한다.
void VocaType::DisplayId() const {
	cout << "\n\tid: " << m_id << endl;
}

//spelling을 화면에 출력한다.
void VocaType::DisplayEnglish() const {
	cout << "\n\tEnglish: " << m_english << endl;
}

//뜻을 화면에 출력한다.
void VocaType::DisplayKorean() const {
	cout << "\n\tKorean: " << m_korean << endl;
}

//id, spelling, 뜻을 화면에 출력한다.
void VocaType::DisplayVoca() const {
	DisplayId();
	DisplayEnglish();
	DisplayKorean();
}

void VocaType::DisplayCorrectPercent() const {
	cout << "\n\t( 정답률: " << GetCorrectPercent() << "% )" << endl;
}

//인자와 spelling을 비교하고 인자보다 작으면 true반환, 아니면 false
bool VocaType::operator<(const VocaType& voca) {
	return(m_english.compare(voca.m_english) < 0);
}

//인자와 spelling을 비교하고 인자보다 크면 true반환, 아니면 false
bool VocaType::operator>(const VocaType& voca) {
	return(m_english.compare(voca.m_english) > 0);
}

//인자와 spelling을 비교하고 인자보다 같은면 true반환, 아니면 false
bool VocaType::operator==(const VocaType& voca) {
	return(m_english.compare(voca.m_english) == 0);
}

//입력 파일디스크립터로부터 Voca타입을 복사해온다.
int VocaType::ReadDataFromFile(ifstream& fin) {
	fin >> m_id;
	fin >> m_english;
	fin >> m_korean;
	return 1;
}

//출력 파일디스크립터에 Voca타입을 작성한다.
int VocaType::WriteDataToFile(ofstream& fout) {
	fout << m_id << " ";
	fout << m_english << " ";
	fout << m_korean << " " << endl;
	return 1;
}

