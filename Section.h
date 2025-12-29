#ifndef SECTION_H
#define SECTION_H

#include<string>
#include<vector>
#include"Employee.h"
using namespace std;
class Section{
    Employee* head;
    Employee* end;
    int num;//存储科室的总人数
    double sum;//存储科室的总工资
public:
    Section():head(nullptr),end(nullptr),num(0),sum(0){}
    ~Section();
    void SecAddEmployee(Employee* p);//添加职工，传入指向目标节点的指针
    void SecDeleteEmployeeById(Employee* ptr);//根据工号删除职工
    void SecMondifyEmployeeById(Employee* ptr,string n,string s,string i,string p,string sec,double sal);//根据工号修改职工

    Employee* SecFindEmployeeById(string Id);//根据工号查找职工
    vector<Employee*> SecFindEmployeeByName(string Name);//根据姓名查找职工
    Employee* SecFindEmployeeByPhone(string phone);//判断电话号码是否重复

    void SecGetAllEmployee();//获取所有的员工
    vector<Employee*> GetAllEmployee();

    int GetNum();//获取职工数量
    double GetSum();//获取职工工资总和
};

#endif // SECTION_H