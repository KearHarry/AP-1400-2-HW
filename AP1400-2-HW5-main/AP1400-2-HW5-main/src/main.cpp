#include <iostream>
#include <gtest/gtest.h>
#include "ingredient.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "cappuccino.h"
#include "mocha.h"

int main(int argc, char **argv)
{
    if (1) // make false to run unit-tests
    {
        Cappuccino* cappuccino = new Cappuccino();
        cappuccino->brew();
        std::cout << cappuccino->get_name() << " costs " << cappuccino->price() << std::endl;
        delete cappuccino;
        Mocha* mocha = new Mocha();
        mocha->brew();
        std::cout << mocha->get_name() << " costs " << mocha->price() << std::endl;
        delete mocha;
        
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}