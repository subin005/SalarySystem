#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Person.h"
#include "Manager.h"
#include "Technican.h"
#include "Saleman.h"
#include "Salemanager.h"

using namespace std;

void inputInfo(vector<Person*> & employees);
void monthPay(vector<Person*> & employees);
void showSalary(vector<Person *> & employees);

int main() {
    vector<Person*> employees;
    
    cout << "========================================" << endl;
    cout << "    公司人员和薪酬管理系统" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    // 批量输入员工信息
    inputInfo(employees);
    
    // 计算每月薪水
    monthPay(employees);
    
    // 显示工资统计报表
    showSalary(employees);
    
    // 释放内存
    for (auto emp : employees) {
        delete emp;
    }
    employees.clear();

    return 0;
}
void inputInfo(vector<Person*> &employees) {
    int numEmployees;
    cout << "请输入员工总数: ";
    cin >> numEmployees;
    cout << endl;
    
    for (int i = 0; i < numEmployees; i++) {
        cout << "--- 输入第 " << (i + 1) << " 个员工信息 ---" << endl;
        cout << "请选择职位类型:" << endl;
        cout << "1. 经理 (Manager)" << endl;
        cout << "2. 技术人员 (Technican)" << endl;
        cout << "3. 推销员 (Saleman)" << endl;
        cout << "4. 销售经理 (Salemanager)" << endl;
        cout << "请输入选择 (1-4): ";
        
        int type;
        cin >> type;
        
        string name;
        int level;

        cout << "请输入姓名: ";
        cin >> name;
        cout << "请输入等级: ";
        cin >> level;
        
        Person* emp = nullptr;
        
        switch(type) {
            case 1: {
                //经理
                emp = new Manager(name, level);
                break;
            }
            case 2: {
                //技术人员
                int workHours;
                cout << "请输入月工作时间(小时): ";
                cin >> workHours;
                emp = new Technican(name, level, workHours);
                break;
            }
            case 3: {
                //推销员
                double sales;
                cout << "请输入当月销售额: ";
                cin >> sales;
                emp = new Saleman(name, level, sales);
                break;
            }
            case 4: {
                //销售经理
                double sales, deptSales;
                cout << "请输入个人当月销售额: ";
                cin >> sales;
                cout << "请输入所管辖部门当月销售总额: ";
                cin >> deptSales;
                emp = new Salemanager(name, level, sales, deptSales);
                break;
            }
            default:
                cout << "无效的选择，跳过该员工。" << endl;
                continue;
        }
        
        if (emp != nullptr) {
            employees.push_back(emp);
            cout << "员工 " << name << " 添加成功！编号: " << emp->getId() << endl;
        }
        cout << endl;
    }
}

void monthPay(vector<Person*> &employees) {
    cout << "\n========================================" << endl;
    cout << "正在计算所有员工的月薪..." << endl;
    cout << "========================================" << endl;

    for (auto emp : employees) {
        emp->pay();
    }

    cout << "月薪计算完成！" << endl << endl;
}

void showSalary(vector<Person*> &employees) {
    cout << "\n========================================" << endl;
    cout << "          工资统计报表" << endl;
    cout << "========================================" << endl;
    cout << left << setw(10) << "编号"
         << setw(15) << "姓名"
         << setw(15) << "职位"
         << setw(8) << "等级"
         << right << setw(12) << "月薪(元)" << endl;
    cout << "----------------------------------------" << endl;

    double totalSalary = 0.0;

    for (auto emp : employees) {
        cout << left << setw(10) << emp->getId()
             << setw(15) << emp->getName()
             << setw(15) << emp->getType()
             << setw(8) << emp->getLevel()
             << right << setw(12) << fixed << setprecision(2) << emp->getSalary()
             << endl;
        totalSalary += emp->getSalary();
    }
    
    cout << "----------------------------------------" << endl;
    
    // 统计信息
    cout << left << setw(48) << "员工总数: " + to_string(employees.size())
         << right << setw(12) << "" << endl;
    cout << left << setw(48) << "月薪总额:"
         << right << setw(12) << fixed << setprecision(2) << totalSalary << endl;
    
    if (employees.size() > 0) {
        cout << left << setw(48) << "平均月薪:"
             << right << setw(12) << fixed << setprecision(2) 
             << (totalSalary / employees.size()) << endl;
    }
    
    cout << "========================================" << endl;
}