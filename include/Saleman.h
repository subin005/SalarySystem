#ifndef SALEMAN_H
#define SALEMAN_H

#include "Person.h"

class Saleman : virtual public Person {
protected:
    double monthlySales;
    
public:
    Saleman();
    Saleman(string name, int level, double sales);

    void setMonthlySales(double sales) {
        monthlySales = sales;
    }
    double getMonthlySales() const {
        return monthlySales;
    }
    
    virtual void pay() override;
    virtual double getSalary() override;
    virtual string getType() const override {
        return "推销员";
    }
};

#endif