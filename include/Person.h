#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
    string id;
    string name;
    int level;
    double salary;
    static int count;
    
public:
    Person();
    Person(string name, int level);
    virtual ~Person();
    
    void setLevel(int level);
    string getId() const { return id; }
    string getName() const { return name; }
    int getLevel() const { return level; }
    static int getCount() { return count; }
    
    virtual void pay() = 0;
    virtual double getSalary() = 0;
    virtual string getType() const = 0;
};

#endif