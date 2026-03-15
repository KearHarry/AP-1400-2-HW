#include "bst.h"
#include <deque>
#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>
#include <algorithm>

/**
 * Node 类的构造函数实现
 */
BST::Node::Node(int value, BST::Node* left, BST::Node* right) : value(value), left(left), right(right) {}
BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}
BST::Node::Node(const BST::Node& node) : value(node.value), left(node.left), right(node.right) {}

/**
 * Node 与 int 的比较运算符实现
 */
bool BST::Node::operator>(int val) const { return value > val; }
bool BST::Node::operator>=(int val) const { return value >= val; }
bool BST::Node::operator<(int val) const { return value < val; }
bool BST::Node::operator<=(int val) const { return value <= val; }
bool BST::Node::operator==(int val) const { return value == val; }

/**
 * 全局运算符实现：支持 int 控制 Node 的各种不等式
 */
bool operator>(int val, const BST::Node& node) { return val > node.value; }
bool operator>=(int val, const BST::Node& node) { return val >= node.value; }
bool operator<(int val, const BST::Node& node) { return val < node.value; }
bool operator<=(int val, const BST::Node& node) { return val <= node.value; }
bool operator==(int val, const BST::Node& node) { return val == node.value; }

/**
 * Node 的输出流实现
 * 格式：[地址] => value:[值] left:[左孩子地址] right:[右孩子地址]
 */
std::ostream& operator<<(std::ostream& os, const BST::Node& node) {
    os << std::left << std::setw(16) << &node
       << " => value:" << std::setw(10) << node.value
       << " left:" << std::setw(16) << node.left
       << " right:" << std::setw(16) << node.right;
    return os;
}

/**
 * BST 类的构造函数实现
 */
BST::BST() : root(nullptr) {}

// 拷贝构造函数：通过 BFS 算法拷贝所有节点并保持结构
BST::BST(const BST& bst) : root(nullptr) {
    std::deque<Node*> q;
    if (bst.root) q.push_back(bst.root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop_front();
        add_node(node->value);
        if (node->left) q.push_back(node->left);
        if (node->right) q.push_back(node->right);
    }
}

// 移动构造函数
BST::BST(BST&& bst) noexcept : root(bst.root) {
    bst.root = nullptr;
}

// 列表构造函数
BST::BST(std::initializer_list<int> list) : root(nullptr) {
    for (int val : list) {
        add_node(val);
    }
}

/**
 * BST 的赋值运算符实现
 */
BST& BST::operator=(const BST& bst) {
    if (this == &bst) return *this;
    this->~BST(); // 清理当前内存
    root = nullptr;
    std::deque<Node*> q;
    if (bst.root) q.push_back(bst.root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop_front();
        add_node(node->value);
        if (node->left) q.push_back(node->left);
        if (node->right) q.push_back(node->right);
    }
    return *this;
}

BST& BST::operator=(BST&& bst) noexcept {
    if (this == &bst) return *this;
    this->~BST();
    root = bst.root;
    bst.root = nullptr;
    return *this;
}

/**
 * 析构函数实现：通过 BFS 遍历所有节点并逐个释放
 */
