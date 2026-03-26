#include "cappuccino.h"
#include "sub_ingredients.h" // 如果你想添加具体的配料进来，比如 Espresso 等，需要引入

// TODO: 初始化默认成分: 2 unit Espresso, 2 unit Milk, 1 unit MilkFoam
Cappuccino::Cappuccino() {
    this->name = "Cappuccino";
    ingredients.push_back(new Espresso(2));
    // 以及添加你的其他的配料
}

// TODO: 深拷贝（记得同时处理父类的 ingredients 和当前类的 side_items）
Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased(cap) {
    // 拷贝 side_items
    for(const auto& i : cap.side_items)
        side_items.push_back(i->clone());
    this->price_per_unit = cap.price_per_unit;
}

// TODO: 析构时清理 side_items
Cappuccino::~Cappuccino() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

// TODO: = 运算符 (记得调父类的 operator=，并且深拷贝 side_items)
void Cappuccino::operator=(const Cappuccino& cap) {
    if (this == &cap) return;
    EspressoBased::operator=(cap);
    // 清理旧的 side_items，拷贝新的
}

// TODO: 返回名字
std::string Cappuccino::get_name() {
    return this->name;
}

// TODO: price 计算 base classes 和 side_items 的总价
double Cappuccino::price() {
    double total = 0.0;
    // 遍历 ingredients 累加
    // 遍历 side_items 累加
    return total;
}

// TODO: 添加配菜
void Cappuccino::add_side_item(Ingredient* side) {
    // 压入 side_items
}

// TODO: 获取配菜列表
std::vector<Ingredient*>& Cappuccino::get_side_items() {
    return side_items;
}
