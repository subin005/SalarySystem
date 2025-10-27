#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Person.h"
#include "Manager.h"
#include "Technican.h"
#include "Saleman.h"
#include "Salemanager.h"
#include "Menu.h"

using namespace std;

// 全局员工列表
vector<Person*> employees;

// 函数声明
void addEmployee();
void addManager();
void addTechnican();
void addSaleman();
void addSalemanager();
void viewAllEmployees();
void calculateSalary();
void showSalaryReport();
void deleteEmployee();
void clearAllEmployees();

int main() {
    cout << "========================================" << endl;
    cout << "    公司人员和薪酬管理系统" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    // 创建子菜单 - 添加员工
    Menu* addEmployeeMenu = new Menu();
    addEmployeeMenu->add_function("添加经理", addManager)
                   ->add_function("添加技术人员", addTechnican)
                   ->add_function("添加推销员", addSaleman)
                   ->add_function("添加销售经理", addSalemanager);
    
    // 创建主菜单
    Menu* mainMenu = new Menu();
    mainMenu->add_submenu("添加员工", addEmployeeMenu)
            ->add_function("查看所有员工", viewAllEmployees)
            ->add_function("计算员工薪资", calculateSalary)
            ->add_function("显示工资报表", showSalaryReport)
            ->add_function("删除员工", deleteEmployee)
            ->add_function("清空所有员工", clearAllEmployees);
    
    // 设置父菜单关系
    addEmployeeMenu->parent = mainMenu;
    
    // 菜单循环
    Menu* currentMenu = mainMenu;
    while (true) {
        cout << "\n=======================================" << endl;
        cout << "当前菜单：" << (currentMenu == mainMenu ? "主菜单" : "添加员工菜单") << endl;
        cout << "========================================" << endl;
        currentMenu->display();
        cout << "请选择操作: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "输入无效，请输入数字！" << endl;
            continue;
        }
        
        currentMenu = currentMenu->run(choice);
    }
    
    // 清理资源
    delete mainMenu;
    for (auto emp : employees) {
        delete emp;
    }
    employees.clear();
    
    return 0;
}
// 添加经理
void addManager() {
    string name;
    int level;
    
    cout << "\n--- 添加经理 ---" << endl;
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    
    Person* emp = new Manager(name, level);
    employees.push_back(emp);
    cout << "经理 " << name << " 添加成功！编号: " << emp->getId() << endl;
}

// 添加技术人员
void addTechnican() {
    string name;
    int level, workHours;
    
    cout << "\n--- 添加技术人员 ---" << endl;
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    cout << "请输入月工作时间(小时): ";
    cin >> workHours;
    
    Person* emp = new Technican(name, level, workHours);
    employees.push_back(emp);
    cout << "技术人员 " << name << " 添加成功！编号: " << emp->getId() << endl;
}

// 添加推销员
void addSaleman() {
    string name;
    int level;
    double sales;
    
    cout << "\n--- 添加推销员 ---" << endl;
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    cout << "请输入当月销售额: ";
    cin >> sales;
    
    Person* emp = new Saleman(name, level, sales);
    employees.push_back(emp);
    cout << "推销员 " << name << " 添加成功！编号: " << emp->getId() << endl;
}

// 添加销售经理
void addSalemanager() {
    string name;
    int level;
    double sales, deptSales;
    
    cout << "\n--- 添加销售经理 ---" << endl;
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    cout << "请输入个人当月销售额: ";
    cin >> sales;
    cout << "请输入所管辖部门当月销售总额: ";
    cin >> deptSales;
    
    Person* emp = new Salemanager(name, level, sales, deptSales);
    employees.push_back(emp);
    cout << "销售经理 " << name << " 添加成功！编号: " << emp->getId() << endl;
}

// 查看所有员工
void viewAllEmployees() {
    cout << "\n========================================" << endl;
    cout << "          所有员工列表" << endl;
    cout << "========================================" << endl;
    
    if (employees.empty()) {
        cout << "暂无员工信息！" << endl;
        return;
    }
    
    cout << left << setw(10) << "编号"
         << setw(15) << "姓名"
         << setw(15) << "职位"
         << setw(8) << "等级" << endl;
    cout << "----------------------------------------" << endl;
    
    for (auto emp : employees) {
        cout << left << setw(10) << emp->getId()
             << setw(15) << emp->getName()
             << setw(15) << emp->getType()
             << setw(8) << emp->getLevel() << endl;
    }
    
    cout << "----------------------------------------" << endl;
    cout << "员工总数: " << employees.size() << endl;
}

// 计算员工薪资
void calculateSalary() {
    cout << "\n========================================" << endl;
    cout << "正在计算所有员工的月薪..." << endl;
    cout << "========================================" << endl;
    
    if (employees.empty()) {
        cout << "暂无员工信息！" << endl;
        return;
    }
    
    for (auto emp : employees) {
        emp->pay();
    }
    
    cout << "月薪计算完成！共计算 " << employees.size() << " 名员工的薪资。" << endl;
}

// 显示工资报表
void showSalaryReport() {
    cout << "\n========================================" << endl;
    cout << "          工资统计报表" << endl;
    cout << "========================================" << endl;
    
    if (employees.empty()) {
        cout << "暂无员工信息！" << endl;
        return;
    }
    
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

// 删除员工
void deleteEmployee() {
    cout << "\n--- 删除员工 ---" << endl;
    
    if (employees.empty()) {
        cout << "暂无员工信息！" << endl;
        return;
    }
    
    cout << "请输入要删除的员工编号: ";
    string id;
    cin >> id;
    
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getId() == id) {
            cout << "已删除员工: " << (*it)->getName() << " (编号: " << id << ")" << endl;
            delete *it;
            employees.erase(it);
            return;
        }
    }
    
    cout << "未找到编号为 " << id << " 的员工！" << endl;
}

// 清空所有员工
void clearAllEmployees() {
    cout << "\n--- 清空所有员工 ---" << endl;
    
    if (employees.empty()) {
        cout << "员工列表已经为空！" << endl;
        return;
    }
    
    cout << "确定要清空所有员工吗？(y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        for (auto emp : employees) {
            delete emp;
        }
        employees.clear();
        cout << "所有员工已清空！" << endl;
    } else {
        cout << "操作已取消。" << endl;
    }
}