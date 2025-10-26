#include "funclib.hpp"

// extern panel p;

void build(){
    person* new_member = nullptr;
    std::cout<<"Enter the type of member to build:"<<std::endl;
    std::cout<<"1. Manegement"<<std::endl;
    std::cout<<"2. Technologist"<<std::endl;
    std::cout<<"3. Saleman"<<std::endl;
    std::cout<<"4. Saleman Manager"<<std::endl;
    int choice;
    std::cin>>choice;
    switch(choice){
        case 1: new_member = new manegement(); break;
        case 2: new_member = new technologist(); break;
        case 3: new_member = new saleman(); break;
        case 4: new_member = new salemanager(); break;
        default:
            std::cout<<"Invalid choice."<<std::endl;
            return;
    }
    // std::cout<<"Build a new member."<<std::endl;
    std::cout<<"Enter name: ";
    std::string name;
    std::cin>>name;
    new_member->name = name;
    std::cout<<"Enter age: ";
    int age;
    std::cin>>age;
    std::string rest_input;
    std::getline(std::cin,rest_input);
    new_member->age = age;
    std::cout<<"Enter sex: (male/female/other)";
    std::string sex;
    std::cin>>sex;
    if(sex == "male"){
        new_member->sex = sex;
    }else if(sex == "female"){
        new_member->sex = sex;
    }else{
        new_member->sex = "other";
    }
    if(choice==2){
        std::cout<<"Enter work time (hours): ";
        int work_time = 0;
        std::cin>>work_time;
        std::getline(std::cin,rest_input);
        dynamic_cast<technologist*>(new_member)->work_time = work_time;
    }else if(choice==3){
        std::cout<<"Enter sale amount: ";
        int sale_amount;
        std::cin>>sale_amount;
        std::getline(std::cin,rest_input);
        dynamic_cast<saleman*>(new_member)->sale_amount = sale_amount;
    }else if(choice==4){
        std::cout<<"Enter sale amount: ";
        int sale_amount;
        std::cin>>sale_amount;
        std::getline(std::cin,rest_input);
        dynamic_cast<salemanager*>(new_member)->sale_amount = sale_amount;
    }
    new_member->id = std::to_string(panel::member_list.size());
    //this can replace by a static variable
    panel::member_list.push_back(new_member);
    // std::cout<<"Member built successfully with ID: "<<new_member->id<<std::endl;
    std::cout<<"Build finished."<<std::endl;
}
void display(){
    if(panel::member_list.size()==0){
        std::cout<<"No member in the list."<<std::endl;
        return;
    }
    for(size_t i=0;i<panel::member_list.size();i++){
        person* member = panel::member_list[i];
        member->pay();
        std::cout<<"Index: "<<i+1<<", Name: "<<member->name<<", Position: "<<member->carear<<", Age: "<<member->age
                 <<", Sex: "<<member->  sex<<", Salary: "<<member->salary<<std::endl;
    } 
}
void display_index(){
    if(panel::member_list.size()==0){
        std::cout<<"No member in the list."<<std::endl;
        return;
    }
    std::string rest_input;
    std::cout<<"1. Manegement"<<std::endl;
    std::cout<<"2. Technologist"<<std::endl;
    std::cout<<"3. Saleman"<<std::endl;
    std::cout<<"4. Saleman Manager"<<std::endl;
    std::cout<<"Choose the type you want to view: ";
    int choice = 0;
    if(!(std::cin>>choice)){
        std::cin.clear();
        std::getline(std::cin,rest_input);
        std::cout<<"Can't recognize '"<<rest_input<<"'"<<std::endl;
    }
    std::string carea_to_find;
    switch(choice){
        case 1 : carea_to_find = "Manegement";break;
        case 2 : carea_to_find = "Technologist";break;
        case 3 : carea_to_find = "Saleman";break;
        case 4 : carea_to_find = "Saleman Manager";break;
        default: carea_to_find = "";
    }
    int i =1;
    bool exist_mark =false;
    for(auto& it : panel::member_list){
        if(it->carear == carea_to_find){
            exist_mark =true;
            it->pay();
            std::cout<<"Index: "<<i++<<", Name: "<<it->name<<", Position: "<<it->carear<<", Age: "<<it->age
                 <<", Sex: "<<it->  sex<<", Salary: "<<it->salary<<std::endl;
        }
    }
    if(!exist_mark){
        std::cout<<"There's not "<<carea_to_find<<" members in list."<<std::endl;
    }
}

