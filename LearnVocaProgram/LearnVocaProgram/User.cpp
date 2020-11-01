#include "User.h"

UserType::UserType() {
    m_name = "";
    m_id = "";
    m_password = "";
    m_recentLoginTime = "";
    m_testScore = -1;
    m_learnLevel = NULL;
    m_status = USER;
    m_recentSearchList.ResizeQueue(5);
}

bool UserType::operator<(const UserType& user) {
    return(this->m_id < user.m_id);
}

bool UserType::operator>(const UserType& user) {
    return(this->m_id > user.m_id);
}

bool UserType::operator==(const UserType& user) {
    return(this->m_id == user.m_id);
}

void UserType::SetId(string id) {
    m_id = id;
}

void UserType::SetPassword(string pw) {
    m_password = pw;
}

void UserType::SetName(string name) {
    m_name = name;
}
void UserType::SetDate() {
    m_recentLoginTime = currentDateTime();
}

void UserType::SetStatus(int status) {
    m_status = status;
}

void UserType::SetTestScore(int testScore) {
    m_testScore = testScore;
}

void UserType::SetLearnLevel(int learnLevel) {
    m_learnLevel = learnLevel;
}

void UserType::SetRecord(string id, string pw, string name, int status) {
    SetId(id);
    SetPassword(pw);
    SetName(name);
    SetStatus(status);
}

string UserType::GetId() {
    return m_id;
}

string UserType::GetPassword() {
    return m_password;
}

string UserType::GetName() {
    return m_name;
}

int UserType::GetLearnLevel() {
    return m_learnLevel;
}

int UserType::GetTestScore() {
    return m_testScore;
}

int UserType::GetStatus() {
    return m_status;
}

void UserType::SetIdFromKB() {
    cout << "\n\tId : ";
    cin >> m_id;
}
void UserType::SetPwFromKB() {
    cout << "\n\tPassword : ";
    cin >> m_password;
}
void UserType::SetNameFromKB() {
    cout << "\n\tName : ";
    cin >> m_name;
}

void UserType::SetRecordFromKB() {
    SetIdFromKB();
    SetPwFromKB();
    SetNameFromKB();
}

const string UserType::currentDateTime() {
    time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y년 %m월 %d일 %H시 %M분 %S초", &tstruct); // YyyymmddhhMMSS 형태의 스트링

    return buf;
}

SortedLinkedListType<SimpleVocaType>* UserType::GetList() {
    return &m_MyVocaList;
}

Queue<SimpleVocaType>* UserType::GetQueue() {
    return &m_recentSearchList;
}

void UserType::DisplayId() {
    cout << "\n\tId : " << m_id << endl;
}
void UserType::DisplayName() {
    cout << "\n\tName : " << m_name << endl;
}
void UserType::DisplayPassword() {
    cout << "\n\tPassword: " << m_password << endl;
}
void UserType::DisplayTestScore() {
    cout << "\n\tTest score : ";
    if (m_testScore == -1) {
        cout << "0\n";
    }
    else {
        cout << m_testScore << endl;
    }
}
void UserType::DisplayLearnLevel() {
    cout << "\n\tLearn level : " << m_learnLevel + 1 << endl;
}
void UserType::DisplayLogTime() {
    if (m_recentLoginTime == "") {
        return;
    }
    else {
        cout << "\n\tRecent Login time : " << m_recentLoginTime << endl;
        return;
    }
}
void UserType::DisplayStatus() {
    if (m_status == ADMIN) {
        cout << "\n\tpermission: ADMIN\n";
    }
    else {
        cout << "\n\tpermission: USER\n";
    }
}

void UserType::DisplayAll() {
    DisplayId();
    DisplayName();
    DisplayLogTime();
    DisplayTestScore();
    DisplayLearnLevel();
    DisplayStatus();
}

int UserType::AddVoca(SimpleVocaType& simpleVoca) {
    if (!m_MyVocaList.Get(simpleVoca)) {
        if (m_MyVocaList.Insert(simpleVoca)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

int UserType::DeleteVoca(SimpleVocaType& simplevoca) {
    if (m_MyVocaList.Get(simplevoca)) {
        if (m_MyVocaList.Delete(simplevoca)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

void UserType::DisplayVoca() {
    if (!m_MyVocaList.isEmpty()) {
        cout << "\n\t********* 내 단어장 목록 *********\n";
        m_MyVocaList.ResetList();
        SimpleVocaType dummy;
        while (m_MyVocaList.GetNext(dummy) != nullptr) {
            dummy.GetPtr()->DisplayVoca();
        }
        return;
    }
    else {
        cout << "\n\t현재 내 단어장이 비어있습니다.\n";
        return;
    }
}

void UserType::DisplayVocaReverse() {
    if (!m_MyVocaList.isEmpty()) {
        cout << "\n\t********* 내 단어장 목록(역순) *********\n";
        m_MyVocaList.ResetListForGetPre();
        SimpleVocaType dummy;
        while (m_MyVocaList.GetPre(dummy) != nullptr) {
            dummy.GetPtr()->DisplayVoca();
        }
        return;
    }
    else {
        cout << "\n\t현재 내 단어장이 비어있습니다.\n";
        return;
    }
}

void UserType::DeleteAllVoca() {
    if (!m_MyVocaList.isEmpty()) {
        cout << "\n\t********* 내 단어장 비우기 *********\n";
        m_MyVocaList.MakeEmpty();
        return;
    }
    else {
        cout << "\n\t현재 내 단어장이 비어있습니다.\n";
        return;
    }
}