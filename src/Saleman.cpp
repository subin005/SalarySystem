#include "Saleman.h"

Saleman::Saleman() : Person(), monthlySales(0.0) {
    level = 1;  // 推销员默认为1级
}

Saleman::Saleman(string name, int level, double sales) :
    Person(name, level), monthlySales(sales) {}

void Saleman::pay() {
    salary = monthlySales * 0.04 + 4000;
}

double Saleman::getSalary() {
    return salary;
}