#include <stdio.h>
#include "Application.h"


//생성자
Application::Application() {
    m_command = -1;
    m_curUser = nullptr;
    UserType Admin;
    Admin.SetRecord("admin", "pwadmin", "admin", ADMIN);
    m_AllUserList.Insert(Admin);
    SimpleUserType2 tempSimpleUser;
    tempSimpleUser.SetPtr(m_AllUserList.GetCurPtr());
    m_AllSimpleUList.Insert(tempSimpleUser);
    InitWordBook();
}

//프로그램 실행함수
void Application::Run() {
    while (1) {
        m_command = GetCommand();
        switch (m_command) {
        case 1: // 로그인
            LogIn();
            break;
        case 2: // 회원가입
            CreateUser();
            break;
        case 3: // 랭킹조회
            ShowRanker();
            break;
        case 0:
            cout << "\t종료합니다.." << endl;
            return;
        default:
            cout << "Caution" << endl;
            break;
        }
    }
}

//유저가 영어단어 학습 프로그램에 접속한다.
void Application::LogIn() {
    int permission = VerifyLogIn();
    if (permission == USER) {
        m_curUser->SetDate();
        while (1) {
            m_command = GetCommandLogIn();
            switch (m_command)
            {
            case 1:
                SearchVoca();
                break;
            case 2:
                TestVoca();
                break;
            case 3:
                LearnVoca();
                break;
            case 4:
                ManageMyVocaList();
                break;
            case 5:
                EditMyInfo();
                break;
            case 6:
                CheckMyInfo();
                break;
            case 0:
                cout << "\t로그아웃.." << endl;
                LogOut();
                return;
            default:
                cout << "Caution" << endl;
                break;
            }
        }
    }
    else if (permission == ADMIN) {
        m_curUser->SetDate();
        while (1) {
            m_command = GetCommandManageUser();
            switch (m_command)
            {
            case 1:
                DeleteUser();
                break;
            case 2:
                EditUser();
                break;
            case 3:
                CheckAllUser();
                break;
            case 0:
                cout << "\t로그아웃.." << endl;
                LogOut();
                return;
            default:
                cout << "Caution" << endl;
                break;
            }
        }
    }
    else
        return;
}

//프로그램 실행함수에서 사용자의 명령을 받는다.
int Application::GetCommand() {
    int c;
    cout << endl << endl;
    cout << "\t************ 영어단어 학습프로그램 **************" << endl << endl;
    cout << "\t    1. 로그인" << endl;
    cout << "\t    2. 회원가입" << endl;
    cout << "\t    3. 랭킹조회" << endl;
    cout << "\t    0. 종료" << endl << endl;
    cout << "\t****************************" << endl << endl;
    cout << endl << "\t Choose a Command--> ";
    cin >> c;
    cout << endl;
    return c;
}

//학습 프로그램에서 사용자의 명령을 입력받는다.
int Application::GetCommandLogIn() {
    int c;
    cout << endl << endl;
    cout << "\t******** " << m_curUser->GetName() << "님, 안녕하세요 **********" << endl << endl;
    cout << "\t    1. 단어 검색하기" << endl;
    cout << "\t    2. 단어 시험보기" << endl;
    cout << "\t    3. 단어 학습하기" << endl;
    cout << "\t    4. 내 단어장 관리하기" << endl;
    cout << "\t    5. 내 정보 수정하기" << endl;
    cout << "\t    6. 내 정보 조회하기" << endl;
    cout << "\t    0. 로그아웃" << endl << endl;
    cout << "\t****************************" << endl << endl;
    cout << endl << "\t Choose a Command--> ";
    cin >> c;
    cout << endl;
    return c;
}

//유저관리에서 사용자의 명령을 받는다.
int Application::GetCommandManageUser() {
    int c;
    cout << endl << endl;
    cout << "\t******** 관리자님, 안녕하세요 **********" << endl << endl;
    cout << "\t    1. 유저정보 삭제하기" << endl;
    cout << "\t    2. 유저정보 수정하기" << endl;
    cout << "\t    3. 유저정보 조회하기" << endl;
    cout << "\t    0. 로그아웃" << endl << endl;
    cout << "\t****************************" << endl << endl;
    cout << endl << "\t Choose a Command--> ";
    cin >> c;
    cout << endl;
    return c;
}

