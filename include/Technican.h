#ifndef TECHNICAN_H
#define TECHNICAN_H

#include "Person.h"

class Technican : public Person {
private:
    int workHours;
    
public:
    Technican();
    Technican(string name, int level, int workHours);
    
    void setWorkHours(int hours) {
        workHours = hours;
    }
    int getWorkHours() const {
        return workHours;
    }
    
    virtual void pay() override;
    virtual double getSalary() override;
    virtual string getType() const override {
        return "技术人员";
    }
};
#endif