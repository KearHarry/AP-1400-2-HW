#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <vector>
#include <initializer_list>

class BST {
public:
    // Node 结构体定义在 BST 内部，表示树中的每一个节点
    struct Node {
        // 构造函数：接受初始值、左孩子指针和右孩子指针
        Node(int value, Node* left = nullptr, Node* right = nullptr);
        // 默认构造函数
        Node();
        // 拷贝构造函数
        Node(const Node& node);

        int value;      // 节点存储的整数值
        Node* left;     // 指向左孩子的指针
        Node* right;    // 指向右孩子的指针

        // 与 int 类型进行比较的运算符重载
        bool operator>(int val) const;
        bool operator>=(int val) const;
        bool operator<(int val) const;
        bool operator<=(int val) const;
        bool operator==(int val) const;
    };

    // BST 构造函数与析构函数
    BST();                                      // 默认构造函数
    BST(const BST& bst);                        // 拷贝构造函数（深拷贝）
    BST(BST&& bst) noexcept;                   // 移动构造函数
    BST(std::initializer_list<int> list);       // 列表构造函数
    ~BST();                                     // 析构函数（释放所有节点内存）

    // 赋值运算符重载
    BST& operator=(const BST& bst);             // 拷贝赋值
    BST& operator=(BST&& bst) noexcept;        // 移动赋值

    // 核心成员函数
    Node*& get_root();                          // 返回根节点指针的引用
    void bfs(std::function<void(Node*& node)> func) const; // 广度优先搜索并应用 func
    size_t length() const;                      // 返回树中节点的总数
    bool add_node(int value);                   // 向树中添加新值（若值已存在则返回 false）
    Node** find_node(int value);                // 查找包含特定值的节点指针的地址
    Node** find_parrent(int value);             // 查找特定值节点的父节点指针的地址
    Node** find_successor(int value);           // 查找特定值节点的后继节点指针的地址
    bool delete_node(int value);                // 删除包含特定值的节点

    // BST 相关的运算符重载
    BST& operator++();    // 前置 ++：将树中所有节点的值加 1
    BST operator++(int);  // 后置 ++：将树中所有节点的值加 1，返回旧树副本

    // 好友函数：输出流重载，用于打印整棵树
    friend std::ostream& operator<<(std::ostream& os, const BST& bst);

private:
    Node* root; // 根节点指针
};

// 全局运算符重载：Node 类型的输出流显示
std::ostream& operator<<(std::ostream& os, const BST::Node& node);

// 全局运算符重载：支持 int 与 Node 的各种不等式比较
bool operator>(int val, const BST::Node& node);
bool operator>=(int val, const BST::Node& node);
bool operator<(int val, const BST::Node& node);
bool operator<=(int val, const BST::Node& node);
bool operator==(int val, const BST::Node& node);

#endif //BST_H

