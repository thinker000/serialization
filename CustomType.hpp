#pragma once
#include <string>
#include "serializable.hpp"
using namespace HW::SERIALIZE;

class A: public Serializable
{
public:
    A(){}
    A(const int& age,const std::string name, const char& gender)
        :m_age(age),m_name(name),m_gender(gender){ };
    A(const A& val){
        m_age = val.m_age;
        m_name = val.m_name;
        m_gender = val.m_gender;
    };
    void show() const
    {
        std::cout<<m_age<<" "<<m_name<<" "<<m_gender<<std::endl;
    }
    ~A(){};
    SERIALIZE_OR_UNSERIALIZE(m_age,m_name,m_gender)
private:
    int m_age;
    std::string m_name;
    char m_gender;
};