//유저의 로그인 정보를 입력받고 정보가 적합한지 검사하고 권한을 분류한다.
int Application::VerifyLogIn() {
    /*UserType temp;
    UserType dummy;
    cout << "\n\t**** 로그인 ****\n";
    temp.SetIdFromKB();
    temp.SetPwFromKB();
    m_AllUserList.ResetList();
    while (m_AllUserList.GetNext(dummy) != nullptr) {
        if (dummy.GetId().compare(temp.GetId()) == 0) {
            if (dummy.GetPassword().compare(temp.GetPassword()) == 0) {
                m_curUser = m_AllUserList.GetCurPtr();
                if (m_curUser->GetStatus() == USER) {
                    cout << "\n\t**** 유저 로그인 성공****\n";
                    return USER;
                }
                else {
                    cout << "\n\t**** 관리자 로그인 성공****\n";
                    return ADMIN;
                }
            }
            else {
                cout << "\n\t**** 비밀번호 정보가 올바르지 않습니다 ****\n";
                return 0;
            }
        }
    }
    cout << "\n\t**** id 정보가 올바르지 않습니다 ****\n";
    return 0;*/

    UserType temp;
    UserType dummy;
    SimpleUserType2 temp2;
    SimpleUserType2 dummy2;
    cout << "\n\t**** 로그인 ****\n";
    temp.SetIdFromKB();
    temp.SetPwFromKB();
    temp2.SetPtr(&temp);
    dummy2.SetPtr(&temp);
    m_AllSimpleUList.ResetList();
    if (m_AllSimpleUList.Get(dummy2)) {
        if (dummy2.GetPtr()->GetPassword().compare(temp2.GetPtr()->GetPassword()) == 0) {
            m_curUser = m_AllSimpleUList.GetCurPtr()->GetPtr();
            if (m_curUser->GetStatus() == USER) {
                cout << "\n\t**** 유저 로그인 성공****\n";
                return USER;
            }
            else {
                cout << "\n\t**** 관리자 로그인 성공****\n";
                return ADMIN;
            }
        }
        else {
            cout << "\n\t**** 비밀번호 정보가 올바르지 않습니다 ****\n";
            return 0;
        }
    }
    else {
        cout << "\n\t**** id 정보가 올바르지 않습니다 ****\n";
    }
    return 0;
}

//유저가 영어단어 학습 프로그램에서 나간다.
void Application::LogOut() {
    m_curUser = nullptr;
}

//유저를 추가한다.
void Application::CreateUser() {
    /*UserType tempUser;
    cout << "\n\t**** 회원가입 ****\n";
    tempUser.SetIdFromKB();
    while (m_AllUserList.Get(tempUser)) {
        cout << "\n\t이미 존재하는 id입니다.\n";
        tempUser.SetIdFromKB();
    }
    tempUser.SetNameFromKB();
    tempUser.SetPwFromKB();
    tempUser.SetStatus(USER);
    if (m_AllUserList.Insert(tempUser)) {
        cout << "\n\t계정이 생성되었습니다.\n";
    }
    else {
        cout << "\n\t계정생성에 실패하였습니다.\n";
    }
    return;
    */
    UserType tempUser;
    SimpleUserType2 tempSimpleUser;
    cout << "\n\t**** 회원가입 ****\n";
    tempUser.SetIdFromKB();
    tempSimpleUser.SetPtr(&tempUser);
    if (m_AllSimpleUList.Get(tempSimpleUser)) {
        cout << "\n\t이미 존재하는 id입니다.\n";
        return;
    }
    else {
        tempUser.SetNameFromKB();
        tempUser.SetPwFromKB();
        tempUser.SetStatus(USER);
        if (m_AllUserList.Insert(tempUser)) {
            tempSimpleUser.SetPtr(m_AllUserList.GetCurPtr());
            if (!m_AllSimpleUList.Insert(tempSimpleUser)) {
                m_AllSimpleUList.ExpandSize();
                m_AllSimpleUList.Insert(tempSimpleUser);
            }
            cout << "\n\t계정이 생성되었습니다.\n";

        }
        else {
            cout << "\n\t계정생성에 실패하였습니다.\n";
        }
        return;
    }
}

