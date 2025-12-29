#include"EmployeeManagementSystem.h"
#include <cctype>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;

void EmployeeManagementSystem::AddEmployee(string n,string s,string i,string p,string sec,double sal){//添加职工
    sec=toLower(sec);//统一科室为小写
    Employee* ptr=new Employee(n,s,i,p,sec,sal);//创建职工节点
    Sections[sec].SecAddEmployee(ptr);//添加职工
    AddEmployeeToFile(ptr);//将职工信息添加到文件
}

void EmployeeManagementSystem::DeleteEmployeeById(string id){//根据工号删除职工
    for (auto& pair : Sections) {
        Employee* p=pair.second.SecFindEmployeeById(id);//p指向目标节点
        if(p!=nullptr){
            cout<<"已经成功删除职工："<<p->name<<endl;
            RemoveEmployeeFromFile(p);//从文件中移除职工信息
            pair.second.SecDeleteEmployeeById(p);//删除职工对应的节点
            return;
        }
    }
    cout<<"该职工不存在"<<endl;
}

void EmployeeManagementSystem::FindEmployeeById(string id){//根据工号查找职工
    for(auto& pair:Sections){
        Employee* p=pair.second.SecFindEmployeeById(id);//SecFindEmployeeById(id)如果职工存在返回指向它的指针，不存在返回空指针
        if(p!=nullptr){
            PrintTableHeader();//打印表头
            PrintEmployeeInfo(p);//打印职工信息
            return;
        }
    }
    cout<<"该职工不存在！"<<endl;
}

bool EmployeeManagementSystem::FindEmployeeById1(string id){//判断工号是否重复
    for(auto& pair:Sections){
        Employee* p=pair.second.SecFindEmployeeById(id);//如果职工存在返回指向它的指针
        if(p!=nullptr){
            return true;
        }
    }
    return false;
}

bool EmployeeManagementSystem::FindEmployeeByPhone(string phone){//判断电话号码是否重复
    for(auto& pair:Sections){
        Employee* p=pair.second.SecFindEmployeeByPhone(phone);//如果电话号码存在返回指向它的指针
        if(p!=nullptr){
            return true;
        }
    }
    return false;
}

void EmployeeManagementSystem::FindEmployeeByNameAndSection(string name,string section){//根据姓名、科室查询职工信息
    bool flag=false;
    for(auto& pair:Sections){//判断科室是否存在
        if(pair.first==section){
            flag=true;
            break;
        }
    }
    if(!flag){
        cout<<"该科室不存在"<<endl;
        return;
    }
    vector<Employee*> p;
    p=Sections[section].SecFindEmployeeByName(name);//根据姓名查找职工，存在返回指向它的指针，不存在返回空指针
    if(!p.empty()){
        PrintTableHeader();//打印表头
        for(int i=0;i<p.size();i++){
            PrintEmployeeInfo(p[i]);//打印职工信息
        }
        return;
    }
    cout<<"查询不到该职工"<<endl;
}

