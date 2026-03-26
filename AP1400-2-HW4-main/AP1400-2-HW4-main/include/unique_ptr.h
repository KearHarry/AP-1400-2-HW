#ifndef UNIQUE_PTR
#define UNIQUE_PTR

// 提前声明类模板
template <typename T>
class UniquePtr {
private:
    T* _p; // 核心：用来存储底层对象的指针

public:
    // 1. 默认构造函数
    UniquePtr();

    // 2. 带参构造函数 (接收一个裸指针)
    UniquePtr(T* p);

    // 3. 析构函数 (负责释放内存)
    ~UniquePtr();

    // 4. 禁用拷贝构造函数和拷贝赋值运算符 (关键要求)
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    // 5. get 方法 (返回内部底层的裸指针)
    T* get() const;

    // 6. 重载 operator*
    T& operator*() const;

    // 7. 重载 operator->
    T* operator->() const;

    // 8. reset 方法 (带参和无参)
    void reset();
    void reset(T* new_p);

    // 9. release 方法 (交出控制权但不释放)
    T* release();

    // 10. Challenge: 重载 bool 运算符
    explicit operator bool() const;
};

// make_unique 是全局函数，定义在类外
template <typename T>
UniquePtr<T> make_unique(T value);

// 重点：在文件末尾包含实现文件
#include "unique_ptr.hpp"

#endif //UNIQUE_PTR