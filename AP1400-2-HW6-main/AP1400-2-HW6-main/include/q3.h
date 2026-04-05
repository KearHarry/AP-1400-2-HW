#ifndef Q3_H
#define Q3_H

#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    // 比较器，用于priority_queue
    struct FlightCompare {
        bool operator()(const Flight& a, const Flight& b) const {
            auto score = [](const Flight& f) {
                return f.duration + f.connection_times + 3 * f.price;
            };
            return score(a) > score(b); // 小的优先
        }
    };

    // 实现读取文件并返回priority_queue
    // 注意：不允许使用for循环
    inline size_t parse_time(const std::string& time_str) {
        size_t total_minutes = 0;
        size_t h_pos = time_str.find('h');
        size_t m_pos = time_str.find('m');
        
        if (h_pos != std::string::npos) {
            total_minutes += std::stoul(time_str.substr(0, h_pos)) * 60;
        }
        if (m_pos != std::string::npos) {
            size_t start = (h_pos != std::string::npos) ? (h_pos + 1) : 0;
            total_minutes += std::stoul(time_str.substr(start, m_pos - start));
        }
        return total_minutes;
    }

    inline size_t parse_connections_time(const std::string& times_str) {
        size_t total = 0;
        size_t start = 0;
        size_t end = times_str.find(',');
        while (end != std::string::npos) {
            total += parse_time(times_str.substr(start, end - start));
            start = end + 1;
            end = times_str.find(',', start);
        }
        total += parse_time(times_str.substr(start));
        return total;
    }

    inline std::priority_queue<Flight, std::vector<Flight>, FlightCompare> gather_flights(const std::string& filename){
        std::priority_queue<Flight, std::vector<Flight>, FlightCompare> pq;
        std::ifstream file(filename);
        std::string line;
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            if (line.back() == '\r') line.pop_back();

            Flight f;
            
            // e.g. "1- flight_number:QR492 - duration:11h30m - connections:3 - connection_times:2h,1h30m,4h15m - price:250"
            size_t start = 0, end = 0;
            
            auto extract_value = [&](const std::string& key) {
                size_t pos = line.find(key + ":");
                if (pos == std::string::npos) return std::string("");
                pos += key.length() + 1;
                size_t dash_pos = line.find(" - ", pos);
                if (dash_pos == std::string::npos) {
                    return line.substr(pos);
                }
                return line.substr(pos, dash_pos - pos);
            };

            f.flight_number = extract_value("flight_number");
            f.duration = parse_time(extract_value("duration"));
            f.connections = std::stoul(extract_value("connections"));
            f.connection_times = parse_connections_time(extract_value("connection_times"));
            f.price = std::stoul(extract_value("price"));
            
            pq.push(f);
        }
        return pq;
    }
} // namespace q3

#endif //Q3_H