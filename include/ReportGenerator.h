#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <vector>
#include "Person.h"

class ReportGenerator {
public:
    // 显示工资报表
    static void showSalaryReport(const std::vector<Person*>& employees);
    
    // 薪资统计分析
    static void showStatistics(const std::vector<Person*>& employees);
    
    // 导出报表到文件
    static void exportReport(const std::vector<Person*>& employees, 
                            const std::string& filename = "data/salary_report.txt");
};

#endif
