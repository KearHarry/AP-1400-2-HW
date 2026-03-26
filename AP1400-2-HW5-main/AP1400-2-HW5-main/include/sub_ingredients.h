#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

// TODO: 如果使用了宏，可以在此处定义宏以简化代码
#define DEFINE_SUB_INGREDIENT(ClassName, PricePerUnit) \
    class ClassName : public Ingredient \
    { \
    public: \
        ClassName(size_t units) : Ingredient{PricePerUnit, units} { \
            this->name = #ClassName; \
        } \
        virtual std::string get_name() override { return this->name; } \
    }

// TODO: 使用宏或手动定义所有的子配料类:
// Cinnamon - price per unit: 5
// Chocolate - price per unit: 5
// Sugar - price per unit: 1
// Cookie - price per unit: 10
// Espresso - price per unit: 15
// Milk - price per unit: 10
// MilkFoam - price per unit: 5
// Water - price per unit: 1

DEFINE_SUB_INGREDIENT(Cinnamon, 5);
// TODO: 添加其他配料类，可以像上面那样使用宏，或者手动实现每个类。

#endif // SUB_INGREDIENTS_H