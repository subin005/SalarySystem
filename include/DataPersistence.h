#ifndef DATAPERSISTENCE_H
#define DATAPERSISTENCE_H

#include <vector>
#include <string>
#include "Person.h"

class DataPersistence {
public:
    // 保存数据到文件
    static void saveToFile(const std::vector<Person*>& employees, 
                          const std::string& filename = "data/employees_data.txt");
    
    // 从文件加载数据
    static void loadFromFile(std::vector<Person*>& employees, 
                            const std::string& filename = "data/employees_data.txt");
};

#endif
