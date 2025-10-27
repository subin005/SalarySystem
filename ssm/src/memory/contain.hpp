#pragma once
#include <string>
#include <vector>
#include <iostream>
struct person{
    std::string name;
    int age;
    std::string sex;
    std::string id;
    double salary;
    std::string carear ="";
    person(std::string name="",int age=0,std::string sex=""):name(name),age(age),sex(sex){}
    virtual ~person(){}
    virtual void pay(){}
};

struct manegement:virtual public person{
    // double salary = 18000;
    manegement(std::string name="",int age=0,std::string sex=""):person(name,age,sex){
        // id = "manegement";
        carear = "Manegement";
        salary = 18000;
    }
    void pay() override{
        //nothing to do
    }
};
struct technologist:public person{
    int work_time;
    
    technologist(std::string name="",int age=0,std::string sex="",int work_time= 0):person(name,age,sex){
        this->work_time = work_time;
        carear = "Technologist";
    }
    void pay() override{
        salary = 100*work_time;
    }
    
};
struct saleman:virtual public person{
    int sale_amount;
    
    saleman(std::string name="",int age=0,std::string sex="",int sale_amount=0):person(name,age,sex){
        this->sale_amount = sale_amount;
        carear = "Saleman";
    }
    void pay() override{
        salary = sale_amount*0.04;
    }
};
struct salemanager:public manegement,public saleman{
    // double sale_performance;
    
    salemanager(std::string name="",int age=0,std::string sex="",int sale_amount=0):manegement(name,age,sex),saleman(name,age,sex,sale_amount){
        // this->sale_performance = sale_performance;
        carear = "Saleman Manager";
    }
    void pay() override{
        manegement::salary = 18000 + sale_amount*0.04;
    }
};


struct panel{
    static std::vector<person*> member_list;    
};

// std::vector<person*> panel::member_list = {};