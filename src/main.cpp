#define _HAS_STD_BYTE 0

#include <windows.h>
#include <iostream>
#include <vector>
#include "Person.h"
#include "Menu.h"
#include "UIHelper.h"
#include "EmployeeManager.h"
#include "DataPersistence.h"
#include "ReportGenerator.h"

using namespace std;

// 全局员工列表
vector<Person*> employees;

// 包装函数用于菜单系统
void addManager() { EmployeeManager::addManager(employees); }
void addTechnican() { EmployeeManager::addTechnican(employees); }
void addSaleman() { EmployeeManager::addSaleman(employees); }
void addSalemanager() { EmployeeManager::addSalemanager(employees); }
void viewAllEmployees() { EmployeeManager::viewAllEmployees(employees); }
void searchEmployee() { EmployeeManager::searchEmployee(employees); }
void modifyEmployee() { EmployeeManager::modifyEmployee(employees); }
void deleteEmployee() { EmployeeManager::deleteEmployee(employees); }
void clearAllEmployees() { EmployeeManager::clearAllEmployees(employees); }
void showSalaryReport() { ReportGenerator::showSalaryReport(employees); }
void showStatistics() { ReportGenerator::showStatistics(employees); }
void exportReport() { ReportGenerator::exportReport(employees); }

int main() {
    UIHelper::setColor(UIHelper::CYAN);
    cout << R"(
    ╔══════════════════════════════════════════════════════════════════════════╗
    ║                                                                          ║
    ║       ____                                          __  __               ║
    ║      / ___|___  _ __ ___  _ __   __ _ _ __  _   _ |  \/  | __ _ _ __     ║
    ║     | |   / _ \| '_ ` _ \| '_ \ / _` | '_ \| | | || |\/| |/ _` | '_ \    ║
    ║     | |__| (_) | | | | | | |_) | (_| | | | | |_| || |  | | (_| | | | |   ║
    ║      \____\___/|_| |_| |_| .__/ \__,_|_| |_|\__, ||_|  |_|\__, |_| |_|   ║
    ║                          |_|                |___/         |___/          ║
    ║            ____        _                   ____            _             ║
    ║           / ___|  __ _| | __ _ _ __ _   _ / ___| _   _ ___| |_ ___ _ __  ║
    ║           \___ \ / _` | |/ _` | '__| | | |\___ \| | | / __| __/ _ \ '_ \ ║
    ║            ___) | (_| | | (_| | |  | |_| | ___) | |_| \__ \ ||  __/ | | |║
    ║           |____/ \__,_|_|\__,_|_|   \__, ||____/ \__, |___/\__\___|_| |_|║
    ║                                     |___/        |___/                   ║
    ║                                                                          ║
    ║                      公司人员和薪酬管理系统 v2.0                         ║
    ║                  Company Management & Salary System                      ║
    ║                                                                          ║
    ╚══════════════════════════════════════════════════════════════════════════╝
    )" << endl;
    UIHelper::resetColor();
    
    UIHelper::printInfo("系统初始化中...");
    
    // 获取并显示当前工作目录（调试用）
    char cwd[1024];
    if (GetCurrentDirectoryA(sizeof(cwd), cwd)) {
        cout << "当前工作目录: " << cwd << endl;
    }
    
    DataPersistence::loadFromFile(employees);
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
    DataPersistence::saveToFile(employees);
    delete mainMenu;
    delete addEmployeeMenu;
    for (auto emp : employees) {
        delete emp;
    }
    employees.clear();
    
    return 0;
}
