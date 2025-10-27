#include "Technican.h"

Technican::Technican() : Person(), workHours(0) {
    level = 3;  // 技术人员默认为3级
}

Technican::Technican(string name, int level, int workHours) :
    Person(name, level), workHours(workHours) {}

void Technican::pay() {
    salary = workHours * 120.0;
}

double Technican::getSalary() {
    return salary;
}