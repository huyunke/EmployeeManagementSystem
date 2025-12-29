//部门名称不区分大小写
#include<iostream>
#include<fstream>
#include"EmployeeManagementSystem.h"
using namespace std;

void menu2(){//打印查询菜单
    cout<<"===========查询职工信息=============="<<endl;
    cout<<"查询完毕请按0并回车来返回上一级菜单"<<endl;
    cout<<"根据工号查询(输入1跳转)"<<endl;
    cout<<"根据姓名、科室查询(输入2跳转)"<<endl;
    cout<<"查询科室所有职工信息(输入3跳转)"<<endl;
    cout<<"查询各个科室的平均工资(输入4跳转)"<<endl;
    cout<<"返回上一级(输入0跳转)"<<endl;
    cout<<"====================================="<<endl;
    cout<<"请输入查询方式[0-4]:";
}

void menu(){//打印主菜单
    cout<<"================主菜单==============="<<endl;
    cout<<"输入数字跳转对应菜单"<<endl;
    cout<<"·添加职工信息(输入1跳转)"<<endl;
    cout<<"·查询职工信息(输入2跳转)"<<endl;
    cout<<"·获取职工的工资排序(输入3跳转)"<<endl;
    cout<<"·修改职工信息(输入4跳转)"<<endl;
    cout<<"·删除职工信息(输入5跳转)"<<endl;
    cout<<"·退出系统(输入0跳转)"<<endl;
    cout<<"====================================="<<endl;
    cout<<"请输入选项[0-5]:";
}

