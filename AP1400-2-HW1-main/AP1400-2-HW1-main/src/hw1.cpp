#include "hw1.h"
#include <iostream>
#include <cmath>
#include <random>

namespace algebra
{
    Matrix zeros(size_t n, size_t m)
    {
        return Matrix(n, std::vector<double>(m, 0.0));
    }
    Matrix ones(size_t n, size_t m)
    {
        return Matrix(n, std::vector<double>(m, 1.0));
    }
    Matrix random(size_t n, size_t m, double min, double max)
    {
        if (min > max)
            throw std::logic_error("min cannot be greater than max");

        Matrix mat = zeros(n, m);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                mat[i][j] = min + static_cast<double>(rand()) / RAND_MAX * (max - min);
            }
        }
        return mat;
    }
    void show(const Matrix& matrix)
    {
        for (const auto& row : matrix)
        {
            for (const auto& elem : row)
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }
    Matrix multiply(const Matrix& matrix, double c)
    {
        if (matrix.empty()) return Matrix();
        Matrix result = zeros(matrix.size(), matrix[0].size());
        for (size_t i = 0; i < matrix.size(); i++)        
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
                result[i][j] = matrix[i][j] * c;
            }
        return result;
    }
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.empty()) return Matrix();
        if (matrix2.empty()) return Matrix();
        if (matrix1[0].size() != matrix2.size())
            throw std::logic_error("Incompatible dimensions for multiplication");
        
        Matrix result = zeros(matrix1.size(), matrix2[0].size());
        for (size_t i = 0; i < matrix1.size(); i++)
            for (size_t j = 0; j < matrix2[0].size(); j++)
                for (size_t k = 0; k < matrix1[0].size(); k++)
                {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
        return result;
    }
    Matrix sum(const Matrix& matrix, double c)
    {
        Matrix result = matrix;
        for(size_t i = 0; i < result.size(); i++){
            for(size_t j = 0; j < result[i].size(); j++)
            {
                result[i][j] += c;
            }
        }
        return result;
    }
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.empty() && matrix2.empty()) return Matrix();
        if (matrix1.empty() || matrix2.empty())
             throw std::logic_error("Incompatible dimensions for addition");

        if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())
            throw std::logic_error("Incompatible dimensions for addition");
        
        Matrix result = zeros(matrix1.size(), matrix1[0].size());
        for (size_t i = 0; i < matrix1.size(); i++)
            for (size_t j = 0; j < matrix1[i].size(); j++)
            {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        return result;
    }
    Matrix transpose(const Matrix& matrix){
        if (matrix.empty()) return Matrix();
        Matrix result = zeros(matrix[0].size(), matrix.size());
        for (size_t i = 0; i < matrix.size(); i++)
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
                result[j][i] = matrix[i][j];
            }
        return result;
    }
    Matrix minor(const Matrix& matrix, size_t r, size_t c){
        if (matrix.empty()) return Matrix();
        Matrix result = zeros(matrix.size() - 1, matrix[0].size() - 1);
        for (size_t i = 0; i < matrix.size(); i++)
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
                if (i != r && j != c)
                {
                    size_t row = i < r ? i : i - 1;
                    size_t col = j < c ? j : j - 1;
                    result[row][col] = matrix[i][j];
                }
            }
        return result;
    }
    double determinant(const Matrix& matrix){
        if (matrix.empty()) return 1.0;
        if (matrix.size() != matrix[0].size())
            throw std::logic_error("Determinant is only defined for square matrices");
        
        if (matrix.size() == 1)
            return matrix[0][0];
        
        double det = 0.0;
        for (size_t j = 0; j < matrix[0].size(); j++)
        {
            det += (j % 2 == 0 ? 1 : -1) * matrix[0][j] * determinant(minor(matrix, 0, j));
        }
        return det;
    }
    Matrix inverse(const Matrix& matrix){
        double det = determinant(matrix);
        if (det == 0)
            throw std::logic_error("Matrix is singular and cannot be inverted");
        
        Matrix adj = adjoint(matrix);
        return multiply(adj, 1.0 / det);
    }
    Matrix adjoint(const Matrix& matrix){
        if (matrix.empty()) return Matrix();
        Matrix result = zeros(matrix.size(), matrix[0].size());
        for (size_t i = 0; i < matrix.size(); i++)
            for (size_t j = 0; j < matrix[i].size(); j++)            {
                result[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * determinant(minor(matrix, i, j));
            }
        return result;
    }
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int dim){
        if (matrix1.empty() && matrix2.empty()) return Matrix();
        if (matrix1.empty()) return matrix2;
        if (matrix2.empty()) return matrix1;

        if (dim == 0) // vertical concatenation
        {
            if (matrix1[0].size() != matrix2[0].size())
                throw std::logic_error("Incompatible dimensions for vertical concatenation");
            
            Matrix result = zeros(matrix1.size() + matrix2.size(), matrix1[0].size());
            for (size_t i = 0; i < matrix1.size(); i++)
                result[i] = matrix1[i];
            for (size_t i = 0; i < matrix2.size(); i++)
                result[matrix1.size() + i] = matrix2[i];
            return result;
        }
        else if (dim == 1) // horizontal concatenation
        {
            if (matrix1.size() != matrix2.size())
                throw std::logic_error("Incompatible dimensions for horizontal concatenation");
            
            Matrix result = zeros(matrix1.size(), matrix1[0].size() + matrix2[0].size());
            for (size_t i = 0; i < matrix1.size(); i++)
            {
                for (size_t j = 0; j < matrix1[i].size(); j++)
                    result[i][j] = matrix1[i][j];
                for (size_t j = 0; j < matrix2[i].size(); j++)
                    result[i][matrix1[i].size() + j] = matrix2[i][j];
            }
            return result;
        }
        else
        {
            throw std::logic_error("Invalid dimension for concatenation");
        }
    }
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
        if (r1 >= matrix.size() || r2 >= matrix.size())
            throw std::logic_error("Row indices out of range");

        Matrix result = matrix;
        std::swap(result[r1], result[r2]);
        return result;
    }
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c){
        if (r >= matrix.size())
            throw std::logic_error("Row index out of range");

        Matrix result = matrix;
        for (size_t j = 0; j < result[r].size(); j++)
        {
            result[r][j] *= c;
        }
        return result;
    }
    Matrix ero_sum(const Matrix& matrix, size_t r1, size_t r2, double c){
        if (matrix.empty()) return Matrix();
        if (r1 >= matrix.size() || r2 >= matrix.size())
            throw std::logic_error("Row indices out of range");

        Matrix result = matrix;
        for (size_t j = 0; j < result[r2].size(); j++)
        {
            result[r2][j] = matrix[r2][j] + c * matrix[r1][j];
        }
        return result;
    }

    Matrix upper_triangular(const Matrix& matrix){ 
        if (matrix.empty()) return Matrix();
        if (matrix.size() != matrix[0].size())
            throw std::logic_error("non-square matrices have no upper triangular form");

        Matrix res = matrix;
        size_t n = res.size();

        for (size_t i = 0; i < n; i++) {
            // Find a row with a non-zero element in the current column
            if (res[i][i] == 0) {
                bool swapped = false;
                for (size_t k = i + 1; k < n; k++) {
                    if (res[k][i] != 0) {
                        res = ero_swap(res, i, k);
                        swapped = true;
                        break;
                    }
                }
                if (!swapped) continue; // Skip to next column if no non-zero element found
            }

            // Eliminate entries below the pivot
            for (size_t j = i + 1; j < n; j++) {
                if (res[j][i] != 0) {
                    double factor = -res[j][i] / res[i][i];
                    res = ero_sum(res, i, j, factor);
                }
            }
        }
        return res;
    }
} // namespace algebra