//유저를 삭제한다.
void Application::DeleteUser() {
    /*UserType tempUser;
    cout << "\n\t**** 삭제할 유저id 입력 ****\n";
    tempUser.SetIdFromKB();
    if (!m_AllUserList.Get(tempUser)) {
        cout << "\n\t해당 id가 없습니다.\n";
        return;
    }
    else {
        if (tempUser.GetStatus() == ADMIN) {
            cout << "\n\t관리자 계정은 삭제할 수 없습니다.\n";
            return;
        }
        else {
            if (m_AllUserList.Delete(tempUser)) {
                cout << "\n\t계정이 삭제되었습니다.\n";
            }
            else {
                cout << "\n\tt계정삭제에 실패하였습니다.\n";
            }
        }
    }*/

    UserType tempUser;
    SimpleUserType2 tempSimpleUser;
    cout << "\n\t**** 삭제할 유저id 입력 ****\n";
    tempUser.SetIdFromKB();
    tempSimpleUser.SetPtr(&tempUser);
    if (!m_AllSimpleUList.Get(tempSimpleUser)) {
        cout << "\n\t해당 id가 없습니다.\n";
        return;
    }
    else {
        if (tempSimpleUser.GetPtr()->GetStatus() == ADMIN) {
            cout << "\n\t관리자 계정은 삭제할 수 없습니다.\n";
            return;
        }
        else {
            if (m_AllSimpleUList.Delete(tempSimpleUser) && m_AllUserList.Delete(tempUser))
            {
                m_AllSimpleUList.ReduceSize();
                cout << "\n\t계정이 삭제되었습니다.\n";
            }     
            else {
                cout << "\n\tt계정삭제에 실패하였습니다.\n";
            }
        }
    }
}

//모든 유저정보를 화면에 출력한다.
void Application::CheckAllUser() {
    /*cout << "\n\t**** 전체 유저정보 ****\n";
    UserType tempUser;
    m_AllUserList.ResetList();
    while (m_AllUserList.GetNext(tempUser) != nullptr) {
        if (tempUser.GetStatus() != ADMIN) {
            tempUser.DisplayAll();
            cout << "\n\t------------\n";
        }
    }*/
    cout << "\n\t**** 전체 유저정보 ****\n";
    SimpleUserType2 tempSimpleUser;
    m_AllSimpleUList.ResetList();
    while (m_AllSimpleUList.GetNext(tempSimpleUser) != -1) {
        if (tempSimpleUser.GetPtr()->GetStatus() != ADMIN) {
            tempSimpleUser.GetPtr()->DisplayAll();
            cout << "\n\t------------\n";
        }
    }
}

//유저 정보를 수정한다.
void Application::EditUser() {
    UserType tempUser;
    SimpleUserType2 tempSimpleUser;
    cout << "\n\t**** 수정할 유저id 입력 ****\n";
    tempUser.SetIdFromKB();
    tempSimpleUser.SetPtr(&tempUser);
    if (!m_AllSimpleUList.Get(tempSimpleUser)) {
        cout << "\n\t해당 id가 없습니다.\n";
        return;
    }
    else {
        if (tempSimpleUser.GetPtr()->GetStatus() == ADMIN) {
            cout << "\n\t관리자 계정은 갱신할 수 없습니다.\n";
            return;
        }
        else {
            
            tempSimpleUser.GetPtr()->SetPwFromKB();
            tempSimpleUser.GetPtr()->SetNameFromKB();
            cout << "\n\t---------- 유저정보 업데이트 완료 ----------\n";
            tempSimpleUser.GetPtr()->DisplayAll();
        }
    }
}

