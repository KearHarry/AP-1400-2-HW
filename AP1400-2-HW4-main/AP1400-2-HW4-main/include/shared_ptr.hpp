template<typename T>
SharedPtr<T>::SharedPtr() : _p(nullptr), _count(nullptr) {}

template<typename T>
SharedPtr<T>::SharedPtr(T* p) : _p(p) {
    if (p) {
        _count = new int(1); // 初始化时只有自己这一个管理者
    } else {
        _count = nullptr; // 传入的是空指针，那就什么都不用数
    }
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    // 1. 如果 _count 不是空的，就让 *_count 减去 1
    if (_count) {
        (*_count)--;
        // 2. 如果 *_count 变成了 0，就 delete _p，并 delete _count
        if (*_count == 0) {
            delete _p;
            delete _count;
        }
    }
    // 3. 把它们置空 (nullptr)
    _p = nullptr;
    _count = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) {
    // 你的代码：浅拷贝 _p 和 _count
    // 然后将 *_count 加 1 (前提是 _count 不为空)
    _p = other._p;
    _count = other._count;
    if (_count) (*_count)++;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
    // 1. 检查是不是在 "自己赋值给自己" (如 a = a;)：if (this == &other) return *this;
    if(this == &other) return *this;
    
    // 2. 让原来的引用计数缩减，若减为 0 则销毁原先管理的内存
    if (_count) {
        (*_count)--;
        if (*_count == 0) {
            delete _p;
            delete _count;
        }
    }

    // 3. 将 _p 和 _count 重新绑定到 other 上，然后增加计数。
    _p = other._p;
    _count = other._count;
    if (_count) {
        (*_count)++;
    }
    
    // 4. 返回 *this
    return *this;
}

template<typename T>
int SharedPtr<T>::use_count() const {
    // 你的代码：如果 _count 不为空，返回 *_count；否则返回 0
    if(_count) return *_count;
    else return 0;
}

template<typename T>
T* SharedPtr<T>::get() const {
    return _p;
}

template<typename T>
T& SharedPtr<T>::operator*() const {
    return *_p;
}

template<typename T>
T* SharedPtr<T>::operator->() const {
    return _p;
}

template<typename T>
void SharedPtr<T>::reset() {
    // 复用析构的衰减逻辑
    if (_count) {
        (*_count)--;
        if (*_count == 0) {
            delete _p;
            delete _count;
        }
    }
    // 最后把它们变成 nullptr 和 nullptr 即可
    _p = nullptr;
    _count = nullptr;
}

template<typename T>
void SharedPtr<T>::reset(T* p) {
    // 复用析构衰减逻辑
    if (_count) {
        (*_count)--;
        if (*_count == 0) {
            delete _p;
            delete _count;
        }
    }
    // 绑定新进来的 p，并生成新的 count
    _p = p;
    if (p) {
        _count = new int(1);
    } else {
        _count = nullptr;
    }
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return _p != nullptr;
}

template<typename T>
SharedPtr<T> make_shared(T value) {
    return SharedPtr<T>(new T(value));
}