int main(){
    try{
        EmployeeManagementSystem EMSE;
        try{
            EMSE.LoadFromFiles();//加载数据
        }
        catch(const exception& e){
            cerr<<"加载数据时出错："<<e.what()<<endl;
            cerr<<"系统将使用空数据启动"<<endl;
        }
        menu();//打印主菜单
        int num;
        while(cin>>num){
            try{
                if(num==0) break;
                switch(num){
                    case 1:{//添加职工
                        cout<<"==========添加职工信息========="<<endl;
                        cout<<"输入完毕请按0并回车来返回上一级菜单"<<endl;
                        cout<<"请输入职工姓名:";
                        string name;
                        while(cin>>name){
                            if(name=="0") break;
                            cout<<"请输入职工性别(female/male):";
                            string sex;
                            cin>>sex;
                            cout<<"请输入职工工号（12位数字）:";
                            string id;
                            cin>>id;
                            cout<<"请输入职工电话（11位数字）:";
                            string phone;
                            cin>>phone;
                            cout<<"请输入职工科室:";
                            string section;
                            cin>>section;
                            cout<<"请输入职工工资:";
                            double salary;
                            cin>>salary;
                            if(salary<=0){
                                cout<<"工资不能小于等于0！请重新输入"<<endl;
                                cout<<"请输入职工姓名:";
                                continue;
                            }
                            if(!EMSE.checkSex(sex)){//校验性别
                                cout<<"性别输入不符合规范(应该输入:female/male)！请重新输入"<<endl;
                                cout<<"请输入职工姓名:";
                                continue;
                            }
                            if(!EMSE.checkId(id)){//校验工号
                                cout<<"该工号不符合规范！请重新输入"<<endl;
                                cout<<"请输入职工姓名:";
                                continue;
                            }
                            if(EMSE.FindEmployeeById1(id)){//判断工号是否重复
                                cout<<"该工号已存在！请重新输入"<<endl;
                                cout<<"请输入职工姓名:";
                                continue;
                            }
                            if(!EMSE.checkPhone(phone)){//校验电话号码
                                cout<<"该电话号码不符合规范！请重新输入"<<endl;
                                cout<<"请输入职工姓名:";
                                continue;
                            }
                            if(EMSE.FindEmployeeByPhone(phone)){//判断电话号码是否重复
                                cout<<"该电话号码已存在！请重新输入"<<endl;
                                cout<<"请输入职工姓名:";
                                continue;
                            }
                            EMSE.AddEmployee(name,sex,id,phone,section,salary);//添加职工
                            cout<<"请输入职工姓名:";
                        }
                        cout<<"添加职工信息完毕!自动返回上一级菜单"<<endl;
                        cout<<"=============================="<<endl;
                        break;
                    }
                    case 2:{//查询职工信息
                        menu2();//打印查询菜单
                        int num2;
                        while(cin>>num2){
                            if(num2==0) break;
                            switch(num2){
                                case 1:{//根据工号查询
                                    cout<<"查询完毕请按0并回车来返回上一级菜单"<<endl;
                                    cout<<"请输入职工工号:";
                                    string id;
                                    while(cin>>id){
                                        if(id=="0") break;
                                        EMSE.FindEmployeeById(id);//根据工号查找职工，输出该职工的所有信息
                                        cout<<"请输入职工工号:";
                                    }
                                    break;
                                }
                                case 2:{//根据姓名、科室查询
                                    cout<<"查询完毕请按0并回车来返回上一级菜单"<<endl;
                                    cout<<"请输入职工姓名:";
                                    string name;
                                    while(cin>>name){
                                        if(name=="0") break;
                                        cout<<"请输入职工科室:";
                                        string section;
                                        cin>>section;
                                        EMSE.FindEmployeeByNameAndSection(name,section);//根据姓名、科室查询职工信息,输出该职工的所有信息
                                        cout<<"请输入职工姓名:";
                                    }
                                    break;
                                }
                                case 3:{//查询科室所有职工信息
                                    cout<<"查询完毕请按0并回车来返回上一级菜单"<<endl;
                                    cout<<"请输入想要查询的科室：";
                                    string section;
                                    while(cin>>section){
                                        if(section=="0") break;
                                        EMSE.GetEmployeeInSection(section);//输出某一科室的所有职工
                                        cout<<"请输入想要查询的科室：";
                                    }
                                    break;
                                }
                                case 4:{//查询各个科室的平均工资
                                    EMSE.AveSalary();
                                    cout<<"成功获取各科室的平均工资，已自动返回上一级菜单"<<endl;
                                    break;
                                }
                                default:{
                                    cout<<"输入指令有误，请重新输入!"<<endl;
                                    break;
                                }
                            }
                            menu2();//打印查询菜单
                        }
                        break;
                    }
                    case 3:{
                        cout<<"==================================职工工资排序=================================="<<endl;
                        EMSE.Sort();
                        cout<<"==============================================================================="<<endl;
                        break;
                    } 
                    case 4:{
                        cout<<"修改完毕请按0并回车来返回上一级菜单"<<endl;
                        cout<<"请输入职工工号：";
                        string id;
                        while(cin>>id){
                            if(id=="0") break;
                            EMSE.ModifyEmployeeById(id);
                            cout<<"请输入职工工号：";
                        }
                        break;
                    }
                    case 5:{
                        cout<<"删除完毕请按0并回车来返回上一级菜单"<<endl;
                        cout<<"请输入职工工号：";
                        string id;
                        while(cin>>id){
                            if(id=="0") break;
                            EMSE.DeleteEmployeeById(id);
                            cout<<"请输入职工工号：";
                        }
                        break;
                    }
                    default:{
                        cout<<"输入指令有误，请重新输入!"<<endl;
                        break;
                    }
                }
            }
            catch(const exception& e){
                cerr<<"操作过程中出现错误"<<e.what()<<endl;
                cerr<<"请重新选择操作"<<endl;
            }
            menu();
        }
        try{
            EMSE.SaveToFile();//退出系统前把科室名称保存到文件中
        }
        catch(const exception& e){
            cerr<<"保存数据时出错："<<e.what()<<endl;
            cerr<<"部分或全部数据可能未保存"<<endl;
            return 1;
        }
        return 0;
    }
    catch(const exception& e){
        cerr<<"系统发生严重错误："<<e.what()<<endl;
        cerr<<"程序将退出"<<endl;
        return 1;
    }
    catch(...){
        cerr<<"系统发生未知严重错误"<<endl;
        cerr<<"程序将退出"<<endl;
        return 1;
    }
}