void EmployeeManagementSystem::ModifyEmployeeById(string id){//根据工号修改职工
    for(auto& pair : Sections) {
        Employee* p=pair.second.SecFindEmployeeById(id);//p指向要目标节点
        if(p!=nullptr){
            string n;
            string s;
            string Id;
            string phone;
            string sec;
            double sal;
            cout<<"请输入更改后的信息(如果不想修改某个信息，输入0即可):"<<endl;
            cout<<"姓名:";
            while(cin>>n){
                try{
                    cout<<"性别:";
                    cin>>s;
                    cout<<"工号:";
                    cin>>Id;
                    cout<<"电话号码:";
                    cin>>phone;
                    cout<<"科室:";
                    cin>>sec;
                    sec=toLower(sec);
                    cout<<"工资:";
                    cin>>sal;

                    //存储旧数据
                    string oldname=p->name;
                    string oldsex=p->sex;
                    string oldsec=p->section;
                    string oldid=p->id;
                    string oldphone=p->phone;
                    double oldsal=p->salary;

                    //处理不修改的情况
                    if(n=="0") n=oldname;
                    if(s=="0") s=oldsex;
                    if(Id=="0") Id=oldid;
                    if(phone=="0") phone=oldphone;
                    if(sec=="0") sec=oldsec;
                    if(sal==0) sal=oldsal;

                    //数据校验
                    if(sal<=0){
                        throw invalid_argument("工资不能小于或等于0!");
                    }
                    if(!checkPhone(phone)){//校验电话号码
                        throw invalid_argument("电话号码不符合规范!");
                    }
                    if(!checkId(Id)){//校验职工工号
                        throw invalid_argument("工号不符合规范！");
                    }
                    if(!checkSex(s)){//校验性别
                        throw invalid_argument("性别输入不符合规范(应该输入:female/male)！");
                    }
                    if(Id!=p->id&&FindEmployeeById1(Id)){//检查工号是否重复
                        throw invalid_argument("该工号已存在!");
                    }
                    if(phone!=p->phone&&FindEmployeeByPhone(phone)){//检查电话号码是否重复
                        throw invalid_argument("该电话号码已存在！");
                    }
                    if(oldsec==sec){//如果科室没更改
                        pair.second.SecMondifyEmployeeById(p,n,s,Id,phone,sec,sal);
                        ModifyEmployeeInFile(p,oldid);//更新文件
                        return;
                    }
                    else{//如果科室更改了
                        RemoveEmployeeFromFile(p);//先把职工从文件中移除
                        pair.second.SecDeleteEmployeeById(p);//再把职工对应的节点删除
                        ModifyAddEmployee(n,s,Id,phone,sec,sal);//更新文件
                        return;
                    }
                }
                catch(const exception& e){
                    cerr<<"错误："<<e.what()<<"请重新输入"<<endl;
                    cout<<"请重新输入更改后的信息："<<endl;
                    cout<<"姓名:";
                }
            }
        }
    }
    cout<<"该职工不存在!"<<endl;
}

void EmployeeManagementSystem::ModifyAddEmployee(string name,string sex,string Id,string phone,string sec,double sal){
    Employee* ptr=new Employee(name,sex,Id,phone,sec,sal);
    Sections[sec].SecAddEmployee(ptr);
    AddEmployeeToFile(ptr);
}

void EmployeeManagementSystem::GetEmployeeInSection(string section){//输出某一科室的所有职工
    for (auto& pair : Sections) {
        if(pair.first==section){
            pair.second.SecGetAllEmployee();//输出科室的所有职工
            return;
        }
    }
    cout<<"该科室不存在！"<<endl;
}

vector<Employee*> EmployeeManagementSystem::GetAllEmployee(){//创建包含整个系统职工的vector
    vector<Employee*> result;
    for (auto& pair : Sections) {
        vector<Employee*> temp=pair.second.GetAllEmployee();
        result.insert(result.end(),temp.begin(),temp.end());
    }
    return result;
}

void EmployeeManagementSystem::AveSalary(){//计算各科室的平均工资
    for (auto& pair : Sections) {
        if(pair.second.GetNum()==0){
            cout<<pair.first<<"的平均工资为：0"<<endl;
            continue;
        }
        cout<<pair.first<<"的平均工资为："<<pair.second.GetSum()/pair.second.GetNum()<<endl;
    }
}

void EmployeeManagementSystem::Sort(){//输出职工工资的排序
    vector<Employee*> result=GetAllEmployee();//GetAllEmployee()创建包含整个系统职工的vector
    QuickSort(result,EmployeeManagementSystem::cmp);
    PrintTableHeader();//打印表头
    for(int i=result.size()-1;i>=0;i--){
        Employee* p=result[i];
        PrintEmployeeInfo(p);//打印职工信息
    }
}

bool EmployeeManagementSystem::cmp(Employee* p1,Employee* p2){//根据工资从小到大排序，工资相等时根据姓名从大到小排序
    if(p1->salary>p2->salary) return false;
    if(p1->salary<p2->salary) return true;
    return p1->name<p2->name;
}

