#ifndef UIHELPER_H
#define UIHELPER_H

#include <iostream>
#include <string>
// windows.h应该在main.cpp中先包含

class UIHelper {
public:
    // 颜色代码
    enum Color {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        GRAY = 7,
        DARK_GRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };

    // 设置控制台文字颜色
    static void setColor(Color textColor, Color bgColor = BLACK) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
    }

    // 重置颜色
    static void resetColor() {
        setColor(GRAY, BLACK);
    }

    // 打印彩色文本
    static void printColored(const std::string& text, Color color) {
        setColor(color);
        std::cout << text;
        resetColor();
    }

    // 打印成功消息
    static void printSuccess(const std::string& message) {
        setColor(GREEN);
        std::cout << "✓ " << message << std::endl;
        resetColor();
    }

    // 打印错误消息
    static void printError(const std::string& message) {
        setColor(RED);
        std::cout << "✗ " << message << std::endl;
        resetColor();
    }

    // 打印警告消息
    static void printWarning(const std::string& message) {
        setColor(YELLOW);
        std::cout << "⚠ " << message << std::endl;
        resetColor();
    }

    // 打印信息消息
    static void printInfo(const std::string& message) {
        setColor(CYAN);
        std::cout << "ℹ " << message << std::endl;
        resetColor();
    }

    // 打印分隔线
    static void printSeparator(char ch = '=', int length = 60) {
        setColor(DARK_CYAN);
        std::cout << std::string(length, ch) << std::endl;
        resetColor();
    }

    // 打印标题
    static void printTitle(const std::string& title) {
        printSeparator();
        setColor(CYAN);
        std::cout << "  " << title << std::endl;
        resetColor();
        printSeparator();
    }

    // 清屏
    static void clearScreen() {
        system("cls");
    }

    // 暂停
    static void pause() {
        setColor(DARK_GRAY);
        std::cout << "\n按任意键继续...";
        resetColor();
        system("pause > nul");
    }
};

#endif