//랭커의 정보를 화면에 출력한다.
void Application::ShowRanker() {
    //      배열로 구현한 showRanker();
    //    SortedArrayList<SimpleUserType> RankerList;
    //    int rank = 1;
    //    cout << "\n\t**** 랭크 정보 ****\n";
    //    UserType tempUser;
    //    SimpleUserType tempSimpleUser;
    //    m_AllUserList.ResetList();
    //    while(m_AllUserList.GetNext(tempUser) != nullptr) {
    //        if(tempUser.GetTestScore() != -1) {
    //            tempSimpleUser.SetPtr(m_AllUserList.GetCurPtr());
    //            RankerList.Insert(tempSimpleUser);
    //        }
    //    }
    //    RankerList.ResetList();
    //    while(RankerList.GetNext(tempSimpleUser) != -1) {
    //        cout << "\n\t" << rank << "등: " << tempSimpleUser.GetPtr()->GetId() << ", 점수: " << tempSimpleUser.GetPtr()->GetTestScore() << endl;
    //        rank++;
    //    }

    MaxHeap<SimpleUserType> RankingList(m_AllUserList.GetLength());
    int Rank = 0;
    int cnt = 0;
    cout << "\n\t**** 랭크 정보 ****\n";
    UserType tempUser;
    SimpleUserType tempSimpleUser;
    SimpleUserType2 tempSimpleUser2;
    m_AllSimpleUList.ResetList();
    while (m_AllSimpleUList.GetNext(tempSimpleUser2) != -1) {
        if (tempSimpleUser2.GetPtr()->GetTestScore() != -1) {
            tempSimpleUser.SetPtr(tempSimpleUser2.GetPtr());
            RankingList.Add(tempSimpleUser);
        }
    }
    while (1) {
        if (RankingList.IsEmpty() || cnt == 100)
            break;
        SimpleUserType simple;
        simple = RankingList.Pop();
        cout << "\n\t" << Rank << "등(ID): " << simple.GetPtr()->GetId() << ", 점수: " << simple.GetPtr()->GetTestScore() << "점" << endl;

        Rank++;
        cnt++;
    }
}

//본인 계정의 정보를 화면에 출력한다.
void Application::CheckMyInfo() {
    cout << "\n\t**** 내 정보 ****\n";
    m_curUser->DisplayAll();
}

//본인 계정의 정보를 수정한다.
void Application::EditMyInfo() {
    cout << "\n\t**** 정보수정 ****\n";
    m_curUser->SetPwFromKB();
    m_curUser->SetNameFromKB();
}

//영어단어를 검색한다.
void Application::SearchVoca() {
    VocaType Item;
    SimpleVocaType simpleItem;
    Item.SetEnglishFromKB();
    m_AllVocaList.ResetList();

    //영어 단어 프로그램에 찾는 영어단어가 존재하지않을 경우
    if (!m_AllVocaList.Get(Item)) {
        cout << "\n\t검색한 영어단어는 프로그램 내에 존재하지 않습니다." << endl;
    }
    //영어 단어 프로그램에 찾는 영어단어가 존재할 경우
    else {
        Item.DisplayKorean();
        simpleItem.SetPtr(&Item);
        m_AllSimpleList.Get(simpleItem);
        m_curUser->GetQueue()->enQueue(simpleItem);
    }
}

