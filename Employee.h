#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include<string>
using namespace std;
struct Employee{
    string name;
    string sex;
    string id;
    string phone;
    string section;
    double salary;
    Employee* next; 
    Employee(string n,string s,string i,string p,string sec,double sal)
        :name(n),sex(s),id(i),phone(p),section(sec),salary(sal),next(nullptr){}
};

#endif // EMPLOYEE_H