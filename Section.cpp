#include"Section.h"
#include<iostream>
#include<iomanip>
using namespace std;

Section::~Section(){
    try{
        Employee* current=head;
        while(current!=nullptr){
            Employee* next=current->next;
            delete current;
            current=next;
        }
        head=nullptr;
        end=nullptr;
        num=0;
        sum=0;
    }
    catch(...){
        cerr<<"警告：科室析构过程中发生错误"<<endl;
    }
}

void Section::SecAddEmployee(Employee* p){//添加职工，传入指向目标节点的指针
    if(head==nullptr){
        head=p;
        end=p;
    }
    else{
        end->next=p;
        end=p;
    }
    num++;
    sum+=p->salary;
}

void Section::SecDeleteEmployeeById(Employee* p){//根据工号删除职工，传入指向目标节点的指针
    if(p==head){//目标节点为头指针
        num--;
        sum-=head->salary;
        if(num==0){
            delete head;
            head=nullptr;
            end=nullptr;
            return;
        }
        head=head->next;
        delete p;
        return;
    }
    if(p==end){//目标节点为尾指针
        Employee* ptr=head;
        while(ptr->next!=end){
            ptr=ptr->next;
        }
        num--;
        sum-=end->salary;
        delete end;
        end=ptr;
        end->next=nullptr;
        return;
    }
    //其他情况
    Employee* ptr=head;
    while(ptr->next!=p){
        ptr=ptr->next;
    }
    num--;
    sum-=p->salary;
    ptr->next=p->next;
    delete p;
    return;
}

void Section::SecMondifyEmployeeById(Employee* ptr,string n,string s,string i,string p,string sec,double sal){//根据工号修改职工
    ptr->name=n;
    ptr->sex=s;
    ptr->id=i;
    ptr->phone=p;
    ptr->salary=sal;
    cout<<"修改成功!"<<endl;
}

Employee* Section::SecFindEmployeeById(string Id){//根据工号查找职工,如果职工存在返回指向它的指针，不存在返回空指针
    Employee* p=head;
    while(p!=nullptr){
        if(p->id==Id){
            return p;
        }
        p=p->next;
    }
    return nullptr;
}

vector<Employee*> Section::SecFindEmployeeByName(string Name){//根据姓名查找职工，如果职工存在返回指向它的指针，不存在返回空指针
    vector<Employee*> result;
    Employee* p=head;
    while(p!=nullptr){
        if(p->name==Name) result.push_back(p);
        p=p->next;
    }
    return result;
}

Employee* Section::SecFindEmployeeByPhone(string phone){//找到了返回指向目标的指针，没找到返回空指针
    Employee* p=head;
    while(p!=nullptr){
        if(p->phone==phone){
            return p;
        }
        p=p->next;
    }
    return nullptr;
}

void Section::SecGetAllEmployee(){//获取所有的员工
    if(num==0){
        cout<<"该科室无员工"<<endl;
        return;
    }
    Employee* p=head;
    cout<<setw(14)<<left<<"姓名"<<setw(12)<<left<<"性别"<<setw(20)<<left<<"工号"<<setw(20)<<left<<"电话"<<setw(20)<<left<<"科室"<<setw(15)<<left<<"工资"<<endl;
    while(p!=nullptr){
        cout<<setw(12)<<left<<p->name<<setw(10)<<left<<p->sex<<setw(18)<<left<<p->id<<setw(18)<<left<<p->phone<<setw(18)<<left<<p->section<<setw(10)<<left<<p->salary<<endl;
        p=p->next;
    }
}

vector<Employee*> Section::GetAllEmployee(){//创建包含所有员工的vector
    vector<Employee*> result;
    Employee* p=head;
    while(p!=nullptr){
        result.push_back(p);
        p=p->next;
    }
    return result;
}

int Section::GetNum(){
    return num;
}

double Section::GetSum(){
    return sum;
}