//영어단어 시험을 본다.
void Application::TestVoca() {
    //  프로그램이 단어를 임의로 선정하여 사용 자의 단어암기 수준을 테스트하는 함수
    SimpleVocaType simpleTempVoca;
    m_AllSimpleList.ResetList();
    srand(time(NULL));
    int randArr[50];
    for (int i = 0; i < 50; i++) {                                    //0~999의 범위에서 50개를 랜덤으로 차출해서
                                                                    //배열 randArr[]에 넣는다.
        randArr[i] = rand() % 1000; //0~999의 범위
        for (int j = 0; j < i; j++) {
            if (randArr[j] == randArr[i]) {
                i--;
                break;
            }
        }
    }
    //배열 randArr[]에 속한 숫자들에 대응하는 배열의 데이터들을
    //단어 테스트용 스택에 넣는다.
    for (int i = 0; i < 50; i++) {
        simpleTempVoca = m_AllSimpleList.GetIndexOfData(randArr[i]);
        m_TestVocaList.push(simpleTempVoca);
    }

    int count = 1, correct = 0, incorrect = 0;
    string English;
    if (m_TestVocaList.isEmpty())
        Run();
    else {
        cout.precision(3); //숫자 자릿수가 3개까지만 출력되게 설정
        while (1) {
            if (m_TestVocaList.getLength() == 0)
                break;
            else {
                cout << "\t단어테스트 ( " << count << "/ 50 ) => 정답 : " << correct << " 오답 : " << incorrect << endl;

                m_TestVocaList.pop(simpleTempVoca);
                cout << "\n\tKorean: " << simpleTempVoca.GetPtr()->GetKorean() << "( 정답률: " << simpleTempVoca.GetPtr()->GetCorrectPercent() << "% )" << endl;
                cout << "\n\t0. 나가기 " << endl;
                cout << "\n\t->"; cin >> English; cout << endl;
                if (English == "0") {
                    cout << endl << "\t<<결과>> 정답 : " << correct << " 오답 : " << incorrect << " 점수 : " << correct * 2 << "점 " << endl;
                    m_TestVocaList.MakeEmpty();
                    if ((correct * 2) > m_curUser->GetTestScore()) {
                        m_curUser->SetTestScore(correct * 2);
                    }
                    return;
                }
                else if (simpleTempVoca.GetPtr()->GetEnglish().compare(English) != 0) {
                    incorrect++;
                    count++;
                    English = simpleTempVoca.GetPtr()->GetEnglish();
                    cout << "\t\t오답!! (" << English << ")" << endl;
                    simpleTempVoca.GetPtr()->PlusWrong();
                    if (!(m_curUser->GetList()->Get(simpleTempVoca))) {
                        cout << "\n\t\t해당 단어를 내 단어장에 추가하시겠습니까?\n\t\t(Y/N):"; cin >> English;
                        cout << endl;
                        if (English.compare("Y") == 0) {
                            if (m_curUser->AddVoca(simpleTempVoca)) {
                                cout << "\t\t내 단어장에 추가되었습니다!!\n";
                            }
                            else {
                                cout << "\t\t내 단어장 추가에 실패하였습니다..\n";
                            }
                        }
                    }
                }
                else {
                    correct++;
                    count++;
                    simpleTempVoca.GetPtr()->PlusCorrect();
                    cout << "\t\t정답!!" << endl << endl;
                }
            }
        }
        ios_base::fmtflags f(cout.flags()); //precision 출력설정 초기화
        cout << endl << "\t<<결과>> 정답 : " << correct << " 오답 : " << incorrect << " 점수 : " << correct * 2 << "점 " << endl;
        m_TestVocaList.MakeEmpty();
        if ((correct * 2) > m_curUser->GetTestScore()) {
            m_curUser->SetTestScore(correct * 2);
        }
    }
}

//영어단어 학습기능 driver
void Application::LearnVoca() {
    while (1)
    {
        m_command = GetCommandLearnLevel();
        if (m_command == 0) {
            return;
        }
        else if (m_command >= 1 && m_command <= 5) {
            SetLearnList(m_command);
        }
        else {
            cout << "\tIllegal selection...\n";
        }
    }
}

//학습레벨 선택에서 사용자의 명령을 입력받는다.
int Application::GetCommandLearnLevel() {
    int command;
    cout << endl << endl;
    cout << "\t---Select Learn Level -- Command ----- " << endl;
    cout << "\t   1 : Level1(001~200)" << endl;
    cout << "\t   2 : Level2(201~400)" << endl;
    cout << "\t   3 : Level3(401~600)" << endl;
    cout << "\t   4 : Level4(601~800)" << endl;
    cout << "\t   5 : Level5(801~1000)" << endl;
    cout << "\t   0 : Exit" << endl;

    cout << endl << "\t Choose a Level--> ";
    cin >> command;
    cout << endl;

    return command;
}

//영어학습 단어리스트가 입력된 레벨에 맞게 채워진다.
void Application::SetLearnList(int l) {
    int LearnLevel = m_curUser->GetLearnLevel();
    if (LearnLevel < l - 1) {
        cout << "\n\tLevel" << LearnLevel + 1 << "부터 학습해주세요.\n";
        return;
    }
    SimpleVocaType simpleTempVoca;
    m_LearnVocaList.MakeEmpty();
    m_AllSimpleList.ResetList();
    srand(time(NULL));
    int randArr[200];
    for (int i = 0; i < 200; i++) {
        randArr[i] = rand() % 200 + (((l - 1) * 200));    //c는 선택된 레벨이다. c가 1이면 0~199 index에 위치한 데이터
        for (int j = 0; j < i; j++) {                    //                       c가 2면 200~399 index에 위치한 데이터
            if (randArr[j] == randArr[i]) {
                i--;
                break;
            }
        }
    }
    // m_LearnVocaList에 m_id 1~200에 해당하는 VocaType을 enQueue한다.
    for (int i = 0; i < 200; i++) {
        simpleTempVoca = m_AllSimpleList.GetIndexOfData(randArr[i]);    //0~199의 인덱스에 위치한 데이터가 무작위로
        m_LearnVocaList.enQueue(simpleTempVoca);                        //학습용 큐에 채워진다.
    }

    //위에서 정해진 영어단어 200개에 대한 학습을 반복한다.
    ExecuteLearn();                                                        //위에서 채워진 학습용 큐에 대한 반복학습이 시작된다.
}