BST::~BST() {
    std::vector<Node*> nodes;
    bfs([&nodes](Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes)
        delete node;
}

/**
 * 获取根节点的引用
 */
BST::Node*& BST::get_root() {
    return root;
}

/**
 * 广度优先搜索 (BFS) 的核心实现
 * 使用队列 (queue) 逐层遍历
 */
void BST::bfs(std::function<void(Node*& node)> func) const {
    if (!root) return;
    std::deque<Node*> q;
    q.push_back(const_cast<Node*&>(root));
    while (!q.empty()) {
        Node* node = q.front();
        q.pop_front();
        func(node);
        if (node->left)
            q.push_back(node->left);
        if (node->right)
            q.push_back(node->right);
    }
}

/**
 * 计算树中节点的数量
 */
size_t BST::length() const {
    size_t count = 0;
    bfs([&count](Node*& node) { count++; });
    return count;
}

/**
 * 向 BST 中添加新节点
 * 根据 BST 性质找到合适的空位，且不允许重复值
 */
bool BST::add_node(int value) {
    Node** current = &root;
    while (*current) {
        if ((*current)->value == value) return false; // 值已存在
        if (value < (*current)->value) current = &((*current)->left);
        else current = &((*current)->right);
    }
    *current = new Node(value, nullptr, nullptr);
    return true;
}

/**
 * 在树中搜索具有特定值的节点指针的地址 (Node**)
 */
BST::Node** BST::find_node(int value) {
    Node** current = &root;
    while (*current) {
        if ((*current)->value == value) return current;
        if (value < (*current)->value) current = &((*current)->left);
        else current = &((*current)->right);
    }
    return nullptr;
}

/**
 * 在树中查找具有特定值的节点的父节点地址
 */
BST::Node** BST::find_parrent(int value) {
    if (!root || root->value == value) return nullptr;
    Node** current = &root;
    while (*current) {
        if ((*current)->left && (*current)->left->value == value) return current;
        if ((*current)->right && (*current)->right->value == value) return current;
        if (value < (*current)->value) current = &((*current)->left);
        else current = &((*current)->right);
    }
    return nullptr;
}

/**
 * 在树中寻找特定值节点的后继节点
 * 后继：比该值大的最小节点（右子树中最左侧的节点）
 */
BST::Node** BST::find_successor(int value) {
    auto target_ptr = find_node(value);
    if (!target_ptr || !*target_ptr) return nullptr;

    // Logic for Predecessor (Max of Left Subtree)
    // 根据测试用例 (TEST15, TEST29, TEST22)，这里的 "successor" 实际上是指前驱节点 (Predecessor)
    // 可能是作业要求的定义不同，或者测试用例的命名有误导性。
    if ((*target_ptr)->left) {
        auto succ_ptr = &(*target_ptr)->left;
        while ((*succ_ptr)->right)
            succ_ptr = &(*succ_ptr)->right;
        return succ_ptr;
    }

    // 如果没有左子树，前驱节点是其某个祖先
    auto current = &root;
    BST::Node** successor = nullptr;
    while (*current && ((*current)->value != value)) {
        if (value > (*current)->value) { // 向右走，说明当前节点比目标小，是潜在的前驱
            successor = current;
            current = &(*current)->right;
        } else {
            current = &(*current)->left;
        }
    }
    return successor;
}

/**
 * 删除包含特定值的节点
 * 需要处理三种情况：叶子节点、单分支节点、双分支节点
 */
bool BST::delete_node(int value) {
    Node** target_ptr = find_node(value);
    if (!target_ptr || !*target_ptr) return false;
    Node* target = *target_ptr;

    if (!target->left && !target->right) { // 1. 被删除者是叶子节点
        *target_ptr = nullptr;
        delete target;
    } else if (!target->left || !target->right) { // 2. 被删除者只有一个孩子
        Node* child = target->left ? target->left : target->right;
        *target_ptr = child;
        delete target;
    } else { // 3. 被删除者有两个孩子
        // 使用 "find_successor" (实际上是 Predecessor) 找到替代节点
        Node** succ_ptr = find_successor(value);
        Node* succ = *succ_ptr;
        target->value = succ->value; 
        
        // 前驱节点 (Predecessor) 是左子树中最大的，所以它肯定没有右孩子
        // 用它的左孩子（如果有）来替换它
        *succ_ptr = succ->left; 
        delete succ;
    }
    return true;
}

/**
 * BST 前置自增运算符：所有节点值 +1
 */
BST& BST::operator++() {
    bfs([](Node*& node) { node->value++; });
    return *this;
}

/**
 * BST 后置自增运算符
 */
BST BST::operator++(int) {
    BST old_bst = *this;
    ++(*this);
    return old_bst;
}

/**
 * BST 输出流重载：打印漂亮的二叉树概览
 */
std::ostream& operator<<(std::ostream& os, const BST& bst) {
    os << std::string(80, '*') << std::endl;
    bst.bfs([&os](BST::Node*& node) {
        os << *node << std::endl;
    });
    os << "binary search tree size: " << bst.length() << std::endl;
    os << std::string(80, '*') << std::endl;
    return os;
}
