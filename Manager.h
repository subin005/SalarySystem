#ifndef MANAGER_H
#define MANAGER_H

#include "Person.h"

class Manager : virtual public Person {
public:
    Manager();
    Manager(string name, int level);

    virtual void pay() override;
    virtual double getSalary() override;
    virtual string getType() const override {
        return "经理";
    }
};

#endif