void clear(){
    std::cout<<"Sure to clear all members? (y/n): ";
    char choice;
    std::cin>>choice;
    if(choice=='y' || choice=='Y'){
        // for(auto member:panel::member_list){
        //     delete member;
        // }
        panel::member_list.clear();
        std::cout<<"All members cleared."<<std::endl;
    }else{
        std::cout<<"Clear operation cancelled."<<std::endl;
    }
}
void clear_index(){
    std::cout<<"Enter the index of member to clear: ";
    int index = 1;
    for(auto member:panel::member_list){
        std::cout<<"Index: "<< index++ <<", Name: "<<member->name<<std::endl;
    }
    std::cin>>index;
    if(index<1 || index>panel::member_list.size()){
        std::cout<<"Invalid index."<<std::endl;
        return;
    }
    index--; //convert to 0-based index
    // delete panel::member_list[index];//here result double free or corruption error
    person* temp = panel::member_list[index];
    panel::member_list.erase(panel::member_list.begin()+index);
    delete temp;
    //dejust the oder of delete and erease  
}

// void change(){
//     std::cout<<"Enter the index of member to change: "<<std::endl;
//     int index = 1;
//     for(auto member:panel::member_list){
//         std::cout<<"Index: "<< index++ <<", Name: "<<member->name<<std::endl;
//     }
//     std::cin>>index;
//     if(index<1 || index>panel::member_list.size()){
//         std::cout<<"Invalid index."<<std::endl;
//         return;
//     }
//     index--; //convert to 0-based index
//     // person* member = panel::member_list[index];
//     // std::cout<<"Changing member: "<<member->name<<std::endl;
//     // std::cout<<"Enter new name (current: "<<member->name<<"): ";
//     // std::string name;
//     // std::cin>>name;
//     // member->name = name;
//     // std::cout<<"Enter new age (current: "<<member->age<<"): ";
//     // int age;
//     // std::cin>>age;
//     // member->age = age;
//     // std::cout<<"Enter new sex (current: "<<member->sex<<"): ";
//     // std::string sex;
//     // std::cin>>sex;
//     // member->sex = sex;
//     // auto temp = panel::member_list[index];
    
//     person* new_member = nullptr;
//     std::cout<<"Enter the type of new member: "<<std::endl;
//     std::cout<<"1. Manegement"<<std::endl;
//     std::cout<<"2. Technologist"<<std::endl;
//     std::cout<<"3. Saleman"<<std::endl;
//     std::cout<<"4. Saleman Manager"<<std::endl;
//     int choice;
//     std::cin>>choice;
//     switch(choice){
//         case 1: new_member = new manegement();break;
//         case 2: new_member = new technologist(); break;
//         case 3: new_member = new saleman(); break;
//         case 4: new_member = new salemanager(); break;
//         default:
//             std::cout<<"Invalid choice."<<std::endl;
//             return;
//     }
//     // std::cout<<"Build a new member."<<std::endl;
//     std::cout<<"Enter name: ";
//     std::string name;
//     std::cin>>name;
//     new_member->name = name;
//     std::cout<<"Enter age: ";
//     int age;
//     std::cin>>age;
//     new_member->age = age;
//     std::cout<<"Enter sex: ";
//     std::string sex;
//     std::cin>>sex;
//     new_member->sex = sex;
//     if(choice==2){
//         std::cout<<"Enter work time (hours): ";
//         int work_time;
//         std::cin>>work_time;
//         // dynamic_cast<technologist*>(new_member)->work_time = work_time;
//         dynamic_cast<technologist*>(new_member)->work_time = work_time;
//     }else if(choice==3){
//         std::cout<<"Enter sale amount: ";
//         int sale_amount;
//         std::cin>>sale_amount;
//         dynamic_cast<saleman*>(new_member)->sale_amount = sale_amount;
//     }else if(choice==4){
//         std::cout<<"Enter sale amount: ";
//         int sale_amount;
//         std::cin>>sale_amount;
//         dynamic_cast<salemanager*>(new_member)->sale_amount = sale_amount;
//     }
//     new_member->id = std::to_string(panel::member_list.size());
//     //this can replace by a static variable
//     delete panel::member_list[index];
//     panel::member_list[index] = new_member;
//     // delete temp;
//     std::cout<<"Change finished."<<std::endl;
// }

