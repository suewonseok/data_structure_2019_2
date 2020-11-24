# 주제: 영어단어 암기 프로그램

## 1. 설계 배경과 특징

여름 방학에 토익 공부를 했었는데 단어 암기가 가장 힘들었습니다. 그래서 경험을 살려 암기를 좀 더 쉽고 효과적인 단어 암기를 위해 해당 프로젝트를 진행하게 되었습니다. 프로그램의 기능별로 적절한 자료구조를 선정하기 위해 고민하는 등 성능 최적화를 꾀했습니다.

## 2. 시연 영상

[![자료구조 시연영상](https://user-images.githubusercontent.com/26649774/100041086-f1422180-2e4b-11eb-9caa-f0ad9c471318.png)](https://youtu.be/FoQstpPptZA)

## 3. 프로그램 기능 & 사용된 자료구조 목록

| 기능 | 자료구조 |
|:--:|:--:|
|1. 유저 관리|Unsorted Linked List & Sorted Array|
|2. 단어 검색|Sorted Array List|
|3. 단어 시험|Stack|
|4. 단어 학습|Queue|
|5. 최근 검색 단어|Queue|
|6. 내 단어장|Doubly Linked List|
|7. 랭킹 조회|Heap|

### 3.1 유저 관리(Unsorted Linked List & Sorted Array)

![1](https://user-images.githubusercontent.com/26649774/99925640-44e83880-2d82-11eb-8414-cf74279250a8.png)
⬆️ UserType 객체가 Unsorted Linked List로 관리됩니다.
<br/>

![2](https://user-images.githubusercontent.com/26649774/99925642-46b1fc00-2d82-11eb-8c22-e326b66054b0.png)

⬆️ UserType을 Unsorted List로 한 이유는  UserType형 포인터만을 변수로 가진 SimpleUserType(4byte)를 Sorted Array로 관리하기 때문입니다. ( Binary Search 가능 ) 실제 데이터(UserType)는 별다른 정렬을 하지 않고 필요할 때 접근만 합니다. 정렬, 조회는 실제 데이터를 가리키는 포인터(SimpleUserType)를 통해 합니다. 객체 크기를 고려한 결정이었습니다. (160 byte vs 4 byte)

### 3.1.1 다른 자료구조와의 비교

| 복잡도/자료구조 | Unsorted Linked & Sorted Array | Doubly Linked List | Binary Search Tree |
|:--:|:--:|:--:|:--:|
|입력|O(N)|O(N)|Best: O(log2N), Worst: O(N)|
|출력|O(N)|O(N)|Best: O(log2N), Worst: O(N)|
|조회|O(log2N)|O(N)|Best: O(log2N), Worst: O(N)|

⬆️ Binary Search Tree의 경우 User의 삽입순서에 의해 시간 복잡도가 좌지우지 되므로 항상 일정한 성능을 낼 수 없습니다. 그렇기 때문에 항상 조회에서 O(log2N)인 UnsortedLinkedList + SortedArrayList 방식으로 User를 관리하는게 옳다고 판단했습니다. 

### 3.2 단어 검색(Sorted Array List)

![3](https://user-images.githubusercontent.com/26649774/99925644-47e32900-2d82-11eb-9bd2-3ec676796ef4.png)
⬆️ Sorted Array List 선정 이유: 단어프로그램은 단어 수가 고정적입니다.(처음 프로그램 시작과 동시에 배열에 단어가 삽입되지만 그 이후로 삽입/추출이 발생하지 않으므로) 또한 단어 검색시 Binary Search가 가능합니다.

### 3.3 단어 시험(Stack)

![4](https://user-images.githubusercontent.com/26649774/99925647-47e32900-2d82-11eb-92e6-692d1dd196e1.png)
⬆️ Stack 선정 이유: 매번 50개의 단어가 들어오며 자료의 출력이 상단에서만 발생해서 스택으로 결정했습니다. 1000개의 단어에서 랜덤으로 50개의 단어를 뽑아와 스택을 만들고 pop형식으로 스택이 empty가 될때까지 단어시험 진행되는 방식입니다.

![5](https://user-images.githubusercontent.com/26649774/99925648-49145600-2d82-11eb-83eb-4246aac741d7.png)
⬆️ 단어 시험 기능에선 객체로 SimpleVocaType을 사용합니다. 객체 크기를 고려한 결정이었습니다. (80 byte vs 4 byte)

### 3.4 단어 학습(Queue)

![6](https://user-images.githubusercontent.com/26649774/99925651-49acec80-2d82-11eb-96ff-44760631a0f2.png)

⬆️ Queue 선정 이유: 데이터의 입력은 뒤를 통해 들어오고 출력은 앞으로만 나오기 때문에 단어학습기능과 적합하다 판단했습니다. 단어학습이 시작되면 레벨을 선택해야하며 레벨에 맞는 단어 200개가 무작위로 큐에 삽입됩니다. 매번 200개의 단어를 다루므로 배열 큐를 사용했습니다.

![7](https://user-images.githubusercontent.com/26649774/99925652-4a458300-2d82-11eb-81f2-35273017bfb0.png)

![8](https://user-images.githubusercontent.com/26649774/99925653-4a458300-2d82-11eb-95d4-8114a013b005.png)

⬆️ 단어 학습 기능에서도 객체로 SimpleVocaType을 사용합니다. 객체 크기를 고려한 결정이었습니다. (80 byte vs 4 byte)

### 3.5 내 단어장(Doubly Linked List)

![9](https://user-images.githubusercontent.com/26649774/99925655-4ade1980-2d82-11eb-99cc-90049c8f3655.png)

⬆️ Doubly Linked List 선정이유:  
Binary Search Tree와 비교: 입출력, 조회에서 불리합니다. 그러나 단어 역조회, 단어 개별 조회 등의 기능구현에는 부적절 했습니다.  
Sorted Array List와 비교: 입출력 시간 복잡도 동일하지만 조회에서 불리했습니다. 그러나 유저가 가입할 때마다 해당 유저가 내 단어장을 관리하지 않아도 빈배열이 만들어지므로 메모리 낭비의 우려가 있었습니다.

![10](https://user-images.githubusercontent.com/26649774/99925656-4b76b000-2d82-11eb-8ae3-22875aa29108.png)

⬆️ 내 단어장 기능에서도 객체로 SimpleVocaType을 사용합니다. 객체 크기를 고려한 결정이었습니다. (80 byte vs 4 byte)

### 3.6 최근 검색 단어(Queue)

![11](https://user-images.githubusercontent.com/26649774/99925657-4b76b000-2d82-11eb-9cf7-7fe29934478b.png)

⬆️ Search Voca에서 단어를 검색할때 마다 Queue에 Enqueue됩니다. Queue가 꽉차는 순간부터 EnQue시에 Deque가 선행된다. 이로써 5개의 최근 검색 단어가 유지됩니다.

### 3.7 랭킹 조회(Heap)

![12](https://user-images.githubusercontent.com/26649774/99925658-4c0f4680-2d82-11eb-8700-d868f1f53e3a.png)

⬆️ Heap 선정 이유: 영어단어 점수 상위 100명까지 출력하기 위해 Heap을 사용했습니다. 현재 가입된 유저에서 TestScore를 Key Value로 Heap을 구성 후 Root Node를 최대 100번까지 출력함으로써 100위까지 출력합니다.

| 복잡도/자료구조 | Heap | Sorted Array | Binary Search Tree |
|:--:|:--:|:--:|:--:|
|입력|N * log2N|N * N|Best: N * log2N, Worst: N * N|
|출력|N * log2N|N|N|

⬇️ 유저가 10000명이고 100등까지 출력한다고 가정하면?
| 복잡도/자료구조 | Heap | Sorted Array | Binary Search Tree |
|:--:|:--:|:--:|:--:|
|입력|10000 * log10000|10000 * 10000|Best: 10000 * log10000, Worst: 10000 * 10000|
|출력|100 * log100|100|100|

⬆️ 출력의 단점보다 입력의 효율을 높게 평가하여 다른 자료구조가 아닌 Heap을 선정했습니다.


## 4. 전체 구조도
![13](https://user-images.githubusercontent.com/26649774/99925660-4ca7dd00-2d82-11eb-956e-c81fb3e108a1.png)

## 5. ADT

### 5.1. Class VocaType
```
Member Function
    VocaType(); 
    int GetId(); 
    string GetEnglish(); 
    string GetKorean(); 
    double GetCorrect();
    double GetWrong();
    double GetCorrectPercent();
    void PlusCorrect();
    void PlusWrong();
    void SetId(int id); 
    void SetEnglish(string english); 
    void SetKorean(string korean); 
    void SetVoca(int id, string english, string korean);
    void SetIdFromKB();
    void SetEnglishFromKB(); 
    void SetKoreanFromKB(); 
    void SetVocaFromKB(); 
    void DisplayId(); 
    void DisplayEnglish(); 
    void DisplayKorean(); 
    void DisplayVoca(); 
    void DisplayCorrectPercent();
    bool operator<(const VocaType& voca); 
    bool operator>(const VocaType& voca); 
    bool operator==(const VocaType& voca); 
    int ReadDataFromFile(ifstream& fin); 
    int WriteDataToFile(ofstream& fout); 
Member Variables
    int m_id; 
    string m_english; 
    string m_korean; 
    double m_correct;
    double m_wrong;
```

### 5.2. Class Application
```
Member Function
    Application();
    void Run();
    void LogIn();
    int GetCommand();
    int GetCommandLogIn();
    int GetCommandManageUser();
    int VerifyLogIn();
    void LogOut();
    void CreateUser();
    void DeleteUser();
    void CheckAllUser();
    void EditUser();
    void ShowRanker();
    void CheckMyInfo();
    void EditMyInfo();
    void SearchVoca();
    void TestVoca();
    void LearnVoca();
    int GetCommandLearnLevel();
    void SetLearnList(int level);
    int ExecuteLearn();
    void ManageMyVocaList(); 
    int GetCommandMyVocaList();
    void AddMyVoca();
    void DeleteMyVoca();
    void InitWordBook();
Member Variables
    int m_command;
    SortedArrayList<VocaType> m_AllVocaList;
    SortedArrayList<SimpleVocaType> m_AllSimpleList;
    StackType<SimpleVocaType> m_TestVocaList;
    Queue<SimpleVocaType> m_LearnVocaList;
    ifstream m_InFile;
    ofstream m_OutFile;
    UnsortedLinkedList<UserType> m_AllUserList;
    SortedArrayList<SimpleUserType2> m_AllSimpleUList;
    UserType* m_curUser;
```

### 5.3. Class UserType
```
Member Function
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
Member Variables
    string m_id; // User Id
    string m_name; // User name
    string m_password; // User password
    string m_recentLoginTime;
    int m_testScore; // word test score
    int m_learnLevel;
    SortedLinkedListType<SimpleVocaType> m_MyVocaList;
    Queue<SimpleVocaType> m_recentSearchList;
    int m_status; //User permission
```

### 5.4. Class UnsortedLinkedListType
```
Member Function
    UnsortedLinkedList(); 
    UnsortedLinkedList(const UnsortedLinkedList<T>& u_l); 
    ~UnsortedLinkedList(); 
    int Insert(T& data); 
    int Delete(T& data);
    void Replace(const T& data);
    void MakeEmpty(); 
    int GetLength(); 
    bool IsFull(); 
    bool IsEmpty(); 
    int Get(T data); 
    void GetNext(T& data); 
    void ResetList(); 
    UnsortedLinkedList<T>& operator= (const UnsortedLinkedList<T> & u_l);
    T* GetCurPtr();
Member Variables
    int m_Length; 
    SinglyNodeType<T>* m_List; 
    SinglyNodeType<T>* m_curPos;
```

### 5.5. Class StackType
```
Member Function
    StackType()
    int push(T& voca)
    int pop(T& voca)
    bool isFull() 
    bool isEmpty()
    int getLength() 
    void MakeEmpty()
Member Variables
    T m_TestVocaList[MAX_SIZE];
    int m_top;
    int m_length;
```

### 5.6. Class SortedLinkedListType
```
Member Function
    SortedLinkedListType();
    ~SortedLinkedListType();
    SortedLinkedListType(const SortedLinkedListType& list);
    int Insert(T& data);
    int Delete(T& data);
    void Replace(const T& data);
    void MakeEmpty();
    NodeType<T>* GetNext(T& data);
    NodeType<T>* GetPre(T& data);
    void ResetList();
    void ResetListForGetPre();
    int GetLength();
    bool isEmpty();
    bool isFull();
    int Get(T& data);
    int CheckBack(T& data);
    int InsertTail(T& data);
    int DeleteTail(T& data);
    T* GetCurPtr();
    SortedLinkedListType<T>& operator=(const SortedLinkedListType<T>& list);
Member Variables
    NodeType<T>* m_head;
    NodeType<T>* m_tail;
    NodeType<T>* m_curPtr; 
    int m_length;
```

### 5.7. Class QueueType
```
Member Function
    Queue();
    int GetLength();
    void enQueue(T& voca);
    int deQueue(T& voca);
    bool isFull();
    bool isEmpty();
    void MakeEmpty(); 
    void ResizeQueue(int i);
Member Variables
    T* m_LearnVocaList;
    int m_iFront;
    int m_iRear;
    int m_length;
    int m_MaxSize;
```

### 5.8. Class SimpleUserType
```
Member Function
    SimpleUserType()
    void SetPtr(UserType* user)
    UserType* GetPtr()
    bool operator<(SimpleUserType& s)
    bool operator>(SimpleUserType& s) 
    bool operator==(SimpleUserType& s)
    bool operator<=(SimpleUserType& s)
Member Variables
    UserType* m_user;
```

### 5.9. Class SimpleUserType2
```
Member Function
    SimpleUserType2()
    void SetPtr(UserType* user)
    UserType* GetPtr()
    bool operator<(SimpleUserType2& s)     
    bool operator>(SimpleUserType2& s)
    bool operator==(SimpleUserType2& s)
Member Variables
    UserType* m_user;
```

### 5.10. Class SortedArrayListType
```
Member Function
    SortedArrayList();
    SortedArrayList(const SortedArrayList<T>& s_l);
    ~SortedArrayList();
    int GetNext(T& data);
    int ResetList();
    int Get(T& data);
    int Insert(T& data);
    int Delete(T& data);
    T* GetCurPtr();
    T GetIndexOfData(int i);
    int GetLength();
    bool isEmpty();
    bool isFull();
    void MakeEmpty();
    void ExpandSize();
    void ReduceSize();
    SortedArrayList<T>& operator=(const SortedArrayList<T>& s_l);
Member Variables
    T* m_List;                   
    int m_maxsize;               
    int m_curPos;
    int m_length;
```

### 5.11. Class MaxHeap
```
Member Function
    MaxHeap();
    MaxHeap(int size);
    ~MaxHeap() ;
    bool IsEmpty();
    bool IsFull();
    int GetLength() const;
    void MakeEmpty();
    int Add(T item); 
    int Delete(T item); 
    T Pop(); 
    void RetrieveItem(T& item, bool& found); 
    void PrintHeap(ostream& os);
    void ReheapDown(int iparent, int ibottom); 
    void ReheapUp(int iroot, int ibottom); 
    void Delete(T item, bool& found, int iparent);
    void Retrieve(T& item, bool& found, int iparent);
Member Variables
    T* m_pHeap;
    int m_iLastNode;
    int m_nMaxSize;
```