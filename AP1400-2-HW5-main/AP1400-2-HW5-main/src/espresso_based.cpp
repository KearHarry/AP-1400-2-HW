#include "espresso_based.h"
#include <iostream>
#include <thread>
#include <chrono>
// TODO: 初始化，无需做太多
EspressoBased::EspressoBased() {
    // 默认空，后续由子类填装内容
}

// TODO: 实现拷贝构造函数 (深拷贝)
EspressoBased::EspressoBased(const EspressoBased& esp) {
    this->name = esp.name;
    // 需要自己给 ingredients 深拷贝每个配料对象 (克隆)
    for (const auto& i : esp.ingredients) {
        this->ingredients.push_back(i);
    }
}

// TODO: 使用 vector clear 之前确保所指向的内存被清掉
EspressoBased::~EspressoBased() {
    for (const auto& i : ingredients)
        delete i;
    ingredients.clear();
    name.clear();
}

// TODO: 赋值运算符重载 (深拷贝)。需要处理自赋值，然后先清理旧的，再深拷贝新的
void EspressoBased::operator=(const EspressoBased& esp) {
    if (this == &esp) return;
    for (const auto& i : ingredients)
        delete i;
    ingredients.clear();
    
    this->name = esp.name;
    // 需要深拷贝 esp.ingredients 到 this->ingredients
    for (const auto& i : esp.ingredients) {
        this->ingredients.push_back(i);
    }
}

// TODO: 返回 ingredients，引用传递
std::vector<Ingredient*>& EspressoBased::get_ingredients() {
    return ingredients;
}

// TODO: 制作咖啡的UI过程。发挥创意！可以是控制台输出，哪怕不是UI框架仅仅用 ASCII 转圈
void EspressoBased::brew() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Starting to brew " << name << "!" << std::endl;
    std::cout << "========================================" << std::endl;

    // 为了做出动画效果，让每一项配料逐个显示
    for (const auto& i : ingredients) {
        std::cout << "=> Adding " << i->get_name() << " ... ";
        // 模拟进度条
        for (int k = 0; k < 10; ++k) {
            std::cout << ".";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 暂停 100 毫秒
        }
        std::cout << " Done!" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=> Brewing coffee ... ";
    for (int k = 0; k < 20; ++k) {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    std::cout << " Finished!" << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "  Your " << name << " is ready! Enjoy!" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
}