#define _HAS_STD_BYTE 0  // 必须在所有包含前定义

#include <windows.h>  // windows.h必须先包含
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include "Person.h"
#include "Manager.h"
#include "Technican.h"
#include "Saleman.h"
#include "Salemanager.h"
#include "Menu.h"
#include "UIHelper.h"

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
void showSalaryReport();
void deleteEmployee();
void clearAllEmployees();
void searchEmployee();
void modifyEmployee();
void showStatistics();
void exportReport();

int main() {
    UIHelper::setColor(UIHelper::CYAN);
    cout << R"(
    ╔══════════════════════════════════════════════════════════════════════╗
    ║                                                                      ║
    ║      ____                                         __  __            ║
    ║     / ___|___  _ __ ___  _ __   __ _ _ __  _   _|  \/  | __ _ _ __ ║
    ║    | |   / _ \| '_ ` _ \| '_ \ / _` | '_ \| | | | |\/| |/ _` | '__|║
    ║    | |__| (_) | | | | | | |_) | (_| | | | | |_| | |  | | (_| | |   ║
    ║     \____\___/|_| |_| |_| .__/ \__,_|_| |_|\__, |_|  |_|\__, |_|   ║
    ║                         |_|                |___/         |___/      ║
    ║           ____        _                   ____            _         ║
    ║          / ___|  __ _| | __ _ _ __ _   _ / ___| _   _ ___| |_ ___ _ __ ___  ║
    ║          \___ \ / _` | |/ _` | '__| | | |\___ \| | | / __| __/ _ \ '_ ` _ \ ║
    ║           ___) | (_| | | (_| | |  | |_| | ___) | |_| \__ \ ||  __/ | | | | |║
    ║          |____/ \__,_|_|\__,_|_|   \__, ||____/ \__, |___/\__\___|_| |_| |_|║
    ║                                    |___/        |___/                        ║
    ║                                                                      ║
    ║                  公司人员和薪酬管理系统 v2.0                         ║
    ║              Company Management & Salary System                      ║
    ║                                                                      ║
    ╚══════════════════════════════════════════════════════════════════════╝
    )" << endl;
    UIHelper::resetColor();
    
    UIHelper::printInfo("系统初始化中...");
    UIHelper::printSuccess("系统加载完成！");
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
            ->add_function("搜索员工", searchEmployee)
            ->add_function("修改员工信息", modifyEmployee)
            ->add_function("显示工资报表", showSalaryReport)
            ->add_function("薪资统计分析", showStatistics)
            ->add_function("导出报表到文件", exportReport)
            ->add_function("删除员工", deleteEmployee)
            ->add_function("清空所有员工", clearAllEmployees);
    
    // 设置父菜单关系
    addEmployeeMenu->parent = mainMenu;
    
    // 菜单循环
    Menu* currentMenu = mainMenu;
    while (true) {
        UIHelper::printSeparator('=', 60);
        UIHelper::setColor(UIHelper::YELLOW);
        cout << "当前菜单：" << (currentMenu == mainMenu ? "主菜单" : "添加员工菜单") << endl;
        UIHelper::resetColor();
        UIHelper::printSeparator('=', 60);
        currentMenu->display();
        
        UIHelper::setColor(UIHelper::GREEN);
        cout << "请选择操作: ";
        UIHelper::resetColor();
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            UIHelper::printError("输入无效，请输入数字！");
            UIHelper::pause();
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
    
    UIHelper::printTitle("添加经理");
    cout << "请输入姓名: ";
    cin >> name;
    cout << "请输入等级: ";
    cin >> level;
    
    Person* emp = new Manager(name, level);
    emp->pay();  // 立即计算薪资
    employees.push_back(emp);
    
    UIHelper::printSuccess("经理 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 添加技术人员
void addTechnican() {
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
    emp->pay();  // 立即计算薪资
    employees.push_back(emp);
    
    UIHelper::printSuccess("技术人员 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 添加推销员
void addSaleman() {
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
    emp->pay();  // 立即计算薪资
    employees.push_back(emp);
    
    UIHelper::printSuccess("推销员 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 添加销售经理
void addSalemanager() {
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
    emp->pay();  // 立即计算薪资
    employees.push_back(emp);
    
    UIHelper::printSuccess("销售经理 " + name + " 添加成功！");
    UIHelper::printInfo("编号: " + emp->getId() + " | 月薪: " + 
                        to_string((int)emp->getSalary()) + "元");
    UIHelper::pause();
}

// 查看所有员工
void viewAllEmployees() {
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

// 显示工资报表
void showSalaryReport() {
    UIHelper::printTitle("工资统计报表");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
    cout << left << setw(10) << "编号"
         << setw(15) << "姓名"
         << setw(15) << "职位"
         << setw(8) << "等级"
         << right << setw(12) << "月薪(元)" << endl;
    UIHelper::printSeparator('-', 60);

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
    
    UIHelper::printSeparator('-', 60);
    UIHelper::setColor(UIHelper::YELLOW);
    cout << left << setw(48) << "员工总数: " + to_string(employees.size())
         << right << setw(12) << "" << endl;
    cout << left << setw(48) << "月薪总额:"
         << right << setw(12) << fixed << setprecision(2) << totalSalary << endl;
    
    if (employees.size() > 0) {
        cout << left << setw(48) << "平均月薪:"
             << right << setw(12) << fixed << setprecision(2) 
             << (totalSalary / employees.size()) << endl;
    }
    UIHelper::resetColor();
    UIHelper::printSeparator('=', 60);
    UIHelper::pause();
}

// 删除员工
void deleteEmployee() {
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
            UIHelper::printSuccess("已删除员工: " + name + " (编号: " + id + ")");
            UIHelper::pause();
            return;
        }
    }
    
    UIHelper::printError("未找到编号为 " + id + " 的员工！");
    UIHelper::pause();
}

// 清空所有员工
void clearAllEmployees() {
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
        UIHelper::printSuccess("所有员工已清空！");
    } else {
        UIHelper::printInfo("操作已取消。");
    }
    UIHelper::pause();
}

// 搜索员工
void searchEmployee() {
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
void modifyEmployee() {
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
    targetEmp->pay();  // 重新计算薪资
    
    UIHelper::printSuccess("员工信息已更新！新月薪: " + to_string((int)targetEmp->getSalary()) + "元");
    UIHelper::pause();
}

// 薪资统计分析
void showStatistics() {
    UIHelper::printTitle("薪资统计分析");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
    // 统计各职位人数和薪资
    int managerCount = 0, techCount = 0, salesCount = 0, salesMgrCount = 0;
    double managerTotal = 0, techTotal = 0, salesTotal = 0, salesMgrTotal = 0;
    double maxSalary = 0, minSalary = 999999;
    Person* maxEmp = nullptr;
    Person* minEmp = nullptr;
    
    for (auto emp : employees) {
        double salary = emp->getSalary();
        
        if (salary > maxSalary) {
            maxSalary = salary;
            maxEmp = emp;
        }
        if (salary < minSalary) {
            minSalary = salary;
            minEmp = emp;
        }
        
        if (emp->getType() == "经理") {
            managerCount++;
            managerTotal += salary;
        } else if (emp->getType() == "技术人员") {
            techCount++;
            techTotal += salary;
        } else if (emp->getType() == "推销员") {
            salesCount++;
            salesTotal += salary;
        } else if (emp->getType() == "销售经理") {
            salesMgrCount++;
            salesMgrTotal += salary;
        }
    }
    
    double totalSalary = managerTotal + techTotal + salesTotal + salesMgrTotal;
    
    UIHelper::printInfo("📊 职位分布统计");
    cout << left << setw(20) << "职位" 
         << setw(10) << "人数" 
         << setw(15) << "总薪资" 
         << "平均薪资" << endl;
    UIHelper::printSeparator('-', 60);
    
    if (managerCount > 0) {
        cout << left << setw(20) << "经理" 
             << setw(10) << managerCount
             << setw(15) << fixed << setprecision(2) << managerTotal
             << (managerTotal / managerCount) << endl;
    }
    if (techCount > 0) {
        cout << left << setw(20) << "技术人员" 
             << setw(10) << techCount
             << setw(15) << fixed << setprecision(2) << techTotal
             << (techTotal / techCount) << endl;
    }
    if (salesCount > 0) {
        cout << left << setw(20) << "推销员" 
             << setw(10) << salesCount
             << setw(15) << fixed << setprecision(2) << salesTotal
             << (salesTotal / salesCount) << endl;
    }
    if (salesMgrCount > 0) {
        cout << left << setw(20) << "销售经理" 
             << setw(10) << salesMgrCount
             << setw(15) << fixed << setprecision(2) << salesMgrTotal
             << (salesMgrTotal / salesMgrCount) << endl;
    }
    
    cout << endl;
    UIHelper::printInfo("💰 薪资极值");
    UIHelper::setColor(UIHelper::GREEN);
    cout << "最高薪资: " << fixed << setprecision(2) << maxSalary << "元 - " 
         << maxEmp->getName() << " (" << maxEmp->getType() << ")" << endl;
    UIHelper::setColor(UIHelper::YELLOW);
    cout << "最低薪资: " << fixed << setprecision(2) << minSalary << "元 - " 
         << minEmp->getName() << " (" << minEmp->getType() << ")" << endl;
    UIHelper::resetColor();
    
    UIHelper::pause();
}

// 导出报表到文件
void exportReport() {
    UIHelper::printTitle("导出报表到文件");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
    string filename = "salary_report.txt";
    ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        UIHelper::printError("无法创建文件！");
        UIHelper::pause();
        return;
    }
    
    outFile << "========================================" << endl;
    outFile << "          工资统计报表" << endl;
    outFile << "========================================" << endl;
    outFile << left << setw(10) << "编号"
            << setw(15) << "姓名"
            << setw(15) << "职位"
            << setw(8) << "等级"
            << right << setw(12) << "月薪(元)" << endl;
    outFile << "----------------------------------------" << endl;

    double totalSalary = 0.0;

    for (auto emp : employees) {
        outFile << left << setw(10) << emp->getId()
                << setw(15) << emp->getName()
                << setw(15) << emp->getType()
                << setw(8) << emp->getLevel()
                << right << setw(12) << fixed << setprecision(2) << emp->getSalary()
                << endl;
        totalSalary += emp->getSalary();
    }
    
    outFile << "----------------------------------------" << endl;
    outFile << left << setw(48) << "员工总数: " + to_string(employees.size())
            << right << setw(12) << "" << endl;
    outFile << left << setw(48) << "月薪总额:"
            << right << setw(12) << fixed << setprecision(2) << totalSalary << endl;
    
    if (employees.size() > 0) {
        outFile << left << setw(48) << "平均月薪:"
                << right << setw(12) << fixed << setprecision(2) 
                << (totalSalary / employees.size()) << endl;
    }
    
    outFile << "========================================" << endl;
    outFile.close();
    
    UIHelper::printSuccess("报表已成功导出到文件: " + filename);
    UIHelper::pause();
}