#define _HAS_STD_BYTE 0

#include <windows.h>  // 必须先包含
#include "EmployeeManager.h"
#include "Manager.h"
#include "Technican.h"
#include "Saleman.h"
#include "Salemanager.h"
#include "UIHelper.h"
#include "DataPersistence.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// 添加经理
void EmployeeManager::addManager(vector<Person*>& employees) {
    string name;
    int level;
    
    UIHelper::printTitle("添加经理");
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    
    Person* emp = new Manager(name, level);
    emp->pay();
    employees.push_back(emp);
    DataPersistence::saveToFile(employees);
    
    UIHelper::printSuccess("经理 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 添加技术人员
void EmployeeManager::addTechnican(vector<Person*>& employees) {
    string name;
    int level, workHours;
    
    UIHelper::printTitle("添加技术人员");
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    cout << "请输入月工作时间(小时): ";
    cin >> workHours;
    
    Person* emp = new Technican(name, level, workHours);
    emp->pay();
    employees.push_back(emp);
    DataPersistence::saveToFile(employees);
    
    UIHelper::printSuccess("技术人员 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 添加推销员
void EmployeeManager::addSaleman(vector<Person*>& employees) {
    string name;
    int level;
    double sales;
    
    UIHelper::printTitle("添加推销员");
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    cout << "请输入当月销售额: ";
    cin >> sales;
    
    Person* emp = new Saleman(name, level, sales);
    emp->pay();
    employees.push_back(emp);
    DataPersistence::saveToFile(employees);
    
    UIHelper::printSuccess("推销员 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 添加销售经理
void EmployeeManager::addSalemanager(vector<Person*>& employees) {
    string name;
    int level;
    double sales, deptSales;
    
    UIHelper::printTitle("添加销售经理");
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    cout << "请输入个人当月销售额: ";
    cin >> sales;
    cout << "请输入所管辖部门当月销售总额: ";
    cin >> deptSales;
    
    Person* emp = new Salemanager(name, level, sales, deptSales);
    emp->pay();
    employees.push_back(emp);
    DataPersistence::saveToFile(employees);
    
    UIHelper::printSuccess("销售经理 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 查看所有员工
void EmployeeManager::viewAllEmployees(const vector<Person*>& employees) {
    UIHelper::printTitle("所有员工列表");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
    cout << left << setw(10) << "编号"
         << setw(15) << "姓名"
         << setw(15) << "职位"
         << setw(8) << "等级" << endl;
    UIHelper::printSeparator('-', 60);
    
    for (auto emp : employees) {
        cout << left << setw(10) << emp->getId()
             << setw(15) << emp->getName()
             << setw(15) << emp->getType()
             << setw(8) << emp->getLevel() << endl;
    }
    
    UIHelper::printSeparator('-', 60);
    UIHelper::printInfo("员工总数: " + to_string(employees.size()));
    UIHelper::pause();
}

// 搜索员工
void EmployeeManager::searchEmployee(const vector<Person*>& employees) {
    UIHelper::printTitle("搜索员工");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
    cout << "请选择搜索方式：" << endl;
    cout << "1. 按编号搜索" << endl;
    cout << "2. 按姓名搜索" << endl;
    cout << "3. 按职位搜索" << endl;
    cout << "请选择: ";
    
    int choice;
    cin >> choice;
    
    vector<Person*> results;
    
    switch(choice) {
        case 1: {
            string id;
            cout << "请输入员工编号: ";
            cin >> id;
            for (auto emp : employees) {
                if (emp->getId() == id) {
                    results.push_back(emp);
                }
            }
            break;
        }
        case 2: {
            string name;
            cout << "请输入员工姓名: ";
            cin >> name;
            for (auto emp : employees) {
                if (emp->getName().find(name) != string::npos) {
                    results.push_back(emp);
                }
            }
            break;
        }
        case 3: {
            string type;
            cout << "请输入职位(经理/技术人员/推销员/销售经理): ";
            cin >> type;
            for (auto emp : employees) {
                if (emp->getType() == type) {
                    results.push_back(emp);
                }
            }
            break;
        }
        default:
            UIHelper::printError("无效的选择！");
            UIHelper::pause();
            return;
    }
    
    if (results.empty()) {
        UIHelper::printWarning("未找到匹配的员工！");
    } else {
        UIHelper::printSuccess("找到 " + to_string(results.size()) + " 名员工：");
        cout << endl;
        cout << left << setw(10) << "编号"
             << setw(15) << "姓名"
             << setw(15) << "职位"
             << setw(8) << "等级"
             << right << setw(12) << "月薪(元)" << endl;
        UIHelper::printSeparator('-', 60);
        
        for (auto emp : results) {
            cout << left << setw(10) << emp->getId()
                 << setw(15) << emp->getName()
                 << setw(15) << emp->getType()
                 << setw(8) << emp->getLevel()
                 << right << setw(12) << fixed << setprecision(2) << emp->getSalary()
                 << endl;
        }
    }
    UIHelper::pause();
}

// 修改员工信息
void EmployeeManager::modifyEmployee(vector<Person*>& employees) {
    UIHelper::printTitle("修改员工信息");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
    cout << "请输入要修改的员工编号: ";
    string id;
    cin >> id;
    
    Person* targetEmp = nullptr;
    for (auto emp : employees) {
        if (emp->getId() == id) {
            targetEmp = emp;
            break;
        }
    }
    
    if (!targetEmp) {
        UIHelper::printError("未找到编号为 " + id + " 的员工！");
        UIHelper::pause();
        return;
    }
    
    UIHelper::printInfo("当前员工信息：");
    cout << "姓名: " << targetEmp->getName() << " | 职位: " << targetEmp->getType() 
         << " | 等级: " << targetEmp->getLevel() << endl;
    
    cout << "\n请输入新的等级 (当前: " << targetEmp->getLevel() << "): ";
    int newLevel;
    cin >> newLevel;
    
    targetEmp->setLevel(newLevel);
    targetEmp->pay();
    DataPersistence::saveToFile(employees);
    
    UIHelper::printSuccess("员工信息已更新！新月薪: " + to_string((int)targetEmp->getSalary()) + "元");
    UIHelper::pause();
}

// 删除员工
void EmployeeManager::deleteEmployee(vector<Person*>& employees) {
    UIHelper::printTitle("删除员工");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
    cout << "请输入要删除的员工编号: ";
    string id;
    cin >> id;
    
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getId() == id) {
            string name = (*it)->getName();
            delete *it;
            employees.erase(it);
            DataPersistence::saveToFile(employees);
            UIHelper::printSuccess("已删除员工: " + name + " (编号: " + id + ")");
            UIHelper::pause();
            return;
        }
    }
    
    UIHelper::printError("未找到编号为 " + id + " 的员工！");
    UIHelper::pause();
}

// 清空所有员工
void EmployeeManager::clearAllEmployees(vector<Person*>& employees) {
    UIHelper::printTitle("清空所有员工");
    
    if (employees.empty()) {
        UIHelper::printWarning("员工列表已经为空！");
        UIHelper::pause();
        return;
    }
    
    UIHelper::printWarning("确定要清空所有 " + to_string(employees.size()) + " 名员工吗？(y/n): ");
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        for (auto emp : employees) {
            delete emp;
        }
        employees.clear();
        DataPersistence::saveToFile(employees);
        UIHelper::printSuccess("所有员工已清空！");
    } else {
        UIHelper::printInfo("操作已取消。");
    }
    UIHelper::pause();
}
