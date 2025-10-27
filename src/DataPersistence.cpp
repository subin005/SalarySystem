#define _HAS_STD_BYTE 0

#include <windows.h>
#include "DataPersistence.h"
#include "Manager.h"
#include "Technican.h"
#include "Saleman.h"
#include "Salemanager.h"
#include "UIHelper.h"
#include <fstream>
#include <sstream>

using namespace std;

// 保存数据到文件
void DataPersistence::saveToFile(const vector<Person*>& employees, const string& filename) {
    // 确保data目录存在
    CreateDirectoryA("data", NULL);
    
    ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        return;  // 静默失败
    }
    
    // 保存员工数量
    outFile << employees.size() << endl;
    
    // 保存每个员工的信息
    for (auto emp : employees) {
        outFile << emp->getType() << "|"
                << emp->getId() << "|"
                << emp->getName() << "|"
                << emp->getLevel() << "|";
        
        if (emp->getType() == "经理") {
            outFile << endl;
        } else if (emp->getType() == "技术人员") {
            Technican* tech = dynamic_cast<Technican*>(emp);
            if (tech) {
                outFile << tech->getWorkHours() << endl;
            }
        } else if (emp->getType() == "推销员") {
            Saleman* sale = dynamic_cast<Saleman*>(emp);
            if (sale) {
                outFile << sale->getMonthlySales() << endl;
            }
        } else if (emp->getType() == "销售经理") {
            Salemanager* saleMgr = dynamic_cast<Salemanager*>(emp);
            if (saleMgr) {
                outFile << saleMgr->getMonthlySales() << "|"
                        << saleMgr->getTotalDeptSales() << endl;
            }
        }
    }
    
    outFile.close();
}

// 从文件加载数据
void DataPersistence::loadFromFile(vector<Person*>& employees, const string& filename) {
    // 尝试多个可能的路径
    string filePaths[] = {
        filename,
        "employees_data.txt",
        "../data/employees_data.txt"
    };
    
    ifstream inFile;
    string usedPath;
    
    for (const string& path : filePaths) {
        inFile.open(path);
        if (inFile.is_open()) {
            usedPath = path;
            break;
        }
    }
    
    if (!inFile.is_open()) {
        UIHelper::printWarning("未找到历史数据文件，从空白开始");
        return;
    }
    
    // 清空现有数据
    for (auto emp : employees) {
        delete emp;
    }
    employees.clear();
    
    int count;
    inFile >> count;
    inFile.ignore();
    
    for (int i = 0; i < count; i++) {
        string line;
        getline(inFile, line);
        
        if (line.empty()) continue;
        
        size_t pos = 0;
        string type, id, name;
        int level;
        
        // 提取职位类型
        pos = line.find('|');
        if (pos == string::npos) continue;
        type = line.substr(0, pos);
        line = line.substr(pos + 1);
        
        // 提取ID
        pos = line.find('|');
        if (pos == string::npos) continue;
        id = line.substr(0, pos);
        line = line.substr(pos + 1);
        
        // 提取姓名
        pos = line.find('|');
        if (pos == string::npos) continue;
        name = line.substr(0, pos);
        line = line.substr(pos + 1);
        
        // 提取等级
        pos = line.find('|');
        if (pos == string::npos) continue;
        level = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        
        // 根据职位类型创建员工对象
        Person* emp = nullptr;
        
        if (type == "经理") {
            emp = new Manager(name, level);
        } else if (type == "技术人员") {
            if (!line.empty()) {
                int workHours = stoi(line);
                emp = new Technican(name, level, workHours);
            }
        } else if (type == "推销员") {
            if (!line.empty()) {
                double sales = stod(line);
                emp = new Saleman(name, level, sales);
            }
        } else if (type == "销售经理") {
            pos = line.find('|');
            if (pos != string::npos && !line.empty()) {
                double sales = stod(line.substr(0, pos));
                double deptSales = stod(line.substr(pos + 1));
                emp = new Salemanager(name, level, sales, deptSales);
            }
        }
        
        if (emp) {
            emp->pay();
            employees.push_back(emp);
        }
    }
    
    inFile.close();
    
    if (employees.size() > 0) {
        UIHelper::printSuccess("成功加载 " + to_string(employees.size()) + " 名员工数据");
    }
}
