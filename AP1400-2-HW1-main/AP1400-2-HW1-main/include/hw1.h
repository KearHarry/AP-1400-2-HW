#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <cstddef>

// 定义 Matrix 类型为二维 vector
using Matrix = std::vector<std::vector<double>>;

namespace algebra {
    // 创建一个 n x m 的零矩阵
    Matrix zeros(size_t n, size_t m);
    
    // 创建一个 n x m 的全 1 矩阵
    Matrix ones(size_t n, size_t m);
    
    // 创建一个 n x m 的随机数矩阵，元素值在 [min, max) 范围内
    Matrix random(size_t n, size_t m, double min, double max);
    
    // 显示矩阵，每个元素保留 3 位小数
    void show(const Matrix& matrix);
    
    // 矩阵与标量相乘
    Matrix multiply(const Matrix& matrix, double c);
    
    // 矩阵与矩阵相乘
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);
    
    // 矩阵加上标量
    Matrix sum(const Matrix& matrix, double c);
    
    // 矩阵相加
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);
    
    // 矩阵转置
    Matrix transpose(const Matrix& matrix);
    
    // 矩阵的余子式
    Matrix minor(const Matrix& matrix, size_t r, size_t c);
    
    // 矩阵拼接
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int dim);
    
    // 初等行变换 - 交换两行
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
    
    // 初等行变换 - 某行乘以常数
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
    
    // 初等行变换 - 将一行的倍数加到另一行
    Matrix ero_sum(const Matrix& matrix, size_t r1, size_t r2, double c);
    
    // 上三角矩阵
    Matrix upper_triangular(const Matrix& matrix);
    
    // 行列式
    double determinant(const Matrix& matrix);

    // 逆矩阵
    Matrix inverse(const Matrix& matrix);
    
    // 伴随矩阵
    Matrix adjoint(const Matrix& matrix);
    
    //上三角矩阵
    Matrix upper_triangular(const Matrix& matrix);
}

#endif //AP_HW1_H
