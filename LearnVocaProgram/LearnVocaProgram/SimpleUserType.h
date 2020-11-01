#pragma once
#include <iostream>
#include "User.h"
using namespace std;


class SimpleUserType {
public:
    SimpleUserType() {
        m_user = nullptr;
    }

    void SetPtr(UserType* user) {
        m_user = user;
    }
    UserType* GetPtr() const {
        return m_user;
    }

    bool operator<(const SimpleUserType& s) {
        return(GetPtr()->GetTestScore() < s.GetPtr()->GetTestScore());
    }
    bool operator>(const SimpleUserType& s) {
        return(GetPtr()->GetTestScore() > s.GetPtr()->GetTestScore());
    }
    bool operator==(const SimpleUserType& s) {
        return(GetPtr()->GetTestScore() == s.GetPtr()->GetTestScore());
    }
    bool operator<=(const SimpleUserType& s) {
        return(GetPtr()->GetTestScore() <= s.GetPtr()->GetTestScore());
    }

private:
    UserType* m_user;
};
