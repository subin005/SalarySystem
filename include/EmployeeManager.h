#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include <vector>
#include "Person.h"

class EmployeeManager {
public:
    // 添加员工
    static void addManager(std::vector<Person*>& employees);
    static void addTechnican(std::vector<Person*>& employees);
    static void addSaleman(std::vector<Person*>& employees);
    static void addSalemanager(std::vector<Person*>& employees);
    
    // 查看和搜索
    static void viewAllEmployees(const std::vector<Person*>& employees);
    static void searchEmployee(const std::vector<Person*>& employees);
    
    // 修改和删除
    static void modifyEmployee(std::vector<Person*>& employees);
    static void deleteEmployee(std::vector<Person*>& employees);
    static void clearAllEmployees(std::vector<Person*>& employees);
};

#endif
