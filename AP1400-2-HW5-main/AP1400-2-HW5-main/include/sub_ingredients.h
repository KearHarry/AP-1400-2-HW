#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFINE_SUB_INGREDIENT(ClassName, PricePerUnit) \
    class ClassName : public Ingredient \
    { \
    public: \
        ClassName(size_t units) : Ingredient{PricePerUnit, units} { \
            this->name = #ClassName; \
        } \
        virtual std::string get_name() override { return this->name; } \
        virtual Ingredient* clone() const override { return new ClassName(*this); } \
    };

DEFINE_SUB_INGREDIENT(Cinnamon, 5);
DEFINE_SUB_INGREDIENT(Chocolate, 5);
DEFINE_SUB_INGREDIENT(Sugar, 1);
DEFINE_SUB_INGREDIENT(Cookie, 10);
DEFINE_SUB_INGREDIENT(Espresso, 15);
DEFINE_SUB_INGREDIENT(Milk, 10);
DEFINE_SUB_INGREDIENT(MilkFoam, 5);
DEFINE_SUB_INGREDIENT(Water, 1);

#endif // SUB_INGREDIENTS_H