void EmployeeManagementSystem::AddEmployeeToFile(const Employee* p){//将职工信息添加到文件
    string sectionFile=GetSectionFilePath(p->section);//GetSectionFilePath(section)返回对应section的文件名
    ofstream outFile(sectionFile,ios::app);
    if(!outFile){
        cout<<"无法打开文件"<<sectionFile<<"进行写入！"<<endl;
        return;
    }
    outFile<<p->name<<" "<<p->sex<<" "<<p->id<<" "<<p->phone<<" "<<p->section<<" "<<p->salary<<endl;
    outFile.close();
}

void EmployeeManagementSystem::RemoveEmployeeFromFile(const Employee* ptr){//将职工信息从文件中删除，传入的参数是指向目标节点的指针
    string sectionFile=GetSectionFilePath(ptr->section);//GetSectionFilePath(section)返回对应section的文件名
    ifstream inFile(sectionFile);
    if(!inFile){
        cout<<"无法打开文件"<<sectionFile<<"进行读取！"<<endl;
        return;
    }
    vector<string> lines;
    string line;
    while(getline(inFile,line)){
        stringstream ss(line);
        string name,sex,id,phone,section;
        double salary;
        ss>>name>>sex>>id>>phone>>section;
        if(id!=ptr->id){
            lines.push_back(line);
        }
    }
    inFile.close();
    ofstream outFile(sectionFile);
    if(!outFile){
        cout<<"文件"<<sectionFile<<"保存失败"<<endl;
        return;
    }
    for(int i=0;i<lines.size();i++){
        outFile<<lines[i]<<endl;
    }
    outFile.close();
}

void EmployeeManagementSystem::ModifyEmployeeInFile(const Employee* p,string oldid){//修改文件中的职工信息（没有修改科室）,传入的参数是指向目标节点的指针
    string sectionFile=GetSectionFilePath(p->section);//GetSectionFilePath(section)返回对应section的文件名
    ifstream inFile(sectionFile);
    if(!inFile){
        cout<<"无法打开文件"<<sectionFile<<"进行读取！"<<endl;
        return;
    }
    vector<string> lines;
    string line;
    while(getline(inFile,line)){
        stringstream ss(line);
        string name,sex,id,phone,section;
        double salary;
        ss>>name>>sex>>id>>phone>>section>>salary;
        if(id!=oldid){
            lines.push_back(line);
        }
        else{
            stringstream newLine;
            newLine<<p->name<<" "<<p->sex<<" "<<p->id<<" "<<p->phone<<" "<<p->section<<" "<<p->salary;
            lines.push_back(newLine.str());
        }
    }
    inFile.close();
    ofstream outFile(sectionFile);
    if(!outFile){
        cout<<"文件"<<sectionFile<<"保存失败"<<endl;
        return;
    }
    for(int i=0;i<lines.size();i++){
        outFile<<lines[i]<<endl;
    }
    outFile.close();
}

void EmployeeManagementSystem::SaveToFile(){//退出系统前把科室名称，科室对应的人数，科室的总工资保存到文件中
    vector<string> section_name;
    for (auto& pair : Sections) {
        if(pair.second.GetNum()==0){//科室人数为0时，不存储
            continue;
        }
        section_name.push_back(pair.first);//存储科室名称
    }
    ofstream outFile("sections.txt");
    if(!outFile){
        cout<<"文件sections.txt打开失败!"<<endl;
        return;
    }
    for(int i=0;i<section_name.size();i++){
        outFile<<section_name[i]<<endl;
    }
    outFile.close();
}

