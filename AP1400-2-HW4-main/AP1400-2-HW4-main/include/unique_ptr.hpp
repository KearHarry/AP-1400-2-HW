template<typename T>
UniquePtr<T>::UniquePtr() : _p(nullptr) {}

template<typename T>
UniquePtr<T>::UniquePtr(T* p) : _p(p) {}

template<typename T>
UniquePtr<T>::~UniquePtr() {
    delete _p; // 释放内存
    _p = nullptr;
}

template<typename T>
T* UniquePtr<T>::get() const {
    return _p;
}

template<typename T>
T& UniquePtr<T>::operator*() const {
    return *_p;
}

template<typename T>
T* UniquePtr<T>::operator->() const {
    return _p;
}

template<typename T>
void UniquePtr<T>::reset() {
    delete _p; // 释放当前资源
    _p = nullptr; // 置空指针
}

template<typename T>
void UniquePtr<T>::reset(T* p) {
    delete _p; // 释放当前资源
    _p = p; // 重新赋值
}

template<typename T>
T* UniquePtr<T>::release() {
    T* p = _p; // 获取指针
    _p = nullptr; // 置空指针
    return p; // 返回指针
}

template<typename T>
UniquePtr<T>::operator bool() const {
    return _p != nullptr; // 如果指针不为空，返回 true；否则返回 false
}

template<typename T>
UniquePtr<T> make_unique(T value) {
    return UniquePtr<T>(new T(value)); // 创建一个新的 T 对象，并返回一个 UniquePtr 管理它
}
