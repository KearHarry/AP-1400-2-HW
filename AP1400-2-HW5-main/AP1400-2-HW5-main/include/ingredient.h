#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient
{
public:
    double get_price_unit() {
        // TODO: 返回单价 price_unit
        return price_unit;
    }
    size_t get_units() {
        // TODO: 返回数量 units
        return units;
    }
    virtual std::string get_name() = 0; // 纯虚函数

    double price() {
        // TODO: 计算并返回总价 (price_unit * units)
        return price_unit * units;
    }

protected:
    Ingredient(double price_unit, size_t units) {
        // TODO: 初始化 price_unit 和 units (成员变量)
        this->price_unit = price_unit;
        this->units = units;
    }

    double price_unit;
    size_t units;
    std::string name;
};

#endif