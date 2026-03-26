#ifndef SHARED_PTR
#define SHARED_PTR

// 提前声明类模板
template <typename T>
class SharedPtr {
private:
    T* _p;          // 核心：用来存储底层对象的指针
    int* _count;    // 新增：引用计数器指针，记录有多少个 SharedPtr 共享这块内存

public:
    // 1. 默认构造函数
    SharedPtr();

    // 2. 带参构造函数 (接收一个裸指针)
    SharedPtr(T* p);

    // 3. 析构函数 (负责减少引用计数并可能释放内存)
    ~SharedPtr();

    // 4. 拷贝构造函数 (允许拷贝，引用计数加 1)
    SharedPtr(const SharedPtr& other);

    // 5. 拷贝赋值运算符 (同上，并处理自赋值和原对象的计数释放)
    SharedPtr& operator=(const SharedPtr& other);

    // 6. use_count 方法 (返回当前的引用计数)
    int use_count() const;

    // 7. get 方法 (返回内部底层的裸指针)
    T* get() const;

    // 8. 重载 operator*
    T& operator*() const;

    // 9. 重载 operator->
    T* operator->() const;

    // 10. reset 方法 (带参和无参)
    void reset();
    void reset(T* p);

    // 11. Challenge: 重载 bool 运算符
    explicit operator bool() const;
};

// make_shared 是全局函数，定义在类外
template <typename T>
SharedPtr<T> make_shared(T value);

// 重点：在文件末尾包含实现文件
#include "shared_ptr.hpp"

#endif //SHARED_PTR