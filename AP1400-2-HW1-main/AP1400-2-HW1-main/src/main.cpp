#include <iostream>
#include "hw1.h"
#include "gtest/gtest.h"
using namespace algebra;
int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        Matrix m = algebra::zeros(2, 2);
        algebra::show(m); 
        
        Matrix s = algebra::sum(m, 1.0);
        algebra::show(s); 
        // debug section
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