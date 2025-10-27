#pragma once
#include "contain.hpp"
#include <fstream>
#include <iostream>

void load_mls() {
    std::ifstream infile("assent/member_data.txt");
    if (!infile.is_open()) {
        std::cerr << "Can not open member_data.txt !" << std::endl;
        return;
    }

    panel::member_list.clear();

    std::string id, name, carear, sex, age;
    std::string extra_data; 
    
    while (std::getline(infile, id) && 
           std::getline(infile, name) && 
           std::getline(infile, age) &&
           std::getline(infile, carear) && 
           std::getline(infile, sex)) {
        // std::cout<<carear<<std::endl;
        person* newMember = nullptr;
        if(carear == "Manegement") {
            auto* mana = new manegement();
            newMember = mana;
        }
        else if (carear == "Technologist") {
            auto* tech = new technologist();
            std::getline(infile, extra_data);
            tech->work_time = std::stoi(extra_data); 
            newMember = tech;
        } 
        else if (carear == "Saleman") {
            auto* sale = new saleman();
            std::getline(infile, extra_data);
            sale->sale_amount = std::stoi(extra_data); 
            newMember = sale;
        }
        else if (carear == "Saleman Manager") {
            auto* manager = new salemanager();
            std::getline(infile, extra_data);
            manager->sale_amount = std::stoi(extra_data); 
            newMember = manager;
        }
        else {
            newMember = new person(); std::cout<<"wrong load";
        }
        
        
        newMember->id = id;
        newMember->name = name;
        newMember->age = std::stoi(age);
        newMember->carear = carear;
        newMember->sex = sex;
        
        panel::member_list.push_back(newMember);
    }

}
void save_mls(){
    std::ofstream outfile("assent/member_data.txt");
    if (!outfile.is_open()) {
            std::cerr << "Can not open " << "member_data.txt" << " to save!" << std::endl;
            return;
        }
    for(auto& it : panel::member_list){
        outfile<< it->id<<'\n'<<it->name<<'\n'<<it->age<<'\n'<<it->carear<<'\n'<<it->sex<<'\n';
        if(it->carear == "Technologist") outfile<< dynamic_cast<technologist*>(it)->work_time<<'\n';
        else if(it->carear == "Saleman") outfile<< dynamic_cast<saleman*>(it)->sale_amount<<'\n';
        else if(it->carear == "Saleman Manager") outfile<< dynamic_cast<salemanager*>(it)->sale_amount<<'\n';
    }
}