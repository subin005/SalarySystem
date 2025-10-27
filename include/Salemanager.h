#ifndef SALEMANAGER_H
#define SALEMANAGER_H

#include "Manager.h"
#include "Saleman.h"

class Salemanager : public Manager, public Saleman {
private:
    double totalDeptSales;
    
public:
    Salemanager();
    Salemanager(string name, int level, double sales, double deptSales);

    void setTotalDeptSales(double sales) {
        totalDeptSales = sales;
    }
    double getTotalDeptSales() const {
        return totalDeptSales;
    }
    
    virtual void pay() override;
    virtual double getSalary() override;
    virtual string getType() const override {
        return "销售经理";
    }
};
#endif