#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cmath>

#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"

int main(int argc, char **argv)
{
    if (0) // make false to run unit-tests
    {
        // debug section
        // Q1 测试
        auto min_cos = q1::gradient_descent(0.01, 0.1, cos);
        std::cout << "Q1 min_cos: " << min_cos << std::endl;

        // Q2 测试
        auto patients = q2::read_file("resources/lung_cancer.csv");
        std::cout << "Q2 patient count: " << patients.size() << std::endl;
        if (!patients.empty()) {
            std::cout << "Q2 first patient: " << patients.front().name << std::endl;
            q2::sort(patients);
            std::cout << "Q2 sorted first: " << patients.front().name << std::endl;
        } else {
            std::cout << "Q2 patients is empty!" << std::endl;
        }

        // Q3 测试
        auto flights = q3::gather_flights("resources/flights.txt");
        if (!flights.empty())
            std::cout << "Q3 top flight: " << flights.top().flight_number << std::endl;

        // Q4 测试
        std::vector<q4::Sensor> sensors{{{0, 0.01}, 0.5}, {{0.5, 0.009}, 0.2}};
        auto kalman = q4::kalman_filter(sensors);
        std::cout << "Q4 kalman: (" << kalman.x << ", " << kalman.y << ")" << std::endl;
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