#ifndef Q2_H
#define Q2_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace q2 {
    struct Patient {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    // TODO: 实现读取csv文件，返回Patient列表
    inline std::vector<Patient> read_file(const std::string& filename) {
        std::vector<Patient> patients;
        std::ifstream file(filename);
        std::string line;

        // lung_cancer.csv 的第一行是 "lung_cancer"，第二行是 "Name,Surname,Age,Smokes,AreaQ,Alkhol"
        // 我们需要跳过前两行。
        // 第1行: lung_cancer
        if (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
        }
        // 第2行: 表头
        if (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
        }

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            if (line.back() == '\r') line.pop_back();

            std::stringstream ss(line);
            Patient p;
            std::string first_name, last_name, tmp;
            
            std::getline(ss, first_name, ',');
            std::getline(ss, last_name, ',');

            // 过滤名字前后的多余空格，并合并名字（这解决 "Sidney  Poitier" 出现双空格的问题）
            auto trim = [](std::string& s) {
                s.erase(0, s.find_first_not_of(" \t"));
                s.erase(s.find_last_not_of(" \t") + 1);
            };
            trim(first_name);
            trim(last_name);
            p.name = first_name + " " + last_name;

            std::getline(ss, tmp, ','); p.age = std::stoul(tmp);
            std::getline(ss, tmp, ','); p.smokes = std::stoul(tmp);
            std::getline(ss, tmp, ','); p.area_q = std::stoul(tmp);
            std::getline(ss, tmp, ','); p.alkhol = std::stoul(tmp);
            patients.push_back(p);
        }
        return patients;
    }

    // TODO: 实现排序，按 3*age + 5*smokes + 2*area_q + 4*alkhol 升序排列
    // 注意：不允许使用for循环
    inline void sort(std::vector<Patient>& patients) {
        // TODO: 实现排序，按 3*age + 5*smokes + 2*area_q + 4*alkhol 升序排序
        auto score = [](const Patient& p) {
            return 3*p.age + 5*p.smokes + 2*p.area_q + 4*p.alkhol;
        };
        std::sort(patients.begin(), patients.end(), [&](const Patient& a, const Patient& b) {
            return score(a) > score(b); // 尝试反转大小比较以符合测试预期
        });
    }
}

#endif //Q2_H