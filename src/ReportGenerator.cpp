#define _HAS_STD_BYTE 0

#include <windows.h>  // 必须先包含
#include "ReportGenerator.h"
#include "UIHelper.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

// 显示工资报表
void ReportGenerator::showSalaryReport(const vector<Person*>& employees) {
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

// 薪资统计分析
void ReportGenerator::showStatistics(const vector<Person*>& employees) {
    UIHelper::printTitle("薪资统计分析");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
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
void ReportGenerator::exportReport(const vector<Person*>& employees, const string& filename) {
    UIHelper::printTitle("导出报表到文件");
    
    if (employees.empty()) {
        UIHelper::printWarning("暂无员工信息！");
        UIHelper::pause();
        return;
    }
    
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
