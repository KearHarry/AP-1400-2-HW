#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1 {
    // TODO: 实现梯度下降算法，支持函数指针、lambda、functor
    // initial: 初始值，step: 步长，func: 目标函数
    template<typename T, typename Func>
    T gradient_descent(T initial, T step, Func func) {
        // TODO: 实现梯度下降主逻辑
        // 提示：可以用数值微分近似梯度
        // 例如：double grad = (func(x + eps) - func(x - eps)) / (2 * eps);
        // 终止条件可以设置为梯度很小或最大迭代次数
        while (true) {
            double grad = (func(initial + step) - func(initial - step)) / (2 * step);
            initial -= step * grad;
            if (std::abs(grad) < 1e-6) {
                break;
            }
        }
        return initial; // TODO: 返回最小值点
    }

    template<typename T, typename Func>
    T gradient_descent(T initial, T step) {
        return gradient_descent(initial, step, Func{});
    }
}

#endif //Q1_H