void EmployeeManagementSystem::LoadFromFiles(){//加载数据
    ifstream inFile("sections.txt");
    if(!inFile){
        throw runtime_error("无法打开文件sections.txt进行读取!");
    }
    string line;
    while(getline(inFile,line)){
        string section;
        stringstream ss(line);
        ss>>section;
        string sectionFile=GetSectionFilePath(section);//GetSectionFilePath(section)返回对应section的文件名
        try{
            ifstream inSectionFile(sectionFile);
            if(!inSectionFile){
                throw runtime_error("无法打开文件"+sectionFile+"进行读取!");
            }
            string sectionline;
            while(getline(inSectionFile,sectionline)){
                stringstream s(sectionline);
                string name,sex,id,phone,sec;
                double salary;
                if(!(s>>name>>sex>>id>>phone>>sec>>salary)){
                    cerr<<"警告：文件"<<sectionFile<<"中存在格式错误的行，已自动跳过该行！"<<endl;
                    continue;
                }
                Employee* p=new Employee(name,sex,id,phone,sec,salary);//创建职工节点
                Sections[section].SecAddEmployee(p);//添加职工到相应的科室
            }
            inSectionFile.close();
        }
        catch(const exception& e){
            cerr<<"读取科室文件时出错："<<e.what()<<endl;
            cerr<<"系统将继续加载其他科室数据"<<endl;
        }
    }
    inFile.close();
    cout<<"数据加载完毕"<<endl;
}

void EmployeeManagementSystem::PrintTableHeader(){//通用打印表头函数
    cout<<setw(14)<<left<<"姓名"<<setw(12)<<left<<"性别"<<setw(20)<<left<<"工号"<<setw(20)<<left<<"电话"<<setw(20)<<left<<"科室"<<setw(15)<<left<<"工资"<<endl;
}

void EmployeeManagementSystem::PrintEmployeeInfo(Employee* p){//通用打印职工函数
    cout<<setw(12)<<left<<p->name<<setw(10)<<left<<p->sex<<setw(18)<<left<<p->id<<setw(18)<<left<<p->phone<<setw(18)<<left<<p->section<<setw(10)<<left<<p->salary<<endl;
}

string EmployeeManagementSystem::toLower(string& str){//统一科室为小写
    string result=str;
    int len=str.length();
    for(int i=0;i<len;i++){
        if(result[i]>='A'&&result[i]<='Z'){
            result[i]+=32;
        }
    }
    return result;
}

bool EmployeeManagementSystem::checkPhone(string phone){//校验电话号码，如果电话号码不符合规范返回false
    int len=phone.length();
    if(len!=11) return false;//电话号码长度不为11位
    for(int i=0;i<len;i++){
        if(phone[i]<='9'&&phone[i]>='0'){
            continue;
        }
        else return false;
    }
    return true;
}

bool EmployeeManagementSystem::checkId(string id){//校验职工工号，如果职工工号不符合规范返回false
    int len=id.length();
    if(len!=12) return false;//工号长度不为12位
    for(int i=0;i<len;i++){
        if(id[i]<='9'&&id[i]>='0'){
            continue;
        }
        else return false;
    }
    return true;
}

bool EmployeeManagementSystem::checkSex(string sex){//校验性别，如果性别不符合规范返回false
    if(sex=="male"||sex=="female") return true;
    else return false;
}

int part(vector<Employee*>& arr,int low,int high,bool(*compare)(Employee*,Employee*)){//自定义快速排序函数的分区函数
    Employee* base=arr[high];
    int i=low-1;
    for(int j=low;j<high;j++){
        if(compare(arr[j],base)){
            i++;
            if(i==j){
                continue;
            }
            else{
                Employee* temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    Employee* temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;
    return i+1;
}

void quickSort(vector<Employee*>& arr,int low,int high,bool(*compare)(Employee*,Employee*)){//自定义快速排序函数的递归实现
    if(low<high){
        int pos=part(arr,low,high,compare);
        quickSort(arr,low,pos-1,compare);
        quickSort(arr,pos+1,high,compare);
    }
}

void EmployeeManagementSystem::QuickSort(vector<Employee*> &arr,bool(*compare)(Employee*,Employee*)){//自定义快速排序函数
    if(arr.empty()) return;
    quickSort(arr,0,arr.size()-1,compare);
}