//영어단어 200개에 대한 학습을 반복한다.
int Application::ExecuteLearn() {
    int LearnLevel = m_curUser->GetLearnLevel();
    string tempString;
    SimpleVocaType simpleTempVoca;

    // m_LearnVocaList에 VocaType이 전부 없어지기 전까지 반복학습 시작
    while (m_LearnVocaList.GetLength() != 0)
    {
        m_LearnVocaList.deQueue(simpleTempVoca);
        simpleTempVoca.GetPtr()->DisplayKorean();
        cout << "\t해당하는 단어입력(중간퇴장: Y): ";
        cin >> tempString;
        if (simpleTempVoca.GetPtr()->GetEnglish().compare(tempString) != 0)    //오답일 경우
        {
            if (tempString == "Y")    //나가고 싶을 경우
            {
                cout << "\n\tLevel" << LearnLevel + 1 << "을 포기합니다.\n";
                m_LearnVocaList.MakeEmpty();
                return 0;
            }
            m_LearnVocaList.enQueue(simpleTempVoca);
            tempString = simpleTempVoca.GetPtr()->GetEnglish();
            cout << "\twrong(" << tempString << "), 남은 학습단어: " << m_LearnVocaList.GetLength() << "개" << endl;
            if (!(m_curUser->GetList()->Get(simpleTempVoca))) {
                cout << "\n\t\t해당 단어를 내 단어장에 추가하시겠습니까?\n\t\t(Y/N):"; cin >> tempString;
                if (tempString.compare("Y") == 0) {
                    if (m_curUser->AddVoca(simpleTempVoca)) {
                        cout << "\t\t내 단어장에 추가되었습니다!!\n";
                    }
                    else {
                        cout << "\t\t내 단어장 추가에 실패하였습니다..\n";
                    }
                }
            }
        }
        else
        {                                                    //정답일 경우
            cout << "\tright!, 남은 학습단어: " << m_LearnVocaList.GetLength() << "개" << endl;
        }
    }
    cout << "\n\tLevel" << LearnLevel + 1 << "단계를 학습 완료했습니다.\n";
    if (LearnLevel < 4) {
        LearnLevel++;
        m_curUser->SetLearnLevel(LearnLevel);
    }
    return 1;
}

//내 단어장 관리 driver
void Application::ManageMyVocaList() {
    while (1)
    {
        m_command = GetCommandMyVocaList();

        switch (m_command)
        {
        case 1:        // 내 단어장 리스트에 영어단어를 추가한다.
            AddMyVoca();
            break;
        case 2:        // 내 단어장 리스트에서 특정 영어단어를 삭제한다.
            DeleteMyVoca();
            break;
        case 3:        // 내 단어장의 모든 영어단어를 화면에 출력한다.
            m_curUser->DisplayVoca();
            break;
        case 4:        // 내 단어장의 모든 영어단어를 역순으로 화면에 출력한다.
            m_curUser->DisplayVocaReverse();
            break;
        case 5:        // 내 단어장에 있는 모든 영어단어를 내 단어장 리스트에서 삭제한다.
            m_curUser->DeleteAllVoca();
            break;
        case 0:
            return;
        default:
            cout << "\tIllegal selection...\n";
            break;
        }
    }
}

//화면에 내 단어장 관리 명령어 목록을 출력하고 키보드로 선택된 명령을 입력받는다.
int Application::GetCommandMyVocaList() {
    int command;
    cout << endl << endl;
    cout << "\t -------Manage my voca------- " << endl;
    cout << "\t   1 : Add voca" << endl;
    cout << "\t   2 : Delete voca" << endl;
    cout << "\t   3 : Display voca" << endl;
    cout << "\t   4 : Display voca(In reverse order)" << endl;
    cout << "\t   5 : Delete my voca list" << endl;
    cout << "\t   0 : Exit" << endl;

    cout << endl << "\t Choose a Command Number--> ";
    cin >> command;
    cout << endl;

    return command;
}

