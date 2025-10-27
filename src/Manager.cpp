#include "Manager.h"

Manager::Manager() : Person() {
    level = 4;  // 经理默认为4级
}

Manager::Manager(string name, int level) : Person(name, level) {
    this->level = level;
}

void Manager::pay() {
    salary = 18000.0;  // 经理固定月薪18000元
}

double Manager::getSalary() {
    return salary;
}
