#include "Person.h"
#include <sstream>
#include <iomanip>

int Person::count = 0;

Person::Person() : name(""), level(0), salary(0.0) {
    count++;
    stringstream ss;
    ss << setw(4) << setfill('0') << (2000 + count);
    id = ss.str();
}

Person::Person(string name, int level) : name(name), level(level), salary(0.0) {
    count++;
    stringstream ss;
    ss << setw(4) << setfill('0') << (2000 + count);
    id = ss.str();
}

Person::~Person() {
    count--;
}

void Person::setLevel(int level) {
    this->level = level;
}