#ifndef EMPLOYEEMANAGEMENTSYSTEM_H
#define EMPLOYEEMANAGEMENTSYSTEM_H

#include<string>
#include<map>
#include"Section.h"
using namespace std;
class EmployeeManagementSystem
{
    map<string,Section> Sections;
    string GetSectionFilePath(const string&section) const{
        return section+".txt";
    }
public:
    void AddEmployee(string n,string s,string i,string p,string sec,double sal);//添加职工
    void DeleteEmployeeById(string id);//根据工号删除职工

    void FindEmployeeById(string id);//根据工号查找职工,输出该职工的所有信息
    bool FindEmployeeById1(string id);//根据工号查找职工,找到返回true
    bool FindEmployeeByPhone(string newphone);//判断电话号码是否重复
    void FindEmployeeByNameAndSection(string name,string section);//根据姓名、科室查询职工信息,输出该职工的所有信息
    
    void ModifyEmployeeById(string id);//根据工号修改职工
    void ModifyAddEmployee(string name,string sex,string Id,string phone,string sec,double sal);//修改职工科室后，添加职工
    
    void GetEmployeeInSection(string section);//输出某一科室的所有职工
    vector<Employee*> GetAllEmployee();
   
    void AveSalary();//计算各科室的平均工资
    void Sort();//根据职工的工资排序
    static bool cmp(Employee* p1,Employee* p2);//比较函数
    void QuickSort(vector<Employee*> &arr,bool(*compare)(Employee*,Employee*));//自定义快速排序函数
    
    void AddEmployeeToFile(const Employee* p);//将职工信息添加到文件
    void RemoveEmployeeFromFile(const Employee* p);//将职工信息从文件中删除
    void ModifyEmployeeInFile(const Employee* p,string oldid);//修改文件中的职工信息（没有修改科室）
    void SaveToFile();//退出系统前把科室名称，科室对应的人数，科室的总工资保存到文件中
    void LoadFromFiles();//重启系统后加载数据，防止系统关闭后，所有数据丢失

    void PrintEmployeeInfo(Employee* p);//通用打印职工函数
    void PrintTableHeader();//通用打印表头函数
    string toLower(string& str);//统一科室名称为小写
    bool checkPhone(string phone);//校验电话号码
    bool checkId(string id);//校验工号
    bool checkSex(string sex);//校验性别
};

#endif // EMPLOYEEMANAGEMENTSYSTEM_H