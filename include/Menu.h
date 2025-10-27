#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>

class Menu {
public:
    std::vector<Menu*> submenus;
    std::vector<std::string> function_texts;
    std::vector<std::string> menu_texts;
    std::vector<void(*)()> functions;
    Menu* parent;

    Menu(Menu* parent = nullptr) : parent(parent) {}
    
    ~Menu() {
        for (auto submenu : submenus) {
            delete submenu;
        }
    }
    
    Menu* add_function(const std::string& text, void(*function)()) {
        function_texts.push_back(text);
        functions.push_back(function);
        return this;
    }
    
    Menu* add_submenu(const std::string& text, Menu* submenu) {
        menu_texts.push_back(text);
        submenus.push_back(submenu);
        return this;
    }

    void display() {
        for (size_t i = 0; i < function_texts.size(); i++) {
            std::cout << i + 1 << ". " << function_texts[i] << std::endl;
        }
        for (size_t i = 0; i < menu_texts.size(); i++) {
            std::cout << i + 1 + function_texts.size() << ". " << menu_texts[i] << std::endl;
        }
        if (parent) {
            std::cout << function_texts.size() + menu_texts.size() + 1 << ". 返回上级菜单" << std::endl;
        }
        std::cout << function_texts.size() + menu_texts.size() + (parent ? 2 : 1) << ". 退出系统" << std::endl;
    }
    
    Menu* run(int index) {
        if (index <= function_texts.size() && index > 0) {
            functions[index - 1]();
            return this;
        } else if (index > function_texts.size() && index <= function_texts.size() + menu_texts.size()) {
            return submenus[index - function_texts.size() - 1];
        } else if (parent && index == function_texts.size() + menu_texts.size() + 1) {
            return parent;
        } else if (index == function_texts.size() + menu_texts.size() + (parent ? 2 : 1)) {
            exit(0);
        } else {
            std::cout << "无效的选项，请重新选择！" << std::endl;
            return this;
        }
    }
};

#endif