//내 단어장 리스트에 영어단어를 추가한다.
void Application::AddMyVoca() {
    VocaType tempVoca;
    SimpleVocaType simpleTempVoca;

    if (m_curUser->GetQueue()->GetLength() != 0) {
        cout << "\n\t최근 검색한 단어: \n";
        while (m_curUser->GetQueue()->deQueue(simpleTempVoca)) {
            cout << "\tEnglish: " << simpleTempVoca.GetPtr()->GetEnglish() << ", Korean: " << simpleTempVoca.GetPtr()->GetKorean() << endl;
        }
    }

    cout << "\n\t내 단어장 리스트에 추가하려는 영어단어 검색: ";
    tempVoca.SetEnglishFromKB();
    if (m_AllVocaList.Get(tempVoca)) {        //영어단어 프로그램에 검색한 영어단어가 존재하는지 검사
        simpleTempVoca = m_AllSimpleList.GetIndexOfData(tempVoca.GetId() - 1);
        if (m_curUser->AddVoca(simpleTempVoca)) {
            cout << "\n\t내 단어장 리스트 업데이트 완료\n";
        }
        else {
            cout << "\n\t내 단어장 리스트 업데이트 실패\n";
        }
    }
    else {                                    //영어단어 프로그램에 존재하지 않는 영어단어일 경우
        cout << "\n\t해당 단어는 영어단어 프로그램에 존재하지 않습니다.\n";
    }
}

//내 단어장 리스트에서 특정 영어단어를 삭제한다.
void Application::DeleteMyVoca() {
    VocaType tempVoca;
    SimpleVocaType simpleTempVoca;

    cout << "\n\t내 단어장 리스트에서 삭제하려는 영어단어 입력: ";
    tempVoca.SetEnglishFromKB();
    if (m_AllVocaList.Get(tempVoca)) {                //프로그램에 삭제하려는 영어단어가 존재하는지 검사
        simpleTempVoca = m_AllSimpleList.GetIndexOfData(tempVoca.GetId() - 1);
        if (m_curUser->DeleteVoca(simpleTempVoca)) {
            cout << "\n\t내 단어장 리스트 업데이트 완료\n";
        }
        else {
            cout << "\n\t내 단어장 리스트 업데이트 실패\n";
        }
    }
    else {                                            //프로그램에 삭제하려는 영어단어가 존재하지 않는 경우
        cout << "\n\t해당 단어는 프로그램에 존재하지 않음\n";
    }
}

//프로그램 영어단어를 파일로부터 초기화한다.
void Application::InitWordBook() {
    m_InFile.open("WordFile.txt");
    VocaType item;                            //Item 삽입할 영단어 정보를 담을 VocaType 객체
    SimpleVocaType simpleItem;                //읽어온 데이터가 담긴 item 객체를 SimpleVocaType 객체인자로 넘겨줌
    m_AllVocaList.ResetList();

    //파일로부터 voca정보를 불러와서 m_AllVocaList를 구성한다.
    while (!m_InFile.eof()) {
        item.ReadDataFromFile(m_InFile);
        m_AllVocaList.Insert(item);//현재 포인터 위치에 읽어온 데이터가 담긴 item 객체를 인자 보냄
    }
    m_InFile.close();

    //m_AllSimpleList를 1000개의 Voca 객체 정보로 구성한다.
    m_AllVocaList.ResetList();
    while (m_AllVocaList.GetNext(item) != -1) {        //m_AllVocaList의 모든 요소를 m_AllSimpleList에 복사하는 과정

        simpleItem.SetPtr(m_AllVocaList.GetCurPtr());    //  m_AllVocaList.GetCurPtr()로 단어리스트 속 각 요소의 포인터를 뽑아온다.
                                                        // ( while문의 GetNextVoca()는 리스트 내의 모든 요소에 접근하기 위한 반복역할)

        m_AllSimpleList.Insert(simpleItem);            // m_AllVocaList의 각요소의 포인터를 갖고있는
                                                        //simpleItem을 m_AllSimpleList에 넣는다.
    }
}