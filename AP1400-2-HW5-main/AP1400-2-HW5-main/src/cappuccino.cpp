#include "cappuccino.h"
#include "sub_ingredients.h"

// TODO: 初始化默认成分: 2 unit Espresso, 2 unit Milk, 1 unit MilkFoam
Cappuccino::Cappuccino() {
    this->name = "Cappuccino";
    // TODO: 向 ingredients 添加 2 个单位 Espresso，2 个单位 Milk，1 个单位 MilkFoam
    // 例如: ingredients.push_back(new Espresso(2));
    //      ingredients.push_back(new Milk(2));
    //      ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

// TODO: 深拷贝（记得同时处理父类的 ingredients 和当前类的 side_items）
Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased(cap) {
    // TODO: 深拷贝 side_items，每个元素都要 clone
    // for(const auto& i : cap.side_items)
    //     side_items.push_back(i->clone());
    for(const auto& i : cap.side_items)
        side_items.push_back(i->clone());
    // std::vector<Ingredient*> is handled by base class EspressoBased
}

// TODO: 析构时清理 side_items
Cappuccino::~Cappuccino() {
    // TODO: 释放 side_items 里的每个指针，防止内存泄漏
    // for(const auto& i : side_items)
    //     delete i;
    // side_items.clear();
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

// TODO: = 运算符 (记得调父类的 operator=，并且深拷贝 side_items)
void Cappuccino::operator=(const Cappuccino& cap) {
    if (this == &cap) return;
    EspressoBased::operator=(cap);
    // TODO: 先释放旧的 side_items，再深拷贝 cap.side_items
    // for(const auto& i : side_items)
    //     delete i;
    // side_items.clear();
    // for(const auto& i : cap.side_items)
    //     side_items.push_back(i->clone());
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
    for (size_t i = 0; i < cap.side_items.size(); i++)
    {
        side_items.push_back(cap.side_items[i]->clone());
    }
    this->name = cap.name;
    
}

// TODO: 返回名字
std::string Cappuccino::get_name() {
    // TODO: 返回咖啡名称
    return this->name;
}

// TODO: price 计算 base classes 和 side_items 的总价
double Cappuccino::price() {
    double total = 0.0;
    // TODO: 遍历 ingredients 和 side_items，累加所有配料的 price()
    // for(const auto& i : ingredients)
    //     total += i->price();
    // for(const auto& i : side_items)
    //     total += i->price();
    for (size_t i = 0; i < ingredients.size(); i++)
    {
        total += ingredients[i]->price();
    }
    for (size_t i = 0; i < side_items.size(); i++)
    {
        total += side_items[i]->price();
    }
    return total;
}

// TODO: 添加配菜
void Cappuccino::add_side_item(Ingredient* side) {
    // TODO: 将 side 指针加入 side_items
    // side_items.push_back(side);
    side_items.push_back(side->clone());
}

// TODO: 获取配菜列表
std::vector<Ingredient*>& Cappuccino::get_side_items() {
    // TODO: 返回 side_items 的引用
    return side_items;
}
