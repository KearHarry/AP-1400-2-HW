#ifndef Q4_H
#define Q4_H

#include <vector>
#include <numeric> 

namespace q4 {
    struct Vector2D {
        double x{};
        double y{};
    };

    struct Sensor {
        Vector2D pos;
        double accuracy;
    };

    // TODO: 实现kalman_filter，返回加权平均位置
    // 注意：不允许使用for循环
    inline Vector2D kalman_filter(const std::vector<Sensor>& sensors) {
        // 计算总权重
        double total_weight = std::accumulate(
            sensors.begin(), sensors.end(), 0.0,
            [](double sum, const Sensor& s) { return sum + s.accuracy; });

        // 计算加权和
        Vector2D weighted_sum = std::accumulate(
            sensors.begin(), sensors.end(), Vector2D{},
            [](Vector2D acc, const Sensor& s) {
                acc.x += s.pos.x * s.accuracy;
                acc.y += s.pos.y * s.accuracy;
                return acc;
            });

        // 返回加权平均
        if (total_weight == 0) return Vector2D{};
        return { weighted_sum.x / total_weight, weighted_sum.y / total_weight };
    }
}

#endif //Q4_H