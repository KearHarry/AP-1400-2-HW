#include "mocha.h"
#include "sub_ingredients.h" // 如果使用具体配料类的话引入

// TODO: 初始化成分: 2 unit Espresso, 2 unit Milk, 1 unit MilkFoam, 1 unit Chocolate
Mocha::Mocha() {
    this->name = "Mocha";
    // 记得往 ingredients 加入对应的 new XXX(...)
}

// TODO: 深拷贝（记得同时处理父类的 ingredients 和当前类的 side_items）
Mocha::Mocha(const Mocha& cap) : EspressoBased(cap) {
    // 还需要深拷贝 side_items
}

// TODO: 析构时清理 side_items
Mocha::~Mocha() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

// TODO: = 运算符 (记得调父类的 operator=，并且深拷贝 side_items)
void Mocha::operator=(const Mocha& cap) {
    if (this == &cap) return;
    EspressoBased::operator=(cap);
    // 清理并在新赋值时拷贝 side_items
}

// TODO: 返回名字
std::string Mocha::get_name() {
    return this->name;
}

// TODO: 计算 base classes 和 side_items 的总价之和
double Mocha::price() {
    double total = 0.0;
    // 累加 ingredients 和 side_items
    return total;
}

// TODO: 增加配菜
void Mocha::add_side_item(Ingredient* side) {
    // 压入 side_items
}

// TODO: 获得配菜引用
std::vector<Ingredient*>& Mocha::get_side_items() {
    return side_items;
}