void change(){
    std::string rest_input;
    std::cout<<"Enter the index of member to change: "<<std::endl;
    int index = 1;
    for(auto member:panel::member_list){
        std::cout<<"Index: "<< index++ <<", Name: "<<member->name<<std::endl;
    }
    std::cin>>index;
    if(index<1 || index>panel::member_list.size()){
        std::cout<<"Invalid index."<<std::endl;
        return;
    }
    index--; //convert to 0-based index    
    person* new_member = nullptr;
    std::cout<<"Enter the type of new member: "<<std::endl;
    std::cout<<"1. Manegement"<<std::endl;
    std::cout<<"2. Technologist"<<std::endl;
    std::cout<<"3. Saleman"<<std::endl;
    std::cout<<"4. Saleman Manager"<<std::endl;
    int choice;
    std::cin>>choice;
    switch(choice){
        case 1: new_member = new manegement();break;
        case 2: new_member = new technologist(); break;
        case 3: new_member = new saleman(); break;
        case 4: new_member = new salemanager(); break;
        default:
            std::cout<<"Invalid choice."<<std::endl;
            return;
    }
    // std::cout<<"Build a new member."<<std::endl;
    std::cout<<"Enter name: ";
    std::string name;
    std::cin>>name;
    new_member->name = name;
    std::cout<<"Enter age: ";
    int age;
    std::cin>>age;
    std::getline(std::cin,rest_input);
    new_member->age = age;
    std::cout<<"Enter sex: (male/female/other)";
    std::string sex;
    std::cin>>sex;
    if(sex == "male"){
        new_member->sex = sex;
    }else if(sex == "female"){
        new_member->sex = sex;
    }else{
        new_member->sex = "other";
    }
    if(choice==2){
        std::cout<<"Enter work time (hours): ";
        // std::cout<<new_member->carear<<std::endl;
        int work_time;
        std::cin>>work_time;
        std::getline(std::cin,rest_input);
        dynamic_cast<technologist*>(new_member)->work_time = work_time;
        // technologist* tech = dynamic_cast<technologist*>(new_member);
    }else if(choice==3){
        std::cout<<"Enter sale amount: ";
        int sale_amount;
        std::cin>>sale_amount;
        std::getline(std::cin,rest_input);
        dynamic_cast<saleman*>(new_member)->sale_amount = sale_amount;
    }else if(choice==4){
        std::cout<<"Enter sale amount: ";
        int sale_amount;
        std::cin>>sale_amount;
        std::getline(std::cin,rest_input);
        dynamic_cast<salemanager*>(new_member)->sale_amount = sale_amount;
    }
    new_member->id = std::to_string(panel::member_list.size());
    //this can replace by a static variable
    delete panel::member_list[index];
    panel::member_list[index] = new_member;
    // delete temp;
    std::cout<<"Change finished."<<std::endl;
}