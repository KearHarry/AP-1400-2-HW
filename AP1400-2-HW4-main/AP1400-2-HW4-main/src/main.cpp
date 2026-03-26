#include <iostream>
#include <gtest/gtest.h>
#include "unique_ptr.h"
#include "shared_ptr.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section 
        // UniquePtr<int> ptr1 = make_unique<int>(5);
        // std::cout << *ptr1 << std::endl;
        // std::cout << ptr1.get() << std::endl;
        // ptr1.reset(new int(10));
        // std::cout << *ptr1 << std::endl;
        // std::cout << ptr1.get() << std::endl;
        // // ptr1.reset();
        // if (ptr1)
        //     std::cout << "ptr1 is not empty" << std::endl;
        // else
        //     std::cout << "ptr1 is empty" << std::endl;
        // ptr1.reset(new int(15));
        // std::cout << *ptr1 << std::endl;
        // std::cout << ptr1.get() << std::endl;

        SharedPtr<int> ptr1 = make_shared<int>(5);
        std::cout << *ptr1 << std::endl;
        std::cout << ptr1.get() << std::endl;
        SharedPtr<int> ptr2 = ptr1;
        std::cout << *ptr2 << std::endl;
        std::cout << ptr2.get() << std::endl;
        std::cout << ptr1.use_count() << std::endl;
        std::cout << ptr2.use_count() << std::endl;
        ptr1.reset();
        std::cout << ptr1.use_count() << std::endl;
        std::cout << ptr2.use_count() << std::endl;
        std::cout << *ptr2 << std::endl;
        std::cout << ptr2.get() << std::endl;
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