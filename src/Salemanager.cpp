#include "Salemanager.h"

Salemanager::Salemanager() : Person(), Manager(), Saleman(), totalDeptSales(0.0) {
    level = 2;  // 销售经理默认为2级
}

Salemanager::Salemanager(string name, int level, double sales, double deptSales)
    : Person(name, level), Manager(name, level), Saleman(name, level, sales), 
      totalDeptSales(deptSales) {}

void Salemanager::pay() {
    // 销售经理的月薪 = 固定月薪5000 + 部门销售总额的2%提成
    salary = 5000.0 + totalDeptSales * 0.02;
}

double Salemanager::getSalary() {
